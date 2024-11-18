#include "admin.h"
#include "clientes.h"
#include "criptomoedas.h"
#include <stdlib.h>

int main(){
    ListaClientes lista_Clientes;
    lista_Clientes = TxtToArray(lista_Clientes);

    ListaAdmins lista_admins;
    lista_admins = TxtToArrayAdmin(lista_admins);

    //Menu Login/Registro
    bool voltarmenu = true;
    while(voltarmenu){
        char menuInicial;
        printf("\nBem vindo admin!!\n");
        printf("1. Registrar\n");
        printf("2. Logar\n");
        printf("3. Sair\n\n");
        printf("Digite a opcao desejada: ");
        scanf("%c", &menuInicial);
        getchar();
        switch (menuInicial) {
            case '1':
                lista_admins = registrarAdmin(lista_admins, &voltarmenu);
                if(voltarmenu){
                    continue;
                }
                break;
            case '2':
                lista_admins = logarAdmin(lista_admins, &voltarmenu);
                if(voltarmenu){
                    continue;
                }
                break;
            case '3':
                printf("Saindo...\n");
                return 0;
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    }

    //Menu Usuario
    Criptomoedas criptomoedas;
    criptomoedas = TxtToCripto(criptomoedas);

    while(true){
        char opcao;
        printf("Bem Vindo!!\n");
        printf("1. Cadastro de Novo Investidor\n");
        printf("2. Excluir Investidor\n");
        printf("3. Cadastro de Criptomoeda\n");
        printf("4. Excluir Ciptomoeda\n");
        printf("5. Comprar Criptomoeda\n");
        printf("6. Consultar Saldo Investidor\n");
        printf("7. Consultar Extrato Investidor\n");
        printf("8. Sair\n");
        printf("\nDigite a opcao desejada: ");
        scanf("%c", &opcao);
        getchar();
        switch(opcao){
          case '1':
            
            break;
          case '2':
            
            break;
          case '3':
            
            break;
          case '4':
            
            break;
          case '5':
            
            break;
          case '6':
            
            break;
          case '7':
            
            break;
          case '8':
            printf("Saindo...");
            return 0;
            break;
          default:
            
            break;
          }

          ArrayToTXTAdmin(lista_admins);
          ArrayToTXT(lista_Clientes);
          CriptoToTXT(criptomoedas);
    }
}