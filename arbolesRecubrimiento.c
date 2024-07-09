#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

// Estructura de datos para almacenar un borde del grafo
struct Borde {
    int inicio, destino, peso;
};

// Objeto de comparación que se usará para ordenar los bordes
struct comparar {
    // Función de comparación para ordenar los bordes por peso en orden no decreciente
    bool operator()(Borde const &a, Borde const &b) const {
        return a.peso > b.peso;
    }
};

// Una clase para representar un conjunto disjunto
class ConjuntoDisjunto {
    unordered_map<int, int> padre;

public:
    // Realiza la operación MakeSet inicializando conjuntos disjuntos para cada vértice
    void hacerConjunto(const vector<Borde> &bordes) {
        for (const Borde &borde : bordes) {
            padre[borde.inicio] = borde.inicio;
            padre[borde.destino] = borde.destino;
        }
    }

    // Encuentra la raíz del conjunto al que pertenece el elemento `k`
    int encontrar(int k) {
        // Si `k` es la raíz, retorna k
        if (padre[k] == k) {
            return k;
        }

        // Recurre para el padre hasta encontrar la raíz y la retorna
        return encontrar(padre[k]);
    }

    // Realiza la unión de dos subconjuntos
    void unir(int a, int b) {
        // Encuentra las raíces de los conjuntos que contienen a y b respectivamente
        int x = encontrar(a);
        int y = encontrar(b);

        // Hace que el padre de x sea y, uniendo los dos conjuntos
        padre[x] = y;
    }

    // Devuelve el tamaño del conjunto de padres
    size_t tamanoPadres() const {
        return padre.size();
    }
};

// Función para construir un árbol de recubrimiento mínimo utilizando el algoritmo de Kruskal
vector<Borde> ejecutarAlgoritmoKruskal(vector<Borde> bordes) {
    // Almacena los bordes presentes en el árbol de recubrimiento mínimo (MST)
    vector<Borde> arbolRecubrimientoMinimo;

    // Inicializa la clase `ConjuntoDisjunto`
    ConjuntoDisjunto conjuntoDisjunto;

    // Crea un conjunto singleton para cada elemento del universo
    conjuntoDisjunto.hacerConjunto(bordes);

    // Ordena los bordes en orden no decreciente de peso
    sort(bordes.begin(), bordes.end(), comparar());

    // El MST contiene exactamente `n-1` bordes, donde `n` es la cantidad de nodos únicos
    while (arbolRecubrimientoMinimo.size() != conjuntoDisjunto.tamanoPadres() - 1) {
        // Considera el siguiente borde con el peso mínimo del grafo
        Borde siguienteBorde = bordes.back();
        bordes.pop_back();

        // Encuentra la raíz de los conjuntos a los que pertenecen los dos extremos
        int x = conjuntoDisjunto.encontrar(siguienteBorde.inicio);
        int y = conjuntoDisjunto.encontrar(siguienteBorde.destino);

        // Verifica si ambos extremos tienen padres diferentes, indicando componentes conectadas diferentes
        if (x != y) {
            arbolRecubrimientoMinimo.push_back(siguienteBorde);
            conjuntoDisjunto.unir(x, y);
        } else {
            cout << "íAdvertencia! Hay al menos dos grafos separados en el conjunto de bordes." << endl;
        }
    }

    return arbolRecubrimientoMinimo;
}

int main() {
    // Vector de los bordes del grafo según el diagrama dado.
    vector<Borde> bordes = {
   {1,2,8},{1,8,10},{1,9,6},{1,10,12},{1,11,3},{1,7,9},{2,5,2},{2,11,7},
   {2,3,10},{3,11,5},{3,4,9},{4,513},{4,6,12},{5,6,10},{5,7,6},{6,7,8},
   {7,8,7},{8,9,3},{9,10,10},{10,11,8}                 
    };

    // Construir el grafo y encontrar el árbol de recubrimiento mínimo
    vector<Borde> arbolRecubrimientoMinimo = ejecutarAlgoritmoKruskal(bordes);

    // Imprimir el resultado
    cout << "El arbol de recubrimiento minimo es:" << endl;
    int pesoTotal = 0;

    // Imprimir los bordes del árbol de recubrimiento mínimo y calcular el peso total
    for (Borde &borde : arbolRecubrimientoMinimo) {
        cout << "(" << borde.inicio << ", " << borde.destino << ", " << borde.peso << ")" << endl;
        pesoTotal += borde.peso;
    }

    // Imprimir el peso total del árbol de recubrimiento mínimo
    cout << "El peso total del arbol de recubrimiento minimo es: " << pesoTotal << endl;

    return 0;
}