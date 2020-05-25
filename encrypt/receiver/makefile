CC = g++
CFLAGS = -lssl -lcrypto -std=c++11

receiver:main.o receiver.o aes.o rsa.o
	$(CC) -o receiver main.o receiver.o aes.o rsa.o $(CFLAGS)
main.o:main.cpp
	$(CC) -c main.cpp $(CFLAGS)
receiver.o:receiver.cpp
	$(CC) -c receiver.cpp $(CFLAGS)
aes.o:aes.cpp
	$(CC) -c aes.cpp $(CFLAGS)
rsa.o:rsa.cpp
	$(CC) -c rsa.cpp $(CFLAGS)
clean:
	rm receiver main.o receiver.o aes.o rsa.o
