CC=gcc
CFLAGS=-c -Wall

all:	main.o iface.o
	$(CC) main.o iface.o -o teste

iface.o:	iface.c
		$(CC) $(CFLAGS) iface.c

main.o:		main.c
		$(CC) $(CFLAGS) -c main.c

clean:
	rm *.o
