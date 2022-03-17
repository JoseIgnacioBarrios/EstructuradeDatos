/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Inform�tica
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*
  * MUY IMPORTANTE: Para realizar este ejercicio solo pod�is
  * modificar el c�digo contenido entre las etiquetas <answer>
  * y </answer>. Toda modificaci�n fuera de esas etiquetas est�
  * prohibida, pues no se tendr� en cuenta para la correcci�n.
  *
  * Tampoco esta permitido modificar las l�neas que contienen
  * las etiquetas <answer> y </answer>, obviamente :-)
  */

  //@ <answer>
  /*
    Introduce aqu� los nombres de los componentes del grupo:

    Componente 1:Jorge Valmaseda Plasencia
    Componente 2:Jose Ignacio Barrios Oros
  */
  //@ </answer>

#include <iostream>
#include <cassert>
#include <fstream>
#include <memory>
#include <utility>
#include <tuple>

template <class T> class BinTree {
public:
    BinTree() : root_node(nullptr) {}

    BinTree(const T& elem)
        : root_node(std::make_shared<TreeNode>(nullptr, elem, nullptr)) {}

    BinTree(const BinTree& left, const T& elem, const BinTree& right)
        : root_node(std::make_shared<TreeNode>(left.root_node, elem,
            right.root_node)) {}

    bool empty() const { return root_node == nullptr; }

    const T& root() const {
        assert(root_node != nullptr);
        return root_node->elem;
    }

    BinTree left() const {
        assert(root_node != nullptr);
        BinTree result;
        result.root_node = root_node->left;
        return result;
    }

    BinTree right() const {
        assert(root_node != nullptr);
        BinTree result;
        result.root_node = root_node->right;
        return result;
    }

    void display(std::ostream& out) const { display_node(root_node, out); }

private:
    // Las definiciones de TreeNode y NodePointer dependen recursivamente
    // la una de la otra. Por eso declaro 'struct TreeNode;' antes de NodePointer
    // para que el compilador sepa, cuando analice la definici�n de NodePointer,
    // que TreeNode va a ser definida m�s adelante.

    struct TreeNode;
    using NodePointer = std::shared_ptr<TreeNode>;

    struct TreeNode {
        TreeNode(const NodePointer& left, const T& elem, const NodePointer& right)
            : elem(elem), left(left), right(right) {}

        T elem;
        NodePointer left, right;
    };

    NodePointer root_node;

    static void display_node(const NodePointer& root, std::ostream& out) {
        if (root == nullptr) {
            out << ".";
        }
        else {
            out << "(";
            display_node(root->left, out);
            out << " " << root->elem << " ";
            display_node(root->right, out);
            out << ")";
        }
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const BinTree<T>& tree) {
    tree.display(out);
    return out;
}

template <typename T> BinTree<T> read_tree(std::istream& in) {
    char c;
    in >> c;
    if (c == '.') {
        return BinTree<T>();
    }
    else {
        assert(c == '(');
        BinTree<T> left = read_tree<T>(in);
        T elem;
        in >> elem;
        BinTree<T> right = read_tree<T>(in);
        in >> c;
        assert(c == ')');
        BinTree<T> result(left, elem, right);
        return result;
    }
}

using namespace std;

//@ <answer>
//---------------------------------------------------------------
// Modificar a partir de aqu�
// --------------------------------------------------------------
template <typename T>
bool recursiva(const BinTree<T>& arbol, int& actual, int& max, int& elemeto,bool res) {
    bool resc = false;
    if (arbol.empty())
    {
        resc = true;
    }
    else if (arbol.left().empty() && arbol.right().empty())
    {
        if (actual>=max)
        {
            max = actual;
            elemeto++;
            
        }
    }
    else
    {
        int actuali=actual, actuald=actual, maxi=max, maxd=max, elemetoi=0, elemetod=0;
        if (!arbol.left().empty())
        {
             actuali++;
            recursiva(arbol.left(), actuali, maxi, elemetoi,false);
        }
        if (!arbol.right().empty())
        {
             actuald++;
            recursiva(arbol.right(), actuald, maxd, elemetod,false);
        }
        if (maxi>maxd)
        {
            max = maxi;
            elemeto = elemetoi;
        }
        else
        {
            if (maxd>maxi)
            {
                max = maxd;
                elemeto = elemetod;
            }
            else
            {
                max = maxd;
                elemeto = elemetod + elemetoi;
            }
        }
        if (res)
        {
            if (maxi>maxd && elemetoi>1 || maxd>maxi && elemetod>1 || maxi==maxd && elemetod+elemetoi>1)
            {
                resc = true;
            }
            else
            {
                resc = false;
            }
        }
        else
        {
            resc = false;
        }
        

       
    }
    return resc;
}


// No olvides el coste!
// consideramos el Coste es O(n) donde n es el numero de nodos del arbol que se tiene que recorrer
template <typename T>
bool estable_altura(const BinTree<T>& arbol) {
    // Implementa aqu� la funci�n. No puedes modificar el tipo
    // de entrada ni de salida. No obstante, puedes apoyarte en
    // funciones auxiliares con el tipo que quieras.
    int actual = 1, max = 0, elemento = 0; 
    bool res = recursiva(arbol,actual,max,elemento,true);
    return res;

}

// Funci�n para tratar un caso de prueba
void tratar_caso() {
    BinTree<int> t = read_tree<int>(cin);
    cout << (estable_altura(t) ? "SI" : "NO") << "\n";
}


//---------------------------------------------------------------
// No modificar por debajo de esta l�nea
// --------------------------------------------------------------
//@ </answer>


int main() {
#ifndef DOMJUDGE
    std::ifstream in("sample.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    int num_casos;
    cin >> num_casos;

    for (int i = 0; i < num_casos; i++) {
        tratar_caso();
    }

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // Descomentar si se trabaja en Windows
    // system("PAUSE");
#endif
    return 0;
}


