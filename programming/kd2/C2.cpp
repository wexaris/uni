#include <iostream>
#include <initializer_list>

template<typename T>
class List {
public:
    struct Node {
        T Data;
        Node* Next = nullptr;
        Node(const T& data) : Data(data) {}
        Node(T&& data) : Data(data) {}
        ~Node() { delete Next; }
    };

    List() = default;
    List(std::initializer_list<T> init) {
        auto iter = init.begin();

        if (iter != init.end()) {
            First = new Node(*iter++);
            Node* curr = First;

            while (iter != init.end()) {
                curr->Next = new Node(*iter++);
                curr = curr->Next;
            }
        }
    }

    ~List() {
        delete First;
    }

    Node* First = nullptr;
};

// Find first Node* that has a certain value.
// Nullptr if none exists.
template<typename T>
typename List<T>::Node* find(List<T>& list, const T& item) {
    auto* curr = list.First;
    while (curr != nullptr) {
        if (curr->Data == item)
            break;
        curr = curr->Next;
    }
    return curr;
}

// Remove the last value from the list,
// if the same value was in the list previously.
template<typename T>
void deleteLastNotUnique(List<T>& list) {
    auto* prev = list.First;
    auto* curr = list.First;
    // Reach end of list
    while (curr->Next != nullptr) {
        prev = curr;
        curr = curr->Next;
    }
    // Look for repeat value
    if (find(list, curr->Data) != curr) {
        if (prev->Next)
            delete prev->Next;
        prev->Next = nullptr;
    }
}

// Print list.
// List item type must support formatting.
template<typename T>
void print(const List<T>& list) {
    auto* curr = list.First;
    while (curr != nullptr) {
        std::cout << curr->Data << ", ";
        curr = curr->Next;
    }
    std::cout << std::endl;
}

int main() {
    List<int> list{ 1, 2, 2, 3, 4, 4 };
    print(list);
    deleteLastNotUnique(list);
    print(list);

    return 0;
}