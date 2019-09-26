# VARIAVEIS
# SERVIDOR

NOME = sr
CC = gcc
PT = -pthread
FILES = sr_tcp.c servidor.c servidor.h
OP = 


all: sr
	./$(NOME)

sr: $(FILES)
	$(CC) $(OP) $(PT) $(FILES) -o $(NOME)
d:
	rm -r $(NOME)