#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "clientes.h"
#ifndef MENU_FUNCOES_H
#define MENU_FUNCOES_H

//Registro
ListaClientes RegistrarCliente(ListaClientes lista_Clientes);

//Exclusão
ListaClientes ExcluirCliente(ListaClientes lista_Clientes);

//Consulta de saldo
void ConsultarSaldo(ListaClientes lista_Clientes);

//Consulta do Extrato
void ConsultarExtrato(ListaClientes lista_Clientes);
#endif 