#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

typedef struct Tree{
  struct Tree* l;
  struct Tree* r;
  int count;
  int fcount;
  int n;
  float f;
  char* city;
  short eq;
}Tree;

typedef struct Tree* pTree;

typedef struct Chainon{
  struct Chainon* last;
  pTree a;
  struct Chainon* next;
}Chain;

typedef struct File{
  Chain* head;
  Chain* tail;
}File;

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

pTree creerArbre(int e, float f, char* city, int count, int fcount){
  pTree a = malloc(sizeof(Tree));
  if (a == NULL){
    printf("Error creerArbre\n");
    exit(10);
  }
  a->count = count;
  a->fcount = fcount;
  a->n = e;
  a->f = f;
  a->city = city;
  a->l = NULL;
  a->r = NULL;
  a->eq=hauteur(a->r)-hauteur(a->l);
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
  File f;
  Chain* c = creerChainon(a);
  f.head = c;
  f.tail = c;
  return f;
}

File creerFile2(pTree a){
  if (a == NULL){
    printf("Error creerFile2\n");
    exit(12);
  }
  if (a->l == NULL){
    File f;
    Chain* c = creerChainon(a);
    f.head = c;
    f.tail = c;
    return f;
  }
  File f;
  f = creerFile2(a->l);
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

Chain* empiler(Chain* p, pTree a){
  if (a == NULL){
    return p;
  }
  if (p == NULL){
    p = creerChainon(a);
    return p;
  }
  Chain* c = creerChainon(a);
  c->next = p;
  p->last = c;
  p = p->last;
  return p;
}

pTree depiler(Chain* p){
  if (p == NULL){
    return NULL;
  }
  Chain* del = p;
  pTree a = p->a;
  if (p->next == NULL){
    p = NULL;
    free(del);
    return a;
  }
  p = p->next;
  p->last = NULL;
  free(del);
  return a;
}

short estFeuille(pTree a){
  if (a == NULL){
    printf("Error estFeuille\n");
    exit(20);
  }
  if (estVide(a->l) && estVide(a->r)){
    return 1;
  }
  return 0;
}

int element(pTree a){
  if (a == NULL){
    printf("Error element\n");
    exit(21);
  }
  return a->n;
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

void ajouterFilsGauche(pTree a, int e, float x, char* city, int count, int fcount){
  if (a == NULL){
    printf("Error ajouterFilsGauche\n");
    exit(24);
  }
  while (a->l != NULL){
    a = a->l;
  }
  a = creerArbre(e, x, city, count, fcount);
}

void ajouterFilsDroit(pTree a, int e, float x, char* city, int count, int fcount){
  if (a == NULL){
    printf("Error ajouterFilsDroit\n");
    exit(25);
  }
  while (a->r != NULL){
    a = a->r;
  }
  a = creerArbre(e, x, city, count, fcount);
}

void traiter2(pTree a){
  if (a != NULL){
    printf("%d ", a->n);
    printf("%f\n", a->f);
  }
}

void traiter3(pTree a){
  if (a != NULL){
    printf("%d ", a->count);
    printf("%s", a->city);
  }
}

void parcoursPrefixe(pTree a){
  if(a != NULL){
    traiter2(a);
    parcoursPrefixe(a->l);
    parcoursPrefixe(a->r);
  }
}

void parcoursPostfixe(pTree a){
  if(a != NULL){
    parcoursPostfixe(a->l);
    parcoursPostfixe(a->r);
    traiter2(a);
  }
}

void parcoursInfixe1(pTree a, File* f){
  if(a != NULL){
    parcoursInfixe1(a->l, f);
    *f = enfiler(*f, a);
    parcoursInfixe1(a->r, f);
  }
}

void parcoursInfixe2(pTree a){
  if(a != NULL){
    parcoursInfixe2(a->l);
    traiter2(a);
    parcoursInfixe2(a->r);
  }
}

void parcoursInfixe3(pTree a){
  if(a != NULL){
    parcoursInfixe3(a->l);
    traiter3(a);
    parcoursInfixe3(a->r);
  }
}

void parcoursLargeur(pTree a){
  if (a == NULL){
    printf("Error parcoursLargeur\n");
    exit(26);
  }
  pTree p = malloc(sizeof(Tree));
  File f = creerFile(a);
  f = enfiler(f, a->l);
  f = enfiler(f, a->r);
  p = defiler(&f);
  traiter2(p);
  while(f.head != NULL && f.tail != NULL){
    p = defiler(&f);
    traiter2(p);
    f = enfiler(f, p->l);
    f = enfiler(f, p->r);
  }
}

pTree modifierRacine(pTree a, int e){
  if(a == NULL){
    return a;
  }
  a->n = e;
  return a;
}

pTree supprimerFilsGauche(pTree a){
  if(a == NULL || a->l == NULL){
    return a;
  }
  File f = creerFile(a->l);
  pTree p = malloc(sizeof(Tree));
  if(p == NULL){
    printf("error supprimerFilsGauche\n");
    exit(27);
  }
  f = enfiler(f, a->l->l);
  f = enfiler(f, a->l->r);
  p = defiler(&f);
  while(f.head != NULL){
    p = defiler(&f);
    f = enfiler(f, p->l);
    f = enfiler(f, p->r);
  }
  return a;
}

pTree supprimerFilsDroit(pTree a){
  if(a == NULL || a->r == NULL){
    return a;
  }
  File f = creerFile(a->r);
  pTree p = malloc(sizeof(Tree));
  if(p == NULL){
    printf("error supprimerFilsDroit\n");
    exit(28);
  }
  f = enfiler(f, a->r->l);
  f = enfiler(f, a->r->r);
  p = defiler(&f);
  while(f.head != NULL){
    p = defiler(&f);
    f = enfiler(f, p->l);
    f = enfiler(f, p->r);
  }
  return a;
}

short estFiliforme(pTree a){
  if(a == NULL){
    return 1;
  }
  if(a->l != NULL && a->r != NULL){
    return 0;
  }
  if(a->l != NULL){
    return estFiliforme(a->l);
  }
  return estFiliforme(a->r);
}

short peigneGauche(pTree a){
  short i = 1;
  if(estFiliforme(a)){
    while(a != NULL){
      if(existeFilsDroit(a)){
        i = 0;
      }
      a = a->l;
    }
    return i;
  }
  else{
    return 0;
  }
}

short peigneDroit(pTree a){
  short i = 1;
  if(estFiliforme(a)){
    while(a != NULL){
      if(existeFilsGauche(a)){
        i = 0;
      }
      a = a->r;
    }
    return i;
  }
  else{
    return 0;
  }
}

pTree constrPeigneGauche(int h){
  char i = 0;
  if (h == 0){
    return NULL;
  }
  pTree a = creerArbre(rand()%11, 0, NULL, 1, 0);
  if(a == NULL){
    printf("error constrPeigneGauche\n");
    exit(29);
  }
  for(i = 1; i<h; i++){
    ajouterFilsGauche(a, rand()%11, 0, NULL, 1, 0);
  }
  return a;
}

pTree constrPeigneDroit(int h){
  char i = 0;
  if (h == 0){
    return NULL;
  }
  pTree a = creerArbre(rand()%11, 0, NULL, 1, 0);
  if(a == NULL){
    printf("error constrPeigneDroit\n");
    exit(30);
  }
  for(i = 1; i<h; i++){
    ajouterFilsDroit(a, rand()%11, 0, NULL, 1, 0);
  }
  return a;
}

int nombreNoeud(pTree a){
  int n = 0;
  File f;
  f.head = NULL;
  f.tail = NULL;
  parcoursInfixe1(a, &f);
  while(f.head != NULL){
    defiler(&f);
    n++;
  }
  return n;
}

pTree ajouterABRrei(pTree a, int e, float x, char* city, int count, int fcount){
  if (a == NULL){
    a = creerArbre(e, x, city, count, fcount);
  }
  else if (e > a->n){
    if(a->r == NULL){
      a->r = creerArbre(e, x, city, count, fcount);
    }
    else{
      ajouterABRrei(a->r, e, x, city, count, fcount);
    }
  }
  else if (e < a->n){
    if(a->l == NULL){
      a->l = creerArbre(e, x, city, count, fcount);
    }
    else{
      ajouterABRrei(a->l, e, x, city, count, fcount);
    }
  }
  else{
    a->f += x;
  }
}

pTree ajouterABRref(pTree a, int e, float x, char* city, int count, int fcount){
  if (a == NULL){
    a = creerArbre(e, x, city, count, fcount);
  }
  else if (x > a->f){
    if(a->r == NULL){
      a->r = creerArbre(e, x, city, count, fcount);
    }
    else{
      ajouterABRref(a->r, e, x, city, count, fcount);
    }
  }
  else if (x < a->f){
    if(a->l == NULL){
      a->l = creerArbre(e, x, city, count, fcount);
    }
    else{
      ajouterABRref(a->l, e, x, city, count, fcount);
    }
  }
}

pTree ajouterABRrec(pTree a, int e, float x, char* city, int count, int fcount){
  if (a == NULL){
    a = creerArbre(e, x, city, count, fcount);
  }
  else if (count > a->count){
    if(a->r == NULL){
      a->r = creerArbre(e, x, city, count, fcount);
    }
    else{
      ajouterABRrec(a->r, e, x, city, count, fcount);
    }
  }
  else if (count < a->count){
    if(a->l == NULL){
      a->l = creerArbre(e, x, city, count, fcount);
    }
    else{
      ajouterABRrec(a->l, e, x, city, count, fcount);
    }
  }
}

void ajouterABRit(pTree a, int e, float x, char* city, int count, int fcount){
  if (a == NULL){
    a = creerArbre(e, x, city, count, fcount);
  }
  else{
    while(a != NULL && a->n != e){
      if(e > a->n){
        if(a->r == NULL){
          a->r = creerArbre(e, x, city, count, fcount);
        }
        else{
          a = a->l;
        }
      }
      else if(e < a->n){
        if(a->l == NULL){
          a->l = creerArbre(e, x, city, count, fcount);
        }
        else{
          a = a->l;
        }
      }
    }
  }
}

short recherche(pTree a, int e, int i){
  if (a == NULL){
    printf("%d n'appartient pas à cet arbre\n", e);
    return i-1;
  }
  if (a->n == e){
    printf("%d appartient à cet arbre\n", e);
    return i;
  }
  if (a->n > e){
    return recherche(a->l, e, i+1);
  }
  if (a->n < e){
    return recherche(a->r, e, i+1);
  }
}

short estABRf(pTree a){
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

pTree insertAVLl(pTree a, int e, float x, char* city, int count, int fcount, int* h){
  if (a==NULL){
    *h=1;
    return creerArbre(e, x, city, count, fcount);
  }
  else if (e < a->n){
    a->l=insertAVLl(a->l, e, x, city, count, fcount, h);
    *h=-*h;
  }
  else if (e > a->n){
    a->r=insertAVLl(a->r, e, x, city, count, fcount, h);
  }
  else{
    *h=0;
    a->f += x;
    return a;
  }
  if(*h!=0){	
    a->eq = a->eq + *h;
    a=eqAVL(a);
    if(a->eq==0){	
      *h=0;
    }
    else{	
      *h=1;
    }
  }
  return a;
}

pTree insertAVLt(pTree a, int e, float x, char* city, int count, int fcount, int* h){
  if (a==NULL){
    *h=1;
    return creerArbre(e, x, city, count, fcount);
  }
  else if (strcmp(city, a->city) < 0){
    a->l=insertAVLt(a->l, e, x, city, count, fcount, h);
    *h=-*h;
  }
  else if (strcmp(city, a->city) > 0){
    a->r=insertAVLt(a->r, e, x, city, count, fcount, h);
  }
  else{
    *h=0;
    a->count++;
    return a;
  }
  if(*h!=0){	
    a->eq = a->eq + *h;
    a=eqAVL(a);
    if(a->eq==0){	
      *h=0;
    }
    else{	
      *h=1;
    }
  }
  return a;
}

short estEq(pTree a){
  if(estVide(a)){
    return 1;
  }
  int n=1;
  if(existeFilsGauche(a)){
    if(hauteur(a->r)-hauteur(a->l)>1 || hauteur(a->r)-hauteur(a->l)<-1){
      return 0;
    }
    else{
      n=estEq(a->l);
    }
  } 
  if (existeFilsDroit(a)){
    if(hauteur(a->r)-hauteur(a->l)>1 || hauteur(a->r)-hauteur(a->l)<-1){
      return 0;
    }
    else{
      n=estEq(a->r);
    }
  }
  return n;
}

pTree creerABRdeArbrel(pTree a){
  if(estABRf(a)){
    return a;
  }
  pTree n = malloc(sizeof(Tree));
  File* f = malloc(sizeof(File));
  f->head = NULL;
  f->tail = NULL;
  if(n == NULL){
    printf("error creerABRdeArbre\n");
    exit(32);
  }
  parcoursInfixe1(a, f);
  pTree abr = malloc(sizeof(Tree));
  if(abr == NULL){
    printf("error creerABRdeArbre\n");
    exit(33);
  }
  while(f->head != NULL){
    n = defiler(f);
    ajouterABRref(abr, n->n, n->f, n->city, n->count, n->fcount);
  }
  return abr;
}

pTree creerABRdeArbret(pTree a){
  if(estABRf(a)){
    return a;
  }
  pTree n = malloc(sizeof(Tree));
  File* f = malloc(sizeof(File));
  f->head = NULL;
  f->tail = NULL;
  if(n == NULL){
    printf("error creerABRdeArbre\n");
    exit(32);
  }
  parcoursInfixe1(a, f);
  pTree abr = malloc(sizeof(Tree));
  if(abr == NULL){
    printf("error creerABRdeArbre\n");
    exit(33);
  }
  while(f->head != NULL){
    n = defiler(f);
    ajouterABRrec(abr, n->n, n->f, n->city, n->count, n->fcount);
  }
  return abr;
}

int main(int argc, char** argv){
  char arg = atoi(argv[1]);
  int n = 0, h;
  short t = 0;
  pTree ai = malloc(sizeof(Tree));
  pTree ad = malloc(sizeof(Tree));
  FILE* data1 = NULL;
  data1 = fopen(argv[2], "r");
  if (data1 == NULL || ai == NULL || ad == NULL){
    printf("C error\n");
    exit(1);
  }
  if (arg == 1){
    float x = 0;
    t = fscanf(data1, "%d", &n);
    t = fscanf(data1, "%f", &x);
    ai = creerArbre(n, x, NULL, 1, 0);
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
      insertAVLl(ai, tmpi, tmpf, NULL, 1, 0, &h);
    }
    ad = creerABRdeArbrel(ai);
    parcoursInfixe2(ad);
  }
  else if (arg == 2){
    char* c = malloc(40*sizeof(char));
    FILE* data2 = NULL;
    data2 = fopen(argv[3], "r");
    if (data2 == NULL){
      printf("C second file error\n");
      exit(2);
    }
    t = fscanf(data1, "%d", &n);
    fgetc(data1);
    c = fgets(c, 39, data1);
    ai = creerArbre(n, 0, c, 1, 0);		// à changer
    free(c);
    while(t != EOF){
      int tmpi = 0;
      char* tmpc = malloc(40*sizeof(char));
      t = fscanf(data1, "%d", &tmpi);
      if (t == EOF){
        break;
      }
      fgetc(data1);
      tmpc = fgets(tmpc, 39, data1);
      if (tmpc == NULL){
        break;
      }
      insertAVLt(ai, tmpi, 0, tmpc, 1, 0, &h);
    }
    parcoursInfixe3(ai);
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
      insertAVLt(ai, tmpi, 0, tmpc, 1, 0, &h);
    }
    ad = creerABRdeArbret(ai);
    parcoursInfixe3(ad);
    printf("Yes\n");
    fflush(stdout);
    fclose(data2);
  }
  else if (arg == 3){
  }
  else{
    printf("Error in shell\n");
  }
  fclose(data1);
  return 0;
}
