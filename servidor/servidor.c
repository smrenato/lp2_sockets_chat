#include "servidor.h"

#define ERROR_CREATE_SOCKET -1
#define ERROR_CREATE_BIND ERROR_CREATE_SOCKET
#define ERROR_LISTEN ERROR_CREATE_SOCKET
#define MSG_BUFF 140




int InterfaceConcexao(uint16_t *porta){

    fflush(stdin);
    system("clear");
    printf("\n\n\n============================================\n");
    printf("\t\t Chat v1.0.0\n");
    printf("Digite a porta de conexao: ");
    scanf("%hu", porta);
    printf("Conectando o servidor chat na porta %hu \n", *porta);
    printf("\n\n\n============================================\n");

    fflush(stdin);
    return 0;
}

//

void* RespostaCliente(void* param){
    param_t parametros = *(param_t*)param;
    int *socket_cliente, cliente_atual = 0, num_clientes_conectados=0;
    char mensagem[MSG_BUFF];
    int i, j;

    socket_cliente = parametros.socket_cliente;
    cliente_atual = parametros.cliente_atual;
    num_clientes_conectados = parametros.numero_total_clientes;

    // resposta do servidor aos 'n' clinetes conectador
    while (1)
    {
        for(i=0; i< num_clientes_conectados; i++){
            read(socket_cliente[i], mensagem, MSG_BUFF);
            
            for (j=0; j< num_clientes_conectados; j++)
            {
                send(socket_cliente[i], mensagem, strlen(mensagem), 0);

            }
            
        }

        /* code */
    }
}

//
int  ClientesConectados(int *ar_socket_clientes_conectados, int *num_clientes_atuais, int* novo_cliente){

    // Aloca memoria se não tiver nehum cliente
    if(ar_socket_clientes_conectados == NULL && (*num_clientes_atuais) == 0){
        ar_socket_clientes_conectados = (int*) malloc(sizeof(int));
       
        if(ar_socket_clientes_conectados == NULL){
            perror("Nao foi possivel alocar memoria");
            exit(EXIT_FAILURE);
        }
    
    }else if((*num_clientes_atuais) > 0){
        ar_socket_clientes_conectados = (int*) realloc(ar_socket_clientes_conectados, ++(*num_clientes_atuais));
        ar_socket_clientes_conectados[(*num_clientes_atuais)-1] = *novo_cliente;
        
        if(ar_socket_clientes_conectados == NULL){
            perror("Nao foi possivel alocar memoria");
            exit(EXIT_FAILURE);
        }
    }
    
    return 0;
}



//
int InicializaServidorTCP(uint16_t porta_conexao, int fila_conexao, struct sockaddr_in* sr_enderessamento){

    // Cria um socket e a associa a um fileDescriptor
    int file_descripitor_servidor;
    struct sockaddr_in enderessamento;
    int bind_retorno;
    
    file_descripitor_servidor = socket(AF_INET, SOCK_STREAM, 0);
    if(file_descripitor_servidor == ERROR_CREATE_SOCKET){
        perror("ERROR!, não foi possivel criar o socket.");
        exit(EXIT_FAILURE);
    }

    // Associa o socket criado a uma porta coma funcão bind
    enderessamento.sin_family  = AF_INET; //familia de protocolos
    enderessamento.sin_addr.s_addr = INADDR_ANY; 
	enderessamento.sin_port = htons(porta_conexao); 
    sr_enderessamento = &enderessamento;

    bind_retorno = bind(file_descripitor_servidor, (struct sockaddr *)&enderessamento, sizeof(enderessamento));
    if(bind_retorno == ERROR_CREATE_BIND){
        perror("ERROR!, Não foi posivel associar a uma porta.");
        exit(EXIT_FAILURE);
    }

    // Servidor apto a receber conexão
    if(listen(file_descripitor_servidor, fila_conexao) == ERROR_LISTEN){
        perror("ERRO!, listen");
        exit(EXIT_FAILURE);
    }

    return file_descripitor_servidor; // retorna o o fd do servidor

}

//

pthread_t** NovaThreadCliente(pthread_t **ar_threads_clientes, int *num_clientes_atual){
    pthread_t *novo_clinete = NULL;

    //Verifica se ja exite clinets no servidor, se não cria uma thread para o clinte atual
    if(ar_threads_clientes == NULL && (*num_clientes_atual) == 0){
        //perror("Nenhum clinte conectado!");

        ar_threads_clientes = (pthread_t**) malloc(sizeof(pthread_t*));
        novo_clinete = (pthread_t*) malloc(sizeof(pthread_t));
        ar_threads_clientes[0] = novo_clinete; 
        
        if(novo_clinete == NULL || ar_threads_clientes == NULL ){
            perror("ERRO, não foi possivel alocar memoria!");
            exit(EXIT_FAILURE);
        }
        
    }else if((*num_clientes_atual) > 0)
    {
     // Se ja existe, aloca uma thread para mais um
        ar_threads_clientes = (pthread_t **) realloc(ar_threads_clientes, ++(*num_clientes_atual));
        novo_clinete = (pthread_t*) malloc(sizeof(pthread_t));
        ar_threads_clientes[(*num_clientes_atual)-1] = novo_clinete;
        
        if(novo_clinete == NULL || ar_threads_clientes == NULL ){
            perror("ERRO, não foi possivel alocar memoria!");
            exit(EXIT_FAILURE);
        }

    }
    
    return ar_threads_clientes;
}