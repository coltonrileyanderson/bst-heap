/* 
 * heapsort.c 
 * by Colton Andreson
 * Feb 15, 2018
 * 
 * this can be used to heapsort a unsorted heap.
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "scanner.h"
#include "heap.h"
#include "integer.h"
#include "string.h"
#include "real.h"

// 0 = i, 1 = r, 2 = s
int file_type = 0;

// 0 = I, 1 = D
int order = 0;

// 0 = don't explain, 1 = explain;
int explain = 0;

// holds the name of the file
char *filename = "";

static void Fatal(char *,...);
static int processOptions(int,char **);
static char *strdup (const char *s);
//static void displayH(HEAP *heap, FILE *fp);
static void heapsort(HEAP *h, void (*display)(void *, FILE *), void(*freeing)(void *), FILE *fp);


int
main(int argc,char **argv) {
	int argIndex;

	if (argc == 1) Fatal("%d arguments!\n",argc-1);

	argIndex = processOptions(argc,argv);

    if (argIndex == 1 && argc == 2)
        filename = argv[1];
    if (explain == 0){
        // increasing order
        if (order == 0) {
            //ints
            if (file_type == 0){
                HEAP *heap = newHEAP(displayINTEGER,compareINTEGER,freeINTEGER);

                FILE *inFile = fopen(filename, "r");

                int i = readInt(inFile);
                insertHEAP(heap,newINTEGER(i));

                while(!feof(inFile)){   
                    i = readInt(inFile);
                    if (i != 0 || !feof(inFile))
                        insertHEAP(heap,newINTEGER(i));
                }
                fclose(inFile);

                heapsort(heap, displayINTEGER, freeINTEGER, stdout);

                freeHEAP(heap);

            }

            // reals
            else if(file_type == 1){
                HEAP *heap = newHEAP(displayREAL,compareREAL,freeREAL);

                FILE *inFile = fopen(filename, "r");

                double d = readReal(inFile);
                insertHEAP(heap,newREAL(d));

                while(!feof(inFile)){   
                    d = readReal(inFile);
                    if (d != 0.0 || !feof(inFile))
                        insertHEAP(heap,newREAL(d));
                }
                fclose(inFile);

                heapsort(heap, displayREAL, freeREAL, stdout);

                freeHEAP(heap);
            }

            //tokens
            else if(file_type == 2){
                HEAP *heap = newHEAP(displaySTRING,compareSTRING,freeSTRING);

                FILE *inFile = fopen(filename, "r");

                char *c;
                char *str = "";

                if(stringPending(inFile)){
                    c = readString(inFile);
                }
                else {
                    c = readToken(inFile);
                }
                
                while (!feof(inFile)){
                    str = strdup(c);
                    insertHEAP(heap, newSTRING(str));

                    if(stringPending(inFile)){
                        c = readString(inFile);
                    }
                    else if (!feof(inFile)) {
                        c = readToken(inFile);
                    }
                }
                fclose(inFile);

                heapsort(heap, displaySTRING, freeSTRING, stdout);

                freeHEAP(heap);
            }
        }
        else if (order == 1) {
            //ints
            if (file_type == 0){
                HEAP *heap = newHEAP(displayINTEGER,compareINTEGERdecr,freeINTEGER);

                FILE *inFile = fopen(filename, "r");

                int i = readInt(inFile);
                insertHEAP(heap,newINTEGER(i));

                while(!feof(inFile)){   
                    i = readInt(inFile);
                    if (i != 0 || !feof(inFile))
                        insertHEAP(heap,newINTEGER(i));
                }
                fclose(inFile);

                heapsort(heap, displayINTEGER, freeINTEGER, stdout);

                freeHEAP(heap);
            }

            // reals
            else if(file_type == 1){
                HEAP *heap = newHEAP(displayREAL,compareREALdecr,freeREAL);

                FILE *inFile = fopen(filename, "r");

                double d = readReal(inFile);
                insertHEAP(heap,newREAL(d));

                while(!feof(inFile)){   
                    d = readReal(inFile);
                    if (d != 0.0 || !feof(inFile))
                        insertHEAP(heap,newREAL(d));
                }
                fclose(inFile);

                heapsort(heap, displayREAL, freeREAL, stdout);

                freeHEAP(heap);
            }

            //tokens
            else if(file_type == 2){
                HEAP *heap = newHEAP(displaySTRING,compareSTRINGdecr,freeSTRING);

                FILE *inFile = fopen(filename, "r");

                char *c;
                char *str = "";

                if(stringPending(inFile)){
                    c = readString(inFile);
                }
                else {
                    c = readToken(inFile);
                }
                
                while (!feof(inFile)){
                    str = strdup(c);
                    free(c);
                    insertHEAP(heap, newSTRING(str));

                    if(stringPending(inFile)){
                        c = readString(inFile);
                    }
                    else if (!feof(inFile)) {
                        c = readToken(inFile);
                    }
                }
                fclose(inFile);

                heapsort(heap, displaySTRING, freeSTRING, stdout);

                freeHEAP(heap);
            }
        }
    }
    else if (explain == 1) {
        printf("%s\n","Written by Colton Anderson");
        printf("%s%s%s%s%s\n","Inserting a value into the heap takes constant time because ", 
            "I use a queue to keep track of the node with open child to insert into. ",
            "Once that node is full, I pop it off the queue and insert at the next ",
            "node with free children. I insert left, then right, to maintain heap properties.", 
            "This is constant because it only ever checks one node, and inserts at that node.");
        printf("%s%s%s\n","Ordering the heap is linear because I use a stack to build the heap. ",
            "I start at the bottom of the heap and pop off values until I get to a node with a child (the middle node). ",
            "Then I bubble that node down. ");
        printf("%s%s%s\n","Extracting takes logarithmic time because I swap the root with the rightmost leaf node, ",
            "then I bubble that leaf node(now the root) down into its spot. ",
            "Which is a logarithmic operation.");
        exit(0);
    }
	return 0;
}

void
Fatal(char *fmt, ...) {
    va_list ap;

    fprintf(stderr,"An error occured: ");
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);

    exit(-1);
}

static int
processOptions(int argc, char **argv)
    {
    int argIndex;
    int argUsed;
    int separateArg;
    char *test;
    char *arg;

    argIndex = 1;

    test = argv[argc - 1];

    while (argIndex < argc && *argv[argIndex] == '-')
        {
        /* check if stdin, represented by "-" is an argument */
        /* if so, the end of options has been reached */
        if (argv[argIndex][1] == '\0') return argIndex;

        separateArg = 0;
        argUsed = 0;

        if (argv[argIndex][2] == '\0')
            {
            arg = argv[argIndex+1];
            separateArg = 1;
            }
        else{
            arg = argv[argIndex]+2;
        }

        switch (argv[argIndex][1])
            {
            /*
             * when option has an argument, do this
             *
             *     examples are -m4096 or -m 4096
             *
             *     case 'm':
             *         MemorySize = atol(arg);
             *         argUsed = 1;
             *         break;
             *
             *
             * when option does not have an argument, do this
             *
             *     example is -a
             *
             *     case 'a':
             *         PrintActions = 1;
             *         break;
             */
            case 'v':
                explain = 1;
                break;    
            case 'I':
                order = 0;

                test = arg;
                if (test[0] != '-'){
                    filename = arg;
                    argUsed = 1;
                }

                break;
            case 'D':
                order = 1;

                test = arg;
                if (test[0] != '-'){
                    filename = arg;
                    argUsed = 1;
                }
                
                break;
            case 'i':
                file_type = 0;

                test = arg;
                if (test[0] != '-'){
                    filename = arg;
                    argUsed = 1;
                }
                
                break;
            case 'r':
                file_type = 1;

                test = arg;
                if (test[0] != '-'){
                    filename = arg;
                    argUsed = 1;
                }
                
                break;
            case 's':
                file_type = 2;

                test = arg;
                if (test[0] != '-'){
                    filename = arg;
                    argUsed = 1;
                }
                
                break;
            default:
                Fatal("option %s not understood\n",argv[argIndex]);
            }

        if (separateArg && argUsed)
            ++argIndex;

        ++argIndex;
        }

    return argIndex;
    }

/*
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
*/

static char *
strdup (const char *s) {
    char *d = malloc (strlen (s) + 1);   // Space for length plus nul
    if (d == NULL) return NULL;          // No memory
    strcpy (d,s);                       // Copy the characters
    return d;                            // Return the new string
}
static void heapsort(HEAP *h, void (*display)(void *, FILE *), void (*freeing)(void *), FILE *fp){
    void *extracted;

    buildHEAP(h);
    //displayH(h, fp);

    extracted = extractHEAP(h);
    (*display)(extracted, fp);
    (*freeing)(extracted);

    while (sizeHEAP(h) != 0) {
        fprintf(fp, "%s", " ");
        extracted = extractHEAP(h);
        (*display)(extracted, fp);
        (*freeing)(extracted);

    }
    fprintf(fp, "\n");
}   