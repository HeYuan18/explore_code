all: server client
server: ./demo/server.c
	gcc ./demo/server.c ./demo/server.h ./demo/stdfx.h -o server
client: ./demo/client.c
	gcc ./demo/client.c ./demo/client.h ./demo/stdfx.h -o client
#.PHONY:clean
clean:
	rm -f server client
