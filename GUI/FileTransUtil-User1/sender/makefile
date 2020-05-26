CC = g++
CFLAGS = -lssl -lcrypto -std=c++11

send:main.o sender.o aes.o rsa.o SHA256.o
	$(CC) -o send main.o sender.o aes.o rsa.o SHA256.o $(CFLAGS)
main.o:main.cpp
	$(CC) -c main.cpp $(CFLAGS)
sender.o:sender.cpp
	$(CC) -c sender.cpp $(CFLAGS)
aes.o:aes.cpp
	$(CC) -c aes.cpp $(CFLAGS)
rsa.o:rsa.cpp
	$(CC) -c rsa.cpp $(CFLAGS)
SHA256.o:SHA256.cpp
	$(CC) -c SHA256.cpp $(CFLAGS)
clean:
	rm send main.o sender.o aes.o rsa.o SHA256.o
