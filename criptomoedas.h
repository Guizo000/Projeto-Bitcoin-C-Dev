#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#ifndef CRIPTOMOEDAS_H
#define CRIPTOMOEDAS_H

struct{
  float bitcoin;
  float ethereum;
  float ripple;
}typedef Criptomoedas;

//PASSA A ATUAL COTAÇÃO DAS CRIPTOS DO TXT PARA A STRUCT CRIPTOMOEDAS
Criptomoedas TxtToCripto(Criptomoedas criptomoedas);

//SALVA A ATUAL COTAÇÃO DAS CRIPTOS EM UM TXT
void CriptoToTXT(Criptomoedas criptomoedas);

#endif