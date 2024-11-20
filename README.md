Criadores: 
Érik Ordine Garcia     RA: 22.224.021-0
Guilherme Rocha Santos RA: 22.124.061-7

Este repositório contém a implementação de um sistema em C para administração de uma exchange de criptomoedas, nele você podera exluir e adicionar investidores, atualizar a cotação e conferir os dados os clientes.

** Estrutura de Arquivos **
- main.c: Arquivo principal onde o programa é executado - contém o menu.
- admin.h: Cabeçalho que contém as definições das estruturas e funções de admin.
- admin.c: Contém as funções relacionadas ao login e cadastro de admins.
- criptomoedas.h: Cabeçalho que contém as definições das estruturas e funções relacionadas a criptomoedas.
- criptomoedas.c: Contém as funções relacionadas à escrita das criptomoedas em struct e txt.
- menu_funcoes.h: Cabeçalho que contém as definições das estruturas e funções que o admin pode executar.
- menu_funcoes.c: Contém as funções que o admin pode executar.
- clientes.h: Cabeçalho que contém as definições das estruturas de clientes.
- clientes.c: Contém as funções relacionadas ao cadastro e login de clientes.


** Funcionalidades **
O sistema oferece as seguintes funcionalidades:

1. Cadastro de Novo Investidor:
  - Permite que o admin cadastre um novo investidor
    
2. Remoção de um Investidor:
  - Permite que o admin remova qualquer investidor ja existente 

3. Consulta ao Saldo de um Investidor:
  - Permite que o admin consulte o saldo de qualquer investidor

4. Consulta ao Extrato de um Investidor:
  - Permite que o admin consulte o extrato de qualquer investidor

5. Atualizar Cotação de Criptomoedas:
  - Permite que o admin atualize a cotação de criptomoedas



**OBSERVAÇÂO:**
Para que o programa de admin fucione corretamente em conjunto com o programa de investidor, eles devem estar como neste repositório, a pasta do programa de investidor e os arquivos do programa de admin no mesmo diretório 



** Compilação e Execução **
## Para compilar o projeto, utilize o comando:
    gcc main.c admin.c menu_funcoes.c criptomoedas.c clientes.c
## Para executar o programa, use:
    acc .\a.exe



