// Autores: Paula Bonilla Leon	9038204, Jerónimo Hurtado Mora	9038219, Juan Manuel Paredes Betancourt	9034283
// Punto de entrada del proyecto. Lee ordenes de la entrada estandar, una por
// linea, ejecuta la operacion correspondiente sobre la lista del inventario y
// escribe una respuesta por orden. Termina cuando se acaba la entrada.
// Formato de ordenes (AJUSTAR a lo que pida el enunciado):
//   AGREGAR codigo nombre cantidad
//   LISTAR
//   CONSULTAR codigo
//   REPONER codigo cantidad
//   ELIMINAR codigo
// Si a una orden le faltan datos o vienen mal escritos, responde
// DATOS INVALIDOS y no toca la lista.
#include "lista.h"

// Compara dos cadenas caracter por caracter. Devuelve true si son iguales
// (mismos caracteres y misma longitud). Avanza mientras ambas tengan el mismo
// caracter y no se haya llegado al final; al salir, son iguales solo si las
// dos terminaron a la vez en '\0'.
// Costo: O(k), con k la longitud de la cadena mas corta.
bool iguales(const char *a, const char *b)
{
  int i = 0;
  while (a[i] != '\0' && a[i] == b[i])
  {
    i++;
  }
  return a[i] == b[i];
}

int main()
{
  Lista inventario;
  char orden[16];

  // scanf devuelve cuantos datos logro leer: 1 mientras haya una palabra;
  // al acabarse la entrada devuelve EOF y el ciclo termina.
  while (scanf("%15s", orden) == 1)
  {

    if (iguales(orden, "AGREGAR"))
    {
      long codigo;
      char nombre[64];
      int cantidad;
      if (scanf("%ld %63s %d", &codigo, nombre, &cantidad) == 3)
      {
        int estado = inventario.agregar(codigo, nombre, cantidad);
        if (estado == 0)
        {
          printf("AGREGADO\n");
        }
        else if (estado == 1)
        {
          printf("REPETIDO\n");
        }
        else
        {
          printf("SIN MEMORIA\n");
        }
      }
      else
      {
        printf("DATOS INVALIDOS\n");
      }
    }
    else if (iguales(orden, "LISTAR"))
    {
      inventario.listar();
    }
    else if (iguales(orden, "CONSULTAR"))
    {
      long codigo;
      if (scanf("%ld", &codigo) == 1)
      {
        Producto p;
        if (inventario.consultar(codigo, p))
        {
          printf("%ld %s %d\n", p.codigo, p.nombre, p.cantidad);
        }
        else
        {
          printf("NO EXISTE\n");
        }
      }
      else
      {
        printf("DATOS INVALIDOS\n");
      }
    }
    else if (iguales(orden, "REPONER"))
    {
      long codigo;
      int cantidad;
      if (scanf("%ld %d", &codigo, &cantidad) == 2)
      {
        if (inventario.reponer(codigo, cantidad))
        {
          printf("REPUESTO\n");
        }
        else
        {
          printf("NO EXISTE\n");
        }
      }
      else
      {
        printf("DATOS INVALIDOS\n");
      }
    }
    else if (iguales(orden, "ELIMINAR"))
    {
      long codigo;
      if (scanf("%ld", &codigo) == 1)
      {
        if (inventario.eliminar(codigo))
        {
          printf("ELIMINADO\n");
        }
        else
        {
          printf("NO EXISTE\n");
        }
      }
      else
      {
        printf("DATOS INVALIDOS\n");
      }
    }
    else
    {
      printf("ORDEN DESCONOCIDA\n");
    }
  }

  // Al salir de main se llama el destructor de inventario, que libera
  // todos los nodos que queden.
  return 0;
}