# Compilación del proyecto. Ajuste FUENTES con los archivos que escriba.
CC      = g++
CFLAGS  = -Wall -Wextra -O2
FUENTES = principal.cpp lista.cpp
PROGRAMA = proyecto

all: $(PROGRAMA)

$(PROGRAMA): $(FUENTES)
	$(CC) $(CFLAGS) $(FUENTES) -o $(PROGRAMA)

# Corre cada entrada de ../datos/ y compara con su salida esperada
pruebas: $(PROGRAMA)
	@for entrada in ../datos/*.in; do \
	  esperada="$${entrada%.in}.out"; \
	  if [ -f "$$esperada" ]; then \
	    ./$(PROGRAMA) < "$$entrada" > /tmp/salida.txt; \
	    if diff -q --strip-trailing-cr /tmp/salida.txt "$$esperada" > /dev/null; then \
	      echo "  OK   $$(basename $$entrada)"; \
	    else \
	      echo "  FALLA $$(basename $$entrada)"; \
	      diff --strip-trailing-cr /tmp/salida.txt "$$esperada" | head -5; \
	    fi; \
	  fi; \
	done

clean:
	rm -f $(PROGRAMA) *.o

.PHONY: all pruebas clean
