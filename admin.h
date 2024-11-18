#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#ifndef ADMIN_H
#define ADMIN_H

struct{
    char cpf[50];
    char senha[50];
}typedef Admin;

struct {
    int qtdAdmins;
    int adminAtual;
    Admin admins[10];
}typedef ListaAdmins;

//Voltar Menu
bool VoltarMenu();

//Informações do array admin para o txt
void ArrayToTXTAdmin(ListaAdmins lista_admins);

//Informações do txt para o array admin
ListaAdmins TxtToArrayAdmin(ListaAdmins lista_Clientes);

//Registro
ListaAdmins registrarAdmin(ListaAdmins lista_admins, bool* voltarMenu);

//Login
ListaAdmins logarAdmin(ListaAdmins lista_admins, bool* voltarMenu);

#endif 