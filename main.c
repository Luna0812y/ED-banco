#include <stdio.h>
#include <stdlib.h>
#include "declaracao.h"


int main(){
    Banco *banco = bancoNovo();
    InicializarBanco(banco);
    Extrato *novoExtrato = (Extrato*)malloc(sizeof(Extrato));
    novoExtrato->num_transacoes = 0;

    int qtd_contas = 0;

    char *menu = criarMenuBanco(banco);
    int opcao;
    printf("%s", menu);
    scanf("%d", &opcao);

    while(opcao != 0){
        if (opcao == 1){
            Conta novaConta;
            CriarConta(&novaConta, banco, qtd_contas);  // Passando o endereço de novaConta
            banco->contas = (Conta *)realloc(banco->contas, (qtd_contas + 1) * sizeof(Conta));
            banco->contas[qtd_contas] = novaConta;
            (qtd_contas)++;

        } else if(opcao == 2){
            MostrarConta(banco, qtd_contas);

        } else if (opcao == 3){
            EntrarConta(banco, qtd_contas, novoExtrato);

        } else if (opcao == 4){
            TransacaoGlobal(banco, qtd_contas, novoExtrato);

        } else if (opcao == 5){
            int num;
            printf("Digite o numero da conta que deseja excluir \n>> ");
            scanf("%d", &num);
            ExcluirConta(banco, num, qtd_contas);

        } else {
            printf("Opcao Invalida");

        }

        printf("%s", menu);
        scanf("%d", &opcao);
    }

    free(banco->contas);
    free(banco);
    free(novoExtrato);

    return 0;
}
