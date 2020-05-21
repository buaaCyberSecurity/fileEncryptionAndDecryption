CC = g++
CFLAGS = -lssl -lcrypto

rec:main.o receiver.o
	$(CC) -o send main.o sender.o $(CFLAGS)
main.o:main.cpp
	$(CC) -c main.cpp $(CFLAGS)
receiver.o:sender.cpp
	$(CC) -c sender.cpp $(CFLAGS)
clean:
	rm send main.o sender.o
