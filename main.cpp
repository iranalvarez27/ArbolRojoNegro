#include <iostream>
#include "black_red_tree.h"
using namespace std;

int main() {
    RedBlackTree<int> tree(5); // Create a RedBlackTree with root value 5

    Node<int>* node1 = new Node<int>();
    node1->data = 3;
    tree.insert(node1);

    Node<int>* node2 = new Node<int>();
    node2->data = 7;
    tree.insert(node2);

    Node<int>* node3 = new Node<int>();
    node3->data = 1;
    tree.insert(node3);
    cout<<tree.empty();

    return 0;
}