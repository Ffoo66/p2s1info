#include "library.h"

short isEmptyl(pTreel a){
	if (a == NULL){
		return 1;
	}
	return 0;
}

int heightl(pTreel a){
	if(isEmptyl(a)){
		return 0;
	}
	return 1 + max2(heightl(a->l),heightl(a->r));
}

pTreel cTreel(int e, float f){
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

Chainl* cChainl(pTreel a){
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

Queuel cQueuel(pTreel a){
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

Queuel enterl(Queuel f, pTreel a){
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

pTreel rmQueuel(Queuel* f){
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

short existLBl(pTreel a){
	if (a == NULL){
		printf("Error existLBl\n");
		exit(22);
	}
	if (isEmptyl(a->l)){
		return 1;
	}
	return 0;
}

short existRBl(pTreel a){
	if (a == NULL){
		printf("Error existRBl\n");
		exit(23);
	}
	if (isEmptyl(a->r)){
		return 1;
	}
	return 0;
}

pTreel lRotl (pTreel a){
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

pTreel rRotl (pTreel a){
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

pTreel doubleLRotl(pTreel a){
	a->r=rRotl(a->r);
	return lRotl(a);
}

pTreel doubleRRotl(pTreel a){
	a->l=lRotl(a->l);
	return rRotl(a);
}

pTreel eqAVLl(pTreel a){
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

pTreel insertAVLl(pTreel a, int e, float x, int* h){
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
	else{
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

void infix1l(pTreel a, Queuel* f){
	if(a != NULL){
		infix1l(a->l, f);
		*f = enterl(*f, a);
		infix1l(a->r, f);
	}
}

pTreel addBSTl(pTreel a, int e, float x){
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

short isBSTl(pTreel a){
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
		if(n->f >= f.head->a->f){
			return 0;
		}
		n = rmQueuel(&f);
	}
	return 1;
}

pTreel cBSTFromTreel(pTreel a){
	if(isBSTl(a)){
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
	infix1l(a, f);
	pTreel bst = malloc(sizeof(Treel));
	if(bst == NULL){
		printf("error cBSTFromTreel\n");
		exit(33);
	}
	while(f->head != NULL){
		n = rmQueuel(f);
		addBSTl(bst, n->n, n->f);
	}
	return bst;
}

void processl(pTreel a){
	if (a != NULL){
		printf("%d;%f\n", a->n, a->f);
	}
}

void infix2l(pTreel a){
	if(a != NULL){
		infix2l(a->r);
		processl(a);
		infix2l(a->l);
	}
}
