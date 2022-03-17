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
  
  Componente 1: Jorge Valmaseda Plasencia
  Componente 2:	Jose Ignacio Barrios Oros
*/
//@ </answer>

#include <iostream>
#include <cassert>
#include <fstream>
#include <cassert>
#include <list>
#include <string>

using namespace std;


enum class Categoria { Primero, Segundo, Postre };

struct Plato {
  Categoria categoria;
  string nombre;
};

// Sobrecarga del operador << para imprimir platos
ostream &operator<<(ostream &out, const Plato &plato) {
  switch (plato.categoria) {
    case Categoria::Primero:
      out << "1";
      break;
    case Categoria::Segundo:
      out << "2";
      break;
    case Categoria::Postre:
      out << "P";
      break;
  }
  out << " " << plato.nombre;
  return out;
}

//@ <answer>
//---------------------------------------------------------------
// Modificar a partir de aquí
// --------------------------------------------------------------
// Indica el coste en función del tamaño del parámetro de entrada
//Coste: O(N) donde N es la longitud de la lista de platos
void ordenar_menu(list<Plato> &platos) {
    auto it1 = platos.begin();
    auto it2 = platos.begin();
    int contPlatos = 0;
    while (it2 != platos.end() && contPlatos < platos.size()) {
        if (it2->categoria != Categoria::Segundo) {
            if (it2->categoria == Categoria::Primero) {
                platos.insert(it1, *it2);
            }
            else {
                platos.insert(platos.end(), *it2);
            }
			if (it1->categoria != Categoria::Segundo){
				it1++;
			}
			it2 = platos.erase(it2);
        }
        else {
			it2++;
        }
		contPlatos++;
    }
}


bool tratar_caso() {
  // Introduce aquí el código para tratar un caso de prueba.
  // Devuelve false si ya no hay más casos de prueba que leer,
  // true en caso contrario.

    int n;
    char cat = ' ';
    cin >> n;
    if (n == 0)
        return false;
    Plato p;
    list<Plato> platos;
    for (int i = 0; i < n; i++) {
        cin >> cat;
        if (cat == '1') {
            p.categoria = Categoria::Primero;
        }
        else if (cat == '2') {
            p.categoria = Categoria::Segundo;
        }
        else if (cat == 'P') {
            p.categoria = Categoria::Postre;
        }

        getline(cin, p.nombre);
        platos.push_back(p);
    }
    ordenar_menu(platos);
    for (auto& it : platos) {
        cout << it << endl;
    }
    cout << "---" << endl;

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
  
  while (tratar_caso()) {  }

#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
  // Descomentar si se trabaja en Windows
  system("PAUSE");
#endif
  return 0;
}

