#include "library.h"

short isEmptyl(pTreel a){	// checks if the tree is empty
	if (a == NULL){
		return 1;
	}
	return 0;
}

int heightl(pTreel a){		// calculates the height of the tree
	if(isEmptyl(a)){
		return 0;
	}
	return 1 + max2(heightl(a->l),heightl(a->r));
}

pTreel cTreel(int e, float f){		// creates a tree which stores the route ID and total distance
	pTreel a = malloc(sizeof(Treel));
	if (a == NULL){
		printf("Error cTreel\n");
		exit(10);
	}
	a->l = NULL;
	a->r = NULL;
	a->n = e;
	a->f = f;
	a->eq=heightl(a->r)-heightl(a->l);
	return a;
}

Chainl* cChainl(pTreel a){	// creates a linked list for the queue
	Chainl* c = malloc(sizeof(Chainl));
	if (c == NULL || a == NULL){
		printf("Error cChainl\n");
		exit(11);
	}
	c->a = a;
	c->next = NULL;
	c->last = NULL;
	return c;
}

Queuel cQueuel(pTreel a){	// creates a queue which contains a tree
	if (a == NULL){
		printf("Error cQueuel\n");
		exit(12);
	}
	Queuel f;
	Chainl* c = cChainl(a);
	f.head = c;
	f.tail = c;
	return f;
}

Queuel enterl(Queuel f, pTreel a){	// enters the tree in the queue
	if (a == NULL){
		return f;
	}
	if (f.tail == NULL){
		f = cQueuel(a);
		return f;
	}
	Chainl* c = cChainl(a);
	f.tail->next = c;
	c->last = f.tail;
	f.tail = f.tail->next;
	return f;
}

pTreel rmQueuel(Queuel* f){	// removes a slot from the queue and returns the tree which was inside
	if(f->head == NULL){
		return NULL;
	}
	Chainl* del = f->head;
	pTreel a = f->head->a;
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

short existLBl(pTreel a){	// checks if the left branch of the tree exists
	if (a == NULL){
		printf("Error existLBl\n");
		exit(22);
	}
	if (isEmptyl(a->l)){
		return 1;
	}
	return 0;
}

short existRBl(pTreel a){	// checks if the right branch of the tree exists
	if (a == NULL){
		printf("Error existRBl\n");
		exit(23);
	}
	if (isEmptyl(a->r)){
		return 1;
	}
	return 0;
}

pTreel lRotl (pTreel a){	// left rotation for the AVL
	pTreel pivot;
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

pTreel rRotl (pTreel a){	// right rotation for the AVL
	pTreel pivot;
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

pTreel doubleLRotl(pTreel a){	// right-left rotation for the AVL
	a->r=rRotl(a->r);
	return lRotl(a);
}

pTreel doubleRRotl(pTreel a){	// left-right rotation for the AVL
	a->l=lRotl(a->l);
	return rRotl(a);
}

pTreel eqAVLl(pTreel a){	// checks the tree's balance to determine if a rotation is needed and makes the correct rotation
	if(existRBl(a)){
		if(a->eq >= 2){
			if(a->r->eq >= 0){
				return lRotl(a);
			}
			else {
				return doubleLRotl(a);
			}
		}
	}
	else if (a->eq <= -2){
		if(existLBl(a)){
			if(a->l->eq <= 0){
				return rRotl(a);
			}
			else {
				return doubleRRotl(a);
			}
		}
	}
	return a;
}

pTreel insertAVLl(pTreel a, int e, float x, int* h){	// inserts a route ID and distance into an AVL
	if (a==NULL){
		*h=1;
		return cTreel(e, x);
	}
	else if (e < a->n){
		a->l=insertAVLl(a->l, e, x, h);
		*h=-*h;
	}
	else if (e > a->n){
		a->r=insertAVLl(a->r, e, x, h);
	}
	else{						// if the ID is already in the tree, the distance will add to the ID's distance value
		*h=0;
		a->f += x;
		return a;
	}
	if(*h!=0){	
		a->eq = a->eq + *h;
		a=eqAVLl(a);
		if(a->eq==0){	
			*h=0;
		}
		else{	
			*h=1;
		}
	}
	return a;
}

void infix1l(pTreel a, Queuel* f){	// fills a queue with the tree which was sorted by route ID
	if(a != NULL){
		infix1l(a->l, f);
		*f = enterl(*f, a);
		infix1l(a->r, f);
	}
}

pTreel addBSTl(pTreel a, int e, float x){	// sorts the route IDs by their total distance from shortest to longest
	if (a == NULL){
		a = cTreel(e, x);
	}
	else if (x > a->f){
		if(a->r == NULL){
			a->r = cTreel(e, x);
		}
		else{
			addBSTl(a->r, e, x);
		}
	}
	else if (x < a->f){
		if(a->l == NULL){
			a->l = cTreel(e, x);
		}
		else{
			addBSTl(a->l, e, x);
		}
	}
}

short isBSTl(pTreel a){				// checks if the tree is already sorted
	if (a == NULL){
		return 1;
	}
	pTreel n = malloc(sizeof(Treel));
	Queuel f;
	f.head = NULL;
	f.tail = NULL;
	if(n == NULL){
		printf("error isBSTl\n");
		exit(31);
	}
	infix1l(a, &f);
	n = rmQueuel(&f);
	while(f.head != NULL){
		if(n->f >= f.head->a->f){	// usage of a queue to compare the distance values
			return 0;
		}
		n = rmQueuel(&f);
	}
	return 1;
}

pTreel cBSTFromTreel(pTreel a){			// creates a tree sorted by total distance from the tree which was sorted by route ID
	if(isBSTl(a)){				// doesn't create another tree if it's already sorted
		return a;
	}
	pTreel n = malloc(sizeof(Treel));
	Queuel* f = malloc(sizeof(Queuel));
	f->head = NULL;
	f->tail = NULL;
	if(n == NULL){
		printf("error cBSTFromTreel\n");
		exit(32);
	}
	infix1l(a, f);				// usage of a queue to get the values from the original tree
	pTreel bst = malloc(sizeof(Treel));
	if(bst == NULL){
		printf("error cBSTFromTreel\n");
		exit(33);
	}
	while(f->head != NULL){
		n = rmQueuel(f);
		addBSTl(bst, n->n, n->f);	// sorts the route IDs by their total distance from shortest to longest instead of route ID
	}
	return bst;
}

void processl(pTreel a){	// writes down the route ID and distance into a file which will be used to draw the graph
	if (a != NULL){
		printf("%d;%f\n", a->n, a->f);
	}
}

void infix2l(pTreel a){		// writes down the route ID and distance from longest distance to shortest
	if(a != NULL){
		infix2l(a->r);
		processl(a);
		infix2l(a->l);
	}
}
