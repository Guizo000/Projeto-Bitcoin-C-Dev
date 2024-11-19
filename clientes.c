#include "clientes.h"

//PASSA AS INFORMAÇÕES DA STRUCT LISTA CLIENTES PRO TXT
void ArrayToTXT(ListaClientes lista_Clientes){
    FILE* file;
    file = fopen("../Projeto_Cripto/usuario.txt", "wb");
    fwrite(lista_Clientes.clientes, sizeof(lista_Clientes.clientes), 1, file);
    fclose(file);
}   

//PASSA AS INFORMAÇÕES DO CLIENTES PRA STRUCY LISTA CLIENTES
ListaClientes TxtToArray(ListaClientes lista_Clientes){
    FILE* file;
    file = fopen("../Projeto_Cripto/usuario.txt", "rb");
    fread(lista_Clientes.clientes, sizeof(lista_Clientes.clientes), 1, file);
    fclose(file);

    //Atualizando qtd clientes
    int i = 0;
    int placeHolderForQtdClientes = 0;
    for(i; i < sizeof(lista_Clientes.clientes) / sizeof(lista_Clientes.clientes[0]); i++){
        if(strlen(lista_Clientes.clientes[i].cpf) != 11){
            break;
        }else{
            placeHolderForQtdClientes++;
        }
    }
    lista_Clientes.qtdClientes = placeHolderForQtdClientes;
    return lista_Clientes;
}


