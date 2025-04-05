all: sender receiver

sender: sender.o
	gcc -o sender sender.o

receiver: receiver.o
	gcc -o receiver receiver.o

receiver.o: receiver.c
	gcc -c receiver.c -o receiver.o -W -Wall -ansi -pedantic

sender.o: sender.c
	gcc -c sender.c -o sender.o -W -Wall -ansi -pedantic

clean:
	rm -rf *.o sender receiver
