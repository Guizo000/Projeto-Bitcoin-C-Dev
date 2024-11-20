Criadores: 
Érik Ordine Garcia     RA: 22.224.021-0
Guilherme Rocha Santos RA: 22.124.061-7

Este repositório contém a implementação de um sistema em C que gerencia carteiras de clientes, permitindo a compra e venda de criptomoedas. As operações são realizadas utilizando a leitura e escrita em arquivos binários para manter os registros das transações de criptomoedas.

** Estrutura de Arquivos **
- projeto.c: Arquivo principal onde o programa é executado.
- cliente.h: Cabeçalho que contém as definições das estruturas de cliente e funções relacionadas à carteira de clientes.
- cliente.c: Contém as funções relacionadas à gestão dos clientes.
- criptomoedas.h: Cabeçalho que contém as definições das estruturas e funções relacionadas a criptomoedas.
- criptomoedas.c: Contém as funções relacionadas à gestão dos clientes.
- clientes.txt: Arquivo binário onde as informações dos clientes e suas carteiras são armazenadas.
- criptomoedas.txt: Arquivo binário onde as transações de criptomoedas são armazenadas.


** Funcionalidades **
O sistema oferece as seguintes funcionalidades:

1. Cadastro de Clientes:
  - ArrayToTXT: Salva a lista de clientes em um arquivo chamado
  - usuario.txt no formato binário.
  - TxtToArray: Lê os dados do arquivo usuario.txt e os armazena na estrutura de dados da lista de clientes.
    
2. Leitura e Escrita em Arquivos:
  - Permite que novos clientes se cadastrem no sistema fornecendo CPF e senha.
  - Verifica se o CPF já está registrado e se é válido (deve ter 11 dígitos numéricos).
  - A senha deve ter entre 5 e 10 caracteres.

3. Depósito de Criptomoedas:
  - Permite que os clientes façam depósitos em suas contas.
  - Valida a entrada para garantir que apenas valores numéricos sejam aceitos.

4. Saque de Criptomoedas:
  - Permite que os clientes realizem saques de suas contas.
  - Assim como no depósito, a função valida a entrada para aceitar somente valores numéricos.

5. Geração de Extratos de Transações:
  - Gera um extrato detalhado das transações realizadas pelo cliente.
  - Exibe a data, valores e taxas das transações de forma clara e organizada.

6. Geração de Extrato:
  - VoltarMenu: Função que permite ao usuário escolher entre recomeçar o processo de cadastro ou voltar ao menu principal.
  - Proporciona uma experiência interativa ao usuário, evitando erros de navegação.


** Fluxo de Operações **
- O usuário executa o programa e seleciona a operação desejada (cadastrar cliente, consultar saldo, realizar depósito, etc.).
- Dependendo da operação, o sistema solicita as informações necessárias e processa a solicitação.
- Os dados de clientes e transações são gravados e lidos de arquivos binários para garantir persistência.
- O extrato pode ser gerado a qualquer momento, exibindo todas as transações realizadas pelo cliente.


** Exemplo de Uso **
-> O cliente pode iniciar o processo de registro, onde será solicitado a fornecer seu CPF e senha.
-> Após o registro, o cliente pode realizar depósitos e saques, seguindo as validações implementadas para garantir que as entradas são válidas.
-> O cliente pode acessar seu extrato de transações a qualquer momento para visualizar suas atividades financeiras.


** Compilação e Execução **
## Para compilar o projeto, utilize o comando:
    gcc projeto.c cadastro.c criptomoedas.c
## Para executar o programa, use:
    acc .\a.exe



