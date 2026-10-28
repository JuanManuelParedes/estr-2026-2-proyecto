// Autores: Paula Bonilla Leon	9038204, Jerónimo Hurtado Mora	9038219, Juan Manuel Paredes Betancourt	9034283
// Lista enlazada simple del inventario: busqueda (interna), consulta y
// reposicion. Las tres comparten el mismo
// recorrido lineal desde cabeza. Los nodos y la clase Lista estan en lista.h.
#include "lista.h"

// Recorre la lista desde cabeza y devuelve el nodo con ese codigo, o nullptr
// si no esta. No modifica la lista.
// Costo: O(n) en el peor caso (codigo al final o ausente); O(1) si la lista
// esta vacia o el codigo esta en el primer nodo. Espacio auxiliar: O(1).
// agregar usa esta funcion para detectar codigos repetidos.
Nodo* Lista::buscar(long codigo) const {
  Nodo* actual = cabeza;
  while (actual != nullptr && actual->dato.codigo != codigo) {
    actual = actual->siguiente;
  }
  return actual;
}

// Agrega un articulo nuevo al inicio de la lista. Devuelve 0 si lo agrego,
// 1 si el codigo ya estaba (sin modificar la lista) y 2 si malloc no pudo
// reservar el nodo (tampoco modifica la lista). El nombre se copia caracter
// por caracter y se corta en 63 caracteres para no salirse del arreglo.
// Costo: el de buscar, O(n), para detectar el codigo repetido; copiar el
// nombre (maximo 63 caracteres) y enlazar el nodo en cabeza es O(1).
// Total O(n). Espacio auxiliar: O(1) (un nodo por llamada).
// Como inserta en cabeza, listar muestra los articulos del ultimo al primero
// agregado.
int Lista::agregar(long codigo, const char* nombre, int cantidad){
  int estado = 0;
  if(buscar(codigo) != nullptr){
    estado = 1; // el codigo ya existe;
  }else{
    Nodo* nuevo = (Nodo*) malloc(sizeof(Nodo));
    if(nuevo == nullptr){
      estado = 2;
    }else{
      //asigna codigo y cantidad
      nuevo-> dato.codigo = codigo;
      nuevo->dato.cantidad = cantidad;
      //copia el nombre con el ciclo
      int i = 0;
      while(i < 63 && nombre[i] != '\0'){
        nuevo->dato.nombre[i] = nombre[i];
        i++;
      }
      nuevo->dato.nombre[i] = '\0';
      nuevo->siguiente = cabeza;
      cabeza = nuevo;
      n++;
    }
  }
  return estado;
}

// Escribe un articulo por linea con el formato "codigo nombre cantidad", del
// primero al ultimo nodo de la lista. No modifica la lista; en una lista vacia no escribe nada.
// Costo: O(n), un paso por nodo y cada impresion es de tamano acotado.
// Espacio auxiliar: O(1).
// Como agregar inserta en cabeza, el orden de salida es del ultimo al primero agregado.
void Lista::listar() const{
  //Recorrer desde cabeza con un puntero actual, igual que buscar.
  Nodo* actual = cabeza;
  while (actual != nullptr){
    printf("%ld %s %d\n", actual->dato.codigo, actual->dato.nombre, actual->dato.cantidad);
    actual = actual->siguiente;
  }
}

// Si el codigo esta, copia el producto en salida y devuelve true; si no,
// devuelve false y deja salida como estaba. No modifica la lista.
// Costo: el de buscar, O(n); la copia del producto es de tamano acotado.
bool Lista::consultar(long codigo, Producto& salida) const{
  Nodo* nodo = buscar(codigo);
  bool encontrado = (nodo != nullptr);
  if (encontrado) {
    salida = nodo->dato;
  }
  return encontrado;
}

// Si el codigo esta, suma cantidad a las existencias y devuelve true; si no,
// devuelve false y NO crea ningun producto.
// Costo: el de buscar, O(n); la suma es O(1).
bool Lista::reponer(long codigo, int cantidad){
  Nodo* nodo = buscar(codigo);
  bool encontrado = (nodo != nullptr);
  if (encontrado) {
    nodo->dato.cantidad = nodo->dato.cantidad + cantidad;
  }
  return encontrado;
}

bool Lista::eliminar(long codigo){
  Nodo* anterior = nullptr;
  Nodo* muerto = cabeza;
  while (muerto != nullptr && muerto->dato.codigo != codigo) {
    anterior = muerto;
    muerto = muerto->siguiente;
  }
  bool encontrado = (muerto != nullptr);
  if (encontrado) {
    if (anterior == nullptr) {               // equivale a p == 0
      cabeza = cabeza->siguiente;
    } else {                                 // equivale a anterior = nodoEn(p - 1)
      anterior->siguiente = muerto->siguiente;
    }
    free(muerto);
    n = n - 1;
  }
  return encontrado;
}