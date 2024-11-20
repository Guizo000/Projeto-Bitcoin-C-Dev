#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#ifndef CADASTRO_H
#define CADASTRO_H

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

//Voltar Menu
bool VoltarMenu();

//Logar
ListaClientes Logar(ListaClientes lista_Clientes, bool* voltarMenu);

//Registrar
ListaClientes Registrar(ListaClientes lista_Clientes, FILE* file, bool* voltarMenu);

//TXT pro Array
ListaClientes TxtToArray(ListaClientes lista_Clientes, FILE* file);

//Array pro TXT
void ArrayToTXT(FILE* file, ListaClientes lista_Clientes);

#endif 