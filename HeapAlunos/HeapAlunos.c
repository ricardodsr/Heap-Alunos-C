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
   if (h->size == N)
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



/**
 * Drops the root element from the heap.
 *
 * @param h The heap of students.
 * @return 0 if the heap is empty, otherwise returns 1.
 */
int drop_root(HeapAlunos* h) {
    // If the heap is empty, return 0
    if (h->size == 0)
        return 0;

    int i = 0; // Index of the current element
    Aluno aux; // Temporary variable for swapping elements
    Aluno pai = h->heap[0]; // Current root element
    int leftChild = 2 * i + 1; // Index of the left child
    int rightChild = 2 * i + 2; // Index of the right child

    do {
        aux = pai; // Store the current root element

        // Check if the right child exists and has a higher media value than the left child
        if (rightChild < h->size && h->heap[rightChild].media > h->heap[leftChild].media) {
            pai = h->heap[rightChild]; // Update the current root to the right child
            h->heap[rightChild] = aux; // Swap the right child with the previous root
            i = rightChild; // Update the index to the right child
        }
        // Check if the left child exists
        else if (leftChild < h->size) {
            pai = h->heap[leftChild]; // Update the current root to the left child
            h->heap[leftChild] = aux; // Swap the left child with the previous root
            i = leftChild; // Update the index to the left child
        }
        // If both children don't exist, break the loop
        else {
            break;
        }

        // Update the indices of the left and right children for the next iteration
        leftChild = 2 * i + 1;
        rightChild = 2 * i + 2;
    }
    // Continue the loop while the media value of the current root is greater than the media values of its children
    while (pai.media > h->heap[leftChild].media || pai.media > h->heap[rightChild].media);

    return 0;
}


