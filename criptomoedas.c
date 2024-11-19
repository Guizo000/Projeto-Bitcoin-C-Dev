#include <time.h>
#include "criptomoedas.h"


//PASSA A ATUAL COTAÇÃO DAS CRIPTOS DO TXT PARA A STRUCT CRIPTOMOEDAS
Criptomoedas TxtToCripto(Criptomoedas criptomoedas){
  FILE* file;
  file = fopen("../Projeto_Cripto/criptomoedas.txt", "rb");

  if (file == NULL){
      file = fopen("../Projeto_Cripto/criptomoedas.txt", "wb");
      fclose(file);
      criptomoedas.bitcoin = 351115;
      criptomoedas.ethereum = 12980;
      criptomoedas.ripple = 3.27;
      CriptoToTXT(criptomoedas);
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

//SALVA A ATUAL COTAÇÃO DAS CRIPTOS EM UM TXT
void CriptoToTXT(Criptomoedas criptomoedas){
  FILE* file;
  file = fopen("../Projeto_Cripto/criptomoedas.txt", "wb");

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


