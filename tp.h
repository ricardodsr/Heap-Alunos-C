#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#define STR 40
#define MAX_HEAP 300
#define NUM_UCEs 10
#define HIST_CANDIDATURAS "historico_candidaturas.txt"
#define HIST_COLOCACOES "historico_colocacoes.txt"

typedef struct Preferencia{
   int uce; 
   int grau; // {1...5} = [maior preferência...menor preferência]
   struct Preferencia * next;
}Preferencia;

typedef struct {
   int ano_pc; // ano de primeira candidatura
   int id;
   char nome[STR];
   char univ[5]; 
   char curso[4];
   float media;
   int n_cand; // nº de UCEs a que se candidata
   char tipo; // (LICENCIADO "l", ALUNO_DE_LICENCIATURA "a" ou PROFISSIONAL "p")
   struct Preferencia *pref;
}Aluno;

typedef struct {
   int id; // em {0,...,NUM_UCEs -1}
   char desig[STR];
   int nvagas;
   char horario;   //  (2,3,4,5,6)
}UCE;

// MAX-HEAP (ALUNOS)
typedef struct {
   int size;
   Aluno heap[MAX_HEAP]; 
}HeapAlunos;

typedef struct {
   int id;
   float media;
   int op;
}Colocado;
 
int init (HeapAlunos *h);
int insert_HeapAlunos (HeapAlunos *h, Aluno a);
int maior (HeapAlunos *h, Aluno *a);
int drop_root (HeapAlunos *h);
void printHeapAlunos (HeapAlunos *h);
int insereOpcoes (HeapAlunos* cands, int id_aluno, int nc, struct Preferencia *all, Aluno *aluno);  // 1 - Sucesso | 0 - Aluno não existe
//int lookupCandidato (Candidatos *cands, int uce_pref[]); // UCEs a que o individuo se candidatou
//int removerCandidato (Candidatos *cands, int codUCE, int id_aluno); // 1 - Sucesso | 0 - Falha

//alocacao.c

int alocacao(HeapAlunos *h, Colocado lic[], int loc[], UCE uce[]);
bool ha_vagas(int uce, Colocado lic[], int loc[]);
int coloca (Aluno *a, Preferencia *p, Colocado lic[], int loc[]);
int printColocados (Colocado lic[], int loc[]);
int initlic (Colocado lic[]);

// FILE
void flushSTR (char s[]);
void printAluno (Aluno a);
int readAlunos (HeapAlunos *alunos, const char filepath[]);
int readUCEs (UCE uces[], const char filepath[]);
void printUCEs (UCE uces[]);
int readOpcoes (HeapAlunos* heapalunos, const char filepath[]);
void insere_historico_candidaturas (Aluno* a);
