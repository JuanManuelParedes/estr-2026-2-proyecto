// Autores: Paula Bonilla Leon	9038204, Jerónimo Hurtado Mora	9038219, Juan Manuel Paredes Betancourt	9034283
#ifndef LISTA_H
#define LISTA_H

#include <cstdio>
#include <cstdlib>
#include <cstring>

struct Producto {
    long codigo;
    char nombre[64];
    int cantidad;
};

struct Nodo {
    Producto dato;
    Nodo* siguiente;
};

class Lista {
 
  private:
  Nodo* cabeza;
  int n;   // número de artículos
 
  public:
  
  Lista(){
    cabeza = nullptr;
    n = 0;
  }
  ~Lista(){
    Nodo* actual = cabeza;
    while(actual != nullptr){
        Nodo* siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }
  }
  int agregar(long codigo, const char* nombre, int cantidad);
  void listar() const;
  Nodo* buscar(long codigo) const;
  bool consultar(long codigo, Producto& salida) const;
  bool reponer(long codigo, int cantidad);
  bool eliminar(long codigo);

};

#endif