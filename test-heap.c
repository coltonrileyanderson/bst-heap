#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"
#include "heap.h"
#include "integer.h"
#include "real.h"
#include "string.h"
#include "scanner.h"

static void displayH(HEAP *heap, FILE *fp);

int main(void) {
    
	HEAP *heap = newHEAP(displayINTEGER,compareINTEGER,freeINTEGER);

    printf("\n%s\n", "Heap Before Insert:");
    printf("%s\n", "----------------------------------");
    displayH(heap, stdout);

    insertHEAP(heap,newINTEGER(8));
    insertHEAP(heap,newINTEGER(9));
    insertHEAP(heap,newINTEGER(2));
    insertHEAP(heap,newINTEGER(5));
    insertHEAP(heap,newINTEGER(4));
    insertHEAP(heap,newINTEGER(10));
    insertHEAP(heap,newINTEGER(1));
    insertHEAP(heap,newINTEGER(3));
    insertHEAP(heap,newINTEGER(7));
    insertHEAP(heap,newINTEGER(6));

    printf("%s\n", "Heap After Insert: ");
    printf("%s\n", "----------------------------------");
    displayH(heap, stdout);

    buildHEAP(heap);
    printf("%s\n", "Build Heap Initial: ");
    printf("%s\n", "----------------------------------");
    displayH(heap, stdout);
    
    INTEGER *temp;

    printf("%s\n", "extracting. . . 1");
    printf("%s\n", "----------------------------------");
    temp = extractHEAP(heap);
    freeINTEGER(temp);
    displayH(heap, stdout);
    
	printf("%s\n", "extracting. . . 2");
    printf("%s\n", "----------------------------------");
    temp = extractHEAP(heap);
    freeINTEGER(temp);
    displayH(heap, stdout);

    printf("%s\n", "extracting. . . 3");
    printf("%s\n", "----------------------------------");
    temp = extractHEAP(heap);
    freeINTEGER(temp);
    displayH(heap, stdout);

    printf("%s\n", "extracting. . . 4");
    printf("%s\n", "----------------------------------");
    temp = extractHEAP(heap);
    freeINTEGER(temp);
    displayH(heap, stdout);

    printf("%s\n", "extracting. . . 5");
    printf("%s\n", "----------------------------------");
    temp = extractHEAP(heap);
    freeINTEGER(temp);
    displayH(heap, stdout);

    printf("%s\n", "extracting. . . 6");
    printf("%s\n", "----------------------------------");
    temp = extractHEAP(heap);
    freeINTEGER(temp);
    displayH(heap, stdout);

    printf("%s\n", "extracting. . . 7");
    printf("%s\n", "----------------------------------");
    temp = extractHEAP(heap);
    freeINTEGER(temp);
    displayH(heap, stdout);

    printf("%s\n", "extracting. . . 8");
    printf("%s\n", "----------------------------------");
    temp = extractHEAP(heap);
    freeINTEGER(temp);
    displayH(heap, stdout);

    printf("%s\n", "extracting. . . 9");
    printf("%s\n", "----------------------------------");
    temp = extractHEAP(heap);
    freeINTEGER(temp);
    displayH(heap, stdout);
    
    printf("%s\n", "extracting. . . 10");
    printf("%s\n", "----------------------------------");
    temp = extractHEAP(heap);
    freeINTEGER(temp);
    displayH(heap, stdout);
    
    printf("%s\n\n", "freeing and exiting. . . ");
    freeHEAP(heap);
    
    return 0;
}

void 
displayH(HEAP *heap, FILE *fp) {
	printf("\n");
    printf("in-order: ");
    displayHEAP(heap,fp);
    printf("\n");
    printf("level: ");
    displayHEAPdebug(heap,fp);
    printf("\n");
}