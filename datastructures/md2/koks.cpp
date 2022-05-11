#include <iostream>
#include <fstream>
#include <stdexcept>

const char* INPUT_FILE = "koks.dat";
const char* OUTPUT_FILE = "koks.rez";

template<typename T>
class Vec {
public:
    Vec() : m_Array(NULL), m_Length(0), m_Capacity(0) {}

    Vec(size_t size) : m_Array(NULL), m_Length(0), m_Capacity(0) {
        reserve(size);
    }

    Vec(size_t size, const T& init) : m_Array(NULL), m_Length(0), m_Capacity(0) {
        reserve(size);
        for (size_t i = 0; i < size; i++) {
            push(init);
        }
    }

    ~Vec() {
        clear();
    }

    void clear() {
        delete[] m_Array;
        m_Length = 0;
        m_Capacity = 0;
    }

    void push(const T& item) {
        if (m_Length + 1 > m_Capacity) {
            reserve((m_Length + 1));
        }

        m_Array[m_Length++] = item;
    }

    // Resize the vector.
    // Trucate if it's larger than the given size.
    // Reserve if it's smaller than the given size.
    void resize(size_t size) {
        if (size == 0)                  // Clear
            clear();
        else if (size > m_Capacity)     // Extend
            reserve(size - m_Capacity);
        else if (size < m_Capacity) {   // Truncate
            T* new_array = new T[size];
            for (size_t i = 0; i < size; i++)
                new_array[i] = m_Array[i];

            delete[] m_Array;
            m_Array = new_array;
            m_Length = size;
            m_Capacity = size;
        }
    }

    // Extend the capacity of the vector by a certain amount.
    void reserve(size_t count) {
        if (count == 0)
            return;

        T* new_array = new T[m_Capacity + count];
        for (size_t i = 0; i < m_Length; i++)
            new_array[i] = m_Array[i];

        delete[] m_Array;
        m_Array = new_array;
        m_Capacity += count;
    }

    bool is_empty() const { return m_Length == 0; }

    size_t len() const { return m_Length; }
    size_t capacity() const { return m_Capacity; }

    T& operator[](size_t pos) { return m_Array[pos]; }
    const T& operator[](size_t pos) const { return m_Array[pos]; }

private:
    T* m_Array;
    size_t m_Length;
    size_t m_Capacity;
};

class Tree {
public:
    Tree(size_t node_count) :
        m_Nodes(node_count, Node()),
        m_NodeParents(node_count, 0) {}

    void add_edge(size_t from, size_t to) {
        if (from > m_Nodes.len() || to > m_Nodes.len())
            return;

        m_Nodes[from - 1].Children.push(&m_Nodes[to - 1]);
        m_NodeParents[to - 1]++;
    }

    size_t root() {
        int root = 0;
        for (size_t i = 0; i < m_Nodes.len(); i++) {
            if (m_NodeParents[i] > 1)
                return 0;

            if (m_NodeParents[i] == 0) {
                if (root != 0)
                    return 0;
                root = i + 1;
            }
        }
        return root;
    }

    int height(size_t root) {
        return root ? traverse(&m_Nodes[root - 1]) : 0;
    }

private:
    struct Node {
        Vec<Node*> Children;
    };

    Vec<Node> m_Nodes;
    Vec<size_t> m_NodeParents;

    static size_t traverse(Node* node) {
        if (node->Children.is_empty())
            return 0;

        size_t height = 0;
        for (size_t i = 0; i < node->Children.len(); i++) {
            size_t h = traverse(node->Children[i]);
            if (h > height)
                height = h;
        }
        return height + 1;
    }
};

int main() {
    size_t root = 0;
    size_t height = 0;

    std::ifstream in(INPUT_FILE);
    if (in.is_open()) {
        int node_count, edge_count;
        in >> node_count >> edge_count;

        Tree tree(node_count);

        int egde_from, edge_to;
        while (in.good() && edge_count--) {
            in >> egde_from >> edge_to;
            tree.add_edge(egde_from, edge_to);
        }

        in.close();

        root = tree.root();
        height = tree.height(root);
    }

    std::ofstream out(OUTPUT_FILE);
    if (out.is_open()) {
        out << root << " " << height << std::endl;
        out.close();
    }
}
