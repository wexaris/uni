#include <iostream>
#include <fstream>

template<typename Type>
class Tree {
    struct Node {
        Type Data;
        Node* Left;
        Node* Right;

        Node(Type data)
            : Data(data), Left(NULL), Right(NULL) {}

        // Delete this node's children
        void remove() {
            if (Left) {
                Left->remove();
                delete Left;
                Left = NULL;
            }
            if (Right) {
                Right->remove();
                delete Right;
                Right = NULL;
            }
        }

        // Add a value into this node's subtree
        void insert(Type val) {
            if (val < Data) {
                if (Left) Left->insert(val);
                else      Left = new Node(val);
            }
            else {
                if (Right) Right->insert(val);
                else       Right = new Node(val);
            }
        }

        // Traverse this node's subtree depth-first,
        // calling the given function with each node's value
        template<typename F>
        void traverse(F& fn) {
            if (Left) Left->traverse(fn);
            fn(Data);
            if (Right) Right->traverse(fn);
        }
    };

public:
    Tree() : m_Root(NULL) {}

    ~Tree() {
        if (m_Root) {
            m_Root->remove();
            delete m_Root;
            m_Root = NULL;
        }
    }

    // Insert a value into this tree
    void insert(Type val) {
        if (m_Root) m_Root->insert(val);
        else        m_Root = new Node(val);
    }

    // Traverse this tree depth-first,
    // calling the given function with each node's value
    template<typename F>
    void traverse(F& fn) {
        if (m_Root)
            m_Root->traverse(fn);
    }

private:
    Node* m_Root;
};

// Functor to be used in tree traversal
struct print {
    std::ofstream File;

    print(const char* file) : File(file) {}

    void operator()(int x) {
        File << x << '\n';
    }
};

int main() {
    Tree<int> tree;

    std::ifstream in("kartosan.dat");
    if (in.is_open()) {
        // Get workable line count from first line.
        std::string line;
        std::getline(in, line);
        int len = atoi(line.c_str());

        // Read required number of lines.
        for (int i = 0; i < len && in.good(); ++i) {
            std::getline(in, line);

            // Append values to list
            int val = atoi(line.c_str());
            tree.insert(val);
        }

        in.close();
    }

    // Write output
    print p("kartosan.rez");
    tree.traverse(p);
}
