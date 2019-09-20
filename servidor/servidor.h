#ifndef __SERVER_H_
#define __SERVER_H_

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



// Structs 
typedef struct log_servidor
{
    int porta;
    int socket_cliente;
    char* mensagem;
    char* envento_servidor;
    char* error_servidor;
    /* data */
}log_servidor_t;

typedef struct parametros
{
    int numero_total_clientes;
    int *socket_cliente;
    int cliente_atual;
    /* data */
}param_t;



// ==========================================================================================
// int InterfaceConcexao(void);
/*
Parametros: 

    porta -> Porta de conexão servidor

Retorno:
    retorna 0;   

*/

int InterfaceConcexao(uint16_t *porta);



//===========================================================================================
//int* ClientesConectados ();
/*
Parametros: 

    socket_clientes_conectados -> array de interios que representa cada socket de cada novo cliente
    num_clientes_atuais -> numero de clinetes atualmente conectados

Retorno:
    retorna 0 se sem sucedido    

*/
int  ClientesConectados(int *ar_socket_clientes_conectados, int *num_clientes_atuais, int* novo_cliente);





//===========================================================================================
//int LogServidor();
/*
Parametros: 
    
    
 
Retorno:
       

*/

int LogServidor();



//===========================================================================================
//void* RespostaCliente(void * parametros);
/*
Parametros: 

    parametros -> Vai conter a informação do socket dos clinets

Retorno:
    retorna o valor padrão de uma thread

*/


void* RespostaCliente(void* param);


//===========================================================================================
//int InicializaServidor();
/*
Parametros: 

    porta_conexao -> numero da porta do servidor
    fila_conexão -> numero maximo de conexão em espera
    sr_enderessamento --> enderessamneto de servidor 

Retorno:
    Se bem sucedido, retorna  um file dercriptor do servidor
*/

int InicializaServidorTCP(uint16_t porta_conexao, int fila_conexao, struct sockaddr_in* sr_enderessamento);


//===========================================================================================
// IGNORAR
//pthread_t** NovoCliente();
/*
Parametros: 

    **ar_threads_clientes -> array de ponteiros para thread_t, representa os clientes conectados
    *num_clientes_atual -> Numero atua de clinets conectados

Retorno:
    Se bem sucedido, retorna o **ar_threads_clientes
*/


pthread_t** NovaThreadCliente(pthread_t **ar_threads_clientes, int *num_clientes_atual);


#endif
