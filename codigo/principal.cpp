// Autores: Paula Bonilla Leon	9038204, Jerónimo Hurtado Mora	9038219, Juan Manuel Paredes Betancourt	9034283
/*Punto de entrada del proyecto. Lee ordenes de la entrada estandar, una por
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
sin llamar a la lista, que exige que no este vacia.
El mismo programa sirve para las tres estructuras: el ciclo de ordenes esta en
procesar, que es una plantilla y solo usa las operaciones de la interfaz comun
(vacia, agregar, listar, consultar, reponer, eliminar). main construye la
estructura y se la pasa por referencia, asi el constructor queda fuera de la
interfaz comun. Cual se construye lo decide el Makefile al compilar:
-DUSAR_TABLA produce proyecto_tabla, -DUSAR_MAPA produce proyecto_mapa y sin
bandera sale proyecto_lista.*/

#include "lista.h"
#include "tablahash.h"
#if __has_include("mapa.h")
#include "mapa.h"
#endif

// Numero de cubetas de la tabla en este programa: un primo, para que el
// residuo reparta mejor los codigos.
const int CUBETAS = 1009;

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

/*Lee las ordenes de la entrada estandar y las ejecuta sobre inventario, que
puede ser una Lista, una TablaHash o un Mapa: solo se llaman las operaciones
que las tres tienen con las mismas firmas.
Costo: la suma de los costos de las ordenes leidas, cada una con el costo de
la operacion en la estructura usada. Espacio auxiliar: O(1) (buffers de
tamano fijo para la orden y el nombre).*/
template <typename Inventario>
void procesar(Inventario& inventario){
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
      if (scanf("%ld %63s", &codigo, nombre) == 2){
        // Si el nombre tenia mas de 63 caracteres, descarta el resto de la palabra.
        int descartados = scanf("%*[^ \t\r\n]");
        (void) descartados;
        if (scanf("%d", &cantidad) == 1){
          if (codigo > 0 && cantidad > 0){
            int estado = inventario.agregar(codigo, nombre, cantidad);
            if (estado == 0){
              printf("ok\n");
            }
            else if (estado == 1){
              printf("repetido\n");
            }
          }else{
            printf("invalido\n");
          }
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
      if (scanf("%ld %d", &codigo, &cantidad) == 2){
        if (codigo > 0 && cantidad > 0){
          if (!inventario.vacia() && inventario.reponer(codigo, cantidad)){
            printf("ok\n");
          }else{
            printf("no existe\n");
          }
        }else{
          printf("invalido\n");
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
}

int main(){
#if defined(USAR_TABLA)
  TablaHash inventario(CUBETAS);
#elif defined(USAR_MAPA)
  Mapa inventario;
#else
  Lista inventario;
#endif
  procesar(inventario);
  // Al salir de main se llama el destructor de inventario, que libera
  // todos los nodos que queden.
  return 0;
}