#include "cliente.h"

#define ERROR_CREATE_SOCKET -1
#define ERROR_ENDERECO_REDE ERROR_CREATE_SOCKET
#define ERROR_CONNECT ERROR_CREATE_SOCKET


int StrtoIP(char *str, int tamanho, char *ip){
    int i, j=0, strTamanho=1;
    char c ='\0';
    char * strTmp[15];

    for ( i = 0; i < tamanho; i++)
    {
        c = str[i];
        if( (c >'/') || (c=='.') ){
            ip[j++] = c;

        }

    }
    

    printf("STR %s\n", str);

}

int InterfaceConcexao(uint16_t *porta, const char* endereco_ip, char* apelido_cliente){

    fflush(stdin);
    system("clear");
    printf("\n\n\n=================== Cliente ==================\n");
    printf("\t\t Chat v1.0.0\n");
    printf("Digite a porta de conexao: ");
    scanf("%hu%*c", porta);
    
    fflush(stdin);
    printf("\n");
    printf("Apelido: ");
    fgets(apelido_cliente, TAM_APELIDO, stdin);
    apelido_cliente[strlen(apelido_cliente)-1] ='\0';
    
    fflush(stdin);
    printf("\n");
    printf("Endereco IP 0.0.0.0: ");
    
    //gets(endereco_ip);
    //fgets(endereco_ip, TAM_APELIDO, stdin);
    //endereco_ip[strlen(endereco_ip)-1] ='\0';

    printf("Conectando o servidor chat na porta %hu \n", *porta);
    printf("Cliente %s | IP %s\n", apelido_cliente, endereco_ip);
    printf("\n\n\n============================================\n");

    //fflush(stdin);
    return 0;
}


//
int InicializaClienteTCP(uint16_t porta, char* endereco_ip){
    
    int socket_cliente =0, endereco_rede, conectar = 0;
    struct sockaddr_in enderessamento;
    //printf("PORTA %hu", porta);
    socket_cliente = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_cliente == ERROR_CREATE_SOCKET) 
	{ 
		perror("Nao foi possivel criar socket do cliente\n"); 
        exit(EXIT_FAILURE);
	} 

    memset(&enderessamento, '0', sizeof(enderessamento));
    enderessamento.sin_family = AF_INET; 
	enderessamento.sin_port = htons(porta);
    
    endereco_rede = inet_pton(AF_INET, "127.0.0.1" , &enderessamento.sin_addr);
    if(endereco_rede == ERROR_ENDERECO_REDE) 
	{ 
		perror("Nao foi possivel criar um endereco de rede\n");
        exit(EXIT_FAILURE);

	}else if(endereco_rede == 0){
        printf("Atencao IP deve ser no formato: ddd.ddd.ddd.ddd\n");
        exit(EXIT_FAILURE);
        
        
    }
    
    conectar = connect(socket_cliente, (struct sockaddr *)&enderessamento, sizeof(enderessamento));
    
    if(conectar == ERROR_CONNECT){
        perror("Nao foi possivel conectar ao servidor\n");
        exit(EXIT_FAILURE);
    }else
    {
        return socket_cliente;
        
    }
    
    return 0;   

}

