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
  
  No te olvides del coste de las operaciones
*/
 
/*
  Introduce aquí los nombres de los componentes del grupo:
  
  Componente 1: Jorge Valmaseda Plasencia
  Componente 2: Jose Ignacio Barrios Oros
*/


// Añade los include que necesites
#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
#include <utility>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <set>

using namespace std;


class Spitter {
public:
  
  Spitter() { }
  
  //Coste: O(n log n) donde n es el numero de hashtag que tiene la publicacion
  void nueva_publicacion(int id, const string &texto, const vector<string> &hashtags) {
	  if (publicaciones.count(id)) {//O(1)
		  throw std::domain_error("Identificador duplicado");
	  }
	  recientes.push_front(texto);//O(1)
	  set<string> s;
	  for (auto it : hashtags) {
		  s.insert(it);//O(log n)
		  publicaciones[id].hashtag.insert(it);//O(log n)
		  dicHashtags[it].insert(id);//O(1)
	  }
	  publicaciones[id] = { texto, s, recientes.begin() };
  }
  
  //Coste: O(n log n) donde n es el numero de hashtag que contiene el set de cada publicacion
  void borrar_publicacion(int id) {
	  if (publicaciones.count(id)) {//O(1)
		  recientes.erase(publicaciones[id].posRecientes);//O(1)
		  auto it = publicaciones[id].hashtag.begin();
		  while (it != publicaciones[id].hashtag.end()) {//O(log n)
			  dicHashtags[*it].erase(id);//O(n)
			  it++;
		  }
		  publicaciones.erase(id);//O(1)
	  }
  }

  //Coste: O(n) donde n es el numero de publicaciones o el numero que nos pide el parametro
  vector<string> mas_recientes(int n) const {
	  vector<string> v;
	  auto it = recientes.begin();
	  if (n >= recientes.size()) {
		while (it != recientes.end()) {
		  v.push_back(*it);
		  it++;
		}
	  }
	  else if (n >= 0 && n < recientes.size()){
		  for (int i = 0; i < n; i++) {
			   v.push_back(*it);
			   it++;
		  }
	  }
	  return v;
  }  

  //Coste: O(log n) donde n es el numero de hashtag que pertenece al set de las publicaciones
  vector<string> hashtags(int id) const {
	  if (!publicaciones.count(id)) {//O(1)
		  throw std::domain_error("Publicacion no existente");
	  }
	  std::vector<string> v(publicaciones.at(id).hashtag.begin(), publicaciones.at(id).hashtag.end());
	  return v;
  }
  
  //Coste: O(log n) donde n es el numero de hashtag que contiene el set
  void anyadir_hashtag(int id, const string &hashtag) {
	  if (!publicaciones.count(id)) {//O(1)
		  throw std::domain_error("Publicacion no existente");
	  }
	  if (!publicaciones[id].hashtag.count(hashtag)) {//O(log n)
		  publicaciones[id].hashtag.insert(hashtag);//O(log n)
		  dicHashtags[hashtag].insert(id);//O(1)
	  }
  }
  
  //Coste: O(1)
  int popularidad(const string &hashtag) const {
	  int r = 0;
	  if (dicHashtags.count(hashtag)) {//O(1)
		  r = dicHashtags.at(hashtag).size();//O(1)
	  }
	  return r;
  }
  
  
private:
  // Añade aquí los atributos que conforman la representación
  // interna del TAD
  //
  // También puedes añadir métodos auxiliares privados

	struct InfoPubli{
		string texto;
		set<string> hashtag;
		list<string>::iterator posRecientes;

		InfoPubli(){}
		InfoPubli(string texto, set<string> hashtag, list<string>::iterator posRecientes) 
			: texto(texto), hashtag(hashtag), posRecientes(posRecientes) {}
	};

	unordered_map<int, InfoPubli> publicaciones;
	list<string> recientes;

	unordered_map<string, unordered_set<int>> dicHashtags;

};


// Función para tratar un caso de prueba
// Devuelve true si se ha procesado el caso de prueba
// o false si no se ha procesado porque se ha encontrado el
// fin de fichero
bool tratar_caso() {
  // Implementar.
	Spitter s;
	string c = "";
	cin >> c;
	if (cin.eof()) return false;
	while (c != "FIN") {
		try {
			int id;
			string h = "";
			if (c == "nueva_publicacion") {
				string texto = "", cadena;
				cin >> id;
				getline(cin, texto);
				getline(cin, h);
				stringstream ss(h);
				string item;
				vector<string> has;
				while (getline(ss, item, ' ') && h != "") {
					has.push_back(item);
				}
				s.nueva_publicacion(id, texto, has);
			}
			else if (c == "hashtags") {
				cin >> id;
				vector<string> has = s.hashtags(id);
				if (has.size() > 0) {
					for (int i = 0; i < has.size(); i++) {
						cout << has[i] << " ";
					}
					cout << endl;
				}
			}
			else if (c == "mas_recientes") {
				int n;
				cin >> n;
				vector<string> reciente = s.mas_recientes(n);
				cout << "Las " << reciente.size() << " publicaciones mas recientes:" << endl;
				for (int i = 0; i < reciente.size(); i++) {
					cout << "   " << reciente[i] << endl;
				}
			}
			else if (c == "anyadir_hashtag") {
				cin >> id;
				cin >> h;
				s.anyadir_hashtag(id, h);
			}
			else if (c == "popularidad") {
				cin >> h;
				cout << s.popularidad(h) << endl;
			}
			else if (c == "borrar_publicacion") {
				cin >> id;
				s.borrar_publicacion(id);
			}
		}catch (exception& e) {
			cout << "ERROR: " << e.what() << "\n";
		}
		cin >> c;
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

