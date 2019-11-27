#include "tp.h"

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
   
   if(h -> size == MAX_HEAP)
      return 0;
        
   h -> heap[h -> size] = a;
   h -> size ++;
   
   int i = h -> size-1;
   Aluno aux; 
   Aluno pai = h -> heap[(i -1)/2];
   Aluno filho = h -> heap[i];
    
   while ( (i>0) && (
           (
            (filho.tipo == 'l') && (
                                    (pai.tipo != 'l') || (filho.media > pai.media)
                                   )
           ) ||
           (
             (filho.tipo != 'l') && (
                                     (pai.tipo != 'l') && (filho.media > pai.media)
                                    )
           )) 
          ) {
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

    while ((
            ((f_esq.tipo == 'l' || f_dir.tipo == 'l') && ((f_esq.media > pai.media) ||
                                                          (f_dir.media > pai.media) ||
                                                          (pai.tipo != 'l')))
            
           || 

            ((f_esq.tipo != 'l' || f_dir.tipo != 'l') && (pai.tipo != 'l') 
                                                      && ((f_esq.media > pai.media) 
                                                           || (f_dir.media > pai.media)))
           )
           && ((2*i + 1) < h -> size)
          )
    {
        aux = pai;
        if (
            ((f_esq.tipo == 'l') && ((f_dir.tipo != 'l') || (f_esq.media > f_dir.media))) 
            || 
            ((f_esq.tipo != 'l') && (f_dir.tipo != 'l') && (f_esq.media > f_dir.media))
           ) 
        {
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

void printHeapAlunos (HeapAlunos *h) {
   if (h -> size == 0){
      printf("Erro: Lista vazia!\n");
      return;
   }

   int i; 
   Aluno a;
   struct Preferencia *x;

   for(i=0; i<(h -> size); i++){
      a = h -> heap[i];
      printf("%d   [%c]   Média %2.2f   Ano %d   Ops: %d   Opções: ", a.id, a.tipo, a.media, a.ano_pc, a.n_cand);
      if (a.pref == NULL)
         printf("Candidatura não processada!");
      else
         for (x = a.pref; x != NULL; x = x -> next)
             printf("[%d,%d]  ",x -> uce, x -> grau);
      printf(" \n");
   }
}

int insereOpcoes (HeapAlunos* heapalunos, int id_aluno, int nc, struct Preferencia *all, Aluno *aluno) {
   int i;
   
   for(i=0; i<MAX_HEAP; i++)
      if((heapalunos -> heap[i].id) == id_aluno){
         heapalunos -> heap[i].n_cand = nc;
         heapalunos -> heap[i].pref = all;

         (*aluno).id = id_aluno;
         strcpy((*aluno).nome,heapalunos -> heap[i].nome);
         (*aluno).ano_pc = (int)heapalunos -> heap[i].ano_pc;
         strcpy((*aluno).univ,heapalunos -> heap[i].univ);
         strcpy((*aluno).curso,heapalunos -> heap[i].curso);
         (*aluno).media = (float)heapalunos -> heap[i].media;
         (*aluno).n_cand = (int)heapalunos -> heap[i].n_cand;
         (*aluno).tipo = (char)heapalunos -> heap[i].tipo;
         (*aluno).pref = all;
         return 1;
      }
   return 0;
}
