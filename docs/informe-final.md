# Informe final

## 1. El escenario y el modelado

Nuestro escenario corresponde al inventario de una tienda, el cual puede ser usado por el encargado para poder llevar un control de manera correcta sobre sus productos.
La información que este maneja y guarda es: un código único que identifica a cada producto para que no se confunda con algún otro, el nombre del artículo y por último la cantidad que haya de ese producto. 

Este inventario resuelve muchas situaciones que serían complicadas de afrontar si en la tienda no se tiene una herramienta que permita llevar el control de los artículos disponibles en esta. Por ejemplo, cuando llega mercancía nueva, se agota un producto o un cliente pregunta si hay existencias de alguno, entre muchas otras.

El programa se comunica de manera que el usuario le otorga unas órdenes, en donde debe colocar unos parámetros específicos y este responde con algunos textos de acuerdo a lo que se le haya pedido. Los detalles están en el siguiente numeral. 

Casi todas las operaciones del inventario (como consultar, reponer, eliminar e incluso agregar, que debe detectar códigos repetidos) comienzan por encontrar el artículo a partir de su código. Cuando el inventario tiene pocos artículos no hay ningún problema, sin embargo, al escalarlo con miles de artículos el costo de buscar predomina sobre todo lo demás. Por esta razón, el proyecto resuelve el mismo problema con dos estructuras: en primer lugar, una lista enlazada simple, donde buscar recorre los nodos, y en segundo lugar, una tabla hash con encadenamiento, que reparte los artículos en cubetas para buscar solo en una de ellas. Además se mide `std::unordered_map` como referencia de una implementación de la biblioteca estándar.

Las dos estructuras reciben las mismas órdenes y por eso deben responder lo mismo con igual entrada, de manera que sea posible medirlas con un solo programa y así comparar sus salidas. La única diferencia esperada es el orden en que sale `listar`, que depende de la estructura y se explica en la sección de la tabla hash.

## 2. Las dos estructuras

Cada artículo del inventario guarda tres datos: su código (debe ser entero positivo único), su nombre (una palabra sin espacios, de a lo sumo 63 caracteres) y su cantidad (también entera positiva).

Las dos estructuras guardan esos mismos artículos, pero organizados
de forma distinta:

- **Lista enlazada simple:** cada nodo guarda un artículo y un
  puntero al siguiente nodo; la estructura guarda un puntero al primero
  (`cabeza`) y el número de artículos $n$.
- **Tabla hash con encadenamiento:** un arreglo de $m$
  cubetas, donde cada cubeta es una lista enlazada como la del avance, y el número total de artículos n de toda la tabla. La función que decide en qué cubeta va cada código se describe en la sección 3.

Las operaciones son las mismas en las dos estructuras:

| Operación | Qué hace | Precondición |
|---|---|---|
| Agregar (id, nombre, cantidad) | Añade un producto al inventario, con su id, nombre y cantidad. Responde `ok` si se añadió, o `repetido` si el artículo ya estaba o `invalido` si se coloca una cantidad o codigo no positivos. | $\text{id} > 0$; nombre no vacío, sin espacios, de a lo sumo 63 caracteres (cabe en `char nombre[64]`); $\text{cantidad} > 0$ |
| Eliminar (id) | Quita el artículo con ese id del inventario. Responde `ok` si se eliminó, o `no existe` si no estaba. | Inventario no vacío ($n \geq 1$) e $\text{id} > 0$, ya que con el inventario vacío no hay nada que quitar. |
| Consultar (id) | Muestra el artículo con ese id: responde con su id, nombre y cantidad, o con `no existe` si no está. No modifica nada. |  Inventario no vacío ($n \geq 1$) e $\text{id} > 0$. |
| Reponer (id, cantidad) | Aumenta la cantidad de un artículo que ya está en el inventario. Responde `ok` si se repuso, o `no existe` si el artículo no está o `invalido` si se coloca una cantidad o codigo no positivos. | Inventario no vacío ($n \geq 1$), $\text{id} > 0$ y $\text{cantidad} > 0$, puesto que con cantidad negativa reponer restaría existencias. |
| Listar | Muestra todos los artículos del inventario, uno por línea. No modifica nada. | Ninguna. Con el inventario vacío no muestra nada. |

Las dos estructuras, y también el envoltorio de `std::unordered_map` que se usa como referencia, ofrecen las mismas operaciones con las mismas firmas, es decir la misma interfaz. 
Esto sucede debido a que el programa que mide los tiempos debe poder usar una u otra sin cambiar y si las interfaces fueran distintas, el programa de medición tendría que tratar cada estructura de forma diferente, y una diferencia en los tiempos podría deberse a ese código como tal y no a la estructura. Entonces, por esta razón, con una sola interfaz lo único que cambia entre una medición y otra es la estructura, y por eso las diferencias medidas pueden ser atribuidas a ella. 

Por otra parte, también ayuda al diseño puesto que, como cada cubeta de la tabla es una lista del avance, la tabla elige la cubeta con la función hash y delega en ella la operación.

Es justamente por lo anterior que las precondiciones realizadas en primer lugar valen para las dos estructuras. En la tabla, "inventario no vacío" significa $n \geq 1$ para toda la tabla, no para una cubeta: una cubeta puede estar vacía aunque la tabla no lo esté.

Lo único que si varía entre las estructuras es su construcción, ya que la tabla necesita el número de cubetas. 

**Casos especiales:**

- Si una precondición no se cumple, la estructura no se modifica. Con el inventario vacío, `ELIMINAR`, `CONSULTAR` responden `no existe`, como está en el enunciado, en cambio `REPONER` responde `invalido`.

- Para el nombre en agregar, si se pasa de 63 carácteres el programa trunca el sobrante, es decir, descarta todos los carácteres que no estén dentro de ese espacio de 63 y el resto de la palabra no afecta a las órdenes siguientes.

- Si `AGREGAR` o `REPONER` reciben un código o una cantidad que no son positivos, la orden responde `invalido` y no modifica la estructura. La respuesta es la misma en las dos estructuras y se menciona anteriormente en la tabla.

## 3. Análisis formal de complejidad

Una demostración por operación no trivial, en cuatro partes:

**Teorema.** (Enunciado con la cota.)

**Demostración.** Se procede de forma directa. (La estrategia.)

*Desarrollo.* (La cadena de desigualdades, con la justificación de cada
paso.)

$$T(n) = \ldots \leq c \cdot n^2 \quad \text{para todo } n \geq k$$

*Conclusión.* Por lo tanto, $T(n) \in O(n^2)$ con testigos $c = \ldots$
y $k = \ldots$

### Modelo de costo

Contamos operaciones elementales: cada comparación, asignación, operación
aritmética, evaluación de un `assert`, llamada a `free` y retorno cuesta una
unidad. Como en el avance, los nombres tienen longitud acotada (63
caracteres) y las operaciones sobre enteros cuestan una constante. $n$ es el
número de artículos guardados, $m$ el número de cubetas de la tabla,
$\alpha = n/m$ su factor de carga y $k_b$ el número de artículos de la cubeta
$b$.

Usamos la notación del avance: $v_i$ es el nodo en la posición $i$ y $c_i$ su
código, con $v_0 = \mathrm{cabeza}$. Por convención, $v_n = \mathrm{nullptr}$
y $v_{-1} = \mathrm{nullptr}$.

### Eliminar en la lista

`Lista::eliminar` avanza con dos punteros, `anterior` y `muerto`, hasta
encontrar el código o llegar al final. Si lo encuentra, reenlaza y libera el
nodo.

**Invariante del ciclo.** Cada vez que se evalúa la condición del `while`,
después de $j$ iteraciones completas:

$$
0 \le j \le n \quad\land\quad \mathrm{muerto} = v_j \quad\land\quad \mathrm{anterior} = v_{j-1} \quad\land\quad \forall i \in \{0,\ldots,j-1\},\ c_i \neq \mathrm{codigo}.
$$

Al empezar, $j = 0$: `muerto` es `cabeza` $= v_0$, `anterior` es
`nullptr` $= v_{-1}$, y el cuantificador recorre un conjunto vacío, así que se
cumple. Una iteración solo ocurre si $c_j \neq \mathrm{codigo}$, y avanza los
dos punteros una posición, así que el invariante se conserva con $j + 1$. La
cantidad $n - j$ disminuye en cada iteración y nunca es negativa, por lo que
el ciclo termina.

Al salir, o bien $\mathrm{muerto} = \mathrm{nullptr}$, entonces $j = n$ y por
el invariante ningún nodo tenía el código; o bien `muerto` es el nodo $v_j$
con $c_j = \mathrm{codigo}$ y `anterior` es justo $v_{j-1}$, el nodo que hay
que reenlazar.

**Efecto sobre los invariantes de la lista.** Si el código estaba en la
posición $p$, la lista queda con $n' = n - 1$ nodos:

$$
v'_i = v_i \ \text{ para } 0 \le i < p, \qquad v'_i = v_{i+1} \ \text{ para } p \le i < n - 1.
$$

Los nodos que quedan conservan su orden y sus enlaces, ningún código se
repite porque solo se quitó uno, y si $p = 0$ la nueva `cabeza` es $v_1$ (o
`nullptr` si la lista queda vacía). Por eso se siguen cumpliendo los tres
invariantes del avance.

**Teorema.** El tiempo de `Lista::eliminar` cumple
$T^{L}_{\text{elim}}(n) \in O(n)$.

**Demostración.** Se procede de forma directa: se cuentan las operaciones
antes del ciclo, en cada iteración y después del ciclo, y el número de
iteraciones se acota con el invariante.

*Desarrollo.* Antes del ciclo hay dos `assert` y dos asignaciones (`anterior`
y `muerto`): 4 unidades. Cada iteración evalúa las dos comparaciones de la
condición y hace dos asignaciones: 4 unidades. La evaluación final de la
condición cuesta a lo sumo 2. Después del ciclo, en el camino más largo
(código encontrado): calcular y asignar `encontrado` (2), el `if` (1), la
comparación de `anterior` con `nullptr` (1), el reenlace (1), `free` (1), la
resta y asignación de `n` (2) y el retorno (1): a lo sumo 9. Por el
invariante, $j \le n$:

$$
T^{L}_{\text{elim}}(n) \le 4 + 4j + 2 + 9 \le 4n + 15 \le 4n + 15n = 19n \quad \text{para todo } n \geq 1.
$$

El último paso usa que $15 \le 15n$ cuando $n \ge 1$.

*Conclusión.* Por lo tanto, $T^{L}_{\text{elim}}(n) \in O(n)$ con testigos
$c = 19$ y $k = 1$. La cota es ajustada: si el código no está, el ciclo hace
las $n$ iteraciones y $T^{L}_{\text{elim}}(n) \ge 4n$, así que el peor caso
es $\Theta(n)$. El mejor caso, el código en `cabeza`, es $O(1)$. El espacio
auxiliar es $O(1)$: dos punteros y un booleano.

### Eliminar en la tabla hash

`TablaHash::eliminar` calcula $b = h(\mathrm{codigo}) = \mathrm{codigo} \bmod m$,
revisa que la cubeta $b$ no esté vacía y delega en `Lista::eliminar` sobre esa
cubeta, que tiene $k_b$ artículos.

**Efecto sobre los invariantes de la tabla.** Sea $E \in \{0, 1\}$ igual a 1
si se eliminó el artículo. Al terminar:

$$
\mathrm{numeroArticulos}' = \mathrm{numeroArticulos} - E \quad\land\quad \mathrm{numeroArticulos}' = \sum_{i=0}^{m-1} k'_i \quad\land\quad \forall i \neq b,\ k'_i = k_i.
$$

Solo cambia la cubeta $b$, que pierde exactamente $E$ nodos, y el contador
baja solo cuando `cubeta.eliminar` devuelve `true`. Las demás cubetas no se
tocan, así que sigue cumpliéndose que todo nodo de la cubeta $i$ tiene código
$c$ con $h(c) = i$.

**Teorema (peor caso).** El tiempo de `TablaHash::eliminar` cumple
$T^{H}_{\text{elim}}(n) \in O(n)$.

**Demostración.** Se procede de forma directa: se cuenta el trabajo propio de
la tabla, que es constante, y se le suma el costo de `Lista::eliminar` sobre
una sola cubeta, que es el teorema anterior con $n$ cambiado por $k_b$.

*Desarrollo.* Las operaciones propias de la tabla son: dos `assert` (2), la
asignación de `eliminado` (1), `indice` (dos `assert`, el residuo, la
asignación y el retorno: 5), tomar la referencia a la cubeta (1), `vacia()`
de la cubeta (comparación y retorno: 2), la negación y el `if` (1), asignar
el resultado (1), el `if (eliminado)` (1), el decremento (2) y el retorno (1):
en total a lo sumo 17. Por el teorema anterior, `Lista::eliminar` sobre la
cubeta cuesta a lo sumo $4k_b + 15$, y una cubeta no puede tener más
artículos que toda la tabla, $k_b \le n$:

$$
T^{H}_{\text{elim}}(n) \le 17 + 4k_b + 15 \le 4n + 32 \le 4n + 32n = 36n \quad \text{para todo } n \geq 1.
$$

*Conclusión.* Por lo tanto, $T^{H}_{\text{elim}}(n) \in O(n)$ con testigos
$c = 36$ y $k = 1$. La cota se alcanza cuando todos los códigos caen en la
misma cubeta ($k_b = n$): la tabla se comporta como la lista. Es el
experimento «una cubeta» de la sección 4.

**Teorema (caso esperado).** Bajo la hipótesis de hashing uniforme (cada
código cae en cualquiera de las $m$ cubetas con probabilidad $1/m$, de forma
independiente de los demás), el tiempo esperado de `TablaHash::eliminar`
cumple $E\!\left[T^{H}_{\text{elim}}\right] \in O(1 + \alpha)$. Si además
$m \ge n$, entonces $E\!\left[T^{H}_{\text{elim}}\right] \in O(1)$.

**Demostración.** Se procede de forma directa: se acota el tamaño esperado de
la cubeta $b$ y se usa que la cota del costo es lineal en $k_b$.

*Desarrollo.* Si el código está en la tabla, la cubeta $b$ contiene ese
artículo y cada uno de los otros $n - 1$ con probabilidad $1/m$. Si no está,
contiene cada uno de los $n$ con probabilidad $1/m$. En los dos casos:

$$
E[k_b] \le 1 + \frac{n - 1}{m} \le 1 + \frac{n}{m} = 1 + \alpha.
$$

Como $T^{H}_{\text{elim}} \le 4k_b + 32$ y la esperanza es lineal:

$$
E\!\left[T^{H}_{\text{elim}}\right] \le 4\,E[k_b] + 32 \le 4(1 + \alpha) + 32 = 36 + 4\alpha \le 36(1 + \alpha).
$$

Si $m \ge n$, entonces $\alpha \le 1$ y

$$
E\!\left[T^{H}_{\text{elim}}\right] \le 36 + 4 = 40 \le 40 \cdot 1 \quad \text{para todo } n \geq 1.
$$

*Conclusión.* Por lo tanto, $E\!\left[T^{H}_{\text{elim}}\right] \in O(1 + \alpha)$
con testigos $c = 36$ y $k = 1$, y con $m \ge n$ (las configuraciones
$m \approx n$ y $m \approx 2n$ de los experimentos) es $O(1)$ con $c = 40$ y
$k = 1$. El espacio auxiliar es $O(1)$: la referencia a la cubeta, un booleano
y los dos punteros de `Lista::eliminar`. Este resultado coincide con el
análisis del encadenamiento en Cormen, Leiserson, Rivest y Stein,
*Introduction to Algorithms*, 4.ª edición, MIT Press, 2022, capítulo 11,
sección 11.2.

### Análisis de espacio

Sean $s_N$, $s_L$ y $s_H$ los tamaños en bytes de `Nodo`, `Lista` y
`TablaHash`, que el compilador fija y no dependen de $n$. En la máquina de los
experimentos, con `sizeof`: $s_N = 88$ (el `Producto` ocupa 80: 8 del código,
64 del nombre, 4 de la cantidad y 4 de relleno; más 8 del puntero), $s_L = 16$
y $s_H = 16$. Contamos los bytes que reserva cada estructura; el encabezado
que `malloc` agrega a cada bloque es otra constante por nodo y no cambia las
cotas.

**Teorema.** El espacio de la lista con $n \ge 1$ artículos cumple
$S^{L}(n) \in O(n)$.

**Demostración.** Se procede de forma directa: la lista guarda el objeto
`Lista` y exactamente un nodo por artículo.

*Desarrollo.*

$$
S^{L}(n) = s_L + s_N\, n = 16 + 88n \le 16n + 88n = 104n \quad \text{para todo } n \geq 1.
$$

*Conclusión.* Por lo tanto, $S^{L}(n) \in O(n)$ con testigos $c = 104$ y
$k = 1$. Como además $S^{L}(n) \ge 88n$, el espacio es $\Theta(n)$.

**Teorema.** El espacio de la tabla con $n$ artículos y $m$ cubetas cumple
$S^{H}(n, m) \in O(n + m)$; si $m \le 4n$, $S^{H}(n) \in O(n)$.

**Demostración.** Se procede de forma directa: la tabla guarda el objeto
`TablaHash`, el arreglo de $m$ objetos `Lista` (uno por cubeta, aunque esté
vacía) y un nodo por artículo.

*Desarrollo.*

$$
S^{H}(n, m) = s_H + s_L\, m + s_N\, n = 16 + 16m + 88n \le 104(n + m) \quad \text{para todo } n + m \geq 1.
$$

En los experimentos $m$ es 101, el primo $\ge n$ o el primo $\ge 2n$. Por el
postulado de Bertrand siempre hay un primo entre $2n$ y $4n$, así que en los
tres casos $m \le 4n$ (para $n \ge 26$ en el caso $m = 101$), y entonces

$$
S^{H}(n) \le 16 + 16 \cdot 4n + 88n = 152n + 16 \le 168n \quad \text{para todo } n \geq 1.
$$

*Conclusión.* Por lo tanto, $S^{H}(n, m) \in O(n + m)$ con testigos $c = 104$
y $k = 1$, y con $m \le 4n$ es $O(n)$ con $c = 168$ y $k = 1$. Frente a la
lista, la tabla gasta $16m$ bytes más: es el precio de tener cubetas vacías.

Para `map`, la biblioteca estándar de g++ (libstdc++) usa un árbol
rojo-negro: cada artículo ocupa un nodo con tres punteros y el color, más el
par clave-producto. También es $\Theta(n)$, con una constante por artículo
mayor que la de nuestros nodos.

Resumen de costos:

| Operación | Desde cero | De la biblioteca | Por qué |
|---|---|---|---|
| Eliminar, lista | $O(n)$ peor caso | $O(\log n)$ | La lista recorre hasta el nodo y su anterior; `map` baja por un árbol balanceado de altura $O(\log n)$. |
| Eliminar, tabla | $O(1 + \alpha)$ esperado, $O(n)$ peor caso | $O(\log n)$ | La tabla solo recorre la cubeta del código; si todos caen en la misma cubeta, recorre todos. |
| Espacio, lista | $\Theta(n)$ | $\Theta(n)$ | Un nodo por artículo. |
| Espacio, tabla | $\Theta(n + m)$ | $\Theta(n)$ | Un nodo por artículo más el arreglo de $m$ cubetas, aunque estén vacías. |

## 4. Experimentos

### 4.1 Pruebas de corrección

Antes de medir, verificamos que las dos estructuras respondan lo mismo con la
misma entrada. `make pruebas` corre cada caso de `datos/` con el programa de la
lista y con el de la tabla (1009 cubetas). Como `LISTAR` sale en orden
distinto en cada estructura, los casos con `LISTAR` tienen además un archivo
`nombre.tabla.out` con la salida esperada de la tabla.

Además de los casos del avance, agregamos tres casos pensados para la tabla:

| Caso | Tipo | Qué verifica |
|---|---|---|
| 07 | funcional | Eliminar con colisiones: 5, 1014 y 2023 caen en la cubeta 5; elimina en medio de la cadena, repite una eliminación y elimina un código cuya cubeta está vacía aunque la tabla no lo esté. |
| 08 | límite | Bordes del índice: 1009 (cubeta 0), 1008 (cubeta $m-1$) y 2018 (cubeta 0 otra vez); vacía la tabla, consulta y elimina sobre ella vacía y vuelve a agregar. |
| 09 | límite | Eliminar con códigos no positivos (`0` y `-5`) con el inventario lleno: responde `no existe` sin modificar nada. En la tabla esto evita un índice negativo, porque el residuo de un número negativo es negativo. Luego elimina los dos productos y repite una eliminación. |

Pendiente: pegar la salida de `make pruebas` cuando estén `consultar` y
`reponer` de la tabla.

### 4.2 Cómo se midió

**Máquina.** Pendiente: procesador, memoria RAM, sistema operativo y la
salida de `g++ --version`. Todas las mediciones se hicieron en esa misma
máquina, compilando con `g++ -Wall -Wextra -O2`.

**Qué se mide.** El programa `codigo/medir.cpp` toma $n$ códigos distintos y,
sobre una estructura vacía, mide por separado tres fases: agregar los $n$
artículos, consultarlos todos y eliminarlos todos. Las consultas y las
eliminaciones van en un orden aleatorio distinto al de inserción. Igual que
`principal.cpp`, la medición es una plantilla que solo usa la interfaz común,
y `main` construye la estructura. La columna `encontrados` cuenta las
consultas que respondieron que el artículo estaba y debe ser $n$: así
verificamos que cada estructura funciona mientras se mide.

**Entradas.** Los códigos se generan con semilla fija (2026), así que las tres
estructuras reciben exactamente la misma entrada:

- *Aleatorio:* $n$ códigos distintos al azar entre $1$ y $10^9$.
- *Una cubeta:* los códigos $m, 2m, \dots, nm$, que tienen residuo 0 y caen
  todos en la cubeta 0. Es el peor caso de la tabla.

**Configuraciones.** Para cada $n \in \{1000, 2000, 5000, 10000, 20000, 40000\}$
medimos: la lista; la tabla con $m = 101$ (tabla pequeña, $\alpha$ crece con
$n$), con $m$ el primo $\ge n$ ($\alpha \approx 1$) y con $m$ el primo
$\ge 2n$ ($\alpha \approx 1/2$); la tabla con todos los códigos en una cubeta;
y `map` como referencia.

**Repeticiones.** Cada configuración se mide 5 veces y se reporta la mediana,
que es menos sensible que el promedio a una repetición interrumpida por el
sistema operativo. Cada repetición corre en un proceso nuevo: si se repite
dentro del mismo programa, los nodos liberados al eliminar en desorden quedan
revueltos en la memoria dinámica, y desde la segunda repetición la lista
recibe nodos dispersos y se ve más lenta por cómo quedó la memoria, no por la
estructura.

### 4.3 Resultados

Pendiente: tablas de `agregar`, `consultar` y `eliminar` (en milisegundos)
y las gráficas `xychart-beta`.

## 5. Lo medido contra lo predicho

(¿Coincide la curva con la cota? Donde no coincida, expliquen por qué:
la constante oculta, la memoria caché, el crecimiento del vector.)

## 6. Conclusiones

(Cuál estructura conviene para este escenario y bajo qué condiciones
cambiaría la respuesta.)
