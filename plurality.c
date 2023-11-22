#include "cs50.h"
#include "stdio.h"
#include "string.h"

#define MAX_CANDIDATES 9

// Estrutura para representar um candidato
typedef struct
{
    char nome[50];
    int votos;
} Candidato;

// Função para encontrar o índice de um candidato pelo nome
int encontrarIndiceCandidato(Candidato candidatos[], int numCandidatos, char nome[])
{
    for (int i = 0; i < numCandidatos; i++)
    {
        if (strcmp(candidatos[i].nome, nome) == 0)
        {
            return i;
        }
    }
    return -1; // Retorna -1 se o candidato não for encontrado
}

// Função para realizar a votação
int votar(Candidato candidatos[], int numCandidatos, char nome[])
{
    int indice = encontrarIndiceCandidato(candidatos, numCandidatos, nome);
    if (indice != -1)
    {
        candidatos[indice].votos++;
        return 1; // Voto computado com sucesso
    }
    return 0; // Candidato não encontrado
}

// Função para encontrar o vencedor
int encontrarVencedor(Candidato candidatos[], int numCandidatos)
{
    int indiceVencedor = 0;

    for (int i = 1; i < numCandidatos; i++)
    {
        if (candidatos[i].votos > candidatos[indiceVencedor].votos)
        {
            indiceVencedor = i;
        }
    }

    return indiceVencedor;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Uso: %s candidato1 candidato2 candidato3 ... candidatoN\n", argv[0]);
        return 1;
    }

    int numCandidatos = argc - 1;

    if (numCandidatos > MAX_CANDIDATES)
    {
        printf("Número máximo de candidatos é %d\n", MAX_CANDIDATES);
        return 2;
    }

    Candidato candidatos[MAX_CANDIDATES];

    // Inicializar candidatos
    for (int i = 0; i < numCandidatos; i++)
    {
        strcpy(candidatos[i].nome, argv[i + 1]);
        candidatos[i].votos = 0;
    }

    int numEleitores;

    // Solicitar o número de eleitores
    do
    {
        numEleitores = get_int("Número de eleitores: ");
    } while (numEleitores < 1);

    // Processar votos
    for (int i = 0; i < numEleitores; i++)
    {
        char voto[50];
        printf("Voto: ");
        scanf("%s", voto);

        if (!votar(candidatos, numCandidatos, voto))
        {
            printf("Candidato não encontrado. Tente novamente.\n");
            i--; // Decrementa i para repetir a entrada para o mesmo eleitor
        }
    }

    // Encontrar o vencedor
    int indiceVencedor = encontrarVencedor(candidatos, numCandidatos);

    // Exibir o vencedor
    printf("%s\n", candidatos[indiceVencedor].nome);

    return 0;
}

