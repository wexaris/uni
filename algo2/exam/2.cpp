
struct Node {
    int info;
    Node* next;
};

Node* ChangeList(Node* listHead) {
    if (!listHead)
        return nullptr;

    Node* first = listHead;
    Node* last = listHead;

    Node* prev = listHead; // Ends up on second-to-last element
    Node* curr = listHead; // Ends up on last element
    while (curr) {
        // Remove zero value nodes
        if (curr->info == 0) {
            Node* next = curr->next;
            prev->next = next;
            delete curr;
            curr = next;
            continue;
        }
        // Save this as possibly the last node
        last = curr;

        // Break if this is the last
        if (!curr->next)
            break;

        prev = curr;
        curr = curr->next;
    }

    // Point second-to-last element to the first
    if (prev != curr)
        prev->next = first;
    // Point last to second
    last->next = first->next;
    // Point first to nothing
    first->next = nullptr;

    return last;
}

#include <iostream>

void print(Node* listHead) {
    for (Node* curr = listHead; curr; curr = curr->next)
        std::cout << curr->info << " ";
    std::cout << std::endl;
}

int main() {
    Node* n = new Node{1};
    Node* root = n;
    n = n->next = new Node{2};
    n = n->next = new Node{0};
    n = n->next = new Node{3};
    n = n->next = new Node{4};
    n = n->next = new Node{0};
    n = n->next = new Node{5};
    root = ChangeList(root);
    print(root);
}
