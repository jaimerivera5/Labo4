#include <iostream>
#include <string>

using namespace std;

//Implementacion de la lista 

class Node 
{
    //interfaz privada
    private:
        int id;
        string name;
        string profile;

        // Tendra un nodo anterior
        Node *previous;
        // Tendra un nodo siguiente
        Node *next;

        //Como las variables son privadas debemos 
        // compartirlas con las funciones
        friend class LinkedList;
};

class LinkedList
{
    //Para los elementos de nuestra lista
    //El constructor
    public:
        // constructor
        LinkedList();
        // el destructor
        ~LinkedList();
        // Asigna memoria dinamicamente, el destructor libera memoria

        // funcion que devuelve el numero entero del primer nodo de
        // la lista HEAD
        int getFront() const;

        // funcion que nos va a devolver el numero del ultimo nodo 
        //de la lista TAIL
        int getBack() const;

        // Funcion para el nuevo nodo, que pasa el valor a la 
        //funcion
        void addFront(int dt, string nombre, string perfil);

        // Funcion para el nuevo nodo, que pasa el valor a la funcion
        void addBack(int dt, string nombre, string perfil);

        //Funcion para eliminar al primer Nodo
        void removeFront();

        //Funcion para eliminar al ultimo Nodo
        void removeBack();

        // Funcion para imprimir la informacion de forma inversa
        void printReverse();

        //Funcion para imprimir la lista del principio al final 
        // Mostrar de forma normal
        void printForward();

    private:
        //Declarar los punteros que apuntan a los nodos centinela
        Node *header;
        Node *trailer;
};

int main()
{
    //crear un objeto de la lista una instancia
    LinkedList ll;
    // AÃ±adir datos a la lista
    ll.addFront(1, "Kylian Mbappe", "trabajador");
    ll.addFront(2, "Cristiano Ronaldo", "administrador");
    ll.addFront(3, "Lionel Andres Messi", "trabajador");
    ll.addFront(4, "Rodolfo Zeladios", "cliente");
    ll.addFront(5, "Eriq Zavaleta", "cliente");
    ll.addFront(6, "Neymar Jr", "trabajador");
    ll.addFront(7, "Vinicius Jr", "administrador");
    ll.addFront(8, "Karim Benzema", "cliente");

    //  Anadir al final
    ll.addBack(9, "Mohamed Salah" , "administrador");
    ll.addBack(10, "Marito Gonzalez", "administrador");
    ll.addBack(11, "Alex Roldan", "cliente");
    ll.addBack(12, "Antoine Griezmann", "cliente");
    ll.addBack(13, "Enrico Hernandez", "trabajador");
    ll.addBack(14, "Robert Lewandowski", "trabajador");

    // Para imprimir
    cout << "Imprimir los datos:" << endl;
    ll.printForward();

    cout << "Imprimir datos alreves:" << endl;
    ll.printReverse();   

    // Eliminar HEAD
    ll.removeFront();

    // Eliminar TAIL
    ll.removeBack();

    //Obtener HEAD
    cout << "El valor de HEAD es: " << ll.getFront() << endl;

    // Obtener TAIL
    cout << "El valor de TAIL es: " << ll.getBack() << endl;

    return 0;
};

LinkedList::LinkedList(){
    // Se define dinamicamente la memoria 
    header = new Node;
    // creamos el trailer (que es el centinela final)
    trailer = new Node;
    //Tenemos que hacer que el header apunte al trailer, 
    // y el trailer al header
    header->next = trailer;
    trailer->previous = header;
    //Como la lista esta vacia se igual a NULL
    header->previous = NULL;
    trailer->next = NULL;
}

//Al final si se puede
LinkedList::~LinkedList(){
    // llama a la funcion removeFront
    //para cuando elimine el elemento de la lista que no este vacia
    //Sera cuando ambos nodos centinela se apunten, es decir no hay head ni tail
    while(header->next!=trailer){
        removeFront();
    }
    //eliminar individualmente
    delete header;
    delete trailer;
}
int LinkedList::getFront() const{
    // Devuelve el primer valor
    //acceder al header
    //accedemos a su dato
    return header->next->id;
}
int LinkedList::getBack() const{
    //Devuelve el ultimo nodo
    return trailer->previous->id;
}
void LinkedList::addFront(int dt, string nombre, string perfil){
    // anadir un nuevo nodo a la memoria que se pasa por valor
    Node *nd = new Node;
    //al nodo que tenemos le ponemos el dato
    nd->id = dt;
    nd->name = nombre;
    nd->profile = perfil;
    nd->previous = header;
    // es decir que ahora esta apuntando al nodo head
    nd->next = header->next; 

    // cambiar los punteros del header, y del nodo head
    // su puntero anterior es el nuevo nodo
    // acceder al nodo head, su puntero previous es 
    // el nuevo nodo anadido a la lista
    header->next->previous = nd;

    // el puntero head 
    header->next = nd;

}
void LinkedList::addBack(int dt, string nombre, string perfil){
    Node *nd = new Node;
    nd->id = dt;
    nd->name = nombre;
    nd->profile = perfil;
    nd->previous=trailer->previous;
    nd->next=trailer;

    //actualizar trailer
    // a traves de trailer accedemos a su nodo previo apunta al nuevo nodo
    trailer->previous->next = nd;
    trailer->previous = nd;
}
void LinkedList::removeFront(){
    // Eliminar el nodo del principio
    // Accedemos al nodo siguiente de head
    Node *nd=header->next->next;
    delete header->next;

    // actualizar los punteros del header y del nodo anterior
    header->next=nd;
    nd->previous=header;
}
void LinkedList::removeBack(){
    // Eliminar a final
    // tomar una referencia al nodo anterior al nodo tail
    Node *nd = trailer->previous->previous;

    delete trailer->previous;

    //actualizar el puntero apuntara al 
    //nodo anterior al nodo tail que se elimino
    trailer->previous=nd;
    nd->next=trailer;
}
void LinkedList::printReverse(){
    // Vamos a imprimirlos 
    // Va del final al principio
    //referencia a tail
    Node *nd=trailer->previous;

    //Si el nodo es diferente al centinela inicial
    while (nd!=header)
    {
        // se imprime el nodo
        cout <<"Id del usuario es : ";
        cout << nd->id<< endl;
        cout <<"Nombre : ";
        cout << nd->name<< endl;
        cout <<"Perfil : ";
        cout << nd->profile<< endl;
        cout << "-----------------------------" <<endl;
        //actualizar el nodo anterior
        nd=nd->previous;
    }    

}
void LinkedList::printForward(){
    // Vamos a imprimirlos 
    // Va del principio al final
    //referencia a head
    Node *nd=header->next;

    //Si el nodo es diferente al centinela final
    while (nd!=trailer)
    {
        // se imprime el nodo
        cout <<"Id del usuario es : ";
        cout << nd->id<< endl;
        cout <<"Nombre : ";
        cout << nd->name<< endl;
        cout <<"Perfil : ";
        cout << nd->profile<< endl;
        cout << "-----------------------------" <<endl;
        //actualizar el nodo al siguiente
        nd=nd->next;
    }    
}