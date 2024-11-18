#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#ifndef CLIENTES_H
#define CLIENTES_H

struct{
    char cpf[50];
    char senha[50];
    char extrato[10];
    float saldoReais;
    float saldoBitcoin;
    float saldoEthereum;
    float saldoRipple;  
}typedef Cliente;

struct {
    int qtdClientes;
    int clienteAtual;
    Cliente clientes[10];

}typedef ListaClientes;

//TXT pro Array
ListaClientes TxtToArray(ListaClientes lista_Clientes);

//Array pro TXT
void ArrayToTXT(ListaClientes lista_Clientes);

#endif 