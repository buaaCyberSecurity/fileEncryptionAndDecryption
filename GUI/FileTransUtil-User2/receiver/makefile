CC = g++
CFLAGS = -lssl -lcrypto

rec:main.o receiver.o
	$(CC) -o rec main.o receiver.o $(CFLAGS)
main.o:main.cpp
	$(CC) -c main.cpp $(CFLAGS)
receiver.o:receiver.cpp
	$(CC) -c receiver.cpp $(CFLAGS)
clean:
	rm rec main.o receiver.o
