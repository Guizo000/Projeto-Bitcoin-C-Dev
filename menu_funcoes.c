#include "menu_funcoes.h"
#include "stdlib.h"
#include "time.h"

//REALIZA O REGISTRO
ListaClientes RegistrarCliente(ListaClientes lista_Clientes){

    lista_Clientes = TxtToArray(lista_Clientes);

    //Input e verificação do cpf
    while(true){
        printf("Digite o cpf do novo investidor -> Sem traco nem pontos: ");
        char cpf[50];
        scanf("%s", cpf);
        getchar();

        bool cpfDuplicado = false;
        for (int i = 0; i < lista_Clientes.qtdClientes; i++) {
            //strcmp retorna == 0 caso estiver um registro com cpf igual
            if (strcmp(cpf, lista_Clientes.clientes[i].cpf) == 0) {
                cpfDuplicado = true;
                break;
            }
        }

        if (cpfDuplicado) {
            printf("CPF ja registrado\n\n");
            return lista_Clientes;
        }

        bool repetirRegistro = false;
        if(strlen(cpf) != 11){
            printf("Quantidade de caracteres invalido para o CPF\n\n");
            return lista_Clientes;     
        }

        int i = 0; 
        for(i; i < strlen(cpf); i++){
            if((cpf[i] >= 65 && cpf[i] <= 90) || (cpf[i] >= 97 && cpf[i] <= 122)){
                printf("Utilize apenas numeros no seu CPF\n\n");
                return lista_Clientes;  
            }
        }

        //Input e verificação da senha
        printf("Digite sua senha -> Entre 5 e 10 caracteres: ");
        char senha[50];
        scanf("%s", senha);
        getchar();

        if(strlen(senha) < 5 || strlen(senha) > 10){
            printf("Quantidade de caracteres invalido para senha\n\n");
            return lista_Clientes;
        }

        //Passando registro pro lista clientes e atualizando qtd clientes
        
        strcpy(lista_Clientes.clientes[lista_Clientes.qtdClientes].senha, senha);
        strcpy(lista_Clientes.clientes[lista_Clientes.qtdClientes].cpf, cpf);
        strcat(cpf, ".txt");
        strcpy(lista_Clientes.clientes[lista_Clientes.qtdClientes].extrato, cpf);
        lista_Clientes.clientes[lista_Clientes.qtdClientes].saldoReais = 0;
        lista_Clientes.clientes[lista_Clientes.qtdClientes].saldoBitcoin = 0;
        lista_Clientes.clientes[lista_Clientes.qtdClientes].saldoEthereum = 0;
        lista_Clientes.clientes[lista_Clientes.qtdClientes].saldoRipple = 0;
        lista_Clientes.qtdClientes++;
        
        //Passando pro TXT
        ArrayToTXT(lista_Clientes);
        printf("Investidor cadastrado com sucesso\n\n");

        return lista_Clientes;
    }
}

//CONSULTA DO SALDO
void ConsultarSaldo(ListaClientes lista_Clientes){
    //Verificando se existem clientes registrados
    FILE* file;
    file = fopen("Projeto_Cripto/usuario.txt", "rb");
    if (file == NULL){
        printf("Nenhum investidor registrado\n\n");
        fclose(file);
        return;
    }
    fclose(file);
    lista_Clientes = TxtToArray(lista_Clientes);

    //Escolhendo cliente
    printf("Digite o cpf do investidor: ");
        char cpf[50];
        scanf("%s", cpf);
        getchar();

    bool clienteEncontrado = false;
    for(int i = 0; i < sizeof(lista_Clientes.clientes)/sizeof(lista_Clientes.clientes[0]); i++){
        if(strcmp(cpf, lista_Clientes.clientes[i].cpf) == 0){
            lista_Clientes.clienteAtual = i;
            clienteEncontrado = true;
        }
    }

    if(!clienteEncontrado) { 
        printf("Investidor nao encontrado\n\n");
        return; 
    }

    printf("\nReais: %.2f", lista_Clientes.clientes[lista_Clientes.clienteAtual].saldoReais);
    printf("\nBitcoins: %.2f", lista_Clientes.clientes[lista_Clientes.clienteAtual].saldoBitcoin);
    printf("\nEthereum: %.2f", lista_Clientes.clientes[lista_Clientes.clienteAtual].saldoEthereum);
    printf("\nRipple: %.2f\n\n", lista_Clientes.clientes[lista_Clientes.clienteAtual].saldoRipple);
}



//CONSULTA DO EXTRATO
void ConsultarExtrato(ListaClientes lista_Clientes){
    //Verificando se existem clientes registrados
    FILE* file;
    file = fopen("Projeto_Cripto/usuario.txt", "rb");
    if (file == NULL){
        printf("Nenhum investidor registrado\n\n");
        fclose(file);
        return;
    }
    fclose(file);

    //Escolhendo cliente
    printf("Digite o cpf do investidor: ");
        char cpf[50];
        scanf("%s", cpf);
        getchar();

    bool clienteEncontrado = false;
    for(int i = 0; i < sizeof(lista_Clientes.clientes)/sizeof(lista_Clientes.clientes[0]); i++){
        if(strcmp(cpf, lista_Clientes.clientes[i].cpf) == 0){
            lista_Clientes.clienteAtual = i;
            clienteEncontrado = true;
        }
    }

    if(!clienteEncontrado) { 
        printf("Investidor nao encontrado\n\n");
        return; 
    }

    char extratoAdress[100] = "Projeto_Cripto/";
    strcat(extratoAdress, lista_Clientes.clientes[lista_Clientes.clienteAtual].extrato);
    file = fopen(extratoAdress, "rb");

    //Verificando se o cliente pposui um extrato
    if (file == NULL){
        printf("Extrato nao encontrado\n\n");
        fclose(file);
        return;
    }

    printf("\n\n");
    char teste[300];
    while(fgets(teste, sizeof(teste), file)){
        printf("%s", teste);
    }
    printf("\n\n");
    fclose(file);
}



//EXCLUSÃO DE CLIENTE
ListaClientes ExcluirCliente(ListaClientes lista_Clientes){
    //Verificando se existem clientes registrados
    FILE* file;
    file = fopen("Projeto_Cripto/usuario.txt", "rb");
    if (file == NULL){
        printf("Nenhum investidor registrado\n\n");
        fclose(file);
        return lista_Clientes;
    }
    fclose(file);

    lista_Clientes = TxtToArray(lista_Clientes);

    //Escolhendo cliente
    printf("Digite o cpf do investidor: ");
    char cpf[50];
    scanf("%s", cpf);
    getchar();

    bool clienteEncontrado = false;
    for(int i = 0; i < sizeof(lista_Clientes.clientes)/sizeof(lista_Clientes.clientes[0]); i++){
        if(strcmp(cpf, lista_Clientes.clientes[i].cpf) == 0){
            lista_Clientes.clienteAtual = i;
            clienteEncontrado = true;
        }
    }

    if(!clienteEncontrado) { 
        printf("Investidor nao encontrado\n\n");
        return lista_Clientes; 
    }

    //Exibindo dados e pedindo confirmação
    printf("\nCPF: %s  ", lista_Clientes.clientes[lista_Clientes.clienteAtual].cpf);
    printf("\nSenha: %s", lista_Clientes.clientes[lista_Clientes.clienteAtual].senha);
    printf("\n\nReais: %.2f", lista_Clientes.clientes[lista_Clientes.clienteAtual].saldoReais);
    printf("\nBitcoins: %.2f", lista_Clientes.clientes[lista_Clientes.clienteAtual].saldoBitcoin);
    printf("\nEthereum: %.2f", lista_Clientes.clientes[lista_Clientes.clienteAtual].saldoEthereum);
    printf("\nRipple: %.2f\n\n", lista_Clientes.clientes[lista_Clientes.clienteAtual].saldoRipple);

    char confirmarExclusao;
    printf("Deseja confirmar a exclusao do investidor (s/n)? ");
    scanf("%c", &confirmarExclusao);
    getchar();

    if(confirmarExclusao != 's' && confirmarExclusao != 'S'){
        printf("Exclusao cancelada\n\n");
        return lista_Clientes;
    }

    //Excluindo o cliente
    int indexQtdClientes = lista_Clientes.qtdClientes - 1;
    
    //Excluindo o extrato
    char placeHolder[100] = "Projeto_Cripto/";
    strcat(placeHolder, lista_Clientes.clientes[lista_Clientes.clienteAtual].extrato);
    remove(placeHolder);

    //Excluindo os outros dados
    if(indexQtdClientes = lista_Clientes.clienteAtual){
        strcpy(lista_Clientes.clientes[lista_Clientes.clienteAtual].cpf, "DELETED");
    }else{
        int i = 0;
        for(i = lista_Clientes.clienteAtual; i < lista_Clientes.qtdClientes; i++){
            lista_Clientes.clientes[i] = lista_Clientes.clientes[i + 1];
        }
        strcpy(lista_Clientes.clientes[i+1].cpf, "DELETED");
    }
    lista_Clientes.qtdClientes--;

    //Passando pro txt
    ArrayToTXT(lista_Clientes);
    printf("Investidor excluido com sucesso\n\n");

    return lista_Clientes;
}

//ATUALIZA A COTAÇÃO DAS CRIPTOMOEDAS
Criptomoedas AtualizarCotacao(Criptomoedas criptomoedas){
  printf("\nCotacao Antiga:\n ");
  printf("Bitcoin: %.2f\tEthereum: %.2f\tRipple: %.2f\n\n", criptomoedas.bitcoin, criptomoedas.ethereum, criptomoedas.ripple);

  srand(time(0)); 
  float number = (rand() % 11) - 5; // GERA NUMEROS ALEATORIOS DE -5 A 5, SEM NUMEROS DECIMAIS
  number = number/100;
  printf("Atualizacao aplicada: %.2f\n\n", number);
  criptomoedas.bitcoin += criptomoedas.bitcoin * number;
  criptomoedas.ethereum += criptomoedas.ethereum * number;
  criptomoedas.ripple += criptomoedas.ripple * number;

  printf("Nova Cotacao:\n ");
  printf("Bitcoin: %.2f\tEthereum: %.2f\tRipple: %.2f\n\n", criptomoedas.bitcoin, criptomoedas.ethereum, criptomoedas.ripple);
  return criptomoedas;
}