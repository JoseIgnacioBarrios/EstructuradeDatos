/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*
  * MUY IMPORTANTE: Para realizar este ejercicio solo podéis
  * modificar el código contenido entre las etiquetas <answer>
  * y </answer>. Toda modificación fuera de esas etiquetas está
  * prohibida, pues no se tendrá en cuenta para la corrección.
  *
  * Tampoco esta permitido modificar las líneas que contienen
  * las etiquetas <answer> y </answer>, obviamente :-)
  */

  //@ <answer>
  /*
    Introduce aquí los nombres de los componentes del grupo:

    Componente 1: Jose Ignacio barrios Oros
    Componente 2: Jorge Valmaseda Plasencia
  */
  //@ </answer>

#include <iostream>
#include <cassert>
#include <fstream>
#include <cassert>

using namespace std;

// Puedes copiar aquí algunas de las implementaciones de los TADs vistos esta semana:

// Pilas: https://github.com/manuelmontenegro/ED/blob/main/lineales/stack_linkedlist/stack_linkedlist.h
// Colas: https://github.com/manuelmontenegro/ED/blob/main/lineales/queue_linkedlist/queue_linkedlist.h
// Colas dobles: https://github.com/manuelmontenegro/ED/blob/main/lineales/deque/dequeue.h

// En caso de utilizar alguno de los TADs anteriores, ha de copiarse TAL CUAL, sin realizar ningún cambio
// en sus implementaciones. Para facilitar la corrección, coloca la implementación de estos TADs fuera
// de las etiquetas <answer> y </answer>. El profesor asumirá que tienen la misma implementación que la
// vista en teoría.

// Alternativamente, puedes utilizar las clases de la librería estándar de C++ (stack<T>, queue<T> y deque<T>).


#ifndef __QUEUE_LINKEDLIST_H
#define __QUEUE_LINKEDLIST_H

#include <cassert>
#include <iostream>

template <typename T> class QueueLinkedList {
public:
    QueueLinkedList() : front_node(nullptr), back_node(nullptr) {}
    QueueLinkedList(const QueueLinkedList& other) {
        copy_nodes_from(other.front_node);
    }

    ~QueueLinkedList() { free_nodes_from(front_node); }

    QueueLinkedList& operator=(const QueueLinkedList& other) {
        if (this != &other) {
            free_nodes_from(front_node);
            copy_nodes_from(other.front_node);
        }
        return *this;
    }

    void push(const T& elem) {
        Node* new_node = new Node{ elem, nullptr };
        if (back_node == nullptr) {
            back_node = new_node;
            front_node = new_node;
        }
        else {
            back_node->next = new_node;
            back_node = new_node;
        }
    }

    void pop() {
        assert(front_node != nullptr);
        Node* target = front_node;
        front_node = front_node->next;
        if (back_node == target) {
            back_node = nullptr;
        }
        delete target;
    }

    T& front() {
        assert(front_node != nullptr);
        return front_node->value;
    }

    const T& front() const {
        assert(front_node != nullptr);
        return front_node->elem;
    }

    bool empty() const { return (front_node == nullptr); }

private:
    struct Node {
        T value;
        Node* next;
    };

    void copy_nodes_from(Node* other);
    void free_nodes_from(Node* other);

    Node* front_node;
    Node* back_node;
};

template <typename T> void QueueLinkedList<T>::copy_nodes_from(Node* other) {
    if (other == nullptr) {
        front_node = nullptr;
        back_node = nullptr;
    }
    else {
        front_node = new Node{ other->value, nullptr };
        back_node = front_node;
        Node* current = other->next;
        while (current != nullptr) {
            Node* new_node = new Node{ current->value, nullptr };
            back_node->next = new_node;
            current = current->next;
            back_node = new_node;
        }
    }
}

template <typename T> void QueueLinkedList<T>::free_nodes_from(Node* other) {
    Node* current = other;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

#endif


//@ <answer>
//---------------------------------------------------------------
// Modificar a partir de aquí
// --------------------------------------------------------------
//Coste: O(N) siendo N el tiempo total t que trascurre al usar una lista los costes de push, back y front son O(1)

bool tratar_caso() {
    // Introduce aquí el código para tratar un caso de prueba.
    // Devuelve false si ya no hay más casos de prueba que leer,
    // true en caso contrario.
    int n, m, t;
    cin >> n >> m >> t;
    //termina el programa
    if (!cin) return false;

    //cout << n<<" " << m<<" " << t << endl;

    QueueLinkedList<int> cinco;
    QueueLinkedList<int> siete;
    int cont = 1;
    for (int i = 0; i < n; i++)
    {
        if (i == n - 1)
        {
            cinco.push(1);
        }
        else
        {
            cinco.push(0);
        }
    }
    for (int i = 0; i < m; i++)
    {
        siete.push(0);
    }
    for (int i = 1; i <= t; i++)
    {
        cont += cinco.front() + siete.front();
        cinco.push(cinco.front() + siete.front());
        siete.push(cinco.front() + siete.front());

        cinco.pop();
        siete.pop();
    }
    cout << cont << endl;

    return true;
}

//---------------------------------------------------------------
// No modificar por debajo de esta línea
// --------------------------------------------------------------
//@ </answer>


int main() {
#ifndef DOMJUDGE
    std::ifstream in("sample.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (tratar_caso()) {}

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // Descomentar si se trabaja en Windows
    // system("PAUSE");
#endif
    return 0;
}