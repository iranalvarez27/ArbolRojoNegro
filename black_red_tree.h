#include <iostream>
#include "node.h"
using namespace std;

template <typename T>
class RedBlackTree{
    private:
        Node<T>* root;
        Node<T>* node;
        //Funcion para limpiar el arbol
        void clearTree(Node<T>* node){
            if(node != nullptr){
                //Primero se elimina los nodos de la izquierda y derecha 
                clearTree(node->right);
                clearTree(node->left);
                //Finalmente el nodo padre
                delete node;
            }
        }

    public:
        //Constructor
        RedBlackTree(){
            this->root = nullptr;
        }
        RedBlackTree(T data){
            node = new Node<T>(data);
            node->data = data;
            node->color = 0;
            node->height = 0;
            node->left = nullptr;
            node->right = nullptr;
            root = node;
        }

        //Destructor
        ~RedBlackTree(){
            clearTree(root);
        }
        
        //Metodos

        //Funcion recursiva para saber la altura de un nodo en el arbol
        int getHeight(Node<T>* node){
            if(empty()){
                return 0; //Como es un arbol vacio, su altura es 0
            }
            else{
                int leftChildHeight = getHeight(node->left);
                int rightChildHeight = getHeight(node->right);
                int maxChildHeight = max(leftChildHeight, rightChildHeight); //Complejidad O(1)
                return maxChildHeight + 1; //Le sumamos uno porque se cuenta el propio nodo
            }
        }

        int getHeight(){
            return getHeight(root);
        }

        int getSize(Node<T>* node){
            if(empty()){
                return 0;
            }
            else{
                int LeftChildSize = getSize(node->left);
                int RightCHildSize = getSize(node->right);
                int totalSize = LeftChildSize + RightCHildSize + 1; //O(1)
                return totalSize; //Tamaño total del arbol
            }
        }

        int getSize(){
            return getSize(root);
        }

        bool empty(){
            return root == nullptr;
        }

        Node<T>* getDepth(Node<T>* node){
            if(empty()){
                return -1;
            }
            else{
                int leftChildDepth = getDepth(node->left);
                int rightChildDepth = getDepth(node->right);
                int maxChildDepth = max(leftChildDepth, rightChildDepth);
                if(node->color == 0){
                    return maxChildDepth + 1; //Si el color del nodo es negro le sumo 1 a la profundidad
                }
                else{
                    return maxChildDepth; //Si es rojo, el resultado permanece igual
                }
            }
        }

        int getDepth(){
            return getDepth(root);

        }
        Node<T>* getParent(){
            return node->parent;
        }

        Node<T>* getSibblings(){
            if(node == nullptr || node->parent == nullptr){
                return make_pair(nullptr, nullptr);
            }
            else if(node == node->parent->left){
                return make_pair(node->parent->right, nullptr);
            }
            else{
                return make_pair(node->parent->left, nullptr);
            }
        }

        Node<T>* getGrandparent(Node<T>* node){
            if (node == nullptr || node->parent == nullptr)
                return nullptr;
            return node->parent->parent;
        }

        Node<T>* getUncle(Node<T>* node){
            Node<T>* grandparent = getGrandparent(node);
            if (grandparent == nullptr)
                return nullptr;
            if (node->parent == grandparent->left)
                return grandparent->right;
            else
                return grandparent->left;
        }

        void leftRotate(Node<T>* node) {
            Node<T>* rightChild = node->right;
            node->right = rightChild->left;

            if (node->parent == nullptr) {
                root = rightChild;
            } else if (node == node->parent->left) {
                node->parent->left = rightChild;
            } else {
                node->parent->right = rightChild;
            }

            rightChild->left = node;
            node->parent = rightChild;
        }

        void rightRotate(Node<T>* node) {
            Node<T>* leftChild = node->left;
            node->left = leftChild->right;

            if (node->parent == nullptr) {
                root = leftChild;
            } else if (node == node->parent->right) {
                node->parent->right = leftChild;
            } else {
                node->parent->left = leftChild;
            }

            leftChild->right = node;
            node->parent = leftChild;
        }
        

        bool getColor(){
            return node->color;
        }

        void setColor(bool color){
            node->color = color;
        }

        Node<T>* getLeftChild(){
            return node->left;
        }

        Node<T>* getRightChild(){
            return node->right;
        }

        Node<T>* getMin(Node<T>* node){
            Node<T>* temp = node;
            while(temp->left != nullptr){
                temp = temp->left;
            }
            return temp;
        }

        Node<T>* getMax(Node<T>* node){
            Node<T>* temp = node;
            while(temp->right != nullptr){
                temp = temp->right;
            }
            return temp;
        }

         Node<T>* getPredecessor(Node<T>* node){
            if(node->left != nullptr)
                return getMax(node->left);

            //Caso: si el nodo no tiene un subsarbol izquierdo, se busca el ancestro mas cercano
            Node<T>* temp = node->parent;
            while(temp != nullptr && node == temp->left){
                node = temp;
                temp = temp->parent;
            }
            return temp;
        } 

         Node<T>* getSuccessor(Node<T>* node){
            if(node->right != nullptr)
                return getMin(node->right);
            //Caso contrario, se busca el sucesor mas cercano
            Node<T>* temp = node->parent;
            while(temp != nullptr && node == temp->right){
                node = temp;
                temp = temp->parent;
            }
            return temp;
         }

        Node<T>* getRoot(){
            return root;
        }

        void setRoot(Node<T>* node){
            root = node;
        } 

        //Insertion function
        void insert(Node<T>* node){
            node->color = 1; //El nodo insertado es siempre rojo
            node->left = nullptr;
            node->right = nullptr;
            
            //Caso base: para arbol vacio el nodo se convierte en la raiz
            if(empty()){
                root = node;
                node->color = 0; //Color negro
                node->left = nullptr;
                node->right = nullptr;
            }

            while(node != root && node->parent->color == 1){
                if(node->parent == getGrandparent(node)->left){
                    Node<T>* uncle = getUncle(node);

                    if(uncle != nullptr && uncle->color == 1){
                        node->parent->color = 0;
                        uncle->color = 0;
                        getGrandparent(node)->color = 1;
                        node = getGrandparent(node);
                    } 
                    else{
                        if(node == node->parent->right){
                            node = node->parent;
                            leftRotate(node);
                        }
                        node->parent->color = 0;
                        getGrandparent(node)->color = 1;
                        rightRotate(getGrandparent(node));
                    }
                }

                else{
                    Node<T>* uncle = getUncle(node);
                    if((uncle != nullptr) && (uncle->color == 1)){
                        node->parent->color = 0;
                        uncle->color = 0;
                        getGrandparent(node)->color = 1;
                        node = getGrandparent(node);
                    } 
                    else{
                        if(node == node->parent->left){
                            node = node->parent;
                            rightRotate(node);
                        }
                    }
                    node->parent->color = 0;
                    getGrandparent(node)->color = 1;
                    leftRotate(getGrandparent(node));
                }
            }
            root->color = 0; //La raiz es siempre negra
        }

    void rotateLeft(Node<T>* node){
        Node<T>* rightChild = node->right; //Nodo apunta al hijo derecho
        node->right = rightChild->left; //Hijo derecho apunta al hijo izquierdo

        //Se verifica que el hijo izquierdo no sea nulo para asignarle el padre
        if(rightChild->left != nullptr){
            rightChild->left->parent = node; //El padre del hijo izquierdo es el nodo
        }

        rightChild->parent = node->parent; //El padre del hijo derecho es el padre del nodo
        if(node->parent == nullptr){ //Si el padre del nodo es nulo, el hijo derecho es la raiz
            root = rightChild; //La raiz es el hijo derecho ahora
        }
        else if(node == node->parent->left){ //Si el nodo es el hijo izquierdo
            node->parent->left = rightChild; //El hijo izquierdo del padre es el hijo derecho
        }
        else{
            node->parent->right = rightChild; //El hijo derecho del padre es el hijo derecho
        }

        rightChild->left = node; //El hijo izquierdo del hijo derecho es el nodo
        node->parent = rightChild; //El padre del nodo es el hijo derecho
    }

    void rotateRight(Node<T>* node){
        Node<T>* leftChild = node->left; //Nodo apunta al hijo izquierdo
        node->left = leftChild->right; //Hijo izquierdo apunta al hijo derecho
        //Se verifica que el hijo derecho no sea nulo para asignarle el padre
        if(leftChild->right != nullptr){
            leftChild->right->parent = node; //El padre del hijo derecho es el nodo
        }
        leftChild->parent = node->parent; //El padre del hijo izquierdo es el padre del nodo
        if(node->parent == nullptr){ //Si el padre del nodo es nulo, el hijo izquierdo es la raiz
            root = leftChild; //La raiz es el hijo izquierdo ahora
        }
        else if(node == node->parent->left){ //Si el nodo es el hijo izquierdo
            node->parent->left = leftChild; //El hijo izquierdo del padre es el hijo derecho
        }
        else{
            node->parent->right = leftChild; //El hijo izquierdo del padre es el hijo izquierdo
        }

        leftChild->right = node; //El hijo derecho del hijo izquierdo es el nodo
        node->parent = leftChild; //El padre del nodo es el hijo izquierdo
    }

    void delete(Node<T>* node){
        Node<T>* temp = node;
        Node<T>* temp2;
        bool tempColor = temp->color; //Color temporal del nodo

        if(node->left == nullptr){
            temp2 = node->right;
            replace(node, node->right);
        } 
        else if(node->right == nullptr){
            temp2 = node->left;
            replace(node, node->left);
        }
        else{
            temp2 = getMin(node->right);
            tempColor = temp2->color;
            temp = temp2->right;

            if(temp->parent == node){
                temp2->parent = temp;
            } else{
                replace(temp2, temp2->right);
                temp2->right = node->right;
                temp2->right->parent = temp2;
            }
            replace(node, temp2);
            temp->left = node->left;
            temp->left->parent = temp;
            temp->color = node->color;
        }
        //Verificamos si el nodo era negro, asi que mantenemos la propiedad del arbol
        if(tempColor == 0){
            delete_adjust(temp);
        }
        delete node;
    }

    void replace(Node<T>* node1, Node<T>* node2){
        if(node1->parent == nullptr){
            root = node2;
        }
        else if(node1 == node1->parent->left){
            node1->parent->left = node2;
        }
        else{
            node1->parent->right = node2;
        }
    
        if(node2 != nullptr){
            node2->parent = node1->parent;
        }
    }

    //Funcion para mantener las propiedades del RB tree luego de eliminar

    void delete_adjust(Node<T>* node){
        while(node != root && (node == nullptr || node->color != 0)){
            if(node == node->parent->left){
                Node<T>* temp = node->parent->right;

                if(temp != nullptr && temp->color == 1){
                    temp->color = 0;
                    node->parent->color = 1;
                    rotateLeft(node->parent);
                    temp = node->parent->right;
                }

                if((temp->left == nullptr || temp->left->color == 0) && (temp->right == nullptr || temp->right->color == 0)){
                    temp->color = 1;
                    node = node->parent;
                }else{
                    if(temp->right == nullptr || temp->right->color == 0){
                        if(temp->left != nullptr){
                            temp->left->color = 0;
                        }
                        temp->color = 1;
                        rotateRight(temp->parent);
                        temp = node->parent->right;
                    }
                    temp->color = node->parent->color;
                    node->parent->color = 0;
                    if(temp->right != nullptr){
                        temp->right->color = 0;
                    }
                    rotateLeft(temp->parent);
                    node = root;
                }
            }
            
        }
        if(node != nullptr){
            node->color = 0;
        }
    }

};

