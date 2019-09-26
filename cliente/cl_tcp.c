#include<stdio.h>

#include "cliente.h"

int main(int argc, char const *argv[])
{
    char ip[TAM_IP] ={'\0'};
    char apelido[TAM_APELIDO];
    char mensagem[BUFFER];
    uint16_t porta;
    
    int flag = 0, count=0;

    int socket_cliente = 0 ;
    InterfaceConcexao(&porta, ip, apelido);
    
    socket_cliente = InicializaClienteTCP(porta, ip);

    while (1)
    {
        ++count;
        if(strcmp(mensagem, "SAIR")){
            break;
        }else  if (!flag)
        {
            
            // enviar informaões do cliente
            flag = 1;
        }else
        {
            
        }
        fgets(mensagem, BUFFER, stdin);
        mensagem[strlen(mensagem)-1] = '\0';
        send(socket_cliente, mensagem, BUFFER, 0);
        


        /* code */
    }
    


    return 0;
}

