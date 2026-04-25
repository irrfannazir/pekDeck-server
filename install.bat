gcc src/server.c src/slib.c -I include -o pekServer -lws2_32
gcc client.c clib.c -o pekDeck -lws2_32