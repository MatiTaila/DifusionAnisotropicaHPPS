CC=gcc
CFLAGS=-Wall -ansi -c -O0 -ggdb

difusionAnisotropica: ipol_anisotropica.o imagen.o ../src/imagen.h
	$(CC) ipol_anisotropica.o imagen.o -o difusionAnisotropica

ipol_anisotropica.o: ../src/ipol_anisotropica.c
	$(CC) $(CFLAGS) ../src/ipol_anisotropica.c

imagen.o: ../src/imagen.c
	$(CC) $(CFLAGS) ../src/imagen.c

clean: 
	rm -f ./*.o