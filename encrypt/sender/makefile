CC = g++
CFLAGS = -lssl -lcrypto

send:main.o sender.o aes.o
	$(CC) -o send main.o sender.o aes.o $(CFLAGS)
main.o:main.cpp
	$(CC) -c main.cpp $(CFLAGS)
sender.o:sender.cpp
	$(CC) -c sender.cpp $(CFLAGS)
aes.o:aes.cpp
	$(CC) -c aes.cpp $(CFLAGS)
clean:
	rm send main.o sender.o aes.o
