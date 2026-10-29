/* Autores: Paula Bonilla Leon	9038204, Jerónimo Hurtado Mora	9038219, Juan Manuel Paredes Betancourt	9034283
Punto de entrada del proyecto. Lee ordenes de la entrada estandar, una por
linea, ejecuta la operacion correspondiente sobre la lista del inventario y
escribe una respuesta por orden. Lee primero cuántas ordenes vienen y procesa exactamente esas
Formato de ordenes:
  AGREGAR codigo nombre cantidad
  LISTAR
  CONSULTAR codigo
  REPONER codigo cantidad
  ELIMINAR codigo
Si a una orden le faltan datos o estos no cumplen las precondiciones
(codigo y cantidad positivos), la ignora sin escribir nada y no toca la lista.
Con el inventario vacio, CONSULTAR, REPONER y ELIMINAR responden "no existe"
sin llamar a la lista, que exige que no este vacia.*/

#include "lista.h"

/*Compara dos cadenas caracter por caracter. Devuelve true si son iguales
(mismos caracteres y misma longitud). Avanza mientras ambas tengan el mismo
caracter y no se haya llegado al final; al salir, son iguales solo si las
dos terminaron a la vez en '\0'.
Costo: O(k), con k la longitud de la cadena mas corta. */
bool iguales(const char *a, const char *b){
  int i = 0;
  while (a[i] != '\0' && a[i] == b[i])
  {
    i++;
  }
  return a[i] == b[i];
}

int main(){
  Lista inventario;
  char orden[16];
  int total = 0;
  int leidas = 0;

  // La primera linea trae cuantas ordenes vienen. Si no se puede leer,
  // se procesan cero ordenes.
  if (scanf("%d", &total) != 1){
    total = 0;
  }

  // scanf devuelve cuantos datos logro leer: 1 mientras haya una palabra;
  // si la entrada se acaba antes de lo anunciado, devuelve EOF y el ciclo
  // termina.
  while (leidas < total && scanf("%15s", orden) == 1){
    leidas++;
    if (iguales(orden, "AGREGAR")){
      long codigo;
      char nombre[64];
      int cantidad;
      if (scanf("%ld %63s %d", &codigo, nombre, &cantidad) == 3 && codigo > 0 && cantidad > 0){
        int estado = inventario.agregar(codigo, nombre, cantidad);
        if (estado == 0){
          printf("ok\n");
        }
        else if (estado == 1){
          printf("repetido\n");
        }
      }
    }
    else if (iguales(orden, "LISTAR")){
      inventario.listar();
    }
    else if (iguales(orden, "CONSULTAR")){
      long codigo;
      if (scanf("%ld", &codigo) == 1){
        Producto p;
        if (!inventario.vacia() && codigo > 0 && inventario.consultar(codigo, p)){
          printf("%ld %s %d\n", p.codigo, p.nombre, p.cantidad);
        }else{
          printf("no existe\n");
        }
      }
    }
    else if (iguales(orden, "REPONER")){
      long codigo;
      int cantidad;
      if (scanf("%ld %d", &codigo, &cantidad) == 2 && codigo > 0 && cantidad > 0){
        if (!inventario.vacia() && inventario.reponer(codigo, cantidad)){
          printf("ok\n");
        }else{
          printf("no existe\n");
        }
      }
    }
    else if (iguales(orden, "ELIMINAR")){
      long codigo;
      if (scanf("%ld", &codigo) == 1){
        if (!inventario.vacia() && codigo > 0 && inventario.eliminar(codigo)){
          printf("ok\n");
        }else{
          printf("no existe\n");
        }
      }
    }
  }
  // Al salir de main se llama el destructor de inventario, que libera
  // todos los nodos que queden.
  return 0;
}