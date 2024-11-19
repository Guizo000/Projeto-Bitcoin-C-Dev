#include "admin.h"

//FUNÇÃO QUE VAI RETORNAR SE O USUARIO DESEJA RECOMEÇAR SEU LOGIN OU REGISTRO OU RETORNAR AO MENU
bool VoltarMenu(){
    char opcao;
    bool voltarMenu;
    while(true){
        printf("Deseja recomecar o processo(1) ou voltar ao menu(2)?\n");
        printf("Digite sua opcao aqui: ");
        scanf("%c", &opcao);
        getchar();
        switch(opcao){
            case '1':
                voltarMenu = false;
                break;
            case '2':
                voltarMenu = true;
                break;
            default:
                printf("Opcao invalida\n");
                continue;
                break;
        }
        return voltarMenu;
    }
}

//INFORMAÇÕES DO ARRAY ADMIN PARA O TXT
void ArrayToTXTAdmin(ListaAdmins lista_admins){
    FILE* file;
    file = fopen("admin.txt", "wb");
    fwrite(lista_admins.admins, sizeof(lista_admins.admins), 1, file);
    fclose(file);
}   

//INFORMAÇÕES DO TXT PARA O ARRAY ADMIN
ListaAdmins TxtToArrayAdmin(ListaAdmins lista_admins){
    FILE* file;
    file = fopen("admin.txt", "rb");
    fread(lista_admins.admins, sizeof(lista_admins.admins), 1, file);
    fclose(file);

    //Atualizando qtd admins
    int i = 0;
    int placeHolderForQtdAdmins = 0;
    for(i; i < sizeof(lista_admins.admins) / sizeof(lista_admins.admins[0]); i++){
        if(strlen(lista_admins.admins[i].cpf) != 11){
            break;
        }else{
            placeHolderForQtdAdmins++;
        }
    }
    lista_admins.qtdAdmins = placeHolderForQtdAdmins;
    return lista_admins;
}

//REGISTRO
ListaAdmins registrarAdmin(ListaAdmins lista_admins, bool* voltarMenu){
    //Input e verificação do cpf
    while(true){
        printf("Digite seu cpf -> Sem traco nem pontos: ");
        char cpf[50];
        scanf("%s", cpf);
        getchar();

        bool cpfDuplicado = false;
        for (int i = 0; i < lista_admins.qtdAdmins; i++) {
            //strcmp retorna == 0 caso estiver um registro com cpf igual
            if (strcmp(cpf, lista_admins.admins[i].cpf) == 0) {
                cpfDuplicado = true;
                break;
            }
        }

        if (cpfDuplicado) {
            printf("CPF ja registrado\n\n");
            *voltarMenu = VoltarMenu();
            if (*voltarMenu) {
                return lista_admins;
            } else {
                continue;
            }
        }

        bool repetirRegistro = false;
        if(strlen(cpf) != 11){
            printf("Quantidade de caracteres invalido para o CPF\n\n");
            *voltarMenu = VoltarMenu();
            if(*voltarMenu){
                return lista_admins;
            }else{
                continue;
            }         
        }

        int i = 0; 
        for(i; i < strlen(cpf); i++){
            if((cpf[i] >= 65 && cpf[i] <= 90) || (cpf[i] >= 97 && cpf[i] <= 122)){
                printf("Utilize apenas numeros no seu CPF\n\n");
                *voltarMenu = VoltarMenu();
                if(*voltarMenu){
                    return lista_admins;
                }else{
                    continue;
                }   
            }
        }

        //Input e verificação a senha
        printf("Digite sua senha -> Entre 5 e 10 caracteres: ");
        char senha[50];
        scanf("%s", senha);
        getchar();

        if(strlen(senha) < 5 || strlen(senha) > 10){
            printf("Quantidade de caracteres invalido para senha\n\n");
            *voltarMenu = VoltarMenu();
            if(*voltarMenu){
                return lista_admins;
            }else{
                continue;
            }   
        }

        //Passando registro pro lista admins e atualizando qtd admins
        
        strcpy(lista_admins.admins[lista_admins.qtdAdmins].senha, senha);
        strcpy(lista_admins.admins[lista_admins.qtdAdmins].cpf, cpf);
        lista_admins.qtdAdmins++;
        
        //PASSANDO REGISTRO PRO TXT 
        ArrayToTXTAdmin(lista_admins);
        *voltarMenu = true;
        return lista_admins;
    }
}

//LOGIN
ListaAdmins logarAdmin(ListaAdmins lista_admins, bool* voltarMenu){
   //Verificação de login
    FILE *file = fopen("admin.txt", "rb");
    if (file == NULL){
        printf("Erro ao abrir o arquivo. Nenhum admin registrado\n");
        return lista_admins;
    }
    fclose(file);
    
    while(true){
        printf("Digite seu cpf: ");
        char cpf[50];
        scanf("%s", cpf);
        getchar();

        printf("Digite sua senha: ");
        char senha[50];
        scanf("%s", senha);
        getchar();

        int i = 0;
        for( i ; i < sizeof(lista_admins.admins)/sizeof(lista_admins.admins[0]); i++){
            if(strcmp(cpf, lista_admins.admins[i].cpf) == 0 && strcmp(senha, lista_admins.admins[i].senha) == 0){
                printf("Login efetuado com sucesso\n\n");
                lista_admins.adminAtual = i;
                *voltarMenu = false;
                return lista_admins;
            }
        }

        printf("Login nao encontrado no sistema\n\n");
        *voltarMenu = VoltarMenu();
        if(*voltarMenu){
            return lista_admins;
        }
    }
}