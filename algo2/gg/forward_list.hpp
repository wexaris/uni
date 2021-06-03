/*******************************************
Rainers Vorza, rv20039

Programma izveidota: 2021/06/01
*******************************************/

#pragma once

// Custom forward list implementation
template<typename Type>
class ForwardList {
private:
    // Base list node
    // Only points to next node, doesn't store any data.
    // Let's us have a `before_begin` iterator.
    struct NodeBase {
        NodeBase* Next = nullptr;
        NodeBase(NodeBase* next = nullptr) : Next(next) {}
        virtual ~NodeBase() = default;
    };

    // Normal list node
    // Extends base node, also stores data.
    struct Node : public NodeBase {
        Type Data;
        Node() = default;
        Node(const Type& item) : Data(item) {}
        Node(Type&& item) : Data(std::move(item)) {}
        virtual ~Node() = default;
    };

    // Non-const iterator
    template<typename IType>
    class forward_iterator {
        friend class ForwardList;
    public:
        forward_iterator(NodeBase* node = nullptr) : m_Node(node) {}

        inline IType& operator*() const  {
            if (!m_Node) throw std::out_of_range("Attempting to access an invalid iterator location!");
            return static_cast<Node*>(m_Node)->Data;
        }
        inline IType* operator->() const {
            if (!m_Node) throw std::out_of_range("Attempting to access an invalid iterator location!");
            return &static_cast<Node*>(m_Node)->Data;
        }

        inline forward_iterator& operator++() {
            if (!m_Node) throw std::out_of_range("Attempting to move past the end of the list!");
            m_Node = m_Node->Next;
            return *this;
        }

        inline forward_iterator operator++(int) {
            if (!m_Node) throw std::out_of_range("Attempting to move past the end of the list!");
            forward_iterator temp(*this);
            m_Node = m_Node->Next;
            return temp;
        }

        inline bool operator==(const forward_iterator& other) const { return m_Node == other.m_Node; }
        inline bool operator!=(const forward_iterator& other) const { return m_Node != other.m_Node; }

        inline NodeBase* node() const      { return m_Node; }
        inline NodeBase* next_node() const { return m_Node->Next; }

    private:
        NodeBase* m_Node;
    };

    // Const iterator
    template<typename IType>
    class const_forward_iterator {
        friend class ForwardList;
    public:
        const_forward_iterator(NodeBase* node = nullptr) : m_Node(node) {}
        const_forward_iterator(const forward_iterator<IType>& iter) : m_Node(iter.node()) {}

        inline const IType& operator*() const  {
            if (!m_Node) throw std::out_of_range("Attempting to access an out-of-bounds iterator location!");
            return static_cast<const Node*>(m_Node)->Data;
        }
        inline const IType* operator->() const {
            if (!m_Node) throw std::out_of_range("Attempting to access an out-of-bounds iterator location!");
            return &static_cast<const Node*>(m_Node)->Data;
        }

        inline const_forward_iterator& operator++() {
            if (!m_Node) throw std::out_of_range("Attempting to move past the end of the list!");
            m_Node = m_Node->Next;
            return *this;
        }

        inline const_forward_iterator operator++(int) {
            if (!m_Node) throw std::out_of_range("Attempting to move past the end of the list!");
            const_forward_iterator temp(*this);
            m_Node = m_Node->Next;
            return temp;
        }

        inline bool operator==(const const_forward_iterator& other) const { return m_Node == other.m_Node; }
        inline bool operator!=(const const_forward_iterator& other) const { return m_Node != other.m_Node; }

        inline NodeBase* node() const      { return m_Node; }
        inline NodeBase* next_node() const { return m_Node->Next; }

    private:
        NodeBase* m_Node;
    };

public:
    using iterator = forward_iterator<Type>;
    using const_iterator = const_forward_iterator<Type>;

    ForwardList() = default;

    ForwardList(ForwardList<Type>&& other) {
        this->swap(other);
    }

    ForwardList(const ForwardList<Type>& other) :
        m_Size(other.size())
    {
        if (size() != 0) {
            NodeBase* curr = m_Head;

            // Create and link following nodes
            for (auto iter = other.begin(); iter != other.end(); iter++) {
                curr->Next = new Node(*iter);
                curr = curr->Next;
            }
        }
    }

    ForwardList(std::initializer_list<Type> list) :
        m_Size(list.size())
    {
        if (size() != 0) {
            NodeBase* curr = m_Head;

            // Create and link following nodes
            for (auto iter = list.begin(); iter != list.end(); iter++) {
                curr->Next = new Node(*iter);
                curr = curr->Next;
            }
        }
    }

    ~ForwardList() {
        clear();
        delete m_Head;
    }

    ForwardList& operator=(ForwardList<Type>&& other) {
        this->swap(other);
        return *this;
    }

    ForwardList& operator=(const ForwardList<Type>& other) {
        ForwardList<Type> temp(other);
        this->swap(temp);
        return *this;
    }

    ForwardList& operator=(std::initializer_list<Type> list) {
        ForwardList<Type> temp(list);
        this->swap(temp);
        return *this;
    }

    iterator insert_after(const const_iterator& iter, const Type& item) {
        Node* new_node = new Node(item);
        return emplace_after(iter, new_node);
    }

    iterator insert_after(const const_iterator& iter, Type&& item) {
        Node* new_node = new Node(std::move(item));
        return emplace_after(iter, new_node);
    }

    void push_front(const Type& item) {
        Node* new_node = new Node(item);
        emplace_after(before_begin(), new_node);
    }

    void push_front(Type&& item) {
        Node* new_node = new Node(std::move(item));
        emplace_after(before_begin(), new_node);
    }

    void pop_front() {
        NodeBase* first = m_Head->Next;
        m_Head->Next = first->Next;
        delete first;
        m_Size--;
    }

    // Inserts a list node after a certain position
    iterator emplace_after(const const_iterator& iter, Node* new_node) {
        // Emplace at end
        NodeBase* curr_node = iter.node();
        NodeBase* next_node = iter.next_node();
        curr_node->Next = new_node;
        new_node->Next = next_node;

        m_Size++;
        return iterator(new_node);
    }

    // Erases list nodes in a certain range
    const_iterator erase_after(const const_iterator& start, const const_iterator& end = nullptr) {
        NodeBase* first = start.node();
        NodeBase* last = end.node();

        // Keep deleting the current node until we reach last
        NodeBase* curr = start.next_node();
        while (curr != last) {
            NodeBase* next = curr->Next;
            delete curr;
            curr = next;
            m_Size--;
        }
        // Point first to last
        first->Next = last;

        return const_iterator(end.m_Node);
    }

    // Deletes all items in the list
    // The head node isn't deleted and should be cleaned up at desctruction time.
    void clear() {
        NodeBase* curr = m_Head->Next;
        while (curr) {
            NodeBase* next = curr->Next;
            delete curr;
            curr = next;
        }
        m_Head->Next = nullptr;
        m_Size = 0;
    }

    void swap(ForwardList& other) {
        if (this != &other) {
            std::swap(m_Head, other.m_Head);
            std::swap(m_Size, other.m_Size);
        }
    }

    inline iterator before_begin()              { return iterator(m_Head); }
    inline const_iterator before_begin() const  { return const_iterator(m_Head); }
    inline const_iterator cbefore_begin() const { return const_iterator(m_Head); }

    inline iterator begin()              { return iterator(m_Head->Next); }
    inline const_iterator begin() const  { return const_iterator(m_Head->Next); }
    inline const_iterator cbegin() const { return const_iterator(m_Head->Next); }

    inline iterator end()                { return iterator(nullptr); }
    inline const_iterator end() const    { return iterator(nullptr); }
    inline const_iterator cend() const   { return const_iterator(nullptr); }

    inline Type& front()             {
        if (!m_Head->Next) throw std::out_of_range("Attempting to access an empty list's first element!");
        return static_cast<Node*>(m_Head->Next)->Data;
    }
    inline const Type& front() const {
        if (!m_Head->Next) throw std::out_of_range("Attempting to access an empty list's first element!");
        return static_cast<Node*>(m_Head->Next)->Data;
    }

    inline std::size_t size() const { return m_Size; }
    inline bool empty() const       { return m_Size == 0; }

private:
    NodeBase* m_Head = new NodeBase();
    std::size_t m_Size = 0;
};
