#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

typedef struct Tree{
	struct Tree* l;
	struct Tree* r;
	char* city;
	int count;
	int fcount;
	int n;
	float f;
	float min;
	float max;
	float moy;
	short eq;
}Tree;

typedef struct Tree* pTree;

typedef struct Treel{
	struct Treel* l;
	struct Treel* r;
	int n;
	float f;
	short eq;
}Treel;

typedef struct Treel* pTreel;

typedef struct Treet1{
	struct Treet1* l;
	struct Treet1* r;
	char* city;
	int count;
	int fcount;
	int n;
	short eq;
}Treet1;

typedef struct Treet1* pTreet1;

typedef struct Treet2{
	struct Treet2* l;
	struct Treet2* r;
	char* city;
	int count;
	int fcount;
	short eq;
}Treet2;

typedef struct Treet2* pTreet2;

typedef struct Trees{
	struct Trees* l;
	struct Trees* r;
	char* city;
	int count;
	int n;
	float f;
	float min;
	float max;
	float moy;
	short eq;
}Trees;

typedef struct Trees* pTrees;

typedef struct Chainon{
	struct Chainon* last;
	pTree a;
	struct Chainon* next;
}Chain;

typedef struct File{
	Chain* head;
	Chain* tail;
}File;

typedef struct Chainonl{
	struct Chainonl* last;
	pTreel a;
	struct Chainonl* next;
}Chainl;

typedef struct Filel{
	Chainl* head;
	Chainl* tail;
}Filel;

typedef struct Chainont{
	struct Chainont* last;
	pTreet1 a;
	struct Chainont* next;
}Chaint;

typedef struct Filet{
	Chaint* head;
	Chaint* tail;
}Filet;

typedef struct Chainons{
	struct Chainons* last;
	pTrees a;
	struct Chainons* next;
}Chains;

typedef struct Files{
	Chains* head;
	Chains* tail;
}Files;

int scan(char** input){							// scanf function but deletes the end
	int a=scanf("%s", input);
	while(getchar() != '\n'){}
	return a;
}

int max2 (int a, int b){
	int m;
	if (a>=b){
		m=a;
	}
	else{
		m=b;
	}
	return m;
}

int min2 (int a, int b){
	int m;
	if (a<=b){
		m=a;
	}
	else{
		m=b;
	}
	return m;
}

short estVide(pTree a){
	if (a == NULL){
		return 1;
	}
	return 0;
}

int hauteur(pTree a){
	if(estVide(a)){
		return 0;
	}
	return 1 + max2(hauteur(a->l),hauteur(a->r));
}

short estVidel(pTreel a){
	if (a == NULL){
		return 1;
	}
	return 0;
}

int hauteurl(pTreel a){
	if(estVidel(a)){
		return 0;
	}
	return 1 + max2(hauteurl(a->l),hauteurl(a->r));
}

short estVidet1(pTreet1 a){
	if (a == NULL){
		return 1;
	}
	return 0;
}

int hauteurt1(pTreet1 a){
	if(estVidet1(a)){
		return 0;
	}
	return 1 + max2(hauteurt1(a->l),hauteurt1(a->r));
}

short estVidet2(pTreet2 a){
	if (a == NULL){
		return 1;
	}
	return 0;
}

int hauteurt2(pTreet2 a){
	if(estVidet2(a)){
		return 0;
	}
	return 1 + max2(hauteurt2(a->l),hauteurt2(a->r));
}

short estVides(pTrees a){
	if (a == NULL){
		return 1;
	}
	return 0;
}

int hauteurs(pTrees a){
	if(estVides(a)){
		return 0;
	}
	return 1 + max2(hauteurs(a->l),hauteurs(a->r));
}

pTree creerArbre(int e, float f, char* city, int count, int fcount){
	pTree a = malloc(sizeof(Tree));
	if (a == NULL){
		printf("Error creerArbre\n");
		exit(10);
	}
	a->l = NULL;
	a->r = NULL;
	a->city = city;
	a->count = count;
	a->fcount = fcount;
	a->n = e;
	a->f = f;
	a->min = f;
	a->max = f;
	a->moy = f;
	a->eq=hauteur(a->r)-hauteur(a->l);
	return a;
}

pTreel creerArbrel(int e, float f){
	pTreel a = malloc(sizeof(Treel));
	if (a == NULL){
		printf("Error creerArbrel\n");
		exit(10);
	}
	a->l = NULL;
	a->r = NULL;
	a->n = e;
	a->f = f;
	a->eq=hauteurl(a->r)-hauteurl(a->l);
	return a;
}

pTreet1 creerArbret1(int e, char* city, int count, int fcount){
	pTreet1 a = malloc(sizeof(Treet1));
	if (a == NULL){
		printf("Error creerArbret1\n");
		exit(10);
	}
	a->l = NULL;
	a->r = NULL;
	a->city = city;
	a->count = count;
	a->fcount = fcount;
	a->n = e;
	a->eq=hauteurt1(a->r)-hauteurt1(a->l);
	return a;
}

pTreet2 creerArbret2(char* city, int count, int fcount){
	pTreet2 a = malloc(sizeof(Treet2));
	if (a == NULL){
		printf("Error creerArbret2\n");
		exit(10);
	}
	a->l = NULL;
	a->r = NULL;
	a->city = city;
	a->count = count;
	a->fcount = fcount;
	a->eq=hauteurt2(a->r)-hauteurt2(a->l);
	return a;
}

pTrees creerArbres(int e, float f, float min, float max, float moy){
	pTrees a = malloc(sizeof(Trees));
	if (a == NULL){
		printf("Error creerArbres\n");
	exit(10);
	}
	a->l = NULL;
	a->r = NULL;
	a->city = NULL;
	a->count = 1;
	a->n = e;
	a->f = f;
	a->min = min;
	a->max = max;
	a->moy = moy;
	a->eq=hauteurs(a->r)-hauteurs(a->l);
	return a;
}

Chain* creerChainon(pTree a){
	Chain* c = malloc(sizeof(Chain));
	if (c == NULL || a == NULL){
		printf("Error creerChainon\n");
		exit(11);
	}
	c->a = a;
	c->next = NULL;
	c->last = NULL;
	return c;
}

File creerFile(pTree a){
	if (a == NULL){
		printf("Error creerFile\n");
		exit(12);
	}
	File f;
	Chain* c = creerChainon(a);
	f.head = c;
	f.tail = c;
	return f;
}

File enfiler(File f, pTree a){
	if (a == NULL){
		return f;
	}
	if (f.tail == NULL){
		f = creerFile(a);
		return f;
	}
	Chain* c = creerChainon(a);
	f.tail->next = c;
	c->last = f.tail;
	f.tail = f.tail->next;
	return f;
}

pTree defiler(File* f){
	if(f->head == NULL){
		return NULL;
	}
	Chain* del = f->head;
	pTree a = f->head->a;
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

Chainl* creerChainonl(pTreel a){
	Chainl* c = malloc(sizeof(Chainl));
	if (c == NULL || a == NULL){
		printf("Error creerChainonl\n");
		exit(11);
	}
	c->a = a;
	c->next = NULL;
	c->last = NULL;
	return c;
}

Filel creerFilel(pTreel a){
	if (a == NULL){
		printf("Error creerFilel\n");
		exit(12);
	}
	Filel f;
	Chainl* c = creerChainonl(a);
	f.head = c;
	f.tail = c;
	return f;
}

Filel enfilerl(Filel f, pTreel a){
	if (a == NULL){
		return f;
	}
	if (f.tail == NULL){
		f = creerFilel(a);
		return f;
	}
	Chainl* c = creerChainonl(a);
	f.tail->next = c;
	c->last = f.tail;
	f.tail = f.tail->next;
	return f;
}

pTreel defilerl(Filel* f){
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

Chaint* creerChainont(pTreet1 a){
	Chaint* c = malloc(sizeof(Chaint));
	if (c == NULL || a == NULL){
		printf("Error creerChainont\n");
		exit(11);
	}
	c->a = a;
	c->next = NULL;
	c->last = NULL;
	return c;
}

Filet creerFilet(pTreet1 a){
	if (a == NULL){
		printf("Error creerFilet\n");
		exit(12);
	}
	Filet f;
	Chaint* c = creerChainont(a);
	f.head = c;
	f.tail = c;
	return f;
}

Filet enfilert(Filet f, pTreet1 a){
	if (a == NULL){
		return f;
	}
	if (f.tail == NULL){
		f = creerFilet(a);
		return f;
	}
	Chaint* c = creerChainont(a);
	f.tail->next = c;
	c->last = f.tail;
	f.tail = f.tail->next;
	return f;
}

pTreet1 defilert(Filet* f){
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

Chains* creerChainons(pTrees a){
	Chains* c = malloc(sizeof(Chains));
	if (c == NULL || a == NULL){
		printf("Error creerChainons\n");
		exit(11);
	}
	c->a = a;
	c->next = NULL;
	c->last = NULL;
	return c;
}

Files creerFiles(pTrees a){
	if (a == NULL){
		printf("Error creerFiles\n");
		exit(12);
	}
	Files f;
	Chains* c = creerChainons(a);
	f.head = c;
	f.tail = c;
	return f;
}

Files enfilers(Files f, pTrees a){
	if (a == NULL){
		return f;
	}
	if (f.tail == NULL){
		f = creerFiles(a);
		return f;
	}
	Chains* c = creerChainons(a);
	f.tail->next = c;
	c->last = f.tail;
	f.tail = f.tail->next;
	return f;
}

pTrees defilers(Files* f){
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

short existeFilsGauche(pTree a){
	if (a == NULL){
		printf("Error existeFilsGauche\n");
		exit(22);
	}
	if (estVide(a->l)){
		return 1;
	}
	return 0;
}

short existeFilsDroit(pTree a){
	if (a == NULL){
		printf("Error existeFilsDroit\n");
		exit(23);
	}
	if (estVide(a->r)){
		return 1;
	}
	return 0;
}

short existeFilsGauchel(pTreel a){
	if (a == NULL){
		printf("Error existeFilsGauchel\n");
		exit(22);
	}
	if (estVidel(a->l)){
		return 1;
	}
	return 0;
}

short existeFilsDroitl(pTreel a){
	if (a == NULL){
		printf("Error existeFilsDroitl\n");
		exit(23);
	}
	if (estVidel(a->r)){
		return 1;
	}
	return 0;
}

short existeFilsGauchet1(pTreet1 a){
	if (a == NULL){
		printf("Error existeFilsGauchet1\n");
		exit(22);
	}
	if (estVidet1(a->l)){
		return 1;
	}
	return 0;
}

short existeFilsDroitt1(pTreet1 a){
	if (a == NULL){
		printf("Error existeFilsDroitt1\n");
		exit(23);
	}
	if (estVidet1(a->r)){
		return 1;
	}
	return 0;
}

short existeFilsGauchet2(pTreet2 a){
	if (a == NULL){
		printf("Error existeFilsGauchet2\n");
		exit(22);
	}
	if (estVidet2(a->l)){
		return 1;
	}
	return 0;
}

short existeFilsDroitt2(pTreet2 a){
	if (a == NULL){
		printf("Error existeFilsDroitt2\n");
		exit(23);
	}
	if (estVidet2(a->r)){
		return 1;
	}
	return 0;
}

short existeFilsGauches(pTrees a){
	if (a == NULL){
		printf("Error existeFilsGauches\n");
		exit(22);
	}
	if (estVides(a->l)){
		return 1;
	}
	return 0;
}

short existeFilsDroits(pTrees a){
	if (a == NULL){
		printf("Error existeFilsDroits\n");
		exit(23);
	}
	if (estVides(a->r)){
		return 1;
	}
	return 0;
}

void traiterl(pTreel a){
	if (a != NULL){
		printf("%d;%f\n", a->n, a->f);
	}
}

void traitert1(pTreet1 a){
	if (a != NULL){
		printf("%d;%d;%s", a->count, a->fcount, a->city);
	}
}

void traitert2(pTreet2 a){
	if (a != NULL){
		printf("%d;%d;%s", a->count, a->fcount, a->city);
	}
}

void traiter1s(pTrees a){
	if (a != NULL){
		a->moy = a->f/a->count;
		a->f = a->max - a->min;
	}
}

void traiter2s(pTrees a){
	if (a != NULL){
		printf("%d;%f;%f;%f\n", a->n, a->min, a->max, a->moy);
	}
}

void parcoursInfixe1(pTree a, File* f){
	if(a != NULL){
		parcoursInfixe1(a->l, f);
		*f = enfiler(*f, a);
		parcoursInfixe1(a->r, f);
	}
}

void parcoursInfixe1l(pTreel a, Filel* f){
	if(a != NULL){
		parcoursInfixe1l(a->l, f);
		*f = enfilerl(*f, a);
		parcoursInfixe1l(a->r, f);
	}
}

void parcoursInfixe1t(pTreet1 a, Filet* f){
	if(a != NULL){
		parcoursInfixe1t(a->l, f);
		*f = enfilert(*f, a);
		parcoursInfixe1t(a->r, f);
	}
}

void parcoursInfixe1s(pTrees a, Files* f){
	if(a != NULL){
		parcoursInfixe1s(a->l, f);
		traiter1s(a);
		*f = enfilers(*f, a);
		parcoursInfixe1s(a->r, f);
	}
}

void parcoursInfixe2l(pTreel a){
	if(a != NULL){
		parcoursInfixe2l(a->r);
		traiterl(a);
		parcoursInfixe2l(a->l);
	}
}

void parcoursInfixe2t1(pTreet1 a){
	if(a != NULL){
		parcoursInfixe2t1(a->r);
		traitert1(a);
		parcoursInfixe2t1(a->l);
	}
}


void parcoursInfixe2t2(pTreet2 a){
	if(a != NULL){
		parcoursInfixe2t2(a->l);
		traitert2(a);
		parcoursInfixe2t2(a->r);
	}
}

void parcoursInfixe2s(pTrees a){
	if(a != NULL){
		parcoursInfixe2s(a->r);
		traiter2s(a);
		parcoursInfixe2s(a->l);
	}
}

pTreel ajouterABRref(pTreel a, int e, float x){
	if (a == NULL){
		a = creerArbrel(e, x);
	}
	else if (x > a->f){
		if(a->r == NULL){
			a->r = creerArbrel(e, x);
		}
		else{
			ajouterABRref(a->r, e, x);
		}
	}
	else if (x < a->f){
		if(a->l == NULL){
			a->l = creerArbrel(e, x);
		}
		else{
			ajouterABRref(a->l, e, x);
		}
	}
}

pTreet1 ajouterABRret(pTreet1 a, int e, char* city, int count, int fcount){
	if (a == NULL){
		a = creerArbret1(e, city, count, fcount);
	}
	else if (count > a->count){
		if(a->r == NULL){
			a->r = creerArbret1(e, city, count, fcount);
		}
		else{
			ajouterABRret(a->r, e, city, count, fcount);
		}
	}
	else if (count < a->count){
		if(a->l == NULL){
			a->l = creerArbret1(e, city, count, fcount);
		}
		else{
			ajouterABRret(a->l, e, city, count, fcount);
		}
	}
}

pTrees ajouterABRres(pTrees a, int e, float x, float min, float max, float moy){
	if (a == NULL){
		a = creerArbres(e, x, min, max, moy);
	}
	else if (x > a->f){
		if(a->r == NULL){
			a->r = creerArbres(e, x, min, max, moy);
		}
		else{
			ajouterABRres(a->r, e, x, min, max, moy);
		}
	}
	else if (x < a->f){
		if(a->l == NULL){
			a->l = creerArbres(e, x, min, max, moy);
		}
		else{
			ajouterABRres(a->l, e, x, min, max, moy);
		}
	}
}

short estABR(pTree a){
	if (a == NULL){
		return 1;
	}
	pTree n = malloc(sizeof(Tree));
	File f;
	f.head = NULL;
	f.tail = NULL;
	if(n == NULL){
		printf("error estABR\n");
		exit(31);
	}
	parcoursInfixe1(a, &f);
	n = defiler(&f);
	while(f.head != NULL){
		if(n->f >= f.head->a->f){
			return 0;
		}
		n = defiler(&f);
	}
	return 1;
}

short estABRl(pTreel a){
	if (a == NULL){
		return 1;
	}
	pTreel n = malloc(sizeof(Treel));
	Filel f;
	f.head = NULL;
	f.tail = NULL;
	if(n == NULL){
		printf("error estABRl\n");
		exit(31);
	}
	parcoursInfixe1l(a, &f);
	n = defilerl(&f);
	while(f.head != NULL){
		if(n->f >= f.head->a->f){
			return 0;
		}
		n = defilerl(&f);
	}
	return 1;
}

short estABRt(pTreet1 a){
	if (a == NULL){
		return 1;
	}
	pTreet1 n = malloc(sizeof(Treet1));
	Filet f;
	f.head = NULL;
	f.tail = NULL;
	if(n == NULL){
		printf("error estABRt\n");
		exit(31);
	}
	parcoursInfixe1t(a, &f);
	n = defilert(&f);
	while(f.head != NULL){
		if(n->count >= f.head->a->count){
			return 0;
		}
		n = defilert(&f);
	}
	return 1;
}

short estABRs(pTrees a){
	if (a == NULL){
		return 1;
	}
	pTrees n = malloc(sizeof(Trees));
	Files f;
	f.head = NULL;
	f.tail = NULL;
	if(n == NULL){
		printf("error estABRs\n");
		exit(31);
	}
	parcoursInfixe1s(a, &f);
	n = defilers(&f);
	while(f.head != NULL){
		if(n->f >= f.head->a->f){
			return 0;
		}
		n = defilers(&f);
	}
	return 1;
}

pTree rotationG (pTree a){
	pTree pivot;
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

pTree rotationD (pTree a){
	pTree pivot;
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

pTree doubleRotationG(pTree a){
	a->r=rotationD(a->r);
	return rotationG(a);
}

pTree doubleRotationD(pTree a){
	a->l=rotationG(a->l);
	return rotationD(a);
}

pTreel rotationGl (pTreel a){
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

pTreel rotationDl (pTreel a){
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

pTreel doubleRotationGl(pTreel a){
	a->r=rotationDl(a->r);
	return rotationGl(a);
}

pTreel doubleRotationDl(pTreel a){
	a->l=rotationGl(a->l);
	return rotationDl(a);
}

pTreet1 rotationGt1 (pTreet1 a){
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

pTreet1 rotationDt1 (pTreet1 a){
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

pTreet1 doubleRotationGt1(pTreet1 a){
	a->r=rotationDt1(a->r);
	return rotationGt1(a);
}

pTreet1 doubleRotationDt1(pTreet1 a){
	a->l=rotationGt1(a->l);
	return rotationDt1(a);
}

pTreet2 rotationGt2 (pTreet2 a){
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

pTreet2 rotationDt2 (pTreet2 a){
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

pTreet2 doubleRotationGt2(pTreet2 a){
	a->r=rotationDt2(a->r);
	return rotationGt2(a);
}

pTreet2 doubleRotationDt2(pTreet2 a){
	a->l=rotationGt2(a->l);
	return rotationDt2(a);
}

pTrees rotationGs (pTrees a){
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

pTrees rotationDs (pTrees a){
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

pTrees doubleRotationGs(pTrees a){
	a->r=rotationDs(a->r);
	return rotationGs(a);
}

pTrees doubleRotationDs(pTrees a){
	a->l=rotationGs(a->l);
	return rotationDs(a);
}

pTree eqAVL(pTree a){
	if(existeFilsDroit(a)){
		if(a->eq >= 2){
			if(a->r->eq >= 0){
				return rotationG(a);
			}
			else {
				return doubleRotationG(a);
			}
		}
	}
	else if (a->eq <= -2){
		if(existeFilsGauche(a)){
			if(a->l->eq <= 0){
				return rotationD(a);
			}
			else {
				return doubleRotationD(a);
			}
		}
	}
	return a;
}

pTreel eqAVLl(pTreel a){
	if(existeFilsDroitl(a)){
		if(a->eq >= 2){
			if(a->r->eq >= 0){
				return rotationGl(a);
			}
			else {
				return doubleRotationGl(a);
			}
		}
	}
	else if (a->eq <= -2){
		if(existeFilsGauchel(a)){
			if(a->l->eq <= 0){
				return rotationDl(a);
			}
			else {
				return doubleRotationDl(a);
			}
		}
	}
	return a;
}

pTreet1 eqAVLt1(pTreet1 a){
	if(existeFilsDroitt1(a)){
		if(a->eq >= 2){
			if(a->r->eq >= 0){
				return rotationGt1(a);
			}
			else {
				return doubleRotationGt1(a);
			}
		}
	}
	else if (a->eq <= -2){
		if(existeFilsGauchet1(a)){
			if(a->l->eq <= 0){
				return rotationDt1(a);
			}
			else {
				return doubleRotationDt1(a);
			}
		}
	}
	return a;
}

pTreet2 eqAVLt2(pTreet2 a){
	if(existeFilsDroitt2(a)){
		if(a->eq >= 2){
			if(a->r->eq >= 0){
				return rotationGt2(a);
			}
			else {
				return doubleRotationGt2(a);
			}
		}
	}
	else if (a->eq <= -2){
		if(existeFilsGauchet2(a)){
			if(a->l->eq <= 0){
				return rotationDt2(a);
			}
			else {
				return doubleRotationDt2(a);
			}
		}
	}
	return a;
}

pTrees eqAVLs(pTrees a){
	if(existeFilsDroits(a)){
		if(a->eq >= 2){
			if(a->r->eq >= 0){
				return rotationGs(a);
			}
			else {
				return doubleRotationGs(a);
			}
		}
	}
	else if (a->eq <= -2){
		if(existeFilsGauches(a)){
			if(a->l->eq <= 0){
				return rotationDs(a);
			}
			else {
				return doubleRotationDs(a);
			}
		}
	}
	return a;
}

pTreel insertAVLl(pTreel a, int e, float x, int* h){
	if (a==NULL){
		*h=1;
		return creerArbrel(e, x);
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

pTreet1 insertAVLt1(pTreet1 a, int e, char* city, int count, int fcount, int* h){
	if (a==NULL){
		*h=1;
		return creerArbret1(e, city, count, fcount);
	}
	else if (strcmp(city, a->city) < 0){
		a->l=insertAVLt1(a->l, e, city, count, fcount, h);
		*h=-*h;
	}
	else if (strcmp(city, a->city) > 0){
		a->r=insertAVLt1(a->r, e, city, count, fcount, h);
	}
	else{
		*h=0;
		a->count++;
		a->fcount += fcount;
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

pTreet2 insertAVLt2(pTreet2 a, char* city, int count, int fcount, int* h){
	if (a==NULL){
		*h=1;
		return creerArbret2(city, count, fcount);
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

pTrees insertAVLs(pTrees a, int e, float x, int* h){
	if (a==NULL){
		*h=1;
		return creerArbres(e, x, x, x, x);
	}
	else if (e < a->n){
		a->l=insertAVLs(a->l, e, x, h);
		*h=-*h;
	}
	else if (e > a->n){
		a->r=insertAVLs(a->r, e, x, h);
	}
	else{
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

pTreel creerABRdeArbrel(pTreel a){
	if(estABRl(a)){
		return a;
	}
	pTreel n = malloc(sizeof(Treel));
	Filel* f = malloc(sizeof(Filel));
	f->head = NULL;
	f->tail = NULL;
	if(n == NULL){
		printf("error creerABRdeArbrel\n");
		exit(32);
	}
	parcoursInfixe1l(a, f);
	pTreel abr = malloc(sizeof(Treel));
	if(abr == NULL){
		printf("error creerABRdeArbrel\n");
		exit(33);
	}
	while(f->head != NULL){
		n = defilerl(f);
		ajouterABRref(abr, n->n, n->f);
	}
	return abr;
}

pTreet1 creerABRdeArbret(pTreet1 a){
	if(estABRt(a)){
		return a;
	}
	pTreet1 n = malloc(sizeof(Treet1));
	Filet* f = malloc(sizeof(Filet));
	f->head = NULL;
	f->tail = NULL;
	if(n == NULL){
		printf("error creerABRdeArbret\n");
		exit(32);
	}
	parcoursInfixe1t(a, f);
	pTreet1 abr = malloc(sizeof(Treet1));
	if(abr == NULL){
		printf("error creerABRdeArbret\n");
		exit(33);
	}
	while(f->head != NULL){
	n = defilert(f);
	ajouterABRret(abr, n->n, n->city, n->count, n->fcount);
	}
	return abr;
}

pTrees creerABRdeArbres(pTrees a){
	if(estABRs(a)){
		return a;
	}
	pTrees n = malloc(sizeof(Trees));
	Files* f = malloc(sizeof(Files));
	f->head = NULL;
	f->tail = NULL;
 	 if(n == NULL){
		printf("error creerABRdeArbres\n");
		exit(32);
	}
	parcoursInfixe1s(a, f);
	pTrees abr = malloc(sizeof(Trees));
	if(abr == NULL){
		printf("error creerABRdeArbres\n");
		exit(33);
	}
	while(f->head != NULL){
		n = defilers(f);
		ajouterABRres(abr, n->n, n->f, n->min, n->max, n->moy);
	}
	return abr;
}

int main(int argc, char** argv){
	char arg = atoi(argv[1]);
	int n = 0, h;
	short t = 0;
	FILE* data1 = NULL;
	data1 = fopen(argv[2], "r");
	if (data1 == NULL){
		printf("C file error\n");
		exit(1);
	}
	if (arg == 1){
		float x = 0;
		pTreel ai = malloc(sizeof(Treel));
		pTreel ad = malloc(sizeof(Treel));
		if (ai == NULL || ad == NULL){
			printf("C error\n");
			exit(1);
		}
		t = fscanf(data1, "%d", &n);
		t = fscanf(data1, "%f", &x);
		ai = creerArbrel(n, x);
		while(t != EOF){
			int tmpi = 0;
			float tmpf = 0;
			t = fscanf(data1, "%d", &tmpi);
			if (t == EOF){
				break;
			}
			t = fscanf(data1, "%f", &tmpf);
			if (t == EOF){
				break;
			}
			insertAVLl(ai, tmpi, tmpf, &h);
		}
		ad = creerABRdeArbrel(ai);
		parcoursInfixe2l(ad);
	}
	else if (arg == 2){
		int m = 0;
		char* c = malloc(40*sizeof(char));
		pTreet1 ai = malloc(sizeof(Treet1));
		pTreet1 ad = malloc(sizeof(Treet1));
		FILE* data2 = NULL;
		data2 = fopen(argv[3], "r");
		if (data2 == NULL || ai == NULL || ad == NULL){
			printf("C error\n");
			exit(2);
		}
		t = fscanf(data1, "%d", &n);
		t = fscanf(data1, "%d", &m);
		fgetc(data1);
		c = fgets(c, 39, data1);
		if (m == 1){
			ai = creerArbret1(n, c, 1, 1);
		}
		else {
			ai = creerArbret1(n, c, 1, 0);
		}
		while(t != EOF){
			int tmpn = 0, tmpm = 0;
			char* tmpc = malloc(40*sizeof(char));
			t = fscanf(data1, "%d", &tmpn);
			if (t == EOF){
				break;
			}
			t = fscanf(data1, "%d", &tmpm);
			if (t == EOF){
				break;
			}
			fgetc(data1);
			tmpc = fgets(tmpc, 39, data1);
			if (tmpc == NULL){
				break;
			}
			if (tmpm == 1){
				ai = insertAVLt1(ai, tmpn, tmpc, 1, 1, &h);
			}
			else{
				ai = insertAVLt1(ai, tmpn, tmpc, 1, 0, &h);
			}
		}
		t = 0;
		while(t != EOF){
			int tmpi = 0;
			char* tmpc = malloc(40*sizeof(char));
			t = fscanf(data2, "%d", &tmpi);
			if (t == EOF){
				break;
			}
			fgetc(data2);
			tmpc = fgets(tmpc, 39, data2);
			if (tmpc == NULL){
				break;
			}
			ai = insertAVLt1(ai, tmpi, tmpc, 1, 0, &h);
		}
		ad = creerABRdeArbret(ai);
		parcoursInfixe2t1(ad);
		fclose(data2);
	}
	else if (arg == 3){
		int m = 0, i = 1;
		char* c = malloc(40*sizeof(char));
		pTreet2 ai = malloc(sizeof(Treet2));
		if (ai == NULL){
			printf("C error\n");
			exit(1);
		}
		t = fscanf(data1, "%d", &n);
		fgetc(data1);
		t = fscanf(data1, "%d", &m);
		fgetc(data1);
		c = fgets(c, 39, data1);
		ai = creerArbret2(c, n, m);
		while(t != EOF){
			int tmpn = 0, tmpm = 0;
			char* tmpc = malloc(40*sizeof(char));
			t = fscanf(data1, "%d", &tmpn);
			if (t == EOF){
				break;
			}
			fgetc(data1);
			t = fscanf(data1, "%d", &tmpm);
			if (t == EOF){
				break;
			}
			fgetc(data1);
			tmpc = fgets(tmpc, 39, data1);
			if (tmpc == NULL){
				break;
			}
			i++;
			ai = insertAVLt2(ai, tmpc, tmpn, tmpm, &h);
		}
		parcoursInfixe2t2(ai);
	}
	else if (arg == 4){
		float x = 0;
		pTrees ai = malloc(sizeof(Trees));
		pTrees ad = malloc(sizeof(Trees));
		if (ai == NULL || ad == NULL){
			printf("C error\n");
			exit(1);
		}
		t = fscanf(data1, "%d", &n);
		t = fscanf(data1, "%f", &x);
		ai = creerArbres(n, x, x, x, x);
		while(t != EOF){
			int tmpi = 0;
			float tmpf = 0;
			t = fscanf(data1, "%d", &tmpi);
			if (t == EOF){
				break;
			}
			t = fscanf(data1, "%f", &tmpf);
			if (t == EOF){
				break;
			}
			insertAVLs(ai, tmpi, tmpf, &h);
		}
		ad = creerABRdeArbres(ai);
		parcoursInfixe2s(ad);
	}
	else{
		printf("Error in shell\n");
	}
	fclose(data1);
	return 0;
}
