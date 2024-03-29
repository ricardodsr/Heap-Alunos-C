#include "tp.h"

void flushSTR (char s[]) {
   int i;
   int j = strlen(s); 
   for (i=0; i<(j-1); s[i++]=' ');
}

int readAlunos(HeapAlunos *heapalunos, const char filepath[]) {
    FILE *f;
    char s[4*STR]; // Increase buffer size
    Aluno a;

    f = fopen(filepath, "r");

    if (!f) return 0;

    while (fgets(s, sizeof(s), f) != NULL) {
        if (sscanf(s, "%d,%[^,],%[^,],%[^,],%f,%c,%d", &a.id, a.nome, a.univ, a.curso, &a.media, &a.tipo, &a.ano_pc) != 7) {
            // Handle error in input format
            return 0;
        }
        a.pref = NULL;
        a.n_cand = 0;
        flushSTR(s);
        if (insert_HeapAlunos(heapalunos, a) == 0) return 0;
    }
    fclose(f);
    return 1;
}


int readUCEs(UCE uces[], const char filepath[]) {
    FILE *f = fopen(filepath, "r");
    if (!f) return 0;

    char buffer[3 * STR]; // buffer for each line
    int id, nvagas;
    char desig[STR], horario;

    while (fscanf(f, "%d,%[^,],%d,%c", &id, desig, &nvagas, &horario) == 4) {
        UCE x;
        x.id = id;
        strcpy(x.desig, desig);
        x.nvagas = nvagas;
        x.horario = horario;
        uces[x.id] = x;
    }

    fclose(f);
    return 1;
}
void printUCEs (UCE uces[]) {
   int i;
   printf("\n[UCEs DISPONIVEIS]\n");
   for (i=0; i<NUM_UCEs; i++)
      printf("Código: %d\tDesignação: %s\tVagas: %d\t Horário: %cª\n",uces[i].id, uces[i].desig, uces[i].nvagas, uces[i].horario);
   printf("\n");
} 

int readOpcoes (HeapAlunos* heapalunos, const char filepath[]) {
   FILE *f;
   char s[3*STR]; // tamanho aceitável
   char *p = NULL;
   int id_aluno;
   int nc;
   Aluno aluno;

   f = fopen (filepath,"r");
 
   if (!f) return 0;

   struct Preferencia *all=NULL,*end;

   while (fgets(s,3*STR,f) != NULL) 
   {
      p = strtok(s,","); 
      id_aluno = (int)atoi(p); // (aluno em questão)
      p = strtok(NULL,","); 
      nc = (int)atoi(p); // nº de UCEs a que se quer candidatar
      p = strtok(NULL,"{");
 
        if ( (p = strtok(NULL,",") ) != NULL){
         
         Preferencia *pref = (Preferencia *)malloc(sizeof(Preferencia));
         pref -> uce = (int)atoi(p);
         p = strtok(NULL,"}");
         pref -> grau = (int)atoi(p);
         pref -> next = NULL;
	 all = pref;
         end = pref;
         p = strtok(NULL,"{");
        

         while((p = strtok(NULL,",")) != NULL){
           Preferencia *pref = (Preferencia *)malloc(sizeof(Preferencia));
           pref -> uce = (int)atoi(p);
           p = strtok(NULL,"}");
           pref -> grau = (int)atoi(p);
           pref -> next = NULL;
           end -> next = pref;
	   end = pref;
           p = strtok(NULL,"{");
         } 
      }
      if(insereOpcoes(heapalunos,id_aluno,nc,all,&aluno) == 0)
            return 0;
      insere_historico_candidaturas(&aluno);
      flushSTR(s);
   }
   fclose(f);
   return 1;   
}

void insere_historico_candidaturas (Aluno* a) {
   FILE *f;
   struct Preferencia *x;

   f = fopen(HIST_CANDIDATURAS, "a+");

   fprintf(f,"%d, %d, %s, %s, %s, %2.2f,%c, %d, ", (*a).id, (*a).ano_pc, (*a).nome, (*a).univ, (*a).curso, (*a).media, (*a).tipo, (*a).n_cand);

   for(x = (*a).pref; x != NULL; x = x -> next){
      if (x -> next == NULL)
         fprintf(f,"{%d,%d}\n", x -> uce, x -> grau);
      else
         fprintf(f,"{%d,%d}, ", x -> uce, x -> grau);
   }
    
   fclose(f);
}
