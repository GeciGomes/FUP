#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* removeZeros(char *s){
    while(*s == '0' && *(s+1) != '\0')
        s++;
    return s;
}
int compara(char *a, char *b){
    a = removeZeros(a);
    b = removeZeros(b);
    int tamA = strlen(a);
    int tamB = strlen(b);
    if(tamA > tamB)
        return 1;
    if(tamA < tamB)
        return -1;
    return strcmp(a,b);
}
char* soma(char *a, char *b){
    int tamA = strlen(a);
    int tamB = strlen(b);
    int maior = (tamA > tamB) ? tamA : tamB;
    char *resp = malloc(maior + 2);
    int i = tamA - 1;
    int j = tamB - 1;
    int k = maior;
    int vaiUm = 0;
    resp[maior + 1] = '\0';
    while(i >= 0 || j >= 0 || vaiUm){
        int total = vaiUm;
        if(i >= 0)
            total += a[i--] - '0';
        if(j >= 0)
            total += b[j--] - '0';
        resp[k--] = (total % 10) + '0';
        vaiUm = total / 10;
    }
    return removeZeros(resp + k + 1);
}

char* subtracao(char *a, char *b){
    int negativo = 0;
    if(compara(a,b) < 0)
    {
        char *aux = a;
        a = b;
        b = aux;
        negativo = 1;
    }
    int tamA = strlen(a);
    int tamB = strlen(b);
    char *resp = malloc(tamA + 2);
    int i = tamA - 1;
    int j = tamB - 1;
    int k = tamA - 1;
    int empresta = 0;
    resp[tamA] = '\0';
    while(i >= 0)
    {
        int digA = (a[i] - '0') - empresta;
        int digB = 0;
        if(j >= 0)
            digB = b[j] - '0';
        if(digA < digB){
            digA += 10;
            empresta = 1;
        }
        else{
            empresta = 0;
        }
        resp[k] = (digA - digB) + '0';
        i--;
        j--;
        k--;
    }
    char *resultado = removeZeros(resp);
    if(!negativo)
        return resultado;
    char *final = malloc(strlen(resultado) + 2);
    final[0] = '-';
    strcpy(final + 1, resultado);
    return final;
}

char* multiplicacao(char *a, char *b)
{
    long long vezes = atoll(b);
    char *resultado = malloc(2);
    strcpy(resultado,"0");
    for(long long i = 0; i < vezes; i++)
    {
        resultado = soma(resultado,a);
    }
    return resultado;
}

char* exponenciacao(char *a, char *b)
{
    long long exp = atoll(b);
    char *resultado = malloc(2);
    strcpy(resultado,"1");
    for(long long i = 0; i < exp; i++)
    {
        resultado = multiplicacao(resultado,a);
    }
    return resultado;
}

char* fatorial(char *a)
{
    long long n = atoll(a);
    char *resultado = malloc(2);
    strcpy(resultado,"1");
    for(long long i = 2; i <= n; i++)
    {
        char aux[50];
        sprintf(aux,"%lld",i);
        resultado = multiplicacao(resultado,aux);
    }
    return resultado;
}

int main()
{
    int op;
    char a[1000];
    char b[1000];
    do{
        printf("\n=== calculadora ===\n");
        printf("1 - Soma \n");
        printf("2 - Subtracao\n");
        printf("3 - Multiplicacao \n");
        printf("4 - Exponenciacao \n");
        printf("5 - Fatorial \n");
        printf("0 - Sair \n");
        scanf("%d",&op);
        switch(op){
            case 1:
                printf("A: ");
                scanf("%s",a);
                printf("B: ");
                scanf("%s",b);
                printf("Resultado: %s\n",soma(a,b));
                break;
            case 2:
                printf("A: ");
                scanf("%s",a);
                printf("B: ");
                scanf("%s",b);
                printf("Resultado: %s\n",subtracao(a,b));
                break;
            case 3:
                printf("A: ");
                scanf("%s",a);
                printf("B: ");
                scanf("%s",b);
                printf("Resultado: %s\n",multiplicacao(a,b));
                break;
            case 4:
                printf("Base: ");
                scanf("%s",a);
                printf("Expoente: ");
                scanf("%s",b);
                printf("Resultado: %s\n",exponenciacao(a,b));
                break;
            case 5:
                printf("Numero: ");
                scanf("%s",a);
                printf("Resultado: %s\n",fatorial(a));
                break;
        }

    }while(op != 0);
    return 0;
}
