CC = g++
CFLAGS = -lssl -lcrypto

rec:main.o receiver.o aes.o
	$(CC) -o rec main.o receiver.o aes.o $(CFLAGS)
main.o:main.cpp
	$(CC) -c main.cpp $(CFLAGS)
receiver.o:receiver.cpp
	$(CC) -c receiver.cpp $(CFLAGS)
aes.o:aes.cpp
	$(CC) -c aes.cpp $(CFLAGS)
clean:
	rm rec main.o receiver.o aes.o
