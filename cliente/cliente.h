#ifndef __CLIENTE_H
#define __CLIENTE_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>


#define TAM_APELIDO 50
#define TAM_IP 15
#define BUFFER 140


int InterfaceConcexao(uint16_t *porta, const char* endereco_ip, char* apelido_cliente);

int InicializaClienteTCP(uint16_t porta, char* endereco_ip);

int StrtoIP(char *str, int tamanho, char *ip );


#endif