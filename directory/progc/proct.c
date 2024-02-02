#include "library.h"

short isEmptyi(pTreei a){	// checks if the ID tree is empty
	if (a == NULL){
		return 1;
	}
	return 0;
}

int heighti(pTreei a){		// calculates the height of the ID tree
	if(isEmptyi(a)){
		return 0;
	}
	return 1 + max2(heighti(a->l),heighti(a->r));
}

pTreei cTreei(int e){		// creates a tree which stores route IDs
	pTreei a = malloc(sizeof(Treei));
	if (a == NULL){
		printf("Error cTreei\n");
		exit(10);
	}
	a->l = NULL;
	a->r = NULL;
	a->n = e;
	a->eq=heighti(a->r)-heighti(a->l);
	return a;
}

short existLBi(pTreei a){	// checks if the left branch of the ID tree exists
	if (a == NULL){
		printf("Error existLBi\n");
		exit(22);
	}
	if (isEmptyi(a->l)){
		return 1;
	}
	return 0;
}

short existRBi(pTreei a){	// checks if the right branch of the ID tree exists
	if (a == NULL){
		printf("Error existRBi\n");
		exit(23);
	}
	if (isEmptyi(a->r)){
		return 1;
	}
	return 0;
}

pTreei lRoti (pTreei a){	// left rotation for the ID AVL
	pTreei pivot;
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

pTreei rRoti (pTreei a){	// right rotation for the ID AVL
	pTreei pivot;
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

pTreei doubleLRoti(pTreei a){	// right-left rotation for the ID AVL
	a->r=rRoti(a->r);
	return lRoti(a);
}

pTreei doubleRRoti(pTreei a){	// left-right rotation for the ID AVL
	a->l=lRoti(a->l);
	return rRoti(a);
}

pTreei eqAVLi(pTreei a){	// checks the ID tree's balance to determine if a rotation is needed and makes the correct rotation
	if(existRBi(a)){
		if(a->eq >= 2){
			if(a->r->eq >= 0){
				return lRoti(a);
			}
			else {
				return doubleLRoti(a);
			}
		}
	}
	else if (a->eq <= -2){
		if(existLBi(a)){
			if(a->l->eq <= 0){
				return rRoti(a);
			}
			else {
				return doubleRRoti(a);
			}
		}
	}
	return a;
}

pTreei insertAVLi(pTreei a, int e, int* i, int* h){	// inserts a route ID into an AVL
	if (a==NULL){
		*h=1;
		*i=1;
		return cTreei(e);
	}
	else if (e < a->n){
		a->l=insertAVLi(a->l, e, i, h);
		*h=-*h;
	}
	else if (e > a->n){
		a->r=insertAVLi(a->r, e, i, h);
	}
	else{
		*h=0;
		return a;
	}
	if(*h!=0){	
		a->eq = a->eq + *h;
		a=eqAVLi(a);
		if(a->eq==0){	
			*h=0;
		}
		else{	
			*h=1;
		}
	}
	return a;
}

short isEmptyt1(pTreet1 a){	// checks if the main tree is empty
	if (a == NULL){
		return 1;
	}
	return 0;
}

int heightt1(pTreet1 a){	// calculates the height of the main tree
	if(isEmptyt1(a)){
		return 0;
	}
	return 1 + max2(heightt1(a->l),heightt1(a->r));
}

pTreet1 cTreet1(int e, char* city, int count, int fcount){	// creates a tree which stores the cities along with an ID AVL and counters
	pTreet1 a = malloc(sizeof(Treet1));
	if (a == NULL){
		printf("Error cTreet1\n");
		exit(10);
	}
	a->l = NULL;
	a->r = NULL;
	a->city = city;
	a->count = count;
	a->fcount = fcount;
	a->a = cTreei(e);
	a->i = 1;
	a->eq=heightt1(a->r)-heightt1(a->l);
	return a;
}

Chaint* cChaint(pTreet1 a){	// creates a linked list for the queue
	Chaint* c = malloc(sizeof(Chaint));
	if (c == NULL || a == NULL){
		printf("Error cChaint\n");
		exit(11);
	}
	c->a = a;
	c->next = NULL;
	c->last = NULL;
	return c;
}

Queuet cQueuet(pTreet1 a){	// creates a queue which contains a tree
	if (a == NULL){
		printf("Error cQueuet\n");
		exit(12);
	}
	Queuet f;
	Chaint* c = cChaint(a);
	f.head = c;
	f.tail = c;
	return f;
}

Queuet entert(Queuet f, pTreet1 a){	// enters the tree in the queue
	if (a == NULL){
		return f;
	}
	if (f.tail == NULL){
		f = cQueuet(a);
		return f;
	}
	Chaint* c = cChaint(a);
	f.tail->next = c;
	c->last = f.tail;
	f.tail = f.tail->next;
	return f;
}

pTreet1 rmQueuet(Queuet* f){	// removes a slot from the queue and returns the tree which was inside
	if(f->head == NULL){
		return NULL;
	}
	Chaint* del = f->head;
	pTreet1 a = f->head->a;
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

short existLBt1(pTreet1 a){	// checks if the left branch of the tree exists
	if (a == NULL){
		printf("Error existLBt1\n");
		exit(22);
	}
	if (isEmptyt1(a->l)){
		return 1;
	}
	return 0;
}

short existRBt1(pTreet1 a){	// checks if the right branch of the tree exists
	if (a == NULL){
		printf("Error existRBt1\n");
		exit(23);
	}
	if (isEmptyt1(a->r)){
		return 1;
	}
	return 0;
}

pTreet1 lRott1 (pTreet1 a){	// left rotation for the main AVL
	pTreet1 pivot;
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

pTreet1 rRott1 (pTreet1 a){	// right rotation for the main AVL
	pTreet1 pivot;
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

pTreet1 doubleLRott1(pTreet1 a){	// right-left rotation for the main AVL
	a->r=rRott1(a->r);
	return lRott1(a);
}

pTreet1 doubleRRott1(pTreet1 a){	// left-right rotation for the main AVL
	a->l=lRott1(a->l);
	return rRott1(a);
}

pTreet1 eqAVLt1(pTreet1 a){	// checks the main tree's balance to determine if a rotation is needed and makes the correct rotation
	if(existRBt1(a)){
		if(a->eq >= 2){
			if(a->r->eq >= 0){
				return lRott1(a);
			}
			else {
				return doubleLRott1(a);
			}
		}
	}
	else if (a->eq <= -2){
		if(existLBt1(a)){
			if(a->l->eq <= 0){
				return rRott1(a);
			}
			else {
				return doubleRRott1(a);
			}
		}
	}
	return a;
}

pTreet1 insertAVLt1(pTreet1 a, int e, char* city, int count, int fcount, int* h){	// inserts a city and a route ID into an AVL
	if (a==NULL){
		*h=1;
		return cTreet1(e, city, count, fcount);
	}
	else if (strcmp(city, a->city) < 0){
		a->l=insertAVLt1(a->l, e, city, count, fcount, h);
		*h=-*h;
	}
	else if (strcmp(city, a->city) > 0){
		a->r=insertAVLt1(a->r, e, city, count, fcount, h);
	}
	else{						// if the city is already in the AVL, adds the route ID into an AVL linked to the city
		int n = 0;
		a->a = insertAVLi(a->a, e, &n, h);
		if (n){					// if the ID was already in the AVL, the counters aren't modified
			a->count++;
			a->fcount += fcount;
		}
		*h=0;
		return a;
	}
	if(*h!=0){	
		a->eq = a->eq + *h;
		a=eqAVLt1(a);
		if(a->eq==0){	
			*h=0;
		}
		else{	
			*h=1;
		}
	}
	return a;
}

void infix1t1(pTreet1 a, Queuet* f){	// fills a queue with the tree which was sorted by alphabetical order
	if(a != NULL){
		infix1t1(a->l, f);
		*f = entert(*f, a);
		infix1t1(a->r, f);
	}
}

pTreet1 addBSTt(pTreet1 a, int e, char* city, int count, int fcount){	// sorts the cities from lowest total count to highest
	if (a == NULL){
		a = cTreet1(e, city, count, fcount);
	}
	else if (count > a->count){
		if(a->r == NULL){
			a->r = cTreet1(e, city, count, fcount);
		}
		else{
			addBSTt(a->r, e, city, count, fcount);
		}
	}
	else if (count < a->count){
		if(a->l == NULL){
			a->l = cTreet1(e, city, count, fcount);
		}
		else{
			addBSTt(a->l, e, city, count, fcount);
		}
	}
}

short isBSTt(pTreet1 a){	// checks if the tree is already sorted
	if (a == NULL){
		return 1;
	}
	pTreet1 n = malloc(sizeof(Treet1));
	Queuet f;
	f.head = NULL;
	f.tail = NULL;
	if(n == NULL){
		printf("error isBSTt\n");
		exit(31);
	}
	infix1t1(a, &f);
	n = rmQueuet(&f);
	while(f.head != NULL){
		if(n->count >= f.head->a->count){	// usage of a queue to compare the total count values
			return 0;
		}
		n = rmQueuet(&f);
	}
	return 1;
}

pTreet1 cBSTFromTreet(pTreet1 a){	// creates a tree sorted by total count from the tree which was sorted by alphabetical order
	if(isBSTt(a)){			// doesn't create another tree if it's already sorted
		return a;
	}
	pTreet1 n = malloc(sizeof(Treet1));
	Queuet* f = malloc(sizeof(Queuet));
	f->head = NULL;
	f->tail = NULL;
	if(n == NULL){
		printf("error cBSTFromTreet\n");
		exit(32);
	}
	infix1t1(a, f);			// usage of a queue to get the values from the original tree
	pTreet1 bst = malloc(sizeof(Treet1));
	if(bst == NULL){
		printf("error cBSTFromTreet\n");
		exit(33);
	}
	while(f->head != NULL){
		n = rmQueuet(f);
		addBSTt(bst, n->a->n, n->city, n->count, n->fcount);	// sorts from lowest total count to highest instead of alphabetical order
	}
	return bst;
}

void processt1(pTreet1 a){
// writes down how many times a city is visited and how many times it was the departure city along with its name itself into a file which will be sorted by alphabetical order
	if (a != NULL){
		printf("%d;%d;%s", a->count, a->fcount, a->city);
	}
}

void infix2t1(pTreet1 a){	// writes down both counters and the city's name from highest total count to lowest
	if(a != NULL){
		infix2t1(a->r);
		processt1(a);
		infix2t1(a->l);
	}
}

short isEmptyt2(pTreet2 a){	// checks if the final tree is empty
	if (a == NULL){
		return 1;
	}
	return 0;
}

int heightt2(pTreet2 a){	// calculates the height of the final tree
	if(isEmptyt2(a)){
		return 0;
	}
	return 1 + max2(heightt2(a->l),heightt2(a->r));
}

pTreet2 cTreet2(char* city, int count, int fcount){	// creates a tree which stores the city and counters
	pTreet2 a = malloc(sizeof(Treet2));
	if (a == NULL){
		printf("Error cTreet2\n");
		exit(10);
	}
	a->l = NULL;
	a->r = NULL;
	a->city = city;
	a->count = count;
	a->fcount = fcount;
	a->eq=heightt2(a->r)-heightt2(a->l);
	return a;
}

short existLBt2(pTreet2 a){	// checks if the left branch of the final tree exists
	if (a == NULL){
		printf("Error existLBt2\n");
		exit(22);
	}
	if (isEmptyt2(a->l)){
		return 1;
	}
	return 0;
}

short existRBt2(pTreet2 a){	// checks if the right branch of the final tree exists
	if (a == NULL){
		printf("Error existRBt2\n");
		exit(23);
	}
	if (isEmptyt2(a->r)){
		return 1;
	}
	return 0;
}

pTreet2 lRott2 (pTreet2 a){	// left rotation for the final AVL
	pTreet2 pivot;
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

pTreet2 rRott2 (pTreet2 a){	// right rotation for the final AVL
	pTreet2 pivot;
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

pTreet2 doubleLRott2(pTreet2 a){	// right-left rotation for the final AVL
	a->r=rRott2(a->r);
	return lRott2(a);
}

pTreet2 doubleRRott2(pTreet2 a){	// left-right rotation for the final AVL
	a->l=lRott2(a->l);
	return rRott2(a);
}

pTreet2 eqAVLt2(pTreet2 a){	// checks the final tree's balance to determine if a rotation is needed and makes the correct rotation
	if(existRBt2(a)){
		if(a->eq >= 2){
			if(a->r->eq >= 0){
				return lRott2(a);
			}
			else {
				return doubleLRott2(a);
			}
		}
	}
	else if (a->eq <= -2){
		if(existLBt2(a)){
			if(a->l->eq <= 0){
				return rRott2(a);
			}
			else {
				return doubleRRott2(a);
			}
		}
	}
	return a;
}

pTreet2 insertAVLt2(pTreet2 a, char* city, int count, int fcount, int* h){	// inserts a city and a route ID in an AVL sorted by alphabetical order
	if (a==NULL){
		*h=1;
		return cTreet2(city, count, fcount);
	}
	else if (strcmp(city, a->city) < 0){
		a->l=insertAVLt2(a->l, city, count, fcount, h);
		*h=-*h;
	}
	else if (strcmp(city, a->city) > 0){
		a->r=insertAVLt2(a->r, city, count, fcount, h);
	}
	else{
		*h=0;
		a->count = count;
		a->fcount = fcount;
		return a;
	}
	if(*h!=0){	
		a->eq = a->eq + *h;
		a=eqAVLt2(a);
		if(a->eq==0){	
			*h=0;
		}
		else{	
			*h=1;
		}
	}
	return a;
}

void processt2(pTreet2 a){
// writes down how many times a city is visited and how many times it was the departure city along with its name into a file which will be used to draw the graph
	if (a != NULL){
		printf("%d;%d;%s", a->count, a->fcount, a->city);
	}
}

void infixt2(pTreet2 a){	// writes down both counters and the city's name by alphabetical order
	if(a != NULL){
		infixt2(a->l);
		processt2(a);
		infixt2(a->r);
	}
}
