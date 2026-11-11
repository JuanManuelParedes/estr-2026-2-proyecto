// Autores: Paula Bonilla Leon	9038204, Jerónimo Hurtado Mora	9038219, Juan Manuel Paredes Betancourt	9034283
#ifndef TABLAHASH_H
#define TABLAHASH_H

#include "lista.h"

/* Tabla hash con encadenamiento y clave entera (el codigo del articulo).
Cada cubeta es una Lista del avance. Un articulo con codigo c vive en la
cubeta indice(c) = c mod m. */
class TablaHash {

  private:
  Lista* cubetas;               // arreglo de nCubetas listas; cubetas[i] es la cubeta i
  int numeroCubetas;            // numero de cubetas
  int numeroArticulos;          // numero total de articulos en toda la tabla

  // Funcion hash: devuelve la cubeta (0..nCubetas-1) que le corresponde al codigo.
  int indice(long codigo) const;

  public:
  // Precondicion: numeroCubetas > 0.
  TablaHash(int numeroCubetas);
  ~TablaHash();

  // Una tabla se copia mal (dos tablas liberarian las mismas cubetas), asi que se prohibe.
  TablaHash(const TablaHash&) = delete;
  TablaHash& operator=(const TablaHash&) = delete;

  // Mismas operaciones y firmas que Lista.
  // Lo que hace cada funcion esta en tablahash.cpp
  bool vacia() const { return numeroArticulos == 0; }
  int agregar(long codigo, const char* nombre, int cantidad);
  void listar() const;
  bool consultar(long codigo, Producto& salida) const;
  bool reponer(long codigo, int cantidad);
  bool eliminar(long codigo);

};

#endif