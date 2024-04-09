#include <time.h>

#define MAX_TRANSACOES 100

// Declaração das structs
typedef struct{
    char cep[10];
    char logradouro[250];
    int numero;
    char cidade[60];
    char uf[5];
} EnderecoTITULAR;

typedef struct{
    int cpf;
    char nome[120];
    int idade;
    int renda;
    EnderecoTITULAR enderecoTitular;
} Titular;

typedef struct{
    int numero;
    int saldo;
    Titular titular;
} Conta;

typedef struct{
    char cep[10];
    char logradouro[250];
    int numero;
    char cidade[60];
    char uf[5];
} EnderecoBANCO;

typedef struct{
    char nome[120];
    EnderecoBANCO enderecoBanco;
    Conta *contas;
} Banco;

typedef struct {
    char tipo; // 'D' para depósito, 'S' para saque, 'T' para transferência
    float valor;
    int conta_destino; 
    time_t timestamp; 
} Transacao;

typedef struct {
    Transacao transacoes[MAX_TRANSACOES];
    int num_transacoes;
} Extrato;

// Declaração das funções
// Banco
Banco *bancoNovo();
char* criarMenuBanco(Banco *banco);
void InicializarBanco(Banco *banco);
void CriarConta(Banco *banco, int *qtd_contas);
void TransacaoGlobal(Banco *banco, int qtd_contas, Extrato *novoExtrato);
void ExcluirConta(Banco *banco, int num, int qtd_contas);
char* criarMenuTransacao(Banco *banco);

// Conta
char* criarMenuConta(Banco *banco, int qtd_contas);
char* criarTransacaoConta(Banco *banco, int qtd_contas);
void MostrarConta(Banco *banco, int qtd_contas);
void EntrarConta(Banco *banco, int qtd_contas, Extrato *novoExtrato);
void atualizarConta(Banco *banco, int num, int qtd_contas, Extrato *novoExtrato);
void TransacaoConta(Banco *banco, int num, int qtd_contas, Extrato *novoextrato);

//Titular
void EntrarPerfilTitular(Banco *banco, int qtd_contas);
void MostrarTitular(Banco *banco, int num, int qtd_contas);
void MostrarEndTitular(Banco *banco, int num, int qtd_contas);
void AtualizarCadastro(Banco *banco, int num, int qtd_contas);
void AtualizarEndTitular(Banco *banco, int num, int qtd_contas);

// Transacao
void Depositar(Banco *banco, int num, int qtd_contas, Extrato *novoExtrato);
void Sacar(Banco *banco, int num, int qtd_contas, Extrato *novoExtrato);
void Transferir(Banco *banco, int num, int qtd_contas, Extrato *novoExtrato);
void adicionarTransacao(Extrato *novoExtrato, char tipo, float valor, int conta_destino);
void imprimirExtrato(Extrato *novoExtrato);