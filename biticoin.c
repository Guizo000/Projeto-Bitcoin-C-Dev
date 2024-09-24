#include "biticoin.h"
#include <time.h>

void EscreverLetraPorLetra(const char* texto, long delay) {
    struct timespec req = {0};  // Estrutura para especificar o tempo
    req.tv_sec = 0;             // Segundos (0 segundos)
    req.tv_nsec = delay * 1000000L;  // Delay em nanosegundos (1 milissegundo = 1.000.000 nanosegundos)

    printf("\n");
    while (*texto) {
        printf("%c", *texto++);
        fflush(stdout);  // Força a saída imediata do caractere
        nanosleep(&req, NULL);  // Atraso entre as letras
    }
    printf("\n");
}

//DEPOSITAR EM REAIS
ListaClientes Depositar(ListaClientes lista_Clientes, FILE* file){
  printf("Quanto voce deseja depositar?\n");
  printf("Digite a quantidade aqui - em numeros: ");
  float deposito;
  scanf("%f", &deposito);
  getchar();
  lista_Clientes.clientes[lista_Clientes.clienteAtual].saldoReais += deposito;
  ArrayToTXT(file, lista_Clientes);
  return lista_Clientes; 
}

//SACAR EM REAIS
ListaClientes Sacar(ListaClientes lista_Clientes, FILE* file){
  
  char senha[10];
  float saque;

  printf("\nSaldo na carteira: %.2f\n", lista_Clientes.clientes[lista_Clientes.clienteAtual].saldoReais);
  //Solicitar
  printf("Quanto deseja sacar?\n");
  printf("Digite a quantidade aqui - em numeros: ");
  scanf("%f", &saque);
  getchar();

  printf("Digite sua senha: ");
  scanf("%s", &senha);
  getchar();

  if (strcmp(senha, lista_Clientes.clientes[lista_Clientes.clienteAtual].senha) != 0){
    printf("Senha incorreta!\n");
    return lista_Clientes;
  }
  //PERGUNTAR SE DESEJA TENTAR NOVAMENTE

  if (saque > lista_Clientes.clientes[lista_Clientes.clienteAtual].saldoReais) {
    printf("Saldo insuficiente para fazer o saque!\n\n");
  } else {
    lista_Clientes.clientes[lista_Clientes.clienteAtual].saldoReais -= saque;
    printf("Saque realizado com sucesso! Novo saldo: %.2f\n\n", lista_Clientes.clientes[lista_Clientes.clienteAtual].saldoReais);
    ArrayToTXT(file, lista_Clientes);
  }

  return lista_Clientes;
}

//Taxa comprarCriptomoeda
float CalcularTaxaCriptomoeda(char operacao[], char criptomoeda[], float valor){
  if(strcmp(operacao, "compra") == 0){
    if (strcmp(criptomoeda, "Bitcoin") == 0){
      return valor * 0.02;
    } else if (strcmp(criptomoeda, "Ethereum") == 0){
      return valor * 0.01;
    } else if (strcmp(criptomoeda, "Ripple") == 0){
      return valor * 0.01;
    }
  }else if(strcmp(operacao, "venda") == 0){
    if (strcmp(criptomoeda, "Bitcoin") == 0){
      return valor * 0.03;
    } else if (strcmp(criptomoeda, "Ethereum") == 0){
      return valor * 0.02;
    } else if (strcmp(criptomoeda, "Ripple") == 0){
      return valor * 0.01;
    }
  }
}

float CalcularPrecoCriptomoeda(char criptomoedaASerComprada[], float qtdCriptomoeda, Criptomoedas criptomoedas){
    if (strcmp(criptomoedaASerComprada, "Bitcoin") == 0){
      return qtdCriptomoeda * criptomoedas.bitcoin;
    } else if (strcmp(criptomoedaASerComprada, "Ethereum") == 0){
      return qtdCriptomoeda * criptomoedas.ethereum;
    } else if (strcmp(criptomoedaASerComprada, "Ripple") == 0){
      return qtdCriptomoeda * criptomoedas.ripple;
    }
}

ListaClientes ComprarCriptomoeda(ListaClientes lista_Clientes, FILE* file, Criptomoedas criptomoedas){
  char criptomoedaASerComprada[50];
  float qtdCriptomoeda;
  char senha[50];

  printf("Usuario: %s\n", lista_Clientes.clientes[lista_Clientes.clienteAtual].cpf);
  printf("Saldo na carteira: %.2f\n", lista_Clientes.clientes[lista_Clientes.clienteAtual].saldoReais);

  printf("Digite a criptomoeda que deseja comprar (Bitcoin, Ethereum, Ripple): ");
  scanf("%s", &criptomoedaASerComprada);
  getchar();

  if (strcmp(criptomoedaASerComprada, "Bitcoin") != 0 && strcmp(criptomoedaASerComprada, "Ethereum") != 0 && strcmp(criptomoedaASerComprada, "Ripple") != 0){
    printf("Criptomoeda Invalida\n");
    return lista_Clientes;
  } 

  printf("Digite a quantidade de %s que deseja comprar: ", criptomoedaASerComprada);
  scanf("%f", &qtdCriptomoeda);
  getchar();
  //FALTANDO VERIFICAR SE O USUARIO DIGITOU ALGUM CARACTERE QUE N SEJA NUMERICO

  printf("Digite sua senha: ");
  scanf("%s", &senha);
  getchar();
  printf("\n");

  if (strcmp(senha, lista_Clientes.clientes[lista_Clientes.clienteAtual].senha) != 0){
    printf("Senha incorreta!\n");
    return lista_Clientes;
  }

  float valorASerPago = CalcularPrecoCriptomoeda(criptomoedaASerComprada, qtdCriptomoeda, criptomoedas);
  float taxa = CalcularTaxaCriptomoeda("compra", criptomoedaASerComprada, valorASerPago);
  float valorTotal = valorASerPago + taxa;

  if (valorTotal > lista_Clientes.clientes[lista_Clientes.clienteAtual].saldoReais) {
    printf("Saldo insuficiente!\n");
    return lista_Clientes;
  }

  printf("Criptomoeda: %s\n", criptomoedaASerComprada);
  printf("Quantidade a ser comprada: %.2f\n", qtdCriptomoeda);
  printf("Preco a ser pago: %.2f\n", valorASerPago);
  printf("Taxa cobrada: %.2f\n", taxa);
  printf("Valor total da compra: %.2f\n", valorTotal);

  char confirmarCompra;
  printf("Deseja confirmar sua compra? (s/n): ");
  scanf("%c", &confirmarCompra);
  getchar();

  if(confirmarCompra == 's' || confirmarCompra == 'S'){
    lista_Clientes.clientes[lista_Clientes.clienteAtual].saldoReais -= valorTotal;
    if(strcmp(criptomoedaASerComprada, "Bitcoin") == 0){
      lista_Clientes.clientes[lista_Clientes.clienteAtual].saldoBitcoin += qtdCriptomoeda;
    } else if (strcmp(criptomoedaASerComprada, "Ethereum") == 0){
      lista_Clientes.clientes[lista_Clientes.clienteAtual].saldoEthereum += qtdCriptomoeda;
    } else if (strcmp(criptomoedaASerComprada, "Ripple") == 0){
      lista_Clientes.clientes[lista_Clientes.clienteAtual].saldoRipple += qtdCriptomoeda;
    }
    printf("Compra realizada com sucesso!\n");
  }else{
    printf("Compra cancelada.\n");
  }

  return lista_Clientes;

}


void ConsultarSaldo(ListaClientes lista_Clientes){
  printf("\nReais: %.2f", lista_Clientes.clientes[lista_Clientes.clienteAtual].saldoReais);
  printf("\nBitcoins: %.2f", lista_Clientes.clientes[lista_Clientes.clienteAtual].saldoBitcoin);
  printf("\nEthereum: %.2f", lista_Clientes.clientes[lista_Clientes.clienteAtual].saldoEthereum);
  printf("\nRipple: %.2f\n\n", lista_Clientes.clientes[lista_Clientes.clienteAtual].saldoRipple);
}

//VENDER CRIPTOMOEDA
ListaClientes VenderCriptomoeda (ListaClientes lista_Cliente, FILE* file, Criptomoedas criptomoedas ){
  char sellcriptomoeda[10];
  float qtdCriptomoeda;
  char senha[50];

  printf("Usuario: %s\n", lista_Cliente.clientes[lista_Cliente.clienteAtual].cpf);

  printf("Digite a criptomoeda que deseja vender (Bitcoin, Ethereum, Ripple): ");
  scanf("%s", sellcriptomoeda);
  getchar();

  if (strcmp(sellcriptomoeda, "Bitcoin") != 0 && strcmp(sellcriptomoeda, "Ethereum") != 0 && strcmp(sellcriptomoeda, "Ripple") != 0){

    printf("Criptomoeda Invalida\n");
    return lista_Cliente;

  }

  float saldocripto = 0;
  if (strcmp(sellcriptomoeda, "Bitcoin") == 0){
    saldocripto = lista_Cliente.clientes[lista_Cliente.clienteAtual].saldoBitcoin;
  } else if (strcmp(sellcriptomoeda, "Ethereum") == 0){
    saldocripto = lista_Cliente.clientes[lista_Cliente.clienteAtual].saldoEthereum;
  } else if (strcmp(sellcriptomoeda, "Ripple") == 0){
    saldocripto = lista_Cliente.clientes[lista_Cliente.clienteAtual].saldoRipple;
  }

  printf("Voce tem %.2f de %s\n", saldocripto, sellcriptomoeda);

  printf("Digite a quantidade de que deseja vender: ");
  scanf("%f", &qtdCriptomoeda);
  getchar();

  if (qtdCriptomoeda > saldocripto) {
    printf("Saldo insuficiente de %s para realizar a venda.\n", sellcriptomoeda);
    return lista_Cliente;
  }

  printf("Digite sua senha: ");
  scanf("%s", senha);
  getchar();
  printf("\n");

  if (strcmp(senha, lista_Cliente.clientes[lista_Cliente.clienteAtual].senha) != 0) {
    printf("Senha invalida!\n");
    return lista_Cliente;
    //FAZER ELE DIGITAR A SENHA DNV OU VOLTAR PARA O MENU

  }

  float valorrecebido = CalcularPrecoCriptomoeda(sellcriptomoeda, qtdCriptomoeda, criptomoedas);

  float taxa = CalcularTaxaCriptomoeda("venda", sellcriptomoeda, valorrecebido);
  
  float valorFinal = valorrecebido - taxa;

  //Detalhes da venda
  printf("Criptomoeda: %s\n", sellcriptomoeda);
  printf("Quantidade a ser vendida: %.2f\n", qtdCriptomoeda);
  printf("Preco a ser recebido: %.2f\n", valorrecebido);
  printf("Valor final a ser recebido: %.2f\n", valorFinal);

  char confirmarVenda;
  printf("Deseja confirmar sua venda (s/n)? ");
  scanf("%c", &confirmarVenda);
  getchar();

  //Confirmar venda
  if (confirmarVenda == 's' || confirmarVenda == 'S'){
    if (strcmp(sellcriptomoeda, "Bitcoin") == 0){
      lista_Cliente.clientes[lista_Cliente.clienteAtual].saldoBitcoin -= qtdCriptomoeda;
    } else if (strcmp(sellcriptomoeda, "Ethereum") == 0){
      lista_Cliente.clientes[lista_Cliente.clienteAtual].saldoEthereum -= qtdCriptomoeda;
    } else if (strcmp(sellcriptomoeda, "Ripple") == 0){
      lista_Cliente.clientes[lista_Cliente.clienteAtual].saldoRipple -= qtdCriptomoeda;
    }

    lista_Cliente.clientes[lista_Cliente.clienteAtual].saldoReais += valorFinal;

    ArrayToTXT(file, lista_Cliente);

    printf("Venda realizada com sucesso! Novo saldo em Reais: %.2f", lista_Cliente.clientes[lista_Cliente.clienteAtual].saldoReais);
  } else {
    printf("Venda cancelada.\n");
  }

  return lista_Cliente;
}
