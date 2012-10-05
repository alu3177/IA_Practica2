# makefile programa P2

# Ficheros con codigo fuente
MAIN = main.cpp
SRCS =
INCS =
OBJS = main.o
EXEC = pract2
LIBS =

# Compilador y opciones
#
CC = g++
CFLAGS = -c -ansi -pedantic
CDEBUG = -g

# Reglas
#
default: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) -o $(EXEC) $(OBJS) $(LIBS)

$(OBJS): $(MAIN) $(SRCS) $(INCS)
	$(CC) $(CFLAGS) $(CDEBUG) $(MAIN) $(SRCS)

clean:
	rm -f $(OBJS) $(EXEC) core*.*

