#include "tp.h"

void clearstdin () {
   while (1)
      if (getchar() == '\n')
         return;
}

void menu() {
   printf("\n\nAeC - ALOCAÇÃO E COISO\n");
   printf(" \n");
   printf("1 - Importar ficheiro de alunos\n");
   printf("2 - Importar ficheiro das UCEs\n");
   printf("3 - Importar ficheiro de opções\n");
   printf("4 - Proceder à alocação\n");
   printf("0 - Sair\n\n");
}

void quit() {
   printf("Exiting program.\n");
}

int main (int args, char **argv) {

   if (args < 4) {
      printf("Exemplo de invocação: >./tp 'alunos.csv' 'uces.csv' 'ops.csv'\n");
      return 0;
   }

   const char y = 'y';
   char op = y;
   HeapAlunos heapalunos;  // guarda os alunos (max-heap) 
   UCE uces[NUM_UCEs];     // guarda as UCEs disponíveis (vector)
   Colocado lic[MAX_HEAP];
   int loc[NUM_UCEs];

   do{
      menu();
      printf(">");
      scanf("%c",&op);
      clearstdin();
      switch(op){
         case '0': quit();
                   op = '0';
                   break;

         case '1': if (readAlunos(&heapalunos,argv[1]) == 0)
                      printf("Erro: ficheiro inexistente/corrompido.\n");                   
                   else
                      printHeapAlunos(&heapalunos);
                   break;

         case '2': if (readUCEs(uces,argv[2]) == 0)
                      printf("Erro: ficheiro inexistente/corrompido.\n");
                   else
                      printUCEs(uces);
                   break;

         case '3': if (readOpcoes(&heapalunos,argv[3]) == 0)
                      printf("Erro: ficheiro inexistente/corrompido\n");
                   else
                      printHeapAlunos(&heapalunos);
                   break;
         case '4': if (alocacao(&heapalunos,lic,loc,uces) != 1)
                      printf("Erro: processo de alocação falhou!\n");
                   else{
                      printColocados(lic,loc);
                     // printColocados(&nl,uces);
                   }
                   break;
         default:  break;
      }
   }
   while (op != '0');
   return 1;
}
