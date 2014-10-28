all: server client
	@echo DONE

server: Server.cpp
	g++ Server.cpp -o server.out

client: Client.cpp
	g++ Client.cpp -o client.out

run: server
	./server &

clean:
	@rm -f *.o server.out client.out
