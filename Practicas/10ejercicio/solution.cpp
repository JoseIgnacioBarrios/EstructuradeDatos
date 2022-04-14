/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

/*
  Utiliza las librerías de la STL en esta práctica.
  
  No te olvides del coste.
*/
 
/*
  Introduce aquí los nombres de los componentes del grupo:
  
  Componente 1: Jorge Valmaseda Plasencia
  Componente 2: Jose Ignacio Barrio Oros
*/



// Añade los include que necesites
#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

// Función para tratar un caso de prueba
// Devuelve true si se ha procesado el caso de prueba
// o false si no se ha procesado porque se ha encontrado la
// marca de fin de entrada
//Coste amortizado: O(n^2) suponiendo que los insert, erase y accesos
//al diccionario tienen coste O(1)
bool tratar_caso() {
  // Implementar.
	int n, c;
	cin >> n >> c;
	if (n == 0 && c == 0)	return false;
	
	unordered_map<string, unordered_set<string>> dicc;
	unordered_map<string, int> barcos;
	/*Suponiendo que estamos mirando los costes amortizados
	este bucle de lectura de entrada es cuadrático ya que
	por cada ordenada se añade los jugadores que posicionan un barco
	en esa coordenada O(n * c) ~ O(n)*/
	for (int i = 0; i < n; i++) {
		string nombre;
		cin >> nombre;
		barcos[nombre] = c;
		for (int j = 0; j < c; j++) {
			string coord;
			cin >> coord;
			dicc[coord].insert(nombre);
		}
	}

	int t;
	cin >> t;
	/*Suponiendo que estamos mirando los costes amortizados
	este bucle de salida, este bucle se realiza t veces y en cada
	coordenada se recorerra con el iterador todos los jugadores
	que esten en esa coordenadas y sean distintos del atacante.
	Por tanto el coste sera O(t*(n*c)) ~ O(n^2)*/
	for (int i = 0; i < t; i++) {
		string atacante;
		string destino;
		cin >> atacante >> destino;
		if (!dicc[destino].empty()) {
			auto it = dicc[destino].begin();
			bool ataque = false, hundido = false, vencido = false;
			while (it != dicc[destino].end()) {
				if (*it != atacante) {
					barcos[*it] -= 1;
					ataque = true;
					if (barcos[*it] > 0) {
						hundido = true;
					}
					else {
						vencido = true;
					}
					it = dicc[destino].erase(it);
				}
				else {
					it++;
				}
			}
			if (ataque && vencido) {
				cout << "VENCIDO" << endl;
			}
			else if (ataque && hundido) {
				cout << "HUNDIDO" << endl;
			}
			else {
				cout << "AGUA" << endl;
			}
		}
		else {
			cout << "AGUA" << endl;
		}

		
	}
	cout << "---" << endl;

	return true;
}


int main() {
#ifndef DOMJUDGE
  std::ifstream in("sample.in");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

  while (tratar_caso()) { }

#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
  // Descomentar si se trabaja en Windows
  // system("PAUSE");
#endif
  return 0;
}

