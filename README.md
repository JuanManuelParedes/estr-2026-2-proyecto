# Proyecto — Estructuras de Datos 2026-2

Repositorio base del proyecto del curso. El proyecto se hace en
**grupos de hasta tres estudiantes**, con un repositorio por grupo:
**haga fork de este repositorio** y trabajen sobre esa copia.

El enunciado completo está en la página del curso:
<https://cardel.github.io/notasUniversidad/2026-II/Estructuras%20de%20Datos/Proyecto/Proyecto%20del%20curso/>

## Integrantes del grupo

Reemplacen esta tabla con sus datos. **Si falta el archivo, o le falta
el nombre, el código o el correo de algún integrante, la entrega pierde
el 20 % de la nota**; quien no aparezca aquí no cuenta como integrante y
su nota del proyecto es 0.0.

| Nombre completo | Código | Correo institucional | Usuario de GitHub |
|---|---|---|---|
| Paula Bonilla Leon  | 9038204 | paula1905@javerianacali.edu.co | paulabonillaleon-ctrl |
|Jerónimo Hurtado Mora  | 9038219 | Jhurtadom@javerianacali.edu.co | jhurtadomora |
| Juan Manuel Paredes Betancourt | 9034283 | juanmaparedesb@javerianacali.edu.co | JuanManuelParedes |

**Escenario escogido:** A - Inventario 

- Estructura escrita desde cero: Lista Enlazada simple y Tablas Hash
- Estructura de la biblioteca contra la que se compara: std::forward_list y std::unordered_map

## Lo primero

1. Un integrante hace fork de este repositorio con el botón **Fork**.
   El fork queda público y las dos entregas se hacen sobre él.
2. En **Settings › Collaborators** agrega a los demás integrantes, para
   que cada uno confirme con su propia cuenta.
3. Llenan la tabla de arriba.

## Fechas

| Entrega | Cierre | Vale |
|---|---|---|
| Avance | viernes 30 de octubre de 2026 | 10 % del curso |
| Final | lunes 16 de noviembre de 2026, 23:59 | 20 % con la sustentación |

Se califica el último commit anterior a la hora de cierre; lo que se
suba después no se tiene en cuenta. La historia de commits cuenta
doble: dice si hubo avance y dice quién hizo qué. Los cambios tienen
que ser significativos: los de puro formato o de comentarios no cuentan.

## Reglas del repositorio

1. **Solo archivos de texto plano**: `.c`, `.cpp`, `.h`, `.md`, `.in`,
   `.out`, `.csv` y el `Makefile`. Nada de comprimidos ni binarios
   —`.pdf`, `.docx`, `.xlsx`, ejecutables, imágenes—. Lo que produce la
   compilación se ignora con `.gitignore`.
2. Las **primeras líneas de cada archivo de código** llevan los autores:
   `// Autores: Nombre1 Codigo1, Nombre2 Codigo2`
3. Los **informes van en Markdown** dentro de `docs/`, con los nombres
   `informe-avance.md` e `informe-final.md`.
4. La **notación matemática** se escribe en LaTeX dentro del Markdown,
   con `$...$` y `$$...$$`: las cotas, los testigos y los invariantes
   van así. Nada de imágenes de fórmulas.
5. **Todos los diagramas** —nodos y punteros, árboles, tablas con sus
   colisiones, trazas y la gráfica de los tiempos— se hacen con
   **Mermaid** dentro del Markdown. La gráfica de los experimentos usa
   `xychart-beta`.

Guías de GitHub:
[Markdown](https://docs.github.com/es/get-started/writing-on-github/getting-started-with-writing-and-formatting-on-github/basic-writing-and-formatting-syntax) ·
[matemáticas](https://docs.github.com/es/get-started/writing-on-github/working-with-advanced-formatting/writing-mathematical-expressions) ·
[Mermaid](https://docs.github.com/en/get-started/writing-on-github/working-with-advanced-formatting/creating-diagrams)

## Qué va en cada carpeta

| Carpeta | Qué contiene |
|---|---|
| `docs/` | `informe-avance.md`, `informe-final.md` y `bitacora.md` |
| `codigo/` | las fuentes en C o C++ y el `Makefile` |
| `datos/` | las entradas de prueba y las mediciones de los experimentos |

## Cómo se compila

Desde `codigo/`:

```bash
make            # produce los ejecutables
make pruebas    # corre los casos de prueba
make clean
```

El código se compila con `gcc -Wall -Wextra` o `g++ -Wall -Wextra` sin
advertencias, usa solo la biblioteca estándar, no lleva `break`,
`continue` ni `goto`, tiene un solo `return` al final de cada función y
libera toda la memoria que reserva.
