#include "HeapAlunos.h"

int init(HeapAlunos *h){
   h -> size = 0;
   return 1;
}

int maior(HeapAlunos *h, Aluno *a){

   if(h -> size == 0)
      return 0;
   *a = (Aluno) h -> heap[0];
   return 1;
}

int insert_HeapAlunos (HeapAlunos *h, Aluno a){

   if(h -> size == 0)
   {
      h -> heap[0] = a;
      h -> size ++;
      return 1;
   }
   
   if(h -> size == N)
      return 0;
        
   h -> heap[h -> size] = a;
   h -> size ++;
   
   int i = h -> size-1;
   Aluno aux; 
   Aluno pai = h -> heap[(i -1)/2];
   Aluno filho = h -> heap[i];
    
   while ((pai.media < filho.media) && (i>0)){
      aux = pai;
      pai = filho;
      filho = aux;

      h -> heap[(i -1)/2] = pai;
      h -> heap[i] = filho;
      i = (i-1)/2;
      pai = h -> heap[(i -1)/2];
      filho = h -> heap[i];
   }
   
   return 1;
}

int drop_root (HeapAlunos *h) {
   
   if (h -> size == 0)
      return 0;
   
    h -> heap[0] = h -> heap[h -> size -1];
    h -> size --;

    int i = 0;
    Aluno aux;
    Aluno pai = h -> heap[0];
    Aluno f_esq = h -> heap[2*i + 1];
    Aluno f_dir = h -> heap[2*i + 2];

    while (((pai.media < f_esq.media) || (pai.media < f_dir.media)) && ((2*i + 1) < h -> size)) {

        aux = pai;
        if (f_esq.media > f_dir.media) {
           pai = f_esq;
           f_esq = aux;
           h -> heap[i] = pai;
           h -> heap[2*i + 1] = f_esq;
           i = 2*i + 1;
        }
        else{
           pai = f_dir;
           f_dir = aux;
           h -> heap[i] = pai;
           h -> heap[2*i + 2] = f_dir;
           i = 2*i + 2;
        }
        pai = h -> heap[i];
        f_esq = h -> heap[2*i + 1];
        f_dir = h -> heap[2*i + 2];        
    }

    return 0;
}
