#include "tp.h"


int printColocados (Colocado lic[], int loc[]) {
   int i,j;
   
   
   for (i=0; i<NUM_UCEs; i++) {
      printf("[Codigo da UCE: %d ] \n",i);
      for (j=loc[i]; j<loc[i+1]; j++)
         if(lic[j].id!=0){
            printf("Id: %d\tMedia: %2.2f\tPreferencia: %d\n", lic[j].id, lic[j].media, lic[j].op);
         }
   }
   return 1;
}


bool ha_vagas(int uce, Colocado lic[], int loc[]){
   return (((lic[loc[uce+1]-1]).id)==0);
}
   
int initlic (Colocado lic[]){
   int i;
   for (i=0;i<MAX_HEAP;i++) {lic[i].id=0;} //MAX_HEAP e o numero maximo de alunos e nao existe nenhum aluno com id=0
   return 1;
}

int coloca (Aluno *a, Preferencia *p, Colocado lic[],int loc[]){
   int i;
   for(i=loc[p->uce];((lic[i].id)!=0) ;i++){}
   lic[i].id = a->id;
   lic[i].media= a->media;
   lic[i].op= p->grau;
   return 1;
}

int alocacao(HeapAlunos *h, Colocado lic[], int loc[], UCE uce[]){
    int i,j=0;
    Aluno a;
    Preferencia *x;

    for (i=0;i<=NUM_UCEs; i++){
       loc[i]=j;
       j+=uce[i].nvagas;
    }

    initlic(lic);

    while(h->size){
       maior(h,&a);
       drop_root(h);

       for (i=0,x=a.pref; (x!=NULL) && (i<a.n_cand); x=x->next){
           if (ha_vagas(x->uce,lic,loc)){
               coloca(&a,x,lic,loc);
               i++;
            }
        }
    }
    return 1;
 } 
