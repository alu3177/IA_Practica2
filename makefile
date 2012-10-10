# makefile programa P2

CC = g++
CFLAGS = -ansi -pedantic
CDEBUG = -g
OBJS = main.o matriz.o problema.o
MAIN = pract2
EXEC = pract2

MAIN: $(OBJS)
	$(CC) $(CDEBUG) $(CFLAGS) -o $(EXEC) $^

main.o: main.cpp
	$(CC) $(CDEBUG) $(CFLAGS) -c $<

matriz.o: lib/matriz.cpp lib/matriz.h
	$(CC) $(CDEBUG) $(CFLAGS) -c $<

problema.o: lib/problema.cpp lib/problema.h
	$(CC) $(CDEBUG) $(CFLAGS) -c $<


.PHONY: clean

clean:
	rm -f $(OBJS) $(EXEC) $@

