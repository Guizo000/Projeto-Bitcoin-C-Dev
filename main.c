#include "admin.h"
#include "clientes.h"
#include "criptomoedas.h"
#include "menu_funcoes.h"
#include <stdlib.h>

int main(){
    ListaClientes lista_Clientes;
    lista_Clientes = TxtToArray(lista_Clientes);

    ListaAdmins lista_admins;
    lista_admins = TxtToArrayAdmin(lista_admins);

    //Menu login/registro
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

    //Menu admin
    Criptomoedas criptomoedas;

    while(true){
        char opcao;
        printf("Bem Vindo!!\n");
        printf("1. Cadastro de Novo Investidor\n");
        printf("2. Excluir Investidor\n");
        printf("3. Consultar Saldo Investidor\n");
        printf("4. Consultar Extrato Investidor\n");
        printf("5. Atualizar Cotacao Criptomoedas\n");
        printf("6. Sair\n");
        printf("\nDigite a opcao desejada: ");
        scanf("%c", &opcao);
        getchar();
        switch(opcao){
          case '1':
            lista_Clientes = RegistrarCliente(lista_Clientes);
            break;
          case '2':
            lista_Clientes = ExcluirCliente(lista_Clientes);
            break;
          case '3':
            ConsultarSaldo(lista_Clientes);
            break;
          case '4':
            ConsultarExtrato(lista_Clientes);
            break;
          case '5':
            criptomoedas = TxtToCripto(criptomoedas);
            criptomoedas = AtualizarCotacao(criptomoedas);
            break;
          case '6':
            printf("Saindo...");
            break;
          default:
            printf("Digito Invalido\n\n");
            break;
          }

          ArrayToTXTAdmin(lista_admins);
          CriptoToTXT(criptomoedas);
    }
}