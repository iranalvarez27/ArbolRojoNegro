//Estructura del nodo base

template <typename T>
struct Node{
    //Valor del nodo
    T data;
    //Padre del nodo
    Node* parent;
    //Hijos de los nodos
    Node* left; 
    Node* right;
    //Color asignado para el nodo: rojo o negro
    bool color; //0 para negro y 1 para rojo
    int height;
    void killSelf(){
            if(left != nullptr) {
                left->killSelf();
            }
            if(right != nullptr) {
                right->killSelf();
            }
            delete this;
        }
};