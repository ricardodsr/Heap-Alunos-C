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

/**
 * Inserts an Aluno into the HeapAlunos.
 * 
 * @param h The HeapAlunos object.
 * @param a The Aluno to be inserted.
 * @return 1 if successful, 0 otherwise.
 */
int insert_HeapAlunos(HeapAlunos *h, Aluno a) {
   // If the heap is empty, insert the Aluno at the first position
   if (h->size == 0) {
      h->heap[0] = a;
      h->size++;
      return 1;
   }

   // If the heap is full, return 0
   if (h->size == MAX_HEAP)
      return 0;

   // Insert the Aluno at the next available position
   h->heap[h->size] = a;
   h->size++;

   int i = h->size - 1;
   Aluno pai = h->heap[(i - 1) / 2];
   Aluno filho = h->heap[i];

   // Bubble up the Aluno to its correct position in the heap
   while ((pai.media < filho.media) && (i > 0)) {
      h->heap[(i - 1) / 2] = filho;
      h->heap[i] = pai;
      i = (i - 1) / 2;
      pai = h->heap[(i - 1) / 2];
      filho = h->heap[i];
   }

   return 1;
}



int drop_root(HeapAlunos *h) {
    if (h->size == 0) {
        return 0; // Heap is empty
    }

    // Move the last element to the root
    h->heap[0] = h->heap[h->size - 1];
    h->size--;

    if (h->size == 0) {
        return 1; // Heap became empty after removal
    }

    int i = 0; // Current index, start at root
    while (1) {
        int leftChildIdx = 2 * i + 1;
        int rightChildIdx = 2 * i + 2;
        int largestIdx = i; // Assume current node is the largest

        // Check if left child exists and is larger than current largest
        if (leftChildIdx < h->size && h->heap[leftChildIdx].media > h->heap[largestIdx].media) {
            largestIdx = leftChildIdx;
        }

        // Check if right child exists and is larger than current largest
        if (rightChildIdx < h->size && h->heap[rightChildIdx].media > h->heap[largestIdx].media) {
            largestIdx = rightChildIdx;
        }

        // If the largest is not the current element, swap and continue down
        if (largestIdx != i) {
            Aluno temp = h->heap[i];
            h->heap[i] = h->heap[largestIdx];
            h->heap[largestIdx] = temp;
            i = largestIdx; // Move to the new index
        } else {
            break; // Heap property is satisfied for this path
        }
    }
    return 1; // Success
}

void printHeapAlunos(HeapAlunos *h) {
    if (h == NULL) {
        printf("printHeapAlunos: Heap pointer is NULL.\n");
        return;
    }
    printf("--- HeapAlunos (STUBBED) ---\n");
    printf("Heap size: %d\n", h->size);
    printf("Max capacity: %d\n", MAX_HEAP); // Assuming MAX_HEAP is accessible
    if (h->size > 0 && h->size <= MAX_HEAP) { // Basic check before accessing heap[0]
        printf("Top student (if any, media as example): %.2f\n", h->heap[0].media);
    }
    printf("(Full print functionality not implemented.)\n");
    printf("-----------------------------\n");
}

// Needs <string.h> for strncpy if used, <stdlib.h> for malloc if used by Preferencia, already in tp.h
// Needs <stdio.h> for printf

int insereOpcoes(HeapAlunos* cands, int id_aluno, int nc, Preferencia *all_prefs, Aluno *aluno_out) {
    printf("--- insereOpcoes (STUBBED) ---\n");
    printf("Attempting to insert options for student ID: %d with %d preferences.\n", id_aluno, nc);

    if (cands == NULL || aluno_out == NULL) {
        printf("insereOpcoes: Critical pointer (cands or aluno_out) is NULL.\n");
        return 0; // Indicate failure
    }

    // Try to find the student in the heap. This is complex logic not suitable for a simple stub.
    // For a stub, we can't easily modify the heap (`cands`).
    // However, `iof.c` uses `aluno_out` to pass to `insere_historico_candidaturas`.
    // We need to populate `aluno_out` minimally.
    // Let's assume the function *would* find the student and populate `aluno_out`.
    // We'll create a dummy Aluno structure for `aluno_out` for now.

    int student_found_idx = -1;
    for (int i = 0; i < cands->size; ++i) {
        if (cands->heap[i].id == id_aluno) {
            student_found_idx = i;
            // Populate aluno_out with the data from the found student
            *aluno_out = cands->heap[i];
            // Now, attach the preferences. This is tricky as Aluno in heap might not have them yet.
            // The actual function would need to handle memory for these preferences carefully.
            // For the stub, we will just assign the passed 'all_prefs' to the 'aluno_out'
            // and update its n_cand.
            // The caller `readOpcoes` creates `all_prefs`. The real `insereOpcoes`
            // would need to either take ownership or copy them.
            // Let's assume it takes ownership for the stub's purpose.
            aluno_out->pref = all_prefs;
            aluno_out->n_cand = nc;

            // Also update the student in the heap if this function is supposed to.
            // This part is complex because it might change heap order.
            // For a stub, we'll do a direct update, ignoring heap order implications.
            cands->heap[student_found_idx].pref = all_prefs; // DANGEROUS if student not found or if all_prefs is temporary
            cands->heap[student_found_idx].n_cand = nc;

            printf("Student %d found in heap. Preferences conceptually linked (STUB).\n", id_aluno);
            break;
        }
    }

    if (student_found_idx == -1) {
        printf("Student %d NOT found in heap. Cannot assign preferences (STUBBED LOGIC).\n", id_aluno);
        // Populate `aluno_out` with some default/error data or minimal data if needed by caller
        aluno_out->id = id_aluno;
        strncpy(aluno_out->nome, "Unknown (Not Found)", STR-1);
        aluno_out->nome[STR-1] = '\0';
        aluno_out->pref = all_prefs; // Still pass prefs for historico
        aluno_out->n_cand = nc;
        // Do not return 0 here as `iof.c` expects this to mostly succeed to write history.
        // The original `insereOpcoes` comment said "1 - Sucesso | 0 - Aluno não existe"
        // So, if not found, it should be 0.
        printf("---------------------------------\n");
        return 0; // Student not found, as per original intent.
    }

    printf("insereOpcoes: STUB executed. Returning 1 (success-like).\n");
    printf("---------------------------------\n");
    return 1; // Indicate success-like for stub
}


