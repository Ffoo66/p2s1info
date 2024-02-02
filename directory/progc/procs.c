#include "library.h"

short isEmptys(pTrees a){	// checks if the tree is empty
	if (a == NULL){
		return 1;
	}
	return 0;
}

int heights(pTrees a){		// calculates the height of the tree
	if(isEmptys(a)){
		return 0;
	}
	return 1 + max2(heights(a->l),heights(a->r));
}

pTrees cTrees(int e, double f, double min, double max, double av){
// creates a tree which stores the route ID and a few statistics (min, max and average step distance)
	pTrees a = malloc(sizeof(Trees));
	if (a == NULL){
		printf("Error cTrees\n");
	exit(10);
	}
	a->l = NULL;
	a->r = NULL;
	a->count = 1;
	a->n = e;
	a->f = f;
	a->min = min;
	a->max = max;
	a->av = av;
	a->rank = max - min;
	a->eq=heights(a->r)-heights(a->l);
	return a;
}

Chains* cChains(pTrees a){	// creates a linked list for the queue
	Chains* c = malloc(sizeof(Chains));
	if (c == NULL || a == NULL){
		printf("Error cChains\n");
		exit(11);
	}
	c->a = a;
	c->next = NULL;
	c->last = NULL;
	return c;
}

Queues cQueues(pTrees a){	// creates a queue which contains a tree
	if (a == NULL){
		printf("Error cQueues\n");
		exit(12);
	}
	Queues f;
	Chains* c = cChains(a);
	f.head = c;
	f.tail = c;
	return f;
}

Queues enters(Queues f, pTrees a){	// enters the tree in the queue
	if (a == NULL){
		return f;
	}
	if (f.tail == NULL){
		f = cQueues(a);
		return f;
	}
	Chains* c = cChains(a);
	f.tail->next = c;
	c->last = f.tail;
	f.tail = f.tail->next;
	return f;
}

pTrees rmQueues(Queues* f){	// removes a slot from the queue and returns the tree which was inside
	if(f->head == NULL){
		return NULL;
	}
	Chains* del = f->head;
	pTrees a = f->head->a;
	if(f->head == f->tail){
		f->head = NULL;
		f->tail = NULL;
		free(del);
		return a;
	}
	else{
		f->head = f->head->next;
		f->head->last = NULL;
		free(del);
		return a;
	}
}

short existLBs(pTrees a){	// checks if the left branch of the tree exists
	if (a == NULL){
		printf("Error existLBs\n");
		exit(22);
	}
	if (isEmptys(a->l)){
		return 1;
	}
	return 0;
}

short existRBs(pTrees a){	// checks if the right branch of the tree exists
	if (a == NULL){
		printf("Error existRBs\n");
		exit(23);
	}
	if (isEmptys(a->r)){
		return 1;
	}
	return 0;
}

pTrees lRots (pTrees a){	// left rotation for the AVL
	pTrees pivot;
	int eqA;
	int eqP;
	pivot = a->r;
	a->r = pivot->l;
	pivot->l = a;
	eqA = a->eq;
	eqP = pivot->eq;
	a->eq = eqA - max2(eqP, 0) - 1;
	pivot->eq = min2(min2(eqA-2,eqA+eqP-2), eqP-1);
	a=pivot;
	return a;
}

pTrees rRots (pTrees a){	// right rotation for the AVL
	pTrees pivot;
	int eqA;
	int eqP;
	pivot = a->l;
	a->l = pivot->r;
	pivot->r = a;
	eqA = a->eq;
	eqP = pivot->eq;
	a->eq = eqA - min2(eqP, 0) + 1;
	pivot->eq = max2(max2(eqA+2,eqA+eqP+2), eqP+1);
	a=pivot;
	return a;
}

pTrees doubleLRots(pTrees a){	// right-left rotation for the AVL
	a->r=rRots(a->r);
	return lRots(a);
}

pTrees doubleRRots(pTrees a){	// left-right rotation for the AVL
	a->l=lRots(a->l);
	return rRots(a);
}

pTrees eqAVLs(pTrees a){	// checks the tree's balance to determine if a rotation is needed and makes the correct rotation
	if(existRBs(a)){
		if(a->eq >= 2){
			if(a->r->eq >= 0){
				return lRots(a);
			}
			else {
				return doubleLRots(a);
			}
		}
	}
	else if (a->eq <= -2){
		if(existLBs(a)){
			if(a->l->eq <= 0){
				return rRots(a);
			}
			else {
				return doubleRRots(a);
			}
		}
	}
	return a;
}

pTrees insertAVLs(pTrees a, int e, double x, int* h){
// inserts a route ID with a distance into an AVL sorted by route ID, the stats are modified if the ID is already in the AVL
	if (a==NULL){
		*h=1;
		return cTrees(e, x, x, x, x);
	}
	else if (e < a->n){
		a->l=insertAVLs(a->l, e, x, h);
		*h=-*h;
	}
	else if (e > a->n){
		a->r=insertAVLs(a->r, e, x, h);
	}
	else{		// if the route ID is already in the tree, changes the statistics according to the distance and adds one to the step count
		*h=0;
		a->f += x;
		a->count++;
		if (x > a->max){
			a->max = x;
		}
		if (x < a->min){
			a->min = x;
		}
		return a;
	}
	if(*h!=0){	
		a->eq = a->eq + *h;
		a=eqAVLs(a);
		if(a->eq==0){	
			*h=0;
		}
		else{	
			*h=1;
		}
	}
	return a;
}

void process1s(pTrees a){	// calculates the average distance per step and the max-min value
	if (a != NULL){
		a->av = a->f/a->count;
		a->rank = a->max - a->min;
	}
}

void infix1s(pTrees a, Queues* f){	// fills a queue with the tree sorted by route ID, calculates the average distance and the max-min value
	if(a != NULL){
		infix1s(a->l, f);
		process1s(a);
		*f = enters(*f, a);
		infix1s(a->r, f);
	}
}

pTrees addBSTs(pTrees a, int e, double x, double min, double max, double av){	// sorts the route IDs by max-min value from lowest to highest
	if (a == NULL){
		a = cTrees(e, x, min, max, av);
	}
	else if (x > a->rank){
		if(a->r == NULL){
			a->r = cTrees(e, x, min, max, av);
		}
		else{
			addBSTs(a->r, e, x, min, max, av);
		}
	}
	else if (x < a->rank){
		if(a->l == NULL){
			a->l = cTrees(e, x, min, max, av);
		}
		else{
			addBSTs(a->l, e, x, min, max, av);
		}
	}
}

short isBSTs(pTrees a){		// checks if the tree is already sorted
	if (a == NULL){
		return 1;
	}
	pTrees n = malloc(sizeof(Trees));
	Queues f;
	f.head = NULL;
	f.tail = NULL;
	if(n == NULL){
		printf("error isBSTs\n");
		exit(31);
	}
	infix1s(a, &f);
	n = rmQueues(&f);
	while(f.head != NULL){
		if(n->f >= f.head->a->f){	// usage of a queue to compare the max-min values
			return 0;
		}
		n = rmQueues(&f);
	}
	return 1;
}

pTrees cBSTFromTrees(pTrees a){		// creates a tree sorted by max-min from the tree which was sorted by route ID
	if(isBSTs(a)){			// doesn't create another tree if it's already sorted
		return a;
	}
	pTrees n = malloc(sizeof(Trees));
	Queues* f = malloc(sizeof(Queues));
	f->head = NULL;
	f->tail = NULL;
 	 if(n == NULL){
		printf("error cBSTFromTrees\n");
		exit(32);
	}
	infix1s(a, f);			// usage of a queue to get the values from the original tree
	pTrees bst = malloc(sizeof(Trees));
	if(bst == NULL){
		printf("error cBSTFromTrees\n");
		exit(33);
	}
	while(f->head != NULL){
		n = rmQueues(f);
		addBSTs(bst, n->n, n->rank, n->min, n->max, n->av);	// sorts the route IDs by max-min from lowest to highest instead of route ID
	}
	return bst;
}

void process2s(pTrees a){	// writes down the route ID and stats into a file which will be used to draw the graph
	if (a != NULL){
		printf("%d;%lf;%lf;%lf\n", a->n, a->av, a->min, a->max);
	}
}

void infix2s(pTrees a){		// writes down the route ID and stats by max-min value from highest to lowest
	if(a != NULL){
		infix2s(a->r);
		process2s(a);
		infix2s(a->l);
	}
}
