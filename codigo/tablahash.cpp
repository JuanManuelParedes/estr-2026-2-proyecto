/* Autores: Paula Bonilla Leon	9038204, Jerónimo Hurtado Mora	9038219, Juan Manuel Paredes Betancourt	9034283
Tabla hash del inventario con encadenamiento: cada cubeta es una Lista.
Operaciones: indice (funcion hash), constructor, destructor, agregar, listar,
consultar, reponer y eliminar. Las declaraciones estan en tablahash.h. */
#include "tablahash.h"

/* Devuelve el indice de la cubeta (0..numeroCubetas-1) que le corresponde al codigo, con
el metodo de la division: el residuo de codigo entre numeroCubetas.
Costo: O(1), una division y un residuo. Espacio auxiliar: O(1).
Precondicion: codigo > 0 y numeroCubetas > 0 (con un codigo negativo el
residuo seria negativo y saldria del arreglo; con 0 cubetas se dividiria
entre cero). */
int TablaHash::indice(long codigo) const{
    assert(codigo > 0);
    assert(numeroCubetas > 0);
    int resultado = (int)(codigo % numeroCubetas);
    return resultado;
}

/* Reserva el arreglo de numeroCubetas listas vacias y deja la tabla sin
articulos. 
Costo: O(m), con m = numeroCubetas, porque se construye una Lista por cubeta.
Espacio: O(m) para el arreglo de cubetas.
Precondicion: numeroCubetas > 0. */
TablaHash::TablaHash(int numeroCubetas){
    assert(numeroCubetas > 0);
    this->numeroCubetas = numeroCubetas;
    this->numeroArticulos = 0;
    this->cubetas = new Lista[numeroCubetas];
}

/* Libera el arreglo de cubetas, donde por dentro, el destructor de cada Lista libera sus nodos.
Costo: O(m + n), m llamadas al destructor de Lista y n nodos liberados en total.
Espacio auxiliar: O(1). */
TablaHash::~TablaHash() {
  delete[] cubetas;
}

/* Agrega un articulo nuevo a la tabla. Calcula la cubeta del codigo con
indice y delega al agregar de lista de esa cubeta, que detecta el codigo
repetido y enlaza el nodo en cabeza. Devuelve 0 si lo agrego, 1 si el codigo
ya estaba (sin modificar la tabla) y 2 si no se pudo reservar memoria o malloc fallo al reservar el
nodo (tampoco modifica la tabla). numeroArticulos solo aumenta cuando el
resultado es 0.
Costo: calcular indice es O(1); el resto es el costo de Lista::agregar sobre
UNA cubeta, que es O(k) con k el numero de articulos de esa cubeta (la busqueda
de repetidos), copiar el nombre (maximo 63 caracteres) y enlazar en cabeza es
O(1). De igual manera el costo depende del caso:
  - Caso esperado: O(1 + alfa), con alfa = n / numeroCubetas, si la funcion
    hash reparte los codigos de forma uniforme.
  - Peor caso: O(n), cuando todos los codigos caen en la misma cubeta, es decir, la
    tabla se comporta como la lista del avance.
Espacio auxiliar: O(1) (un nodo por llamada).
Precondicion: codigo > 0, nombre no vacio, sin espacios y de a lo sumo 63
caracteres, cantidad > 0. */
int TablaHash::agregar(long codigo, const char* nombre, int cantidad) {
    assert(codigo > 0);
    assert(cantidad > 0);
    assert(nombre != nullptr && nombre[0] != '\0');
    int estado = cubetas[indice(codigo)].agregar(codigo, nombre, cantidad);
    if (estado == 0) {
        numeroArticulos++;
    }
    return estado;
}

/* Escribe todos los articulos de la tabla, uno por linea, con el formato
"codigo nombre cantidad". Recorre las cubetas de la 0 a la numeroCubetas-1 y
le pide a cada una que se liste. No modifica la tabla; con la tabla vacia no
escribe nada.
Orden de salida: por cubeta, y dentro de cada cubeta del ultimo al primero
agregado, ya que la lista inserta en cabeza. No coincide con el de la lista del
avance, que sale del ultimo al primero agregado de todo el inventario.
Costo: Theta(numeroCubetas + n). El ciclo hace numeroCubetas iteraciones
aunque haya cubetas vacias, y entre todas las cubetas se escriben los n
articulos. Con la tabla vacia sigue costando Theta(numeroCubetas).
Espacio auxiliar: O(1) (el contador del ciclo).
Precondicion: ninguna.*/
void TablaHash::listar() const {
  int i = 0;
  while (i < numeroCubetas) {
    cubetas[i].listar();
    i++;
  }
}

/* TODO (Paula): consultar. Recuerda proteger la cubeta vacia. */
bool TablaHash::consultar(long codigo, Producto& salida) const {
  bool encontrado = false;
  (void) codigo; (void) salida;
  return encontrado;
}

/* TODO (Paula): reponer. */
bool TablaHash::reponer(long codigo, int cantidad) {
  bool encontrado = false;
  (void) codigo; (void) cantidad;
  return encontrado;
}

/* TODO (Jeronimo): eliminar. Actualiza numeroArticulos si elimino. */
bool TablaHash::eliminar(long codigo) {
  bool eliminado = false;
  (void) codigo;
  return eliminado;
}