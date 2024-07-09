#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
using namespace std;

// Un nodo del árbol
struct Nodo
{
	char ch;
	int freq;
	Nodo *izquierda, *derecha;
};

// Función para asignar un nuevo nodo del árbol
Nodo* obtenerNodo(char ch, int freq, Nodo* izquierda, Nodo* derecha)
{
	Nodo* nodo = new Nodo();

	nodo->ch = ch;
	nodo->freq = freq;
	nodo->izquierda = izquierda;
	nodo->derecha = derecha;

	return nodo;
}

// Objeto de comparación para ordenar la cola de prioridad
struct comp
{
	bool operator()(Nodo* izq, Nodo* der)
	{
		// El elemento de mayor prioridad tiene la frecuencia más baja
		return izq->freq > der->freq;
	}
};

int calcular_costo_total(Nodo* raiz){
    if(raiz->izquierda == NULL && raiz->derecha == NULL){
        return 0;
    }
    return raiz->freq + calcular_costo_total(raiz->izquierda) + calcular_costo_total(raiz->derecha);
}

// Recorre el árbol Huffman y almacena los códigos Huffman en un mapa.
void codificar(Nodo* raiz, string str,
			unordered_map<char, string> &codigosHuffman)
{
	if (raiz == nullptr)
		return;

	// Se encontró un nodo hoja
	if (!raiz->izquierda && !raiz->derecha) {
		codigosHuffman[raiz->ch] = str;
	}

	codificar(raiz->izquierda, str + "0", codigosHuffman);
	codificar(raiz->derecha, str + "1", codigosHuffman);
}

// Recorre el árbol Huffman y decodifica la cadena codificada
void decodificar(Nodo* raiz, int &indice, string str)
{
	if (raiz == nullptr) {
		return;
	}

	// Se encontró un nodo hoja
	if (!raiz->izquierda && !raiz->derecha)
	{
		cout << raiz->ch;
		return;
	}

	indice++;

	if (str[indice] =='0')
		decodificar(raiz->izquierda, indice, str);
	else
		decodificar(raiz->derecha, indice, str);
}

// Construye el árbol Huffman y decodifica el texto de entrada
Nodo* construirArbolHuffman(string texto)
{
	// Calcula la frecuencia de aparición de cada carácter
	// y almacénalo en un mapa
	unordered_map<char, int> frecuencia;
	for (char ch: texto) {
		frecuencia[ch]++;
	}

	// Crea una cola de prioridad para almacenar nodos del árbol
	// de Huffman;
	priority_queue<Nodo*, vector<Nodo*>, comp> cola_prioridad;

	// Crea un nodo hoja para cada carácter y agrégalo
	// a la cola de prioridad.
	for (auto par: frecuencia) {
		cola_prioridad.push(obtenerNodo(par.first, par.second, nullptr, nullptr));
	}

	// Realiza el proceso hasta que haya más de un nodo en la cola
	while (cola_prioridad.size() != 1)
	{
		// Remueve los dos nodos de mayor prioridad
		// (menor frecuencia) de la cola
		Nodo *izquierda = cola_prioridad.top(); cola_prioridad.pop();
		Nodo *derecha = cola_prioridad.top();	cola_prioridad.pop();

		// Crea un nuevo nodo interno con estos dos nodos
		// como hijos y con una frecuencia igual a la suma
		// de las frecuencias de los dos nodos. Agrega el nuevo nodo
		// a la cola de prioridad.
		int suma = izquierda->freq + derecha->freq;
		cola_prioridad.push(obtenerNodo('\0', suma, izquierda, derecha));
	}

	// raíz almacena el puntero a la raíz del Árbol de Huffman
	return cola_prioridad.top();
}

// Algoritmo de codificación Huffman
int main()
{
    string entrada_usuario;
    cout << "Bautista Coello Alexandra & Gomez Lopez Miguel Angel 3CM1 ";
        cout << "\n\n\n";

    cout << "Ingresa una cadena para la codificacion Huffman: ";
    getline(cin, entrada_usuario);

	Nodo* raiz = construirArbolHuffman(entrada_usuario);

	unordered_map<char, string> codigosHuffman;
	codificar(raiz, "", codigosHuffman);

	cout << "\nLos codigos de Huffman son:\n";
	for (auto par: codigosHuffman) {
		cout << par.first << " " << par.second << '\n';
	}

	cout << "\nLa cadena original es:\n" << entrada_usuario << '\n';

	string cadena_codificada = "";
	for (char ch: entrada_usuario) {
		cadena_codificada += codigosHuffman[ch];
	}

	cout << "\nLa cadena codificada es:\n" << cadena_codificada << '\n';

	int indice = -1;
	cout << "\nLa cadena decodificada es:\n";
	while (indice < (int)cadena_codificada.size() - 2) {
		decodificar(raiz, indice, cadena_codificada);
	}

	int costoTotal = calcular_costo_total(raiz);
	cout << "\nEl costo total del arbol es: " << costoTotal << '\n';

	return 0;
}