#include <fstream>

constexpr const char* INPUT_FILE = "exchange.in";
constexpr const char* OUTPUT_FILE = "exchange.out";

constexpr size_t MAX_ENTRY_LENGTH = 80;

// Custom remove_reference<T> implementation
template<typename T> struct remove_ref      { using type = T; };
template<typename T> struct remove_ref<T&>  { using type = T; };
template<typename T> struct remove_ref<T&&> { using type = T; };

// Custom move() implementation.
// Cuts down on extra initializations.
template<typename T>
constexpr typename remove_ref<T>::type&& move(T&& x) {
    return static_cast<typename remove_ref<T>::type&&>(x);
}

// Custom strcmp() implementation.
// None was available through only <fstream>.
inline int str_cmp(const char* s1, const char* s2) {
    while(*s1 && (*s1 == *s2))
        ++s1, ++s2;
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

// Custom memcpy() implementation.
// None was available through only <fstream>.
inline void mem_cpy(void* dest, const void* src, size_t n) {
   const char* csrc = (const char*)src;
   char* cdest = (char*)dest;
   for (size_t i = 0; i < n; i++)
       cdest[i] = csrc[i];
}

// Simple string class for char* management.
class String {
public:
    String() = default;

    // Create copy of another string.
    String(const String& other) :
        m_Length(other.m_Length),
        m_Str(new char[other.m_Length + 1])
    {
        mem_cpy(m_Str, other.m_Str, other.m_Length);
    }

    // Create from moved string.
    String(String&& other) :
        m_Length(other.m_Length),
        m_Str(other.m_Str)
    {
        other.m_Length = 0;
        other.m_Str = nullptr;
    }

    // Create from character array.
    String(const char* str, size_t len) :
        m_Length(len),
        m_Str(new char[len + 1]{})
    {
        mem_cpy(m_Str, str, len);
    }

    ~String() {
        delete[] m_Str;
    }

    // Copy data from another string
    //
    // This could probably be made more efficient by tracking and preserving
    // the string's capacity. This could get rid of many extra new/delete calls.
    inline String& operator=(const String& other) {
        if (m_Length != other.m_Length) {
            delete[] m_Str;
            m_Length = other.m_Length;
            m_Str = new char[m_Length + 1];
        }
        mem_cpy(m_Str, other.m_Str, m_Length);
        return *this;
    }

    // Take ownership of moved string
    inline String& operator=(String&& other) {
        if (this != &other) {
            delete[] m_Str;
            m_Length = other.m_Length;
            m_Str = other.m_Str;
            other.m_Str = nullptr;
        }
        return *this;
    }

    inline bool operator==(const String& other) const {
        return m_Length == other.m_Length && str_cmp(m_Str, other.m_Str) == 0;
    }
    inline bool operator!=(const String& other) const {
        return m_Length != other.m_Length || str_cmp(m_Str, other.m_Str) != 0;
    }

    friend std::ostream& operator<<(std::ostream& out, const String& str) {
        return out << str.m_Str;
    }

private:
    size_t m_Length = 0;
    char* m_Str = nullptr;
};

// A single ask or bid.
struct Entry {
    size_t Time;
    char Action; // 'A' for ask, 'B' for bid
    String PersonID;
    String ProductName;
};

std::ostream& operator<<(std::ostream& out, const Entry& entry) {
    return out <<
        entry.Time << " " <<
        entry.Action << " " <<
        entry.PersonID << " " <<
        entry.ProductName;
}

// Simple doubly-linked list of Entries.
// Provides access to the first and last items in the list.
//
// Moving though the nodes can be done with next() and prev().
// It's a bit clunky, and, personally, I would have liked to add an iterator,
// but I think it gets the job done, and I couldn't be bothered.
class EntryList {
    // Base node structure.
    // Links to surrounding nodes. Holds no data.
    //
    // Data is protected to not allow a user to manually change the list's linkage.
    // Though, technically, one could still pass a node to an unrelated list
    // and mess it up.
    struct NodeBase {
        friend class EntryList;
    protected:
        NodeBase* Prev = nullptr;
        NodeBase* Next = nullptr;
        NodeBase(NodeBase* prev, NodeBase* next) : Prev(prev), Next(next) {}
    };

    // Main node structure.
    // Extends BaseNode. Holds data.
    struct Node : public NodeBase {
        Entry Data;
        Node(Entry&& entry, NodeBase* prev, NodeBase* next) :
            NodeBase(prev, next), Data(move(entry)) {}
        inline Node* prev() { return (Node*)Prev; }
        inline Node* next() { return (Node*)Next; }
        inline const Node* prev() const { return (Node*)Prev; }
        inline const Node* next() const { return (Node*)Next; }
    };

public:
    EntryList() {
        m_Head->Next = m_Tail;
        m_Tail->Prev = m_Head;
    }
    ~EntryList() {
        clear();
        delete m_Head;
        delete m_Tail;
    }

    inline Node* first() { return (Node*)m_Head->Next; }
    inline Node* last() { return (Node*)m_Tail->Prev; }
    inline const Node* first() const { return (Node*)m_Head->Next; }
    inline const Node* last() const { return (Node*)m_Tail->Prev; }

    inline size_t size() const { return m_Size; }

    // Add a new element after some other one
    inline Node* insert_after(Entry&& e, Node* node) {
        Node* new_node = new Node{move(e), node, node->next()};
        new_node->prev()->Next = new_node;
        new_node->next()->Prev = new_node;
        m_Size++;
        return new_node;
    }

    // Add a new element to the end of the list.
    inline Node* push(Entry&& e) {
        return insert_after(move(e), last());
    }

    // Deletes all items in the list
    // The head and tail nodes aren't deleted and should be cleaned up at desctruction.
    void clear() {
        NodeBase* curr = first();
        while (curr != m_Tail) {
            // Manually delete them all
            // remove() would waste time relinking the list
            NodeBase* next = curr->Next;
            delete curr;
            curr = next;
        }
        m_Head->Next = m_Tail;
        m_Tail->Prev = m_Head;
        m_Size = 0;
    }

    // Remove a node from the list.
    // Moves the pointer to the previous node.
    // If the removed node is the first element, accessing its data is
    // undefined behaviour. (Since the previous node is only a NodeBase)
    // Moving to the next node is still valid.
    inline void remove(Node*& node) {
        NodeBase* prev = node->Prev;
        NodeBase* next = node->Next;
        prev->Next = next;
        next->Prev = prev;
        delete node;
        node = (Node*)prev;
        m_Size--;
    }

private:
    NodeBase* m_Head = new NodeBase(nullptr, nullptr); // Head before first element
    NodeBase* m_Tail = new NodeBase(nullptr, nullptr); // Tail after last element
    size_t m_Size = 0;
};

// Character range checks
inline bool is_ws(char c)    { return c == ' ' || c == '\r' || c == '\n' || c == '\t'; }
inline bool is_alpha(char c) { return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'); }
inline bool is_num(char c)   { return ('0' <= c && c <= '9'); }
inline bool is_alnum(char c) { return is_alpha(c) || is_num(c); }
inline int get_num(char c)   { return c - '0'; }

// Returns a parsed time instant.
// Pointer should point to the first symbol of the value.
// Pointer will be moved to the next symbol after the vale.
inline size_t parse_time(char*& str) {
    size_t time = 0;
    while (is_num(*str)) {
        time *= 10;
        time += get_num(*str);
        str++;
    }
    return time;
}

// Returns a pointer to the start of a personal ID.
// Pointer should point to the first symbol of the ID.
// Pointer will be moved to the next symbol after the ID.
inline String parse_id(char*& str) {
    String id(str, 11); // ID is guaranteed to be 11
    str += 11;
    return id;
}

// Returns a parsed product name.
// Pointer should point to the first symbol of the name.
// Pointer will be moved to the next symbol after the name.
inline String parse_product(char*& str) {
    char* start = str;
    size_t len = 0;
    while (is_alnum(*str)) {
        len++;
        str++;
    }
    return String(start, len);
}

// Returns a parsed Entry.
// Pointer should point to the first symbol of the entry.
inline Entry parse_entry(char* str) {
    size_t time = parse_time(str);
    str++;
    char action = *str++;
    str++;
    String id = parse_id(str);
    str++;
    String product = parse_product(str);
    return Entry{time, action, move(id), move(product)};
}

// Returns true if two entries match.
// One would be an ask, the other a bid, and the product names would match.
inline bool match(const Entry& e1, const Entry& e2) {
    return e1.Action != e2.Action && e1.ProductName == e2.ProductName;
}

// Update input file to only contain the unmatched entries.
void update_input_file(const EntryList& list1, const EntryList& list2) {
    // Open and clear the input file
    std::ofstream file(INPUT_FILE);
    if (!file.is_open()) {
        fprintf(stderr, "Failed to open input file!\n");
        return;
    }

    auto* e1 = list1.first();
    auto* e2 = list2.first();

    // Print list1 items
    while (e1 != list1.last()->next()) {
        // List2 has entries
        if (e2 != list2.last()->next()) {
            // Print the first chronological entry
            if (e1->Data.Time <= e2->Data.Time) {
                file << e1->Data << std::endl; // list1 item
                e1 = e1->next();
            }
            else {
                file << e2->Data << std::endl; // list2 item
                e2 = e2->next();
            }
        }
        // List2 is empty
        else {
            file << e1->Data << std::endl;
            e1 = e1->next();
        }
    }
    // Print list2 items
    while (e2 != list2.last()->next()) {
        file << e2->Data << std::endl;
        e2 = e2->next();
    }
}

int main() {
    EntryList asks;
    EntryList bids;

    // Open input file
    std::ifstream in(INPUT_FILE);
    if (!in.is_open()) {
        fprintf(stderr, "Failed to open input file!\n");
        return -1;
    }

    // Read input line by line
    char linebuf[MAX_ENTRY_LENGTH + 1];
    while (in.good()) {
        in.getline(linebuf, MAX_ENTRY_LENGTH);

        // Parse current entry
        Entry entry = parse_entry(linebuf);
        // Add entry to asks or bids
        entry.Action == 'A' ?
            asks.push(move(entry)) :
            bids.push(move(entry));
    }
    in.close();

    // Open output file
    std::ofstream out(OUTPUT_FILE);
    if (!out.is_open()) {
        fprintf(stderr, "Failed to open output file!\n");
        return -1;
    }

    // Keep starting size of ask list
    // Used to check if any matches were found
    size_t ask_count = asks.size();

    // Loop over all the asks
    for (auto* ask = asks.first(); ask != asks.last()->next(); ask = ask->next()) {
        Entry& entry_a = ask->Data;

        // Loop over all the bids
        for (auto* bid = bids.first(); bid != bids.last()->next(); bid = bid->next()) {
            Entry& entry_b = bid->Data;

            // Look for matches
            if (match(entry_a, entry_b)) {
                // Print matching entries
                size_t time = entry_a.Time > entry_b.Time ? entry_a.Time : entry_b.Time;
                out << time << " " << entry_a.PersonID << " " << entry_b.PersonID << std::endl;

                // Remove entries from lists
                asks.remove(ask);
                bids.remove(bid);

                // Update contents of the input file
                update_input_file(asks, bids);

                // Stop checking, go to next ask
                goto next_ask;
            }
        }
        next_ask:;
    }
    // Print '0' if no matches were found
    if (ask_count == asks.size()) {
        out << "0" << std::endl;
    }
    out.close();
}
