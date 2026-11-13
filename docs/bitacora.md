# Bitácora

Va en `docs/`, como los informes.

Una entrada por sesión de trabajo, con la fecha, quién trabajó, qué se
hizo y qué quedó pendiente. La entrada más reciente va arriba.

## 2026 - 11 - 13 — Informe final

- Quiénes: Paula Bonilla Leon, código 9038204.
- Qué hicimos: Completé, con apoyo de ChatGPT/Codex, el análisis de `consultar`, `reponer`, `agregar` y `listar` en la sección 3 del informe final. Añadí las demostraciones para la lista enlazada y la tabla hash y actualicé el resumen de costos.
- Qué quedó pendiente: Subir mi rama y revisar con el grupo las pruebas integradas y las mediciones de la entrega final.

## 2026 - 11 - 13 — Programación de la tabla hash

- Quiénes: Paula Bonilla Leon, código 9038204.
- Qué hicimos: Implementé `consultar` y `reponer` en `codigo/tablahash.cpp`. Ambas funciones verifican que la cubeta tenga productos antes de buscar en ella. Compilé la versión de tabla hash y ejecuté `03_consultar_reponer`; `fc` no encontró diferencias con la salida esperada. Guardé el código en el commit `5be5e80`.
- Qué quedó pendiente: Completar la sección 3 del informe y ejecutar las demás pruebas del grupo.


- Quiénes: Jerónimo Hurtado Mora, código 9038219
- Qué hicimos: Agregué los casos de prueba de la tabla en `datos/`: el 07 (eliminar con colisiones: 5, 1014 y 2023 caen en la misma cubeta; elimina en medio de la cadena, repite una eliminación y elimina un código cuya cubeta está vacía), el 08 (bordes del índice: cubeta 0, cubeta m-1, vaciar la tabla y volver a agregar) y el 09 (eliminar con códigos no positivos, que en la tabla evitaría un índice negativo). Los tres pasan con la lista. También escribí en la sección 3 del informe final el modelo de costo, el análisis formal de eliminar en la lista y en la tabla hash (con invariante del ciclo, testigos c y k y caso esperado) y el análisis de espacio, y en la sección 4 las pruebas de corrección y cómo se mide.
- Qué quedó pendiente: Los `.csv` de medición (`mediciones.csv` y `mediciones-crudas.csv`), que se generan con el medidor cuando estén `consultar` y `reponer` de la tabla y el envoltorio de `map`; con ellos, las tablas y gráficas de la sección 4, el contraste de la sección 5 y las conclusiones. Falta también actualizar el Makefile para compilar `proyecto_tabla` y `medidor`.

## 2026 - 11 - 12
- Quiénes: Jerónimo Hurtado Mora, código 9038219
- Qué hicimos: Escribí `eliminar` en `tablahash.cpp`: calcula la cubeta con `indice`, revisa que la cubeta no esté vacía (porque `Lista::eliminar` exige una lista no vacía), delega en el `eliminar` de la lista y actualiza `numeroArticulos`, con su documentación de costo. Volví genérico `principal.cpp`: el ciclo de órdenes pasó a la plantilla `procesar`, que recibe la estructura por referencia, y `main` construye una `Lista`, una `TablaHash` o un `Mapa` según la bandera de compilación. Agregué `medir.cpp`, que mide agregar, consultar y eliminar con códigos generados con semilla fija, con tres tamaños de tabla y un modo con todos los códigos en una cubeta.
- Qué quedó pendiente: Los casos de prueba de la tabla, el análisis formal de eliminar y de espacio, y los experimentos.

## 2026 - 11 - 12
- Quiénes: Juan Manuel Paredes, codigo 9034283
- Qué hicimos: Actualice tablahash.cpp y principal.cpp con los comentarios hechos por el profe e hice las partes 1 y 2 del informe final-
- Qué quedó pendiente: Las funciones faltantes de `tablahash.cpp`y las partes 3, 4, 5 y 6 del informe final.

## 2026 - 11 - 10
- Quiénes: Juan Manuel Paredes, codigo 9034283
- Qué hicimos: Comencé con la primera parte del código de la sección final, es decir, la tabla hash, realice el `tablahash.h` y agregar y listar, con el constructor, el destructor y una funcion auxiliar en `tablahash.cpp`, con sus respectivos comentarios.
- Qué quedó pendiente: Las funciones faltantes de `tablahash.cpp`y comenzar con el informe final.

## 2026 - 11 - 01
- Quiénes: Jerónimo Hurtado Mora, código 9038219
- Qué hicimos: Terminé de actualizar el informe del avance. Reescribí la sección 5 con los seis casos de prueba y sus salidas obtenidas con `make pruebas`, escribí la sección 4 (qué medir: variar el número de productos, medir el tiempo de las consultas y separar el tiempo de construcción) y quité los textos de borrador y pendientes de las secciones 2 y 3.
- Qué quedó pendiente: Hacer las mediciones de la sección 4.

## 2026 - 10 - 30
- Quiénes: Juan Manuel Paredes, codigo 9034283
- Qué hicimos: Realicé los casos pruebas, colocandolos en la carpetas `datos/`, con el del enunciado, los propuestos y dos limite, corri make y todo dio ok, por lo que el codigo ya quedó terminado y compila perfecto sin advertencias.
- Qué quedó pendiente: Terminar de escribir y revisar por completo el informe-avance, con los respectivos casos de prueba y demás.

## 2026 - 10 - 29
- Quiénes: Juan Manuel Paredes, codigo 9034283
- Qué hicimos: Coloque las precondiciones correctas con assert, y termine de corregir todo lo que estuviera mal en todos los archivos, para que todo tenga coherencia, ademas arreglé documentanción y las precondiciones en el informe.
- Qué quedó pendiente: Realizar las respectivas pruebas para comprobar fallos o advertencias y agregarlo a README.md de la carpeta `docs/`.

## 2026 - 10 - 28
- Quiénes: Jerónimo Hurtado Mora, código 9038219
- Qué hicimos: Escribí `eliminar` en `lista.cpp` (casos primero, intermedio, último y lista vacía) y `principal.cpp`, que lee las órdenes, llama a la lista y escribe las respuestas. 
- Qué quedó pendiente: Realizar las respectivas pruebas para comprobar fallos o advertencias y agregarlo a README.md de la carpeta `docs/`

## 2026 - 10 - 28
- Quiénes: Juan Manuel Paredes, codigo 9034283
- Qué hicimos: Escribí lista.h con sus respectivas funciones, junto al struct Nodo y Producto, además de colocar las funciones de agregar y listar en lista.cpp. 
- Qué quedó pendiente: Realizar las respectivas pruebas para comprobar fallos o advertencias y agregarlo a README.md de la carpeta `docs/`.

## 2026 - 10 - 27

- Quiénes: Paula Bonilla Leon, código 9038204.
- Qué hicimos: Escribí mi parte del código en `codigo/lista.cpp`: `buscar` (recorrido lineal interno), `consultar` y `reponer`. Preparé el caso funcional 2 (`consultar_reponer.in` y `.out`) y registré su salida obtenida en el informe del avance. Probé con un banco local y piezas provisionales: salida igual a la esperada, sin advertencias con `-Wall -Wextra` y sin errores con AddressSanitizer.
- Qué quedó pendiente: Integrar con `lista.h`, `eliminar` y `principal.cpp` de los compañeros (ajustar nombres si difieren); agregar `lista.cpp` a `FUENTES` del Makefile; correr `make pruebas` con el programa completo, registrar la salida real y subir los cambios con mi cuenta.

## 2026 - 10 - 22

- Quiénes: Juan Manuel Paredes, codigo 9034283
- Qué hicimos: Avancé con el README.MD y el informe-avance.md pensando en las operaciones necesario y que debemos tener listo para empezar a codificar.
- Qué quedó pendiente: La codificación de la estructura y las operaciones.

## 2026 - 10 - 22

- Quiénes: Paula Bonilla Leon, código 9038204.
- Qué hicimos: Trabaje en el borrador de la sección 3 del informe del avance, explicando la lista enlazada simple, su justificación y los costos de las operaciones del inventario. Revisamos el diagrama y preparamos las entradas y salidas esperadas de los casos de prueba.
- Qué quedó pendiente: Confirmar el libro guía, revisar el borrador con el grupo, implementar buscar, consultar y reponer, e integrar las funciones con las de los compañeros. Ejecutar las pruebas con el programa completo y registrar las salidas obtenidas.
