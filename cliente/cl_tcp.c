#include<stdio.h>

#include "cliente.h"

int main(int argc, char const *argv[])
{
    char ip[TAM_IP] = "124.0.0.1";
    char apelido[TAM_APELIDO];
    char mensagem[BUFFER];
    char *aux, info_cliente[TAM_IP+BUFFER+TAM_APELIDO] = "Cliente conectado: ", *sair = "?sair";
    uint16_t porta;
    
    int flag = 0, count=0;

    int socket_cliente = 0 ;
    InterfaceConcexao(&porta, ip, apelido);
    
    socket_cliente = InicializaClienteTCP(porta, ip);

    while (1)
    {
 

        ++count;
        if(!strcmp(mensagem, sair)){
            
            aux = info_cliente;
            strcat(aux, apelido);
            strcat(aux, " ");
            strcat(aux, ip);
            strcat(aux, " ");
            strcat(aux, "SAIU");
            strcat(aux, " ");
            aux = NULL;
            send(socket_cliente, info_cliente, TAM_IP+BUFFER+TAM_APELIDO, 0);
            system("clear");
 
            break;

        }else  if (!flag)
        {
            // enviar informaões do cliente
            aux = info_cliente;
            strcat(aux, apelido);
            strcat(aux, " ");
            strcat(aux, ip);
            aux = NULL;
            send(socket_cliente, info_cliente, TAM_IP+BUFFER+TAM_APELIDO, 0);
            flag = 1;
            system("clear");

        }else if(flag == 1){
            
            // informacoe de chat
            strcat(mensagem, apelido);
            strcat(mensagem, " ");
            strcat(mensagem, ip);
            send(socket_cliente, info_cliente, TAM_IP+BUFFER+TAM_APELIDO, 0);
            system("clear");
            flag = 2;

        }else if (flag == 2)
        {   
            printf("->:");
            fgets(mensagem, 140, stdin);
            
            if(send(socket_cliente, mensagem, BUFFER, 0)){
                printf("++\n");

            }

            if(read(socket_cliente, mensagem, BUFFER)){
                printf("SERVER: %s--\n", mensagem);
                
            }
            //send(socket_cliente, );
            //read();

        }




        /* code */
    }

    close(socket_cliente);
    return 0;
}

