CC = g++
CFLAGS = -lssl -lcrypto -std=c++11

sha256:main.o SHA256.o
	$(CC) -o sha256 main.o SHA256.o $(CFLAGS)
main.o:main.cpp
	$(CC) -c main.cpp $(CFLAGS)
SHA256.o:SHA256.cpp
	$(CC) -c SHA256.cpp $(CFLAGS)
clean:
	rm sha256 main.o SHA256.o
