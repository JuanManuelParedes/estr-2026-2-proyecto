// Autores: Paula Bonilla Leon 9038204
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

// Si el codigo esta, copia el producto en salida y devuelve true; si no,
// devuelve false y deja salida como estaba. No modifica la lista.
// Costo: el de buscar, O(n); la copia del producto es de tamano acotado.
bool Lista::consultar(long codigo, Producto& salida) const {
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
bool Lista::reponer(long codigo, long cantidad) {
  Nodo* nodo = buscar(codigo);
  bool encontrado = (nodo != nullptr);
  if (encontrado) {
    nodo->dato.cantidad = nodo->dato.cantidad + cantidad;
  }
  return encontrado;
}
