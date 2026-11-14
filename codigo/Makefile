# Compilación del proyecto.
# principal.cpp se compila una vez por estructura: sin bandera sale el programa
# con la lista, con -DUSAR_TABLA el de la tabla hash y con -DUSAR_MAPA el de
# std::map (solo si ya existe mapa.h, el envoltorio con las mismas firmas).
CC      = g++
CFLAGS  = -Wall -Wextra -O2
FUENTES = principal.cpp lista.cpp tablahash.cpp $(wildcard mapa.cpp)
ENCABEZADOS = lista.h tablahash.h $(wildcard mapa.h)
PROGRAMAS = proyecto_lista proyecto_tabla $(if $(wildcard mapa.h),proyecto_mapa)
# Tamanos y repeticiones de los experimentos (make medir)
TAMANOS = 1000 2000 5000 10000 20000 40000
REPETICIONES = 5
MEDICIONES = ../datos/mediciones.csv
CRUDAS = ../datos/mediciones-crudas.csv

all: $(PROGRAMAS) medidor

proyecto_lista: $(FUENTES) $(ENCABEZADOS)
	$(CC) $(CFLAGS) $(FUENTES) -o proyecto_lista

proyecto_tabla: $(FUENTES) $(ENCABEZADOS)
	$(CC) $(CFLAGS) -DUSAR_TABLA $(FUENTES) -o proyecto_tabla

proyecto_mapa: $(FUENTES) $(ENCABEZADOS)
	$(CC) $(CFLAGS) -DUSAR_MAPA $(FUENTES) -o proyecto_mapa

# Programa de medicion. Si existe mapa.h (el envoltorio de std::map), medir.cpp
# lo incluye solo; por eso se agrega a las dependencias con wildcard.
medidor: medir.cpp lista.cpp tablahash.cpp $(ENCABEZADOS) $(wildcard mapa.cpp)
	$(CC) $(CFLAGS) medir.cpp lista.cpp tablahash.cpp $(wildcard mapa.cpp) -o medidor

# Corre todos los experimentos. Cada medicion es un proceso nuevo (ver el
# comentario de medir.cpp); las REPETICIONES quedan en ../datos/mediciones-crudas.csv
# y en ../datos/mediciones.csv queda la mediana de cada configuracion.
# Para cada tamano: la lista, la tabla con tres numeros de cubetas, la tabla con
# todos los codigos en la misma cubeta y, si existe, el mapa.
medir: medidor
	@echo "estructura,cubetas,modo,n,agregar_ms,consultar_ms,eliminar_ms,encontrados" > $(CRUDAS)
	@for n in $(TAMANOS); do \
	  echo "  midiendo n = $$n"; \
	  r=1; \
	  while [ $$r -le $(REPETICIONES) ]; do \
	    ./medidor lista $$n cercana aleatorio >> $(CRUDAS); \
	    for t in chica cercana grande; do \
	      ./medidor tabla $$n $$t aleatorio >> $(CRUDAS); \
	    done; \
	    ./medidor tabla $$n cercana colision >> $(CRUDAS); \
	    if [ -f mapa.h ]; then ./medidor mapa $$n cercana aleatorio >> $(CRUDAS); fi; \
	    r=$$((r + 1)); \
	  done; \
	done
	@awk -F, '{ gsub(/\r/, "") } \
	NR == 1 { print; next } \
	{ c = $$1 "," $$2 "," $$3 "," $$4; if (!(c in cuenta)) orden[++k] = c; q = ++cuenta[c]; \
	  for (o = 1; o <= 3; o++) v[c, o, q] = $$(4 + o); enc[c] = $$8 } \
	END { for (i = 1; i <= k; i++) { c = orden[i]; r = cuenta[c]; f = c; \
	  for (o = 1; o <= 3; o++) { \
	    for (a = 1; a <= r; a++) x[a] = v[c, o, a] + 0; \
	    for (a = 2; a <= r; a++) { t = x[a]; b = a - 1; while (b >= 1 && x[b] > t) { x[b + 1] = x[b]; b-- } x[b + 1] = t } \
	    f = f "," sprintf("%.3f", x[int((r + 1) / 2)]) } \
	  print f "," enc[c] } }' $(CRUDAS) > $(MEDICIONES)
	@echo "  listo: $(MEDICIONES)"

# Convierte ../datos/mediciones.csv en las tablas de Markdown y las graficas
# xychart-beta del informe, para copiarlas sin pasar los numeros a mano.
tablas:
	@awk -F, '{ gsub(/\r/, "") } \
	NR > 1 { n = $$4; if (!(n in visto)) { visto[n] = 1; ns[++k] = n } \
	  s = $$1; \
	  if (s == "tabla") { if ($$3 == "colision") s = "colision"; else if ($$2 == 101) s = "chica"; else if ($$2 < 2 * n) s = "cercana"; else s = "grande" } \
	  hay[s] = 1; for (o = 1; o <= 3; o++) v[o, s, n] = $$(4 + o) } \
	END { split("agregar consultar eliminar", op, " "); \
	  split("lista chica cercana grande colision mapa", se, " "); \
	  nom["lista"] = "lista"; nom["chica"] = "tabla $$m=101$$"; nom["cercana"] = "tabla $$m \\approx n$$"; \
	  nom["grande"] = "tabla $$m \\approx 2n$$"; nom["colision"] = "tabla, una cubeta"; nom["mapa"] = "`map`"; \
	  corto["lista"] = "lista"; corto["colision"] = "una cubeta"; corto["chica"] = "m=101"; \
	  corto["cercana"] = "m~n"; corto["grande"] = "m~2n"; corto["mapa"] = "map"; \
	  for (o = 1; o <= 3; o++) { \
	    print "**" op[o] " (ms, mediana de las repeticiones)**"; print ""; \
	    f = "| $$n$$ |"; g = "|---|"; \
	    for (i = 1; i <= 6; i++) if (se[i] in hay) { f = f " " nom[se[i]] " |"; g = g "---|" } \
	    print f; print g; \
	    for (j = 1; j <= k; j++) { f = "| " ns[j] " |"; for (i = 1; i <= 6; i++) if (se[i] in hay) f = f " " v[o, se[i], ns[j]] " |"; print f } \
	    print "" } \
	  eje = "["; for (j = 1; j <= k; j++) eje = eje (j > 1 ? ", " : "") ns[j]; eje = eje "]"; \
	  split("lista colision chica|cercana grande mapa", grupo, "|"); \
	  split("lentas|rapidas", gnom, "|"); \
	  for (o = 2; o <= 3; o++) for (gi = 1; gi <= 2; gi++) { \
	    split(grupo[gi], miembros, " "); lin = ""; \
	    for (i = 1; i <= 3; i++) if (miembros[i] in hay) lin = lin (lin == "" ? "" : ", ") corto[miembros[i]]; \
	    print "```mermaid"; print "xychart-beta"; \
	    print "  title \"" op[o] ": estructuras " gnom[gi] ": " lin " (en ese orden)\""; \
	    print "  x-axis \"n\" " eje; print "  y-axis \"milisegundos\""; \
	    split(grupo[gi], miembros, " "); \
	    for (i = 1; i <= 3; i++) if (miembros[i] in hay) { f = "  line ["; for (j = 1; j <= k; j++) f = f (j > 1 ? ", " : "") v[o, miembros[i], ns[j]]; print f "]" } \
	    print "```"; print "" } }' $(MEDICIONES)

# Corre cada entrada de ../datos/ con cada programa y compara con la salida
# esperada. Como LISTAR sale en orden distinto en cada estructura, si existe
# nombre.tabla.out (o nombre.mapa.out) ese programa se compara contra ese
# archivo; si no, todos se comparan contra nombre.out.
pruebas: $(PROGRAMAS)
	@for programa in $(PROGRAMAS); do \
	  tipo="$${programa#proyecto_}"; \
	  for entrada in ../datos/*.in; do \
	    base="$${entrada%.in}"; \
	    esperada="$$base.out"; \
	    if [ -f "$$base.$$tipo.out" ]; then esperada="$$base.$$tipo.out"; fi; \
	    if [ -f "$$esperada" ]; then \
	      ./$$programa < "$$entrada" > /tmp/salida.txt; \
	      if diff -q --strip-trailing-cr /tmp/salida.txt "$$esperada" > /dev/null; then \
	        echo "  OK    $$tipo  $$(basename $$entrada)"; \
	      else \
	        echo "  FALLA $$tipo  $$(basename $$entrada)"; \
	        diff --strip-trailing-cr /tmp/salida.txt "$$esperada" | head -5; \
	      fi; \
	    fi; \
	  done; \
	done

clean:
	rm -f proyecto_lista proyecto_tabla proyecto_mapa medidor proyecto *.o

.PHONY: all pruebas medir tablas clean