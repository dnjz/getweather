CC = gcc
CFLAGS = -Wall -g 
CFLAGS = -pthread


all: server client

client: client.o trabalho3_SO.o errorUtils.o
	$(CC) -o $@ $^

client.o: client.c trabalho3_SO.h
	$(CC) $(CFLAGS) -c -o $@ $<

server: server.o trabalho3_SO.o trabalho2_SO.o errorUtils.o -lpthread
	$(CC) -o $@ $^

server.o: server.c trabalho3_SO.h 
	$(CC) $(CFLAGS) -c -o $@ $<

trabalho3_SO: trabalho3_SO.o errorUtils.o
	$(CC) $(CFLAGS) -c -o $@ $<

trabalho3_SO.o: trabalho3_SO.c trabalho3_SO.h
	$(CC) $(CFLAGS) -c -o $@ $<

trabalho2_SO: trabalho2_SO.c trabalho2_SO.h
	$(CC) $(CFLAGS) -c -o $@ $<

errorUtils.o: errorUtils.c errorUtils.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o $(BIN)




	

