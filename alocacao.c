#include "tp.h"
/**

// printColocados()
// This function takes two parameters - an array of Colocado objects and an array of integers.
// It prints out the code of the UCE (Unidade de Educação Continuada) and the ID, average score and preference level of each student placed in one of those UCEs.

// ha_vagas()
// This function takes three parameters - the index of the UCE, an array of Colocado objects, and an array of integers.
// It checks if there are still vacancies in a particular UCE and returns a boolean value.

// initlic()
// This function takes one parameter - an array of Colocado objects. 
// It initializes the Colocado array with zeros.

// coloca()
// This function takes four parameters - a pointer to an Aluno object, a pointer to a Preferencia object, an array of Colocado objects, and an array of integers. 
// It assigns a student to an UCE based on their preference level and updates the Colocado array accordingly.

// alocacao() 
// This function takes four parameters - a HeapAlunos structure, an array of Colocado objects, an array of integers, and an array of UCE objects.
// It handles the entire student placement process. It looks through the HeapAlunos structure and assigns students to UCEs based on their preferences. It also updates the Colocado array and the location array as it goes through the process

**/

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

    j = 0;
    for (i = 0; i < NUM_UCEs; i++) {
       loc[i] = j;
       j += uce[i].nvagas;
    }
    loc[NUM_UCEs] = j; // Set the last element to the total number of slots

    initlic(lic);

    while(h->size > 0){ // Ensure loop terminates correctly
       maior(h, &a);
       drop_root(h);

       Preferencia *current_pref = a.pref;
       while (current_pref != NULL) {
           // Check if UCE ID is valid before calling ha_vagas
           if (current_pref->uce >= 0 && current_pref->uce < NUM_UCEs) {
               if (ha_vagas(current_pref->uce, lic, loc)) {
                   coloca(&a, current_pref, lic, loc);
                   // insere_historico_colocacoes(&a, current_pref->uce); // If such a function is needed
                   break; // Student placed, exit preference loop
               }
           }
           current_pref = current_pref->next;
       }
    }
    return 1;
 } 
