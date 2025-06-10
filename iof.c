#include "tp.h"

void flushSTR (char s[]) {
   int i;
   int j = strlen(s); 
   for (i=0; i<(j-1); s[i++]=' ');
}

int readAlunos(HeapAlunos *heapalunos, const char filepath[]) {
    FILE *f = NULL;
    char s[4*STR]; // Increase buffer size
    Aluno a;
    int line_number = 0;

    init(heapalunos); // Initialize the heap

    f = fopen(filepath, "r");
    if (!f) {
        perror("Error opening alunos file");
        return 0;
    }

    while (fgets(s, sizeof(s), f) != NULL) {
        line_number++;
        s[strcspn(s, "\n")] = 0; // Remove trailing newline

        if (sscanf(s, "%d,%[^,],%[^,],%[^,],%f,%c,%d", &a.id, a.nome, a.univ, a.curso, &a.media, &a.tipo, &a.ano_pc) != 7) {
            fprintf(stderr, "Error parsing alunos file at line %d: %s\n", line_number, s);
            fclose(f);
            return 0;
        }
        a.pref = NULL;
        a.n_cand = 0;
        // flushSTR(s); // Removed
        if (insert_HeapAlunos(heapalunos, a) == 0) {
            fprintf(stderr, "Error inserting student from line %d into heap.\n", line_number);
            fclose(f);
            return 0;
        }
    }
    fclose(f);
    return 1;
}


int readUCEs(UCE uces[], const char filepath[]) {
    FILE *f = NULL;
    char line_buffer[3 * STR]; // Buffer for fgets
    int line_number = 0;

    f = fopen(filepath, "r");
    if (!f) {
        perror("Error opening UCEs file");
        return 0;
    }

    while (fgets(line_buffer, sizeof(line_buffer), f) != NULL) {
        line_number++;
        line_buffer[strcspn(line_buffer, "\n")] = 0; // Remove trailing newline

        UCE current_uce_data; // Temporary UCE struct to hold parsed data
        // Attempt to parse the line
        if (sscanf(line_buffer, "%d,%[^,],%d,%c", &current_uce_data.id, current_uce_data.desig, &current_uce_data.nvagas, &current_uce_data.horario) == 4) {
            if (current_uce_data.id < 0 || current_uce_data.id >= NUM_UCEs) {
                fprintf(stderr, "Error in UCEs file at line %d: UCE ID %d is out of range (0-%d).\n", line_number, current_uce_data.id, NUM_UCEs - 1);
                fclose(f);
                return 0;
            }
            // Use strncpy for designation to prevent buffer overflow
            uces[current_uce_data.id].id = current_uce_data.id;
            strncpy(uces[current_uce_data.id].desig, current_uce_data.desig, STR - 1);
            uces[current_uce_data.id].desig[STR - 1] = '\0'; // Ensure null termination
            uces[current_uce_data.id].nvagas = current_uce_data.nvagas;
            uces[current_uce_data.id].horario = current_uce_data.horario;
        } else {
            fprintf(stderr, "Error parsing UCEs file at line %d: %s\n", line_number, line_buffer);
            fclose(f);
            return 0;
        }
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
   FILE *f = NULL;
   char s[3*STR]; // tamanho aceitável
   char *p = NULL;
   int id_aluno;
   int nc;
   Aluno aluno; // This seems to be populated by insereOpcoes
   int line_number = 0;

   f = fopen (filepath,"r");
   if (!f) {
       perror("Error opening opcoes file");
       return 0;
   }

   struct Preferencia *all=NULL,*end=NULL;

   while (fgets(s,3*STR,f) != NULL) 
   {
      line_number++;
      s[strcspn(s, "\n")] = 0; // Remove trailing newline, if any, from fgets
      all = NULL; // Reset for each line/student
      end = NULL;

      p = strtok(s,","); 
      if (!p) { /* Malformed line */ continue; } // Basic check
      id_aluno = (int)atoi(p);

      p = strtok(NULL,","); 
      if (!p) { /* Malformed line */ continue; }
      nc = (int)atoi(p);

      // The rest of the strtok logic for preferences
      p = strtok(NULL,"{"); // Consumes up to the first '{'
      while (p != NULL && (p = strtok(NULL,",")) != NULL) { // p will be the UCE value
         Preferencia *pref = (Preferencia *)malloc(sizeof(Preferencia));
         if (!pref) { // Malloc failure
             perror("Failed to allocate memory for preferencia");
             // Free already allocated parts of 'all' for this student
             Preferencia *current_pref_to_free = all;
             Preferencia *next_pref_to_free;
             while (current_pref_to_free != NULL) {
                 next_pref_to_free = current_pref_to_free->next;
                 free(current_pref_to_free);
                 current_pref_to_free = next_pref_to_free;
             }
             all = NULL;
             fclose(f);
             return 0;
         }
         pref->uce = (int)atoi(p);

         p = strtok(NULL,"}"); // p will be the grau value
         if (!p) { /* Malformed pair */ free(pref); break; }
         pref->grau = (int)atoi(p);
         pref->next = NULL;

         if (all == NULL) {
             all = pref;
             end = pref;
         } else {
             end->next = pref;
             end = pref;
         }
         p = strtok(NULL,"{"); // Consumes up to the next '{' or end of string
      }

      if(insereOpcoes(heapalunos,id_aluno,nc,all,&aluno) == 0) {
         fprintf(stderr, "Error processing options for student %d (line approx %d).\n", id_aluno, line_number);
         // Free the linked list 'all'
         Preferencia *current_pref = all;
         Preferencia *next_pref;
         while (current_pref != NULL) {
             next_pref = current_pref->next;
             free(current_pref);
             current_pref = next_pref;
         }
         all = NULL;
         fclose(f);
         return 0;
      }
      // insere_historico_candidaturas(&aluno); // This was in original, assuming it's correct
      // flushSTR(s); // Removed
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
