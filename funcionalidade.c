#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 
#include "declaracao.h"

// inicializar ----------------------------------------------------------------------------------------------------------------------------
void InicializarBanco(Banco *banco) {
    strcpy(banco->nome, "Banco Central");
    strcpy(banco->enderecoBanco.cep, "65657-54");
    strcpy(banco->enderecoBanco.cidade, "Teresina");
    strcpy(banco->enderecoBanco.logradouro, "Rua 7 de Setembro");
    banco->enderecoBanco.numero = 6578;
    strcpy(banco->enderecoBanco.uf, "PI");
}

Banco *bancoNovo() {
    Banco *banco = (Banco *)malloc(sizeof(Banco));
    banco->contas = NULL;
    return banco;
}


// criar ------------------------------------------------------------------------------------------------------------------------------------
void CriarConta(Banco *banco, int *qtd_contas) {
    Conta novaConta;
    int novoCPF;

    printf("\nPreencha os dados do titular\n");
    printf("-- CPF \n>> ");
    scanf("%d", &novoCPF);

    for (int i = 0; i < *qtd_contas; i++) {
        if (banco->contas[i].titular.cpf == novoCPF) {
            printf("CPF já existente\n\n");
            printf("-- Outro cpf\n>> ");
            scanf("%d", &novoCPF);
            i = -1;
        }
    }

    novaConta.titular.cpf = novoCPF;

    printf("-- Nome \n>> ");
    scanf(" %119[^\n]", novaConta.titular.nome);
    printf("-- Idade\n>> ");
    scanf("%d", &novaConta.titular.idade);
    printf("-- Renda\n>> ");
    scanf("%d", &novaConta.titular.renda);

    printf("\nPreencha os dados de endereco\n");
    printf("-- CEP\n>> ");
    scanf(" %9[^\n]", novaConta.titular.enderecoTitular.cep);
    printf("-- Logradouro\n>> ");
    scanf(" %249[^\n]", novaConta.titular.enderecoTitular.logradouro);
    printf("-- Numero\n>> ");
    scanf("%d", &novaConta.titular.enderecoTitular.numero);
    printf("-- Cidade\n>> ");
    scanf(" %59[^\n]", novaConta.titular.enderecoTitular.cidade);
    printf("-- UF\n>> ");
    scanf(" %4[^\n]", novaConta.titular.enderecoTitular.uf);

    // Gerar um número de conta entre 1000 e 9999
    int numeroGerado = rand() % 9999 + 1000;
    for (int i = 0; i < *qtd_contas; i++) {
        while (banco->contas[i].numero == numeroGerado) {
            numeroGerado = rand() % 9999 + 1000;
        }
    }

    novaConta.numero = numeroGerado;
    novaConta.saldo = 0;

    banco->contas = (Conta *)realloc(banco->contas, (*qtd_contas + 1) * sizeof(Conta));
    banco->contas[*qtd_contas] = novaConta;
    (*qtd_contas)++;
}

// menu ----------------------------------------------------------------------------------------------------------------------------
char* criarMenuBanco(Banco *banco) {
    char *menu = (char*)malloc(500 * sizeof(char));

    sprintf(menu, "\n>>>    Bem-vindo(a) ao %s   <<<\n>>> %s, %d - %s <<<\n>>> %s - %s <<<\n1 - Abrir conta\n2 - Mostrar conta\n3 - Entrar na conta\n4 - Transacao\n5  - Excluir conta\n0 - Sair\n\n>>> ",
            banco->nome, banco->enderecoBanco.logradouro, banco->enderecoBanco.numero,
            banco->enderecoBanco.cep, banco->enderecoBanco.cidade, banco->enderecoBanco.uf);

    return menu;
}


char* criarMenuConta(Banco *banco, int qtd_contas) {
    for(int i = 0; i < qtd_contas; i++){
        char *menu = (char*)malloc(500 * sizeof(char));
        sprintf(menu, "\n>>>  Ola, %s <<<\n>>> Conta: %d  CPF: %d <<<\n>>> Saldo: R$%d,00 <<<\n1 - Atualizar Saldo\n2 - Transacao\n3 - Perfil do Titular\n4 - Extrato Bancario\n5 - Excluir conta\n0 - Sair\n\n>>> ",
                banco->contas[i].titular.nome, banco->contas[i].numero, banco->contas[i].titular.cpf, banco->contas[i].saldo);
        return menu;

    }
}


char* criarMenuTransacao(Banco *banco) {
    char *menu = (char*)malloc(500 * sizeof(char));

    sprintf(menu, ">>> Transacao Global <<<\n1 - Depositar\n2 - Sacar\n3 - Transferir \n4 - Ver extrato\n0 - Sair \n\n>>> ");

    return menu;
}

char* criarTransacaoConta(Banco *banco, int qtd_contas) {
    char *menu = (char*)malloc(500 * sizeof(char));

    for(int i = 0; i < qtd_contas; i++){
        sprintf(menu, ">>> Transacao da Conta %s <<<\n>>> Saldo: R$%d,00 <<<\n1 - Depositar\n2 - Sacar\n3 - Transferir \n4 - Ver extrato\n0 - Sair \n\n>>> ",
        banco->contas[i].numero, banco->contas[i].saldo);

        return menu;

    }
}

char* criarMenuTitular(Banco *banco, int qtd_contas) {
    char *menu = (char*)malloc(500 * sizeof(char));

    for(int i = 0; i < qtd_contas; i++){
        sprintf(menu, "\n>>>  Ola, %s <<<\n>>> Conta: %d  CPF: %d <<<\n1 - Atualizar Cadastro\n2 - Atualizar Endereco\n0 - Sair\n\n>>> ",
                banco->contas[i].titular.nome, banco->contas[i].numero, banco->contas[i].titular.cpf);

        return menu;
    }
}


// movimentação  ----------------------------------------------------------------------------------------------------------------------------
void TransacaoGlobal(Banco *banco, int qtd_contas, Extrato *novoExtrato){
    char *menu = criarMenuTransacao(banco);
    int opcao;
    printf("%s", menu);
    scanf("%d", &opcao);

    while (opcao != 0){
        if (opcao == 1) {
            int num;
            printf("Digite para Depositar o dinheiro: \n");
            printf("Numero da conta ou chave pix CPF \n>> ");
            scanf("%d", &num);
            Depositar(banco, num, qtd_contas, novoExtrato);

        } else if (opcao == 2) {
            int num;
            printf("Digite para Sacar o dinheiro: \n");
            printf("Numero da conta ou chave pix CPF \n>> ");
            scanf("%d", &num);
            Sacar(banco, num, qtd_contas, novoExtrato);

        }else if (opcao == 3) {
            int num;
            printf("Digite para Transferir o dinheiro: \n");
            printf("Numero da conta ou chave pix CPF \n>> ");            
            scanf("%d", &num);
            Transferir(banco, num, qtd_contas, novoExtrato);

        }else if (opcao == 4) {
            imprimirExtrato(novoExtrato);

        }else {
            printf("Opcao invalida \n");

        }

        printf("%s", menu);
        scanf("%d", &opcao);

    }
}

void TransacaoConta(Banco *banco, int num, int qtd_contas, Extrato *novoextrato){
    char *menuConta = criarTransacaoConta(banco, qtd_contas);
    int opcaoC;
    printf("%s", menuConta);
    scanf("%d", &opcaoC);
    while(opcaoC != 0){
        if(opcaoC == 1){
            Depositar(banco, num, qtd_contas, novoextrato);

        }else if(opcaoC == 2){
            Sacar(banco, num, qtd_contas, novoextrato);

        }else if (opcaoC == 3){
            Transferir(banco, num, qtd_contas, novoextrato);

        }else if (opcaoC == 4){
            imprimirExtrato(novoextrato);

        }else{
            printf("Opcao Invalida\n");

        }  

        printf("%s", menuConta);
        scanf("%d", &opcaoC);
    }
}

void Depositar(Banco *banco, int num, int qtd_contas, Extrato *novoExtrato) {
    int valor;
    for (int i = 0; i < qtd_contas; i++) {
        if (num == banco->contas[i].numero || num == banco->contas[i].titular.cpf) {
            printf("Digite o valor que deseja Depositar \n>> ");
            scanf("%d", &valor);

            banco->contas[i].saldo += valor;
            printf("Novo saldo: R$%d,00\n", banco->contas[i].saldo);
        }
    }

    adicionarTransacao(novoExtrato, 'D', valor, num);
}

void Sacar(Banco *banco, int num, int qtd_contas, Extrato *novoExtrato) {
    int valor;
    for (int i = 0; i < qtd_contas; i++) {
        if (num == banco->contas[i].numero || num == banco->contas[i].titular.cpf) {
            printf("Digite o valor que deseja Sacar \n>> ");
            scanf("%d", &valor);

            if(banco->contas[i].saldo >= valor){
                banco->contas[i].saldo -= valor;
                printf("Novo saldo: R$%d,00\n", banco->contas[i].saldo);

            }

        }
    }

    adicionarTransacao(novoExtrato, 'S', valor, num);

}

void Transferir(Banco *banco, int num, int qtd_contas, Extrato *novoeExtrato) {
    int outraConta, valor;

    printf("Digite o número ou chave pix (CPF) da conta para qual deseja transferir: \n>> ");
    scanf("%d", &outraConta);

    int encontrada = 0;

    for (int i = 0; i < qtd_contas; i++) {
        if (num == banco->contas[i].numero || num == banco->contas[i].titular.cpf) {
            for (int j = 0; j < qtd_contas; j++) {
                if (outraConta == banco->contas[i].numero || outraConta == banco->contas[i].titular.cpf) {
                    encontrada = 1;
                    printf("Digite o valor que deseja Tranferir \n>> ");
                    scanf("%d", &valor);

                    if (banco->contas[i].saldo >= valor) {
                        banco->contas[i].saldo -= valor;
                        banco->contas[j].saldo += valor;
                        printf("Transferência realizada com sucesso.\n");
                    } else {
                        printf("Saldo insuficiente para realizar a transferência.\n");
                    }
                }
            }
        } 
    }
    

    if (!encontrada) {
        printf("Conta de destino não encontrada.\n");
    }

    adicionarTransacao(novoeExtrato, 'T', valor, outraConta);
}

void adicionarTransacao(Extrato *novoExtrato, char tipo, float valor, int conta_destino) {
    Transacao nova_transacao;
    nova_transacao.tipo = tipo;
    nova_transacao.valor = valor;
    nova_transacao.conta_destino = conta_destino; 
    nova_transacao.timestamp = time(NULL); 

    novoExtrato->transacoes[novoExtrato->num_transacoes] = nova_transacao;
    novoExtrato->num_transacoes++;

}

void imprimirExtrato(Extrato *novoExtrato) {
    printf("------- Extrato Bancario -------\n");
    for (int i = 0; i < novoExtrato->num_transacoes; i++) {
        struct tm *tm_info = localtime(&novoExtrato->transacoes[i].timestamp);
        char timestamp_str[20];
        strftime(timestamp_str, 20, "%Y-%m-%d %H:%M:%S", tm_info);

        printf("[%s] ", timestamp_str);
        if (novoExtrato->transacoes[i].tipo == 'D') {
            printf("Deposito: ");
        } else if (novoExtrato->transacoes[i].tipo == 'S') {
            printf("Saque: ");
        } else if (novoExtrato->transacoes[i].tipo == 'T') {
            printf("Transferencia para conta %d: ", novoExtrato->transacoes[i].conta_destino);
        }
        printf("%.2f\n", novoExtrato->transacoes[i].valor);
    }
    printf("--------------------------------\n");
}



// atuzalização  ----------------------------------------------------------------------------------------------------------------------------
void atualizarConta(Banco *banco, int num, int qtd_contas, Extrato *novoExtrato) {
    int encontrado = 0;

    for (int i = 0; i < qtd_contas; i++) {
        if (num == banco->contas[i].numero) {
            encontrado = 1;
            printf("Conta\n>> Saldo: R$%d,00\n", banco->contas[i].saldo);
            char menu[] = ">>> Atualizar Saldo <<<\n1 - Depositar\n2 - Sacar\n3 - Transferir \n0 - Sair \n\n>>> ";
            int opcao;
            printf("%s", menu);
            scanf("%d", &opcao);

            while (opcao != 0) {

                if (opcao == 1) {
                    Depositar(banco, num, qtd_contas, novoExtrato);

                } else if (opcao == 2) {
                    Sacar(banco, num, qtd_contas, novoExtrato);

                } else if (opcao == 3) {
                    Transferir(banco, num, qtd_contas, novoExtrato);

                } else {
                    printf("Opcao invalida \n");

                }

                printf("%s", menu);
                scanf("%d", &opcao);

            } 

            printf("Dados da conta atualizados com sucesso.\n");
            break;

        }

    }
    
    if (!encontrado) {
        printf("Conta não encontrada.\n");

    }
}

void AtualizarCadastro(Banco *banco, int num, int qtd_contas){
    for(int i = 0; i < qtd_contas; i++){
        if(num == banco->contas[i].titular.cpf){
            char menu[] = ">>> Atualizar Cadastro <<<\n1 - Nome\n2 - Idade\n3 - Renda\n4 - Tudo \n0 - Sair \n\n>>> ";
            int opcao;
            printf("%s", menu);
            scanf("%d", &opcao);

            while (opcao != 0){

                if (opcao == 1) {
                    printf("Nome Atual: %s\n", banco->contas[i].titular.nome);

                    printf("Digite o novo nome: \n>> ");
                    scanf("%250[^\n]",&banco->contas[i].titular.nome);

                } else if (opcao == 2) {
                    printf("Idade Atual: %d\n", banco->contas[i].titular.idade);

                    printf("Digite a nova idade: \n>> ");
                    scanf("%d",&banco->contas[i].titular.idade);

                }else if (opcao == 3) {
                    printf("Renda Atual: R$%d,00\n", banco->contas[i].titular.renda);

                    printf("Digite a nova renda: \n>> ");
                    scanf("%d",&banco->contas[i].titular.renda);

                }else if (opcao == 4) {
                    printf("------------ Dados do Atuais -----------\n");
                    MostrarTitular(banco, num, qtd_contas);

                    printf("Digite o novo nome: \n>> ");
                    scanf("%250[^\n]",&banco->contas[i].titular.nome);
                    printf("Digite a nova idade: \n>> ");
                    scanf("%d",&banco->contas[i].titular.idade);
                    printf("Digite a nova renda: \n>> ");
                    scanf("%d",&banco->contas[i].titular.renda);

                }else {
                    printf("Opcao invalida \n");

                }

                printf("%s", menu);
                scanf("%d", &opcao);    

            } 

        }else{
            printf("CPF não encontrado \n");
        }
    }
}

void AtualizarEndTitular(Banco *banco, int num, int qtd_contas){
    for(int i = 0; i < qtd_contas; i++){
        if(num == banco->contas[i].titular.cpf){
            char menu[] = ">>> Atualizar Endereco <<<\n1 - CEP\n2 - Logradouro\n3 - Numero\n4 - Cidade \n5 - UF \n6 - Tudo \n0 - Sair \n\n>>> ";
            int opcao;
                printf("%s", menu);
                scanf("%d", &opcao);

            while (opcao != 0){

                if (opcao == 1) {
                    printf("CEP Atual: %s\n", banco->contas[i].titular.enderecoTitular.cep);

                    printf("Digite o novo CEP: \n>> ");
                    scanf("%20[^\n]",&banco->contas[i].titular.enderecoTitular.cep);

                } else if (opcao == 2) {
                    printf("Logradouro Atual: %s\n", banco->contas[i].titular.enderecoTitular.logradouro);

                    printf("Digite o novo logradouro: \n>> ");
                    scanf("%250[^\n]",&banco->contas[i].titular.enderecoTitular.logradouro);

                }else if (opcao == 3) {
                    printf("Numero Atual: %d\n", banco->contas[i].titular.enderecoTitular.numero);

                    printf("Digite o novo numero: \n>> ");
                    scanf("%d",&banco->contas[i].titular.enderecoTitular.numero);

                }else if (opcao == 4) {
                    printf("Cidade Atual: %s\n", banco->contas[i].titular.enderecoTitular.cidade);

                    printf("Digite a nova cidade: \n>> ");
                    scanf("%100[^\n]",&banco->contas[i].titular.enderecoTitular.cidade);


                }else if (opcao == 5) {
                    printf("UF Atual: %s\n", banco->contas[i].titular.enderecoTitular.uf);

                    printf("Digite a nova UF: \n>> ");
                    scanf("%10[^\n]",&banco->contas[i].titular.enderecoTitular.uf);

                }else if (opcao == 6) {
                    printf("------------ Dados do Atuais -----------\n");
                    MostrarEndTitular(banco, num, qtd_contas);

                    printf("Digite o novo CEP: \n>> ");
                    scanf("%s",&banco->contas[i].titular.enderecoTitular.cep);
                    printf("Digite o novo logradouro: \n>> ");
                    scanf("%250[^\n]",&banco->contas[i].titular.enderecoTitular.logradouro);
                    printf("Digite o novo numero: \n>> ");
                    scanf("%d",&banco->contas[i].titular.enderecoTitular.numero);
                    printf("Digite a nova cidade: \n>> ");
                    scanf("%100[^\n]",&banco->contas[i].titular.enderecoTitular.cidade);
                    printf("Digite a nova UF: \n>> ");
                    scanf("%10[^\n]",&banco->contas[i].titular.enderecoTitular.uf);

                }
                else {
                    printf("Opcao invalida \n");

                }

                printf("%s", menu);
                scanf("%d", &opcao);

            } 

        }else{
            printf("CPF não encontrado \n");
        }
    }
}


// mostrar  ----------------------------------------------------------------------------------------------------------------------------
void MostrarConta(Banco *banco, int qtd_contas){
    if(qtd_contas != 0){
        printf("---------- Contas Cadastratdas ----------\n");
        printf("-----------------------------------------\n");

        for(int i = 0; i < qtd_contas; i++){
            printf("| Numero da Conta: %d\n", banco->contas[i].numero);
            printf("| Nome: %s  CPF: %d\n", banco->contas[i].titular.nome, banco->contas[i].titular.cpf);
            printf("| Saldo: R$%d,00\n", banco->contas[i].saldo); 
            printf("-----------------------------------------\n");
        }
        }if(qtd_contas == 0) {
            printf("Contas nao encontradas !!\n\n");
        }
}

void MostrarTitular(Banco *banco, int num, int qtd_contas){
    printf("------------ Dados do Titular -----------\n");
    printf("-----------------------------------------\n");

    for(int i = 0; i < qtd_contas; i++){
        if(num == banco->contas[i].titular.cpf){
            printf("| CPF: %d  Idade: %d\n", banco->contas[i].titular.cpf, banco->contas[i].titular.idade);
            printf("| Nome: %s\n", banco->contas[i].titular.nome);
            printf("| Renda: R$%d,00\n", banco->contas[i].titular.renda); 
            printf("-----------------------------------------\n");

        }else{
            printf("CPF não encontrado \n");
        }

        
    }
}

void MostrarEndTitular(Banco *banco, int num, int qtd_contas) {
    printf("------- Dados do Endereco Titular -------\n");
    printf("-----------------------------------------\n");

    for (int i = 0; i < qtd_contas; i++) {
        if (num == banco->contas[i].titular.cpf) {
            printf("| Cep: %s  Numero: %d\n", 
                   banco->contas[i].titular.enderecoTitular.cep, banco->contas[i].titular.enderecoTitular.numero); 
            printf("| Logradouro: %s\n", 
                   banco->contas[i].titular.enderecoTitular.logradouro); 
            printf("| Cidade: %s  UF: %s\n", 
                   banco->contas[i].titular.enderecoTitular.cidade, banco->contas[i].titular.enderecoTitular.uf);
            printf("-----------------------------------------\n");
        } else {
            printf("CPF não encontrado \n");
        }
    }
}



// entrar  ----------------------------------------------------------------------------------------------------------------------------
void EntrarConta(Banco *banco, int qtd_contas, Extrato *novoExtrato){
    int num;
    printf("Digite: \n");
    printf("Numero da conta ou cpf do titular\n>> ");
    scanf("%d", &num);

    for(int i = 0; i < qtd_contas; i++){
        if(num != banco->contas[i].numero || num != banco->contas[i].titular.cpf){
            printf("Conta Nao encontrada \n");
        }

    }

    char *menuConta = criarMenuConta(banco, qtd_contas);
    int opcaoC;
    printf("%s", menuConta);
    scanf("%d", &opcaoC);
    while(opcaoC != 0){
        if(opcaoC == 1){
            atualizarConta(banco, num, qtd_contas, novoExtrato);

        }else if(opcaoC == 2){
            TransacaoConta(banco, num, qtd_contas, novoExtrato);

        }else if (opcaoC == 3){
            EntrarPerfilTitular(banco, qtd_contas);

        }else if (opcaoC == 4){
            imprimirExtrato(novoExtrato);

        }else if (opcaoC == 5){
            int num;
            printf("Digite o numero da conta ou CPF do titular que deseja excluir \n>> ");
            scanf("%d", &num);
            ExcluirConta(banco, num, qtd_contas);

        }else{
            printf("Opcao Invalida\n");

        }  

        printf("%s", menuConta);
        scanf("%d", &opcaoC);
    }

}


void EntrarPerfilTitular(Banco *banco, int qtd_contas){
    int num;
    printf("Digite o CPF do titular: \n");
    scanf("%d", &num);

    for(int i = 0; i < qtd_contas; i++){
        if(num != banco->contas[i].titular.cpf){
            printf("Titular nao encontrado \n");
        }

    }

    char *menuTitular = criarMenuTitular(banco, qtd_contas);
    int opcaoT;
    printf("%s", menuTitular);
    scanf("%d", &opcaoT);
    while(opcaoT != 0){
        if(opcaoT == 1){
            MostrarTitular(banco, num, qtd_contas);
            AtualizarCadastro(banco, num, qtd_contas);

        }else if(opcaoT == 3){
            MostrarEndTitular(banco, num, qtd_contas);
            AtualizarEndTitular(banco, num, qtd_contas);

        }else{
            printf("Opcao Invalida\n");
        }

        printf("%s", menuTitular);
        scanf("%d", &opcaoT);

    }
}



// Excluir -------------------------------------------------------------------------------------------------------- 
void ExcluirConta(Banco *banco, int num, int qtd_contas){
    int encontrado = 0; 

    for(int i = 0; i < qtd_contas; i++){
        if(num == banco->contas[i].numero || num == banco->contas[i].titular.cpf){
            encontrado = 1;
            printf("Conta: \n>> Numero: %d - Nome do Titular: %s\n", 
            banco->contas[i].numero, banco->contas[i].titular.nome);
        
            for(int j = i; j < qtd_contas - 1; j++) {
                banco->contas[j] = banco->contas[j + 1];
                j++; 
            }

            printf("Conta removida com sucesso.\n");
            break;

        }
    }
        if (!encontrado) {
            printf("Conta não encontrada.\n");
        }
}