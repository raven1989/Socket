all: server client
	@echo DONE

server: Server.cpp
	g++ Server.cpp -o server

client: Client.cpp
	g++ Client.cpp -o client

run: server
	./server &

clean:
	@rm -f *.o server client
