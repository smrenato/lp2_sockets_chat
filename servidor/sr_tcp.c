#include <stdio.h>
#include "servidor.h"

#define FILA_CONEXAO 5
#define ACCEPT_ERROR -1
#define BUFF 140

int main(int argc, char const *argv[])
{
    uint16_t porta = 0;
    int fd_socket=0;
    int novo_cliente = 0;
    struct sockaddr_in* enderessamento = NULL;
    int  lista_clientes[10];
    socklen_t sock_len =0;
    int num_clientes_conetados = 0;
    pthread_t thread_resposta_cliente;
    param_t parametros = {};
    int i=0, flag = 0;
    char buffer[BUFF];


    // definido porta
    InterfaceConcexao(&porta);

    // Iniciando o servidor
    fd_socket = InicializaServidorTCP(porta, FILA_CONEXAO, enderessamento);
    sock_len = sizeof(*enderessamento);
    
    //
    
    while (1)
    {
        
        printf("Aguardando conexao.\n");
        novo_cliente = accept(fd_socket, (struct sockaddr*) enderessamento, (socklen_t*)&sock_len);
        
        if(novo_cliente == ACCEPT_ERROR){
            perror("Não foi possivel aceitar a solicitacao\n");
            continue;
        }else{
          

            lista_clientes[i++] = novo_cliente;

            read(novo_cliente, buffer, BUFF);
            printf("SOY UNO MANITO %d :%s\n", lista_clientes[i], buffer);
            
            fgets(buffer, BUFF, stdin);

            buffer[strlen(buffer)-1] ='\0';
            send(novo_cliente, buffer, BUFF, 0);

            pthread_create(&thread_resposta_cliente, NULL, RespostaCliente, NULL/*ainda flata o array de cleintes*/);

        }

        


        // {
        //     printf("Cliente: %d entrou!\n", novo_cliente);
        //     ClientesConectados(lista_clientes, &num_clientes_conetados, &novo_cliente);
        
        
        // }
        // parametros.cliente_atual = novo_cliente;
        // parametros.numero_total_clientes = num_clientes_conetados;
        // parametros.socket_cliente = lista_clientes;
   
        // pthread_create(&t, NULL, RespostaCliente, (void*)&parametros);
        

    }

    close(fd_socket);
    
    return 0;
}
