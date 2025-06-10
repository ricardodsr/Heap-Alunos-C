// Max-Heap de Alunos (orientada pela média do aluno)
#include "tp.h"

int init (HeapAlunos *h);
// Complexidade O(1). Constante, consiste apenas em colocar o tamanho da heap a 0.
int insert_heap (HeapAlunos *h, Aluno a); 
// 0 - Bag cheio, 1 - Sucesso
// Complexidade O(log n). No entando, como 50% dos elementos na heap são folhas e, como 75% dos
// elementos da heap estão nos últimos 2 níveis, a inserção far-se-á tipicamente com poucas
// operações de bubble-up. Desta forma, a inserção é, em média, feita em tempo constante.
int maior (HeapAlunos *h, Aluno *a);   
// 0 - Bag vazio, 1 - Sucesso
// O(1) - Apenas se verifica heap[0]
int drop_root (HeapAlunos *h);
// 0 - Bag vazio, 1 - Sucesso
// Complexidade O(log n). O processo de eliminação do elemento máximo da max-heap consiste em
// colocar na raiz (eliminando a raiz original) o elemento que está na última posição da heap
// e, como provavelmente o invariante de heap foi quebrado, fazer sucessivas operações de
// bubble down até este ser restabelecido.
