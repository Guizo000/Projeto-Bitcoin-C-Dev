#include "menu_funcoes.h"

//REALIZA O REGISTRO
ListaClientes registrarCliente(ListaClientes lista_Clientes){
    //INPUT E VERIFICAÇÃO DO CPF
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

        //INPUT E VERIFICAÇÃO DA SENHA
        printf("Digite sua senha -> Entre 5 e 10 caracteres: ");
        char senha[50];
        scanf("%s", senha);
        getchar();

        if(strlen(senha) < 5 || strlen(senha) > 10){
            printf("Quantidade de caracteres invalido para senha\n\n");
            return lista_Clientes;
        }

        //PASSANDO REGISTRO PRO LISTACLIENTES E ATUALIZANDO QTDCLIENTES
        
        strcpy(lista_Clientes.clientes[lista_Clientes.qtdClientes].senha, senha);
        strcpy(lista_Clientes.clientes[lista_Clientes.qtdClientes].cpf, cpf);
        char placeHolder[10];
        snprintf(placeHolder, sizeof(placeHolder), "%d", lista_Clientes.qtdClientes);
        strcat(placeHolder, ".txt");
        strcpy(lista_Clientes.clientes[lista_Clientes.qtdClientes].extrato, placeHolder);
        lista_Clientes.clientes[lista_Clientes.qtdClientes].saldoReais = 0;
        lista_Clientes.clientes[lista_Clientes.qtdClientes].saldoBitcoin = 0;
        lista_Clientes.clientes[lista_Clientes.qtdClientes].saldoEthereum = 0;
        lista_Clientes.clientes[lista_Clientes.qtdClientes].saldoRipple = 0;
        lista_Clientes.qtdClientes++;
        
        printf("\n");
        return lista_Clientes;
    }
}