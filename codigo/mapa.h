// Autores: Paula Bonilla Leon	9038204, Jerónimo Hurtado Mora	9038219, Juan Manuel Paredes Betancourt	9034283
#ifndef MAPA_H
#define MAPA_H

#include "lista.h"
#include <map>
#include <new>        // std::bad_alloc

/* Envoltorio de std::map para el inventario: el contenedor de referencia de
los experimentos (tercera curva). Guarda cada articulo con su codigo como
clave. Por dentro, std::map es un arbol rojo-negro (arbol binario de busqueda
balanceado), asi que buscar, insertar y borrar cuestan O(log n).
Tiene las mismas operaciones y firmas que Lista y TablaHash, para que
principal.cpp y medir.cpp lo usen sin cambiar. Todo esta en este archivo
porque cada funcion es corta y solo delega en std::map. */
class Mapa {

  private:
  std::map<long, Producto> articulos;   // clave: codigo del articulo

  public:

  // No necesita constructor ni destructor propios: std::map empieza vacio y
  // libera sus nodos solo al destruirse.

  bool vacia() const { return articulos.empty(); }

  /* Agrega un articulo nuevo. Devuelve 0 si lo agrego, 1 si el codigo ya
  estaba (sin modificar el mapa) y 2 si no se pudo reservar memoria (tampoco
  modifica el mapa). El nombre se copia caracter por caracter y se corta en 63
  caracteres, igual que en Lista.
  Costo: O(log n), insert busca la clave en el arbol y, si no esta, inserta y
  rebalancea. Espacio auxiliar: O(1) (un nodo del arbol por llamada).
  Precondicion: codigo > 0, nombre no vacio, sin espacios y de a lo sumo 63
  caracteres, cantidad > 0. */
  int agregar(long codigo, const char* nombre, int cantidad) {
    assert(codigo > 0);
    assert(cantidad > 0);
    assert(nombre != nullptr && nombre[0] != '\0');
    Producto nuevo;
    nuevo.codigo = codigo;
    nuevo.cantidad = cantidad;
    int i = 0;
    while (i < 63 && nombre[i] != '\0') {
      nuevo.nombre[i] = nombre[i];
      i++;
    }
    nuevo.nombre[i] = '\0';
    int estado = 1;
    try {
      // insert no reemplaza: si la clave ya estaba, devuelve false en second.
      if (articulos.insert(std::make_pair(codigo, nuevo)).second) {
        estado = 0;
      }
    } catch (const std::bad_alloc&) {
      estado = 2;               // new fallo al reservar el nodo del arbol
    }
    return estado;
  }

  /* Escribe un articulo por linea con el formato "codigo nombre cantidad".
  std::map recorre las claves de menor a mayor, asi que sale ordenado por
  codigo (distinto de la lista y de la tabla). No modifica el mapa.
  Costo: O(n), el recorrido en orden del arbol. Espacio auxiliar: O(1). */
  void listar() const {
    std::map<long, Producto>::const_iterator it = articulos.begin();
    while (it != articulos.end()) {
      printf("%ld %s %d\n", it->second.codigo, it->second.nombre, it->second.cantidad);
      ++it;
    }
  }

  /* Si el codigo esta, copia el producto en salida y devuelve true; si no,
  devuelve false y deja salida como estaba. No modifica el mapa.
  Costo: O(log n), find baja por el arbol. Espacio auxiliar: O(1).
  Precondicion: n >= 1 y codigo > 0. */
  bool consultar(long codigo, Producto& salida) const {
    assert(!vacia());
    assert(codigo > 0);
    std::map<long, Producto>::const_iterator it = articulos.find(codigo);
    bool encontrado = (it != articulos.end());
    if (encontrado) {
      salida = it->second;
    }
    return encontrado;
  }

  /* Si el codigo esta, suma cantidad a las existencias y devuelve true; si
  no, devuelve false y NO crea ningun producto.
  Costo: O(log n), find baja por el arbol; la suma es O(1).
  Precondicion: n >= 1, codigo > 0, cantidad > 0. */
  bool reponer(long codigo, int cantidad) {
    assert(!vacia());
    assert(codigo > 0);
    assert(cantidad > 0);
    std::map<long, Producto>::iterator it = articulos.find(codigo);
    bool encontrado = (it != articulos.end());
    if (encontrado) {
      it->second.cantidad = it->second.cantidad + cantidad;
    }
    return encontrado;
  }

  /* Elimina el articulo con ese codigo. Devuelve true si lo elimino y false
  si el codigo no estaba (no modifica el mapa). erase devuelve cuantas claves
  borro, que es 0 o 1 porque las claves no se repiten.
  Costo: O(log n), buscar la clave, borrar el nodo y rebalancear.
  Espacio auxiliar: O(1).
  Precondicion: n >= 1 y codigo > 0. */
  bool eliminar(long codigo) {
    assert(!vacia());
    assert(codigo > 0);
    bool eliminado = (articulos.erase(codigo) == 1);
    return eliminado;
  }

};

#endif
