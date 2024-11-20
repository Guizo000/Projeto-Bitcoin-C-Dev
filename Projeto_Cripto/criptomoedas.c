#include <time.h>
#include "criptomoedas.h"


void EscreverLetraPorLetra(const char* texto, long delay){
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

//SALVA OS EXTRATOS DO USUARIO ATUAL NO TXT
void SalvarExtratoTXT(char operacao[], char qtd[], char criptomoeda[], char preco[], char taxa[], char arquivo[]){
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);

  FILE* file;
  file = fopen(arquivo, "ab");

  char ano[50];
  char mes[50];
  char dia[50];
  char hora[50];
  char min[50];
  char sec[50];

  snprintf(ano, sizeof(ano), "%.02d", tm.tm_mday);
  snprintf(mes, sizeof(mes), "%.02d", tm.tm_mon + 1);
  snprintf(dia, sizeof (dia), "%.02d", tm.tm_year + 1900);
  snprintf(hora, sizeof (hora), "%.02d", tm.tm_hour);
  snprintf(min, sizeof (min), "%.02d", tm.tm_min);
  snprintf(sec, sizeof (sec), "%.02d", tm.tm_sec);

  if(!strcmp(operacao, "Comprar Criptomoedas") || !strcmp(operacao, "Vender Criptomoedas")){
    fprintf(file, "Data: %s-%02s-%02s %02s:%02s:%02s Operacao: %s Qtd: %s Criptomoeda: %s Valor: %s Taxa: %s\n", dia, mes, ano, hora, min, sec, operacao, qtd, criptomoeda, preco, taxa);
  }else{
    fprintf(file, "Data: %s-%02s-%02s %02s:%02s:%02s Operacao: %s Qtd: %s\n", dia, mes, ano, hora, min, sec, operacao, qtd);
  }
  
 
  fclose(file);
  
}

//SALVA A ATUAL COTAÇÃO DAS CRIPTOS EM UM TXT
void CriptoToTXT(FILE* file, Criptomoedas criptomoedas){
  file = fopen("criptomoedas.txt", "wb");

  char bitcoin[50];
  snprintf(bitcoin, sizeof bitcoin, "%.2f", criptomoedas.bitcoin);
  fwrite(bitcoin, sizeof(bitcoin), 1, file);

  char ethereum[50];
  snprintf(ethereum, sizeof ethereum, "%.2f", criptomoedas.ethereum);
  fwrite(ethereum, sizeof(ethereum), 1, file);

  char ripple[50];
  snprintf(ripple, sizeof ripple, "%.2f", criptomoedas.ripple);
  fwrite(ripple, sizeof(ripple), 1, file);

  fclose(file);
}

//PASSA A ATUAL COTAÇÃO DAS CRIPTOS DO TXT PARA A STRUCT CRIPTOMOEDAS
Criptomoedas TxtToCripto(FILE* file, Criptomoedas criptomoedas){
  file = fopen("criptomoedas.txt", "rb");

  if (file == NULL){
      file = fopen("criptomoedas.txt", "wb");
      fclose(file);
      criptomoedas.bitcoin = 351115;
      criptomoedas.ethereum = 12980;
      criptomoedas.ripple = 3.27;
      CriptoToTXT(file, criptomoedas);
      return criptomoedas;
  }  

  char bitcoin[50];
  char ethereum[50];
  char ripple[50];
  
  fread(bitcoin, sizeof(bitcoin), 1, file);
  fread(ethereum, sizeof(ethereum), 1, file);
  fread(ripple, sizeof(ripple), 1, file);

  criptomoedas.bitcoin = atof(bitcoin);
  criptomoedas.ethereum = atof(ethereum);
  criptomoedas.ripple = atof(ripple);

  fclose(file);

  return criptomoedas;
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

//EXIBE TODAS AS OPERAÇÕES REALIZADAS
void ConsultarExtrato(char arquivo[]){
  FILE* file;
  file = fopen(arquivo, "rb");

  char teste[300];
  while(fgets(teste, sizeof(teste), file)){
    printf("%s", teste);
  }

  fclose(file);
}

//DEPOSITAR EM REAIS
ListaClientes Depositar(ListaClientes lista_Clientes, FILE* file){
  printf("Quanto voce deseja depositar?\n");
  printf("Digite a quantidade aqui - em numeros: ");
  char depositoChar[50];
  scanf("%s", &depositoChar);
  getchar();

  //Veriica se tem letra 
  for(int i = 0; i < strlen(depositoChar); i++){
      if((depositoChar[i] >= 65 && depositoChar[i] <= 90) || (depositoChar[i] >= 97 && depositoChar[i] <= 122)){
          printf("Utilize apenas numeros\n\n");
          return lista_Clientes;
      }
  }

  float deposito = atof(depositoChar);
  lista_Clientes.clientes[lista_Clientes.clienteAtual].saldoReais += deposito;
  SalvarExtratoTXT("Deposito", depositoChar, "NULL", "NULL", "NULL", lista_Clientes.clientes[lista_Clientes.clienteAtual].extrato);
  printf("Deposito realizado com sucesso!!\n\n");
  return lista_Clientes; 
}

//SACAR EM REAIS
ListaClientes Sacar(ListaClientes lista_Clientes, FILE* file){
  
  char senha[10];

  printf("\nSaldo na carteira: %.2f\n", lista_Clientes.clientes[lista_Clientes.clienteAtual].saldoReais);
  //Solicitar
  printf("Quanto deseja sacar?\n");
  printf("Digite a quantidade aqui - em numeros: ");
  char saqueChar[50];
  scanf("%s", &saqueChar);
  getchar();

  //Verifica se tem letra 
  for(int i = 0; i < strlen(saqueChar); i++){
      if((saqueChar[i] >= 65 && saqueChar[i] <= 90) || (saqueChar[i] >= 97 && saqueChar[i] <= 122)){
          printf("Utilize apenas numeros\n\n");
          return lista_Clientes;
      }
  }
  float saque = atof(saqueChar);
  
  printf("Digite sua senha: ");
  scanf("%s", &senha);
  getchar();

  if (strcmp(senha, lista_Clientes.clientes[lista_Clientes.clienteAtual].senha) != 0){
    printf("Senha incorreta!\n\n");
    return lista_Clientes;
  }
  //PERGUNTAR SE DESEJA TENTAR NOVAMENTE

  if (saque > lista_Clientes.clientes[lista_Clientes.clienteAtual].saldoReais) {
    printf("Saldo insuficiente para fazer o saque!\n\n");
  } else {
    lista_Clientes.clientes[lista_Clientes.clienteAtual].saldoReais -= saque;
    printf("Saque realizado com sucesso! Novo saldo: %.2f\n\n", lista_Clientes.clientes[lista_Clientes.clienteAtual].saldoReais);
  }

   SalvarExtratoTXT("Saque", saqueChar, "NULL", "NULL", "NULL", lista_Clientes.clientes[lista_Clientes.clienteAtual].extrato);

  return lista_Clientes;
}

//TAXA OPERAÇÃO COM CRIPTOMOEDAS
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

//CALCULAR PREÇO DE CRIPTOMOEDA PARA COMPRA  E VENDA
float CalcularPrecoCriptomoeda(char criptomoedaASerOperada[], float qtdCriptomoeda, Criptomoedas criptomoedas){
    if (strcmp(criptomoedaASerOperada, "Bitcoin") == 0){
      return qtdCriptomoeda * criptomoedas.bitcoin;
    } else if (strcmp(criptomoedaASerOperada, "Ethereum") == 0){
      return qtdCriptomoeda * criptomoedas.ethereum;
    } else if (strcmp(criptomoedaASerOperada, "Ripple") == 0){
      return qtdCriptomoeda * criptomoedas.ripple;
    }
}

//COMPRA CRIPTOMOEDA
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

    char qtdCriptomoedaChar[10];
    snprintf(qtdCriptomoedaChar, sizeof(qtdCriptomoedaChar), "%.2f", qtdCriptomoeda);
    char valorTotalChar[10];
    snprintf(valorTotalChar, sizeof(valorTotalChar), "%.2f", valorTotal);
    char taxaChar[10];
    snprintf(taxaChar, sizeof(taxaChar), "%.2f", taxa);

    SalvarExtratoTXT("Comprar Criptomoedas", qtdCriptomoedaChar, criptomoedaASerComprada, valorTotalChar, taxaChar, lista_Clientes.clientes[lista_Clientes.clienteAtual].extrato);
  }else{
    printf("Compra cancelada.\n");
  }

  return lista_Clientes;

}

//CONSULTA DO SALDO
void ConsultarSaldo(ListaClientes lista_Clientes){
  printf("\nReais: %.2f", lista_Clientes.clientes[lista_Clientes.clienteAtual].saldoReais);
  printf("\nBitcoins: %.2f", lista_Clientes.clientes[lista_Clientes.clienteAtual].saldoBitcoin);
  printf("\nEthereum: %.2f", lista_Clientes.clientes[lista_Clientes.clienteAtual].saldoEthereum);
  printf("\nRipple: %.2f\n\n", lista_Clientes.clientes[lista_Clientes.clienteAtual].saldoRipple);
}

//VENDER CRIPTOMOEDA
ListaClientes VenderCriptomoeda (ListaClientes lista_Cliente, FILE* file, Criptomoedas criptomoedas){
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
    printf("Saldo insuficiente de %s para realizar a venda.\n\n", sellcriptomoeda);
    return lista_Cliente;
  }

  printf("Digite sua senha: ");
  scanf("%s", senha);
  getchar();
  printf("\n");

  if (strcmp(senha, lista_Cliente.clientes[lista_Cliente.clienteAtual].senha) != 0) {
    printf("Senha invalida!\n\n");
    return lista_Cliente;
    //FAZER ELE DIGITAR A SENHA DNV OU VOLTAR PARA O MENU

  }

  float valorrecebido = CalcularPrecoCriptomoeda(sellcriptomoeda, qtdCriptomoeda, criptomoedas);

  float taxa = CalcularTaxaCriptomoeda("venda", sellcriptomoeda, valorrecebido);
  
  float valorFinal = valorrecebido - taxa;

  //Detalhes da venda
  printf("Criptomoeda: %s\n", sellcriptomoeda);
  printf("Quantidade a ser vendida: %.2f\n", qtdCriptomoeda);
  printf("Valor de venda: %.2f\n", valorrecebido);
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

    char qtdCriptomoedaChar[10];
    snprintf(qtdCriptomoedaChar, sizeof(qtdCriptomoedaChar), "%.2f", qtdCriptomoeda);
    char valorTotalChar[10];
    snprintf(valorTotalChar, sizeof(valorTotalChar), "%.2f", valorFinal);
    char taxaChar[10];
    snprintf(taxaChar, sizeof(taxaChar), "%.2f", taxa);

    SalvarExtratoTXT("Vender Criptomoedas", qtdCriptomoedaChar, sellcriptomoeda, valorTotalChar, taxaChar, lista_Cliente.clientes[lista_Cliente.clienteAtual].extrato);

    printf("Venda realizada com sucesso! Novo saldo em Reais: %.2f\n\n", lista_Cliente.clientes[lista_Cliente.clienteAtual].saldoReais);
  } else {
    printf("Venda cancelada.\n\n");
  }

  return lista_Cliente;
}
