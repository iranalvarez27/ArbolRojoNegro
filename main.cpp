#include <iostream>
#include "black_red_tree.h"  // Asegúrate de incluir correctamente el archivo de encabezado de tu implementación

int main() {
    // Crear un árbol Red-Black
    RedBlackTree<int> rbTree;

    // Insertar nodos
    rbTree.insert(new Node<int>(10));
    rbTree.insert(new Node<int>(5));
    rbTree.insert(new Node<int>(15));
    rbTree.insert(new Node<int>(3));
    rbTree.insert(new Node<int>(7));
    rbTree.insert(new Node<int>(12));
    rbTree.insert(new Node<int>(18));

    // Imprimir propiedades del árbol
    std::cout << "Altura del árbol: " << rbTree.getHeight() << std::endl;
    std::cout << "Tamaño del árbol: " << rbTree.getSize() << std::endl;
    std::cout << "Profundidad del árbol: " << rbTree.getDepth() << std::endl;

    // Imprimir nodos en orden
    std::cout << "Nodos en orden ascendente: ";
    // Agrega una función de impresión en orden (in-order traversal)

    // Ejemplo de eliminación de un nodo (ajusta según tus necesidades)
    Node<int>* nodeToDelete = rbTree.search(7);
    if (nodeToDelete) {
        rbTree.remove(nodeToDelete);
        std::cout << "Nodo 7 eliminado" << std::endl;
    } else {
        std::cout << "Nodo 7 no encontrado" << std::endl;
    }

    // Imprimir propiedades después de la eliminación
    std::cout << "Altura del árbol después de la eliminación: " << rbTree.getHeight() << std::endl;
    std::cout << "Tamaño del árbol después de la eliminación: " << rbTree.getSize() << std::endl;
    std::cout << "Profundidad del árbol después de la eliminación: " << rbTree.getDepth() << std::endl;

    return 0;
}
