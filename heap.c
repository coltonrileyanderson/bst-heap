/* 
 * heap.c 
 * by Colton Andreson
 * Feb 15, 2018
 * 
 * this is the implementation of heap.h. 
 * this implementation can be used to build a generic heap
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "string.h"
#include "bst.h"
#include "heap.h"
#include "stack.h"
#include "queue.h"


struct heap {
	BST *tree;
	
	QUEUE *queue;
	STACK *stack;

	int size;

	void (*display)(void *v, FILE *fp);
	int (*comparator)(void *val1,void *val2);
    void (*free)(void *v);
}; 


static void
swapper (BSTNODE *n1, BSTNODE *n2) {
	void *temp;
	temp = getBSTNODEvalue(n1);
	setBSTNODEvalue(n1, getBSTNODEvalue(n2));
	setBSTNODEvalue(n2, temp);
}


static void bubbleDown(HEAP *h, BSTNODE *n);
/******************************************************************************************************/
/*											HEAP FUNCTIONS											  */
/******************************************************************************************************/

/******************************************************************************************************/
/*											HEAP CONSTRUCTOR										  */

HEAP *
newHEAP(void (*d)(void *,FILE *), int (*c)(void *,void *), void (*f)(void *)) {
	HEAP *nHeap = (HEAP *)malloc(sizeof(HEAP));

	assert(nHeap != 0);

	nHeap->display = d;
	nHeap->comparator = c;
	nHeap->free = f;

	nHeap->size = 0;

	BST *bst = newBST(nHeap->display, NULL, NULL, nHeap->free);
	STACK *stk = newSTACK(nHeap->display, NULL);
	QUEUE *que = newQUEUE(nHeap->display, NULL);

	nHeap->tree = bst;
	nHeap->stack = stk;
	nHeap->queue = que;

    return nHeap;
}

void
setHEAPsize(HEAP *h, int s) {
	h->size = s;
}

int
sizeHEAP(HEAP *h) {
	int s = h->size;
	return s;
}

void *
peekHEAP(HEAP *h){
	BST *t = h->tree;
	BSTNODE *temp = getBSTroot(t);
	void *rtn = getBSTNODEvalue(temp);
	return rtn;
}

void
insertHEAP(HEAP *h,void *value) {
	BST *t = h->tree;
	STACK *s = h->stack;
	QUEUE *q = h->queue;

	BSTNODE *n = newBSTNODE(value);
	int h_size, t_size;
	h_size = sizeHEAP(h);
	t_size = sizeBST(t);

	h_size += 1;
	t_size += 1;

	setHEAPsize(h, h_size);
	setBSTsize(t, t_size);

	if (getBSTroot(t) == NULL) {
		setBSTroot(t, n);
		setBSTNODEparent(n, NULL);
		setBSTNODEleft(n, NULL);
		setBSTNODEright(n, NULL);
		push(s, n);
		enqueue(q, n);

	}
	else {		
		while(1){
			BSTNODE *test = peekQUEUE(q);

			if (getBSTNODEleft(test) != NULL && getBSTNODEright(test) != NULL) {
				dequeue(q);

			}
			else if (getBSTNODEleft(test) == NULL && getBSTNODEright(test) == NULL) {
				setBSTNODEleft(test, n);
				setBSTNODEparent(n, test);
				push(s, n);
				enqueue(q, n);

				break;
			}

			else if (getBSTNODEleft(test) != NULL && getBSTNODEright(test) == NULL) {
				setBSTNODEright(test, n);
				setBSTNODEparent(n, test);
				push(s, n);
				enqueue(q, n);

				break;
			}
		}

		
	}
	
}

static void
bubbleDown(HEAP *h, BSTNODE *n) {
	BSTNODE *left = getBSTNODEleft(n);
	BSTNODE *right = getBSTNODEright(n);
	BSTNODE *test;

	if (left != 0 && h->comparator(getBSTNODEvalue(left), getBSTNODEvalue(n)) < 0){
		test = left;
	}
	else test = n;

	if(right != 0 && h->comparator(getBSTNODEvalue(right), getBSTNODEvalue(test)) < 0){
		test = right;
	}

	if (test != n){
		swapper(n, test);
		bubbleDown(h, test);
	}
}

void 
buildHEAP(HEAP *h) {
	//BST *t = h->tree;
	STACK *s = h->stack;
	STACK *newS = newSTACK(h->display, NULL);

	while(sizeSTACK(s) != 0) {
		BSTNODE *temp = pop(s);
		bubbleDown(h, temp);	
		push(newS, temp);
		
	}

	while(sizeSTACK(newS) != 0) {
		BSTNODE *node = pop(newS);

		push(s, node);
	}

	freeSTACK(newS);
}

void *
extractHEAP(HEAP *h) {
	BST *t = h->tree;
	STACK *s = h->stack;
	
	if(sizeHEAP(h) == 0)
		return NULL;

	BSTNODE *temp, *root;
	root = getBSTroot(t);
	temp = pop(s);

	if (root != temp) {
		swapper(root, temp);

		BSTNODE *parent;
		parent = getBSTNODEparent(temp);
		
		if (getBSTNODEleft(parent) == temp) {
			setBSTNODEleft(parent, NULL);
			setBSTNODEparent(temp, NULL);
			setBSTNODEleft(temp, NULL);
			setBSTNODEright(temp, NULL);
		} 

		else if (getBSTNODEright(parent) == temp) {
			setBSTNODEright(parent, NULL);
			setBSTNODEparent(temp, NULL);
			setBSTNODEleft(temp, NULL);
			setBSTNODEright(temp, NULL);
		}

		bubbleDown(h, root);
		//buildHEAP(h);
		
	}
	else {
		setBSTroot(t, NULL);
		setBSTNODEparent(temp, NULL);
		setBSTNODEleft(temp, NULL);
		setBSTNODEright(temp, NULL);
	}

	int size = sizeHEAP(h);
	size -= 1;
	setHEAPsize(h, size);
	void *rtn = getBSTNODEvalue(temp);
	freeBSTNODE(temp, NULL);
	return rtn;
	
	
}

void
displayHEAP(HEAP *h,FILE *fp) {
	BST *t = h->tree;
	if (t != NULL) {
		displayBST(t, fp);
	}
}

void
displayHEAPdebug(HEAP *h,FILE *fp) {
	BST *t = h->tree;
	int hs = sizeHEAP(h);
	int bsts = sizeHEAP(h);

	fprintf(fp, "heap size: %d\n", hs);
	fprintf(fp, "bst size: %d\n", bsts);

	if (t != NULL) {
		displayBSTdebug(t, fp);
	}
}


/******************************************************************************************************/
/*											free Functions											  */

void
freeHEAP(HEAP *h){
	BST *t = h->tree;
	QUEUE *q = h->queue;
	STACK *s = h->stack;

	freeBST(t);

	freeQUEUE(q);
	freeSTACK(s);

	free(h);
}
