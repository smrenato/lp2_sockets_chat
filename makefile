# VARIAVEIS
# depois eu termino

CC = gcc
PTHREAD = -pthead
LIB = 
OBJ = 
PATHSR = servidor/*.c 
PATHCL = cliente/*.c
NSR = sr
NCL = cl
OP = 


all: prog

prog: sr cl
# Compila ambos

sr: servidor
    echo "Gerando Objetos \n"
    $(CC) $(PTHREAD) $(OP) -c $(PATHSR)
    mkdir objsr
    mov *.o objsr
    $(CC) $(PTHREAD) $(OP) objsr -o sr
    rm -r objsr

        
cl: cliente
    $(CC) $(PTHREAD) $(OP) -c $(PATHCL) 
