#include <fstream>

constexpr const char* INPUT_FILE = "team.in";
constexpr const char* OUTPUT_FILE = "team.out";

constexpr size_t MAX_ENTRY_LENGTH = 64;

// Basic binary tree node.
// Deletes it's children when destroyed.
struct BinTreeNode {
    int Value;
    BinTreeNode* Left = nullptr;
    BinTreeNode* Right = nullptr;

    BinTreeNode(int val) : Value(val) {}
    ~BinTreeNode() { remove_children(); }

    // Returns true if this node has no children.
    inline bool is_leaf() const { return !Left && !Right; }

    // Add a child with the given value to this node.
    // Does not search for existing nodes with this value,
    // and allows values to repeat within the tree.
    // No child nodes after the first two will be added.
    BinTreeNode* add(int val) {
        if (!Left)  return Left = new BinTreeNode(val);
        if (!Right) return Right = new BinTreeNode(val);
        fprintf(stderr, "Node(%i) already has children!\n", Value);
        return nullptr;
    }

    // Finds a node with the given value in this tree.
    // If none is found, returns nullptr.
    BinTreeNode* find(int val) {
        if (Value == val)
            return this;

        BinTreeNode* ret = nullptr;
        if (Left)
            ret = Left->find(val);
        if (!ret && Right)
            ret = Right->find(val);
        return ret;
    }

    // Remove and destroy this node's children.
    // This will cascade and remove the entire tree from this point on.
    void remove_children() {
        delete Left;
        delete Right;
        Left = nullptr;
        Right = nullptr;
    }
};

// Binary tree that supports out of order construction.
// Arbitrary node relations can be constructed,
// before any subtrees are merged and a single binary tree is compiled.
//
// Merging relies on a nodes children only being defined once.
// Relies a lot on iteration, could probably use a tail pointer.
class ManagedBinTree {
    // Simple list node that owns a tree root.
    struct ListNode {
        BinTreeNode* Tree;
        ListNode* Prev = nullptr;
        ListNode* Next = nullptr;
        ListNode(BinTreeNode* data, ListNode* prev = nullptr, ListNode* next = nullptr) :
            Tree(data), Prev(prev), Next(next) {}
        ~ListNode() { delete Tree; }
    };

public:
    ManagedBinTree() = default;
    ~ManagedBinTree() { remove_trees(); }

    // Finds a node with the given value.
    // If none is found, adds it as a new subtree.
    BinTreeNode* find_or_add(int val) {
        BinTreeNode* exists = find(val);
        return exists ? exists : add_tree(new BinTreeNode(val));
    }

    // Finds a node with the given value.
    // If none is found, returns nullptr.
    BinTreeNode* find(int val) const {
        BinTreeNode* exists = nullptr;
        for (ListNode* curr = First; curr && !exists; curr = curr->Next)
            exists = curr->Tree->find(val);
        return exists;
    }

    // Returns the compiled tree.
    // If the tree is incomplete and all its subtrees can't be merged,
    // nullptr is returned.
    BinTreeNode* get() {
        // No tree
        if (!First)
            return nullptr;
        // Multiple subtrees
        if (First->Next) {
            compile();
            if (First->Next) return nullptr; // Incomplete
        }
        // Good
        return First->Tree;
    }

private:
    ListNode* First = nullptr;

    // Attempts to compile multiple subtrees into a single binary tree.
    void compile() {
        for (ListNode* curr = First; curr; curr = curr->Next)
            merge_tree(curr->Tree);
    }

    // Attempts to merge any subtrees into this node.
    // If this node is a leaf, looks for any roots with the same value,
    // merging them if they match.
    void merge_tree(BinTreeNode* tree) {
        if (!tree)
            return;

        // This works from the perspective of a leaf node that could possibly
        // be the correct position for a subtree.

        // This node would have to be a leaf, since for a subtree to form in the first place,
        // it has to be defined before its correct position.
        // This only works if every node can only define its list of children once.
        if (tree->is_leaf()) {
            ListNode* root = find_root(tree->Value);
            if (root && root->Tree != tree) {
                tree->Left = root->Tree->Left;
                tree->Right = root->Tree->Right;
                root->Tree->Left = nullptr;
                root->Tree->Right = nullptr;
                remove_tree(root);
            }
        }
        // Check the children
        else {
            merge_tree(tree->Left);
            merge_tree(tree->Right);
        }
    }

    // Finds a root node with the given value.
    // If none is found, returns nullptr.
    ListNode* find_root(int val) const {
        ListNode* exists = nullptr;
        for (ListNode* curr = First; curr && !exists; curr = curr->Next)
            if (curr->Tree->Value == val)
                exists = curr;
        return exists;
    }

    // Add a subtree.
    // Returns a pointer to the root node
    BinTreeNode* add_tree(BinTreeNode* tree) {
        ListNode* new_node = new ListNode(tree);
        if (First) {
            ListNode* last = last_tree();
            last->Next = new_node;
            new_node->Prev = last;
        }
        else {
            First = new_node;
        }
        return new_node->Tree;
    }

    // Remove and destory all of the subtrees.
    void remove_trees() {
        ListNode* curr = First;
        while (curr) {
            ListNode* next = curr->Next;
            remove_tree(curr);
            curr = next;
        }
        First = nullptr;
    }

    // Remove and destory the given subtree.
    void remove_tree(ListNode* tree) {
        if (tree) {
            // Handle this being First
            if (tree == First) First = tree->Next;
            else               tree->Prev->Next = tree->Next;
            // Remove
            delete tree;
        }
    }

    // Get the last subtree.
    // If there are none, returns nullptr.
    inline ListNode* last_tree() const {
        ListNode* curr = First;
        while (curr->Next)
            curr = curr->Next;
        return curr;
    }
};

// Character range checks
inline bool is_num(char c) { return ('0' <= c && c <= '9'); }
inline int get_num(char c) { return c - '0'; }

// Returns a parsed integer value.
// Pointer should point to the first symbol of the value.
// Pointer will be moved to the next symbol after the value.
unsigned parse_int(char*& str) {
    unsigned time = 0;
    while (is_num(*str)) {
        time *= 10;
        time += get_num(*str);
        str++;
    }
    return time;
}

// Returns the height of a tree
unsigned get_height(const BinTreeNode* root) {
    if (!root)
        return 0;

    unsigned left = get_height(root->Left);
    unsigned right = get_height(root->Right);
    unsigned max = left > right ? left : right;
    return max + 1;
}

// Prints all of the nodes at a certain level of a tree
void print_level(std::ostream& out, const BinTreeNode* root, int level) {
    if (!root)
        return;

    if (level == 1)
        out << root->Value << " ";
    else if (level > 1) {
        print_level(out, root->Left, level - 1);
        print_level(out, root->Right, level - 1);
    }
}

// Prints every node of every level of a tree in reverse (bottom to top)
void print_levels_rev(const BinTreeNode* root) {
    if (!root)
        return;

    // Open output file
    std::ofstream out(OUTPUT_FILE);
    if (!out.is_open()) {
        fprintf(stderr, "Failed to open output file!\n");
        return;
    }

    // Print every level in the tree
    unsigned h = get_height(root);
    for (unsigned i = h; i > 0; i--) {
        out << i - 1 << ": ";
        print_level(out, root, i);
        out << std::endl;
    }
}

int main() {
    ManagedBinTree tree;

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
        char* str = linebuf;

        // Parse people
        int p1 = parse_int(str);
        if (!p1) break;
        str++;
        int p2 = parse_int(str);
        str++;
        int p3 = parse_int(str);

        // Add relation to tree
        BinTreeNode* node = tree.find_or_add(p1);
        if (p2) node->add(p2);
        if (p3) node->add(p3);
    }
    in.close();

    // Print the tree's levels in reverse
    print_levels_rev(tree.get());
}
