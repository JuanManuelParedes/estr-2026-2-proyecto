// Autores: Paula Bonilla Leon	9038204, Jerónimo Hurtado Mora	9038219, Juan Manuel Paredes Betancourt	9034283
/*Programa de medicion de los experimentos. Mide, sobre una misma lista de
codigos, cuanto tardan las tres operaciones que cambian con el tamano:
agregar los n articulos, consultarlos todos y eliminarlos todos.
Uso:
  ./medidor estructura n tamano modo
    estructura:   lista | tabla | mapa
    n:            numero de articulos (n > 0)
    tamano:       numero de cubetas de la tabla (la lista y el mapa lo ignoran)
                    chica   -> 101 cubetas
                    cercana -> el primo mas pequeno >= n   (alfa cercano a 1)
                    grande  -> el primo mas pequeno >= 2n  (alfa cercano a 1/2)
    modo:         aleatorio -> n codigos distintos al azar entre 1 y 10^9
                  colision  -> codigos m, 2m, ..., nm: todos caen en la cubeta 0
Escribe una linea CSV con UNA medicion:
  estructura,cubetas,modo,n,agregar_ms,consultar_ms,eliminar_ms,encontrados
encontrados cuenta las consultas que respondieron true y debe ser n (sirve de
verificacion).
Cada repeticion se corre en un proceso nuevo (el Makefile llama al programa
varias veces y saca la mediana). Si se repitiera dentro del mismo proceso, los
nodos liberados al eliminar en desorden quedan revueltos en la memoria
dinamica, y la siguiente repeticion recibiria nodos dispersos: la lista se
veria mas lenta por como quedo la memoria y no por la estructura.
Los codigos se generan con semilla fija, asi que las tres estructuras reciben
exactamente la misma entrada.
Igual que principal.cpp, la medicion es una plantilla que solo usa la interfaz
comun; main construye la estructura (el constructor queda fuera de la
interfaz). El mapa entra solo si existe mapa.h con la clase Mapa. */

#include "lista.h"
#include "tablahash.h"
#if __has_include("mapa.h")
#include "mapa.h"
#define HAY_MAPA 1
#endif
#include <chrono>
#include <string>
#include <random>
#include <vector>
#include <algorithm>

/*Devuelve true si x es primo, probando divisores desde 2 hasta raiz de x.
Costo: O(raiz(x)). Espacio auxiliar: O(1). */
bool esPrimo(long x){
  bool primo = (x >= 2);
  long d = 2;
  while (primo && d * d <= x){
    if (x % d == 0){
      primo = false;
    }
    d++;
  }
  return primo;
}

/*Devuelve el primo mas pequeno mayor o igual a x.
Costo: O(g * raiz(x)), con g la distancia al siguiente primo, que en la
practica es pequena. Espacio auxiliar: O(1). */
long siguientePrimo(long x){
  long p = x;
  while (!esPrimo(p)){
    p++;
  }
  return p;
}

/*Mide una repeticion sobre inventario, que llega vacio: agrega los codigos en
el orden de codigos, y luego los consulta y los elimina en el orden de orden
(una permutacion de los mismos codigos). Guarda los tres tiempos en
milisegundos en tiempos[0..2] y cuantas consultas encontraron el articulo en
encontrados. Al terminar, inventario queda vacio.
Las consultas y las eliminaciones se hacen siempre con el inventario no vacio,
asi que se cumplen las precondiciones de las dos estructuras.
Costo: el de n agregar + n consultar + n eliminar en la estructura usada.
Espacio auxiliar: O(1) fuera de los articulos que se guardan. */
template <typename Inventario>
void medirUna(Inventario& inventario, const std::vector<long>& codigos,
              const std::vector<long>& orden, double tiempos[3], int& encontrados){
  int n = (int) codigos.size();
  Producto p;
  encontrados = 0;

  std::chrono::steady_clock::time_point t0 = std::chrono::steady_clock::now();
  int i = 0;
  while (i < n){
    inventario.agregar(codigos[i], "producto", 1);
    i++;
  }
  std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
  i = 0;
  while (i < n){
    if (inventario.consultar(orden[i], p)){
      encontrados++;
    }
    i++;
  }
  std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
  i = 0;
  while (i < n){
    inventario.eliminar(orden[i]);
    i++;
  }
  std::chrono::steady_clock::time_point t3 = std::chrono::steady_clock::now();

  tiempos[0] = std::chrono::duration<double, std::milli>(t1 - t0).count();
  tiempos[1] = std::chrono::duration<double, std::milli>(t2 - t1).count();
  tiempos[2] = std::chrono::duration<double, std::milli>(t3 - t2).count();
}

int main(int argc, char* argv[]){
  int resultado = 0;
  if (argc != 5){
    fprintf(stderr, "uso: %s lista|tabla|mapa n chica|cercana|grande aleatorio|colision\n", argv[0]);
    resultado = 1;
  }else{
    std::string estructura = argv[1];
    long n = atol(argv[2]);
    std::string tamano = argv[3];
    std::string modo = argv[4];

    // Numero de cubetas segun el tamano pedido.
    long m = 101;
    if (tamano == "cercana"){
      m = siguientePrimo(n);
    }else if (tamano == "grande"){
      m = siguientePrimo(2 * n);
    }

    // Codigos de prueba, con semilla fija para que todas las estructuras
    // reciban la misma entrada.
    std::vector<long> codigos;
    std::mt19937_64 generador(2026);
    if (modo == "colision"){
      long i = 1;
      while (i <= n){
        codigos.push_back(i * m);        // i*m mod m = 0: todos en la cubeta 0
        i++;
      }
    }else{
      std::uniform_int_distribution<long> azar(1, 1000000000L);
      while ((long) codigos.size() < n){
        while ((long) codigos.size() < n){
          codigos.push_back(azar(generador));
        }
        // Quitar repetidos: ordenar, dejar uno de cada y volver a llenar.
        std::sort(codigos.begin(), codigos.end());
        codigos.erase(std::unique(codigos.begin(), codigos.end()), codigos.end());
      }
      std::shuffle(codigos.begin(), codigos.end(), generador);
    }
    std::vector<long> orden = codigos;
    std::shuffle(orden.begin(), orden.end(), generador);

    double tiempos[3] = {0, 0, 0};
    int encontrados = 0;
    bool valida = (n > 0);
    if (valida && estructura == "lista"){
      Lista inventario;
      medirUna(inventario, codigos, orden, tiempos, encontrados);
    }else if (valida && estructura == "tabla"){
      TablaHash inventario((int) m);
      medirUna(inventario, codigos, orden, tiempos, encontrados);
#ifdef HAY_MAPA
    }else if (valida && estructura == "mapa"){
      Mapa inventario;
      medirUna(inventario, codigos, orden, tiempos, encontrados);
#endif
    }else{
      valida = false;
    }

    if (!valida){
      fprintf(stderr, "argumentos invalidos o estructura no disponible: %s\n", argv[1]);
      resultado = 1;
    }else{
      if (estructura != "tabla"){
        m = 0;                          // la lista y el mapa no tienen cubetas
      }
      printf("%s,%ld,%s,%ld,%.3f,%.3f,%.3f,%d\n", estructura.c_str(), m, modo.c_str(), n,
             tiempos[0], tiempos[1], tiempos[2], encontrados);
    }
  }
  return resultado;
}