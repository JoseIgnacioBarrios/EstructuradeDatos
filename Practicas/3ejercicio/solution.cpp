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
  
  Componente 1:
  Componente 2:
*/
//@ </answer>


#include <iostream>
#include <cassert>
#include <fstream>

using namespace std;

class ListLinkedDouble {
private:
  struct Node {
    int value;
    Node *next;
    Node *prev;
  };

public:
  ListLinkedDouble() : num_elems(0) {
    head = new Node;
    head->next = head;
    head->prev = head;
  }

  ListLinkedDouble(const ListLinkedDouble &other) : ListLinkedDouble() {
    copy_nodes_from(other);
    num_elems = other.num_elems;
  }

  ~ListLinkedDouble() { delete_nodes(); }

  void push_front(const int &elem) {
    Node *new_node = new Node{elem, head->next, head};
    head->next->prev = new_node;
    head->next = new_node;
    num_elems++;
  }

  void push_back(const int &elem) {
    Node *new_node = new Node{elem, head, head->prev};
    head->prev->next = new_node;
    head->prev = new_node;
    num_elems++;
  }

  void pop_front() {
    assert(num_elems > 0);
    Node *target = head->next;
    head->next = target->next;
    target->next->prev = head;
    delete target;
    num_elems--;
  }

  void pop_back() {
    assert(num_elems > 0);
    Node *target = head->prev;
    target->prev->next = head;
    head->prev = target->prev;
    delete target;
    num_elems--;
  }

  int size() const { return num_elems; }

  bool empty() const { return num_elems == 0; };

  const int &front() const {
    assert(num_elems > 0);
    return head->next->value;
  }

  int &front() {
    assert(num_elems > 0);
    return head->next->value;
  }

  const int &back() const {
    assert(num_elems > 0);
    return head->prev->value;
  }

  int &back() {
    assert(num_elems > 0);
    return head->prev->value;
  }

  const int &operator[](int index) const {
    assert(0 <= index && index < num_elems);
    Node *result_node = nth_node(index);
    return result_node->value;
  }

  int &operator[](int index) {
    assert(0 <= index && index < num_elems);
    Node *result_node = nth_node(index);
    return result_node->value;
  }

  ListLinkedDouble &operator=(const ListLinkedDouble &other) {
    if (this != &other) {
      delete_nodes();
      head = new Node;
      head->next = head->prev = head;
      copy_nodes_from(other);
      num_elems = other.num_elems;
    }
    return *this;
  }

  void display(std::ostream &out) const;

  void display() const { display(std::cout); }
  
  
  // Nuevo método
  // Se implementa más abajo
  void add_to(int index, int val);
  

private:
  Node *head;
  int num_elems;

  Node *nth_node(int n) const;
  void delete_nodes();
  void copy_nodes_from(const ListLinkedDouble &other);
  
  // Nuevos métodos
  // Se implementan más abajo
  static void attach(Node *node, Node *before);  
  static void detach(Node *node);
};

ListLinkedDouble::Node *ListLinkedDouble::nth_node(int n) const {
  int current_index = 0;
  Node *current = head->next;

  while (current_index < n && current != head) {
    current_index++;
    current = current->next;
  }

  return current;
}

void ListLinkedDouble::delete_nodes() {
  Node *current = head->next;
  while (current != head) {
    Node *target = current;
    current = current->next;
    delete target;
  }

  delete head;
}

void ListLinkedDouble::copy_nodes_from(const ListLinkedDouble &other) {
  Node *current_other = other.head->next;
  Node *last = head;

  while (current_other != other.head) {
    Node *new_node = new Node{current_other->value, head, last};
    last->next = new_node;
    last = new_node;
    current_other = current_other->next;
  }
  head->prev = last;
}

void ListLinkedDouble::display(std::ostream &out) const {
  out << "[";
  if (head->next != head) {
    out << head->next->value;
    Node *current = head->next->next;
    while (current != head) {
      out << ", " << current->value;
      current = current->next;
    }
  }
  out << "]";
}

std::ostream &operator<<(std::ostream &out, const ListLinkedDouble &l) {
  l.display(out);
  return out;
}

//@ <answer>
//---------------------------------------------------------------
// Modificar a partir de aquí
// --------------------------------------------------------------

// No olvides el coste!
//Coste: O(1) ya que solo cambiamos los punteros de cada nodo
void ListLinkedDouble::attach(Node *node, Node *before) {
  // Implementar
    before->next->prev = node; 
    node->next = before->next; 
    before->next = node; 
    node->prev = before;
}

// No olvides el coste!
//Coste: O(1) ya que solo cambiamos los punteros de cada nodo
void ListLinkedDouble::detach(Node *node) {
  // Implementar
    node->prev->next = node->next;
    node->next->prev = node->prev;
    node->prev = nullptr;
    node->next = nullptr;   
}


// Coste: O(n), donde n es el num_elems en el peor de los casos tendrá
//que recorrer hasta num_elems-2 (ya que atajamos si hay que colocar el
// elemento al final o al principio de la lista this)
/*Este metodo desacopla un nodo elegido por un index, suma un valor m y lo
añade de forma ordenada crecientemente, el index debe ser 0<=index<N.
Desacopla un nodo de la lista, guarda su valor antiguo y al volver a acoplarlo
lo compara el valor nuevo con el antiguo; si el valor antiguo es mayor que el nuevo
entonces el nodo debe estar a la izquierda de la lista de donde estaba anteriormente,
si esa nueva posicion es la posicion 0 directamente la acopla a la derecha del nodo fantasma,
si la posicion nueva está entre 0 y index-1 recorrera la lista de derecha a izquierda y lo acoplara
a la derecha del nodo previo que debe tener. En el caso de que este a la derecha es lo mismo pero
se recorre la lista de izquierda a derecha, si la nueva posicion es el final de la lista se
acopla directamente apuntando al nodo final de la lista.

Si el valor nuevo y antiguo son iguales se acoplara al prevaux que se calculo antes de buscar el nodo
a desacoplar. Y si la lista tenia solo 1 elemento pues acoplamos directamente a la derecha del nodo fantasma
*/
void ListLinkedDouble::add_to(int index, int val) {
  // Implementar
    if (!this->empty()) {
        if (index >= 0 && index <= num_elems -1) {
            Node* cur = nth_node(index); // apunto al nodo que estoy buscando
			Node* sig = cur->next;
			Node* prevaux = cur->prev;
            detach(cur);
            int x = cur->value;
            cur->value += val;
			if (head->next == head){//Si la lista solo tiene 1 elemento
				attach(cur, head);
			}else if (x > cur->value) { //0 hasta i-1
				if (head->next->value >= cur->value){
					attach(cur, head);
				}
				else{
					while (prevaux != head && cur->value < prevaux->value) {//se recorre la lista a partir de donde se extrajo el nodo hasta encontrar la nueva posicion
						prevaux = prevaux->prev;
					}
					attach(cur, prevaux);
				}
			}
			else if (x < cur->value){//i hasta num_elems-1
				if (head->prev->value <= cur->value) {//Se coloca al principio de la lista
					attach(cur, head->prev);
				}
				else{
					while (sig != head && cur->value > sig->value) {
						sig = sig->next;
					}
					attach(cur, sig->prev);
				}
			}
            else { 
				attach(cur, prevaux);
            }
        }
    }
}



bool tratar_caso() {
  // Introduce aquí el código para tratar un caso de prueba.
  // Devuelve false si se ha leído la marca de fin de entrada;
  // true en caso contrario.
    int  n, i, m;
    ListLinkedDouble l1;
    cin >> n >> i >> m;
    if (n == 0 && i == 0 && m == 0)
        return false;
    int x;
    for (int i = 0; i < n; i++) {
        cin >> x;
        l1.push_back(x);
    }
    l1.add_to(i, m);
    l1.display();
    cout << endl;
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
  
  while(tratar_caso()) { }

#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
  // Descomentar si se trabaja en Windows
   system("PAUSE");
#endif
  return 0;
}
