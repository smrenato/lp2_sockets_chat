#include <stdio.h>
#include "servidor.h"

#define FILA_CONEXAO 5
#define ACCEPT_ERROR -1

int main(int argc, char const *argv[])
{
    uint16_t porta = 0;
    int fd_socket=0;
    int novo_cliente = 0;
    struct sockaddr_in* enderessamento = NULL;
    int * lista_clientes = NULL;
    socklen_t sock_len =0;
    int num_clientes_conetados = 0;
    

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
        }else
        {
            printf("Cliente: %d entrou!\n", novo_cliente);
            ClientesConectados(lista_clientes, &num_clientes_conetados, &novo_cliente);
        }
        
        

    }
    
    return 0;
}
