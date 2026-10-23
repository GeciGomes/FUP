#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_ALUNOS 100

typedef struct {
    int dia;
    int mes;
    int ano;
} Data;
typedef struct {
    char login[50];
    char senha[31];
} Usuario;
typedef struct {
    char matricula[20];
    char nome[100];
    char curso[50];
    int periodo;
    char situacao[10];
    Data dt_cadastro;
    Data dt_nascimento;
} Aluno;

void criptografarSenha(char *senha, char *senhaCripto) {
    int i = 0;
    while (senha[i] != '\0') {
        int original = (unsigned char)senha[i];
        int criptografado = (original - 4 + 256) % 256;
        senhaCripto[i] = (char)criptografado;
        i++;
    }
    senhaCripto[i] = '\0';
}
int validarSenha(char *senha) {
    int tam = strlen(senha);
    if (tam < 10 || tam > 30) {
        return 0;
    }
    int maiusculas = 0;
    int minusculas = 0;
    int especiais = 0;
    for (int i = 0; i < tam; i++) {
        if (senha[i] >= 'A' && senha[i] <= 'Z') {
            maiusculas++;
        } else if (senha[i] >= 'a' && senha[i] <= 'z') {
            minusculas++;
        } else if ((senha[i] >= '0' && senha[i] <= '9') == 0) {
            especiais++;
        }
    }
    if (maiusculas >= 2 && minusculas >= 1 && especiais >= 1) {
        return 1;
    }
    return 0;
}

void cadastrarUsuario() {
    char novoLogin[50];
    char novaSenha[31];
    char senhaCripto[31];
    Usuario u;
    FILE *arq;
    printf("\n--- CADASTRO DE USUARIO ---\n");
    printf("Digite o login desejado: ");
    scanf("%s", novoLogin);
    arq = fopen("usuario.txt", "r");
    if (arq != NULL) {
        // Verifica se leu exatamente os 2 campos esperados
        while (fscanf(arq, "%[^;];%s\n", u.login, u.senha) == 2) {
            if (strcmp(u.login, novoLogin) == 0) {
                printf("Erro: Esse login ja existe!\n");
                fclose(arq);
                return;
            }
        }
        fclose(arq);
    }
    printf("Digite a senha: ");
    scanf("%s", novaSenha);

    if (validarSenha(novaSenha) == 0) {
        printf("Erro: Senha nao cumpre os requisitos!\n");
        return;
    }

    criptografarSenha(novaSenha, senhaCripto);

    arq = fopen("usuario.txt", "a");
    if (arq == NULL) {
        printf("Erro ao abrir arquivo de usuarios.\n");
        return;
    }

    fprintf(arq, "%s;%s\n", novoLogin, senhaCripto);
    fclose(arq);
    printf("Usuario cadastrado com sucesso!\n");
}

int login() {
    char loginDigitado[50];
    char senhaDigitada[31];
    char senhaCripto[31];
    Usuario u;
    FILE *arq;
    int logado = 0;
    char opcao;
    while (logado == 0) {
        printf("\n--- TELA DE LOGIN ---\n");
        printf("Login: ");
        scanf("%s", loginDigitado);
        printf("Senha: ");
        scanf("%s", senhaDigitada);
        criptografarSenha(senhaDigitada, senhaCripto);
        arq = fopen("usuario.txt", "r");
        int encontrou = 0;
        if (arq != NULL) {
            // Verifica se leu exatamente os 2 campos
            while (fscanf(arq, "%[^;];%s\n", u.login, u.senha) == 2) {
                if (strcmp(u.login, loginDigitado) == 0 && strcmp(u.senha, senhaCripto) == 0) {
                    encontrou = 1;
                    break;
                }
            }
            fclose(arq);
        }
        if (encontrou == 1) {
            logado = 1;
            return 1;
        } else {
            printf("Login ou senha incorretos.\n");
            printf("Deseja se cadastrar? (S/N): ");
            scanf(" %c", &opcao);
            if (opcao == 'S' || opcao == 's') {
                cadastrarUsuario();
            } else {
                return 0;
            }
        }
    }
    return 0;
}

void inserirAluno() {
    Aluno a;
    Aluno aux;
    FILE *arq;
    printf("\n--- INSERIR ALUNO ---\n");
    printf("Matricula: ");
    scanf("%s", a.matricula);
    arq = fopen("aluno.txt", "r");
    if (arq != NULL) {
        // Verifica se leu exatamente os 11 campos do registro do aluno
        while (fscanf(arq, "%[^;];%[^;];%[^;];%d;%[^;];%d;%d;%d;%d;%d;%d\n",
                      aux.matricula, aux.nome, aux.curso, &aux.periodo, aux.situacao,
                      &aux.dt_cadastro.dia, &aux.dt_cadastro.mes, &aux.dt_cadastro.ano,
                      &aux.dt_nascimento.dia, &aux.dt_nascimento.mes, &aux.dt_nascimento.ano) == 11) {
            if (strcmp(aux.matricula, a.matricula) == 0) {
                printf("Erro: Matricula ja cadastrada!\n");
                fclose(arq);
                return;
            }
        }
        fclose(arq);
    }
    printf("Nome completo: ");
    scanf(" %[^\n]", a.nome);
    printf("Curso: ");
    scanf(" %[^\n]", a.curso);
    printf("Periodo: ");
    scanf("%d", &a.periodo);
    printf("Situacao (Ativo/Inativo): ");
    scanf("%s", a.situacao);
    printf("Data de nascimento (dd mm aaaa): ");
    scanf("%d %d %d", &a.dt_nascimento.dia, &a.dt_nascimento.mes, &a.dt_nascimento.ano);
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    a.dt_cadastro.dia = tm.tm_mday;
    a.dt_cadastro.mes = tm.tm_mon + 1;
    a.dt_cadastro.ano = tm.tm_year + 1900;
    arq = fopen("aluno.txt", "a");
    if (arq == NULL) {
        printf("Erro ao abrir arquivo.\n");
        return;
    }
    fprintf(arq, "%s;%s;%s;%d;%s;%d;%d;%d;%d;%d;%d\n",
            a.matricula, a.nome, a.curso, a.periodo, a.situacao,
            a.dt_cadastro.dia, a.dt_cadastro.mes, a.dt_cadastro.ano,
            a.dt_nascimento.dia, a.dt_nascimento.mes, a.dt_nascimento.ano);
    fclose(arq);
    printf("Aluno inserido com sucesso!\n");
}

void listarTodos() {
    Aluno a;
    FILE *arq = fopen("aluno.txt", "r");
    if (arq == NULL) {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }
    printf("\n--- TODOS OS ALUNOS ---\n");
    while (fscanf(arq, "%[^;];%[^;];%[^;];%d;%[^;];%d;%d;%d;%d;%d;%d\n",
                  a.matricula, a.nome, a.curso, &a.periodo, a.situacao,
                  &a.dt_cadastro.dia, &a.dt_cadastro.mes, &a.dt_cadastro.ano,
                  &a.dt_nascimento.dia, &a.dt_nascimento.mes, &a.dt_nascimento.ano) == 11) {
        printf("Matricula: %s | Nome: %s | Status: %s\n", a.matricula, a.nome, a.situacao);
    }
    fclose(arq);
}
void listarAtivos() {
    Aluno a;
    FILE *arq = fopen("aluno.txt", "r");
    if (arq == NULL) return;
    printf("\n--- ALUNOS ATIVOS ---\n");
    while (fscanf(arq, "%[^;];%[^;];%[^;];%d;%[^;];%d;%d;%d;%d;%d;%d\n",
                  a.matricula, a.nome, a.curso, &a.periodo, a.situacao,
                  &a.dt_cadastro.dia, &a.dt_cadastro.mes, &a.dt_cadastro.ano,
                  &a.dt_nascimento.dia, &a.dt_nascimento.mes, &a.dt_nascimento.ano) == 11) {
        if (strcmp(a.situacao, "Ativo") == 0 || strcmp(a.situacao, "ativo") == 0) {
            printf("Matricula: %s | Nome: %s | Status: %s\n", a.matricula, a.nome, a.situacao);
        }
    }
    fclose(arq);
}
void listarInativos() {
    Aluno a;
    FILE *arq = fopen("aluno.txt", "r");
    if (arq == NULL) return;
    printf("\n--- ALUNOS INATIVOS ---\n");
    while (fscanf(arq, "%[^;];%[^;];%[^;];%d;%[^;];%d;%d;%d;%d;%d;%d\n",
                  a.matricula, a.nome, a.curso, &a.periodo, a.situacao,
                  &a.dt_cadastro.dia, &a.dt_cadastro.mes, &a.dt_cadastro.ano,
                  &a.dt_nascimento.dia, &a.dt_nascimento.mes, &a.dt_nascimento.ano) == 11) {
        if (strcmp(a.situacao, "Inativo") == 0 || strcmp(a.situacao, "inativo") == 0) {
            printf("Matricula: %s | Nome: %s | Status: %s\n", a.matricula, a.nome, a.situacao);
        }
    }
    fclose(arq);
}

void ordenarAlunos() {
    Aluno lista[MAX_ALUNOS];
    int n = 0;
    int criterio;
    FILE *arq = fopen("aluno.txt", "r");
    if (arq == NULL) return;
    while (n < MAX_ALUNOS && fscanf(arq, "%[^;];%[^;];%[^;];%d;%[^;];%d;%d;%d;%d;%d;%d\n",
                  lista[n].matricula, lista[n].nome, lista[n].curso, &lista[n].periodo, lista[n].situacao,
                  &lista[n].dt_cadastro.dia, &lista[n].dt_cadastro.mes, &lista[n].dt_cadastro.ano,
                  &lista[n].dt_nascimento.dia, &lista[n].dt_nascimento.mes, &lista[n].dt_nascimento.ano) == 11) {
        n++;
    }
    fclose(arq);
    printf("\nEscolha o criterio de ordenacao:\n1. Por Nome\n2. Por Matricula\nOpcao: ");
    scanf("%d", &criterio);
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            int trocar = 0;
            if (criterio == 1 && strcmp(lista[j].nome, lista[j+1].nome) > 0) {
                trocar = 1;
            } else if (criterio == 2 && strcmp(lista[j].matricula, lista[j+1].matricula) > 0) {
                trocar = 1;
            }
            if (trocar == 1) {
                Aluno temp = lista[j];
                lista[j] = lista[j+1];
                lista[j+1] = temp;
            }
        }
    }
    printf("\n--- ALUNOS ORDENADOS ---\n");
    for (int i = 0; i < n; i++) {
        printf("Matricula: %s | Nome: %s | Curso: %s\n", lista[i].matricula, lista[i].nome, lista[i].curso);
    }
}

void alterarAluno() {
    char matProcurada[20];
    Aluno lista[MAX_ALUNOS];
    int n = 0;
    int achou = -1;
    FILE *arq;
    printf("\nDigite a matricula para alterar: ");
    scanf("%s", matProcurada);
    arq = fopen("aluno.txt", "r");
    if (arq == NULL) return;
    while (n < MAX_ALUNOS && fscanf(arq, "%[^;];%[^;];%[^;];%d;%[^;];%d;%d;%d;%d;%d;%d\n",
                  lista[n].matricula, lista[n].nome, lista[n].curso, &lista[n].periodo, lista[n].situacao,
                  &lista[n].dt_cadastro.dia, &lista[n].dt_cadastro.mes, &lista[n].dt_cadastro.ano,
                  &lista[n].dt_nascimento.dia, &lista[n].dt_nascimento.mes, &lista[n].dt_nascimento.ano) == 11) {
        if (strcmp(lista[n].matricula, matProcurada) == 0) {
            achou = n;
        }
        n++;
    }
    fclose(arq);

    if (achou == -1) {
        printf("Erro: Aluno nao encontrado!\n");
        return;
    }
    printf("Novo Nome: ");
    scanf(" %[^\n]", lista[achou].nome);
    printf("Novo Curso: ");
    scanf(" %[^\n]", lista[achou].curso);
    printf("Novo Periodo: ");
    scanf("%d", &lista[achou].periodo);
    printf("Nova Situacao: ");
    scanf("%s", lista[achou].situacao);
    arq = fopen("aluno.txt", "w");
    for (int i = 0; i < n; i++) {
        fprintf(arq, "%s;%s;%s;%d;%s;%d;%d;%d;%d;%d;%d\n",
                lista[i].matricula, lista[i].nome, lista[i].curso, lista[i].periodo, lista[i].situacao,
                lista[i].dt_cadastro.dia, lista[i].dt_cadastro.mes, lista[i].dt_cadastro.ano,
                lista[i].dt_nascimento.dia, lista[i].dt_nascimento.mes, lista[i].dt_nascimento.ano);
    }
    fclose(arq);
    printf("aluno alterado com sucesso!\n");
}
void alterarKesimo() {
    int k;
    Aluno lista[MAX_ALUNOS];
    int n = 0;
    FILE *arq;
    arq = fopen("aluno.txt", "r");
    if (arq == NULL) return;

    while (n < MAX_ALUNOS && fscanf(arq, "%[^;];%[^;];%[^;];%d;%[^;];%d;%d;%d;%d;%d;%d\n",
                  lista[n].matricula, lista[n].nome, lista[n].curso, &lista[n].periodo, lista[n].situacao,
                  &lista[n].dt_cadastro.dia, &lista[n].dt_cadastro.mes, &lista[n].dt_cadastro.ano,
                  &lista[n].dt_nascimento.dia, &lista[n].dt_nascimento.mes, &lista[n].dt_nascimento.ano) == 11) {
        n++;
    }
    fclose(arq);
    printf("\nDigite a posicao do aluno (1 a %d): ", n);
    scanf("%d", &k);
    int indice = k - 1;
    if (indice < 0 || indice >= n) {
        printf("Erro: Posicao invalida!\n");
        return;
    }
    printf("Novo Nome: ");
    scanf(" %[^\n]", lista[indice].nome);
    printf("Novo Curso: ");
    scanf(" %[^\n]", lista[indice].curso);
    printf("Novo Periodo: ");
    scanf("%d", &lista[indice].periodo);
    printf("Nova Situacao: ");
    scanf("%s", lista[indice].situacao);
    arq = fopen("aluno.txt", "w");
    for (int i = 0; i < n; i++) {
        fprintf(arq, "%s;%s;%s;%d;%s;%d;%d;%d;%d;%d;%d\n",
                lista[i].matricula, lista[i].nome, lista[i].curso, lista[i].periodo, lista[i].situacao,
                lista[i].dt_cadastro.dia, lista[i].dt_cadastro.mes, lista[i].dt_cadastro.ano,
                lista[i].dt_nascimento.dia, lista[i].dt_nascimento.mes, lista[i].dt_nascimento.ano);
    }
    fclose(arq);
    printf("Aluno alterado com sucesso!\n");
}
void removerAluno() {
    char matProcurada[20];
    Aluno lista[MAX_ALUNOS];
    int n = 0;
    int achou = -1;
    char conf;
    FILE *arq;
    printf("\nDigite a matricula para remover: ");
    scanf("%s", matProcurada);
    arq = fopen("aluno.txt", "r");
    if (arq == NULL) return;
    while (n < MAX_ALUNOS && fscanf(arq, "%[^;];%[^;];%[^;];%d;%[^;];%d;%d;%d;%d;%d;%d\n",
                  lista[n].matricula, lista[n].nome, lista[n].curso, &lista[n].periodo, lista[n].situacao,
                  &lista[n].dt_cadastro.dia, &lista[n].dt_cadastro.mes, &lista[n].dt_cadastro.ano,
                  &lista[n].dt_nascimento.dia, &lista[n].dt_nascimento.mes, &lista[n].dt_nascimento.ano) == 11) {
        if (strcmp(lista[n].matricula, matProcurada) == 0) {
            achou = n;
        }
        n++;
    }
    fclose(arq);
    if (achou == -1) {
        printf("Erro: Matricula nao encontrada.\n");
        return;
    }
    printf("\nDados do Aluno:\nNome: %s\nMatricula: %s\n", lista[achou].nome, lista[achou].matricula);
    printf("Deseja realmente remover? (S/N): ");
    scanf(" %c", &conf);

    if (conf == 'S' || conf == 's') {
        arq = fopen("aluno.txt", "w");
        for (int i = 0; i < n; i++) {
            if (i != achou) {
                fprintf(arq, "%s;%s;%s;%d;%s;%d;%d;%d;%d;%d;%d\n",
                        lista[i].matricula, lista[i].nome, lista[i].curso, lista[i].periodo, lista[i].situacao,
                        lista[i].dt_cadastro.dia, lista[i].dt_cadastro.mes, lista[i].dt_cadastro.ano,
                        lista[i].dt_nascimento.dia, lista[i].dt_nascimento.mes, lista[i].dt_nascimento.ano);
            }
        }
        fclose(arq);
        printf("Aluno removido.\n");
    } else {
        printf("Remocao cancelada.\n");
    }
}

void menu() {
    char opcao;
    do {
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("a. Inserir aluno\n");
        printf("b. Listar todos\n");
        printf("c. Listar ativos\n");
        printf("d. Listar inativos\n");
        printf("e. Listar ordenados por um criterio (nome ou matricula)\n");
        printf("f. Alterar por matricula\n");
        printf("g. Alterar k-esimo\n");
        printf("h. Remover aluno\n");
        printf("i. Sair\n");
        printf("Escolha a opcao: ");
        scanf(" %c", &opcao);
        switch (opcao) {
            case 'a': case 'A': inserirAluno(); break;
            case 'b': case 'B': listarTodos(); break;
            case 'c': case 'C': listarAtivos(); break;
            case 'd': case 'D': listarInativos(); break;
            case 'e': case 'E': ordenarAlunos(); break;
            case 'f': case 'F': alterarAluno(); break;
            case 'g': case 'G': alterarKesimo(); break;
            case 'h': case 'H': removerAluno(); break;
            case 'i': case 'I': printf("Saindo...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 'i' && opcao != 'I');
}
int main() {
    if (login() == 1) {
        menu();
    }
    return 0;
}
