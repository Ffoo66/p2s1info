//td6 : avl
#include <stdio.h>
#include <math.h>
#include <stdlib.h>  
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>

int scan(char* input){					// scanf function but deletes the end
	int a=scanf("%c", input);
	while(getchar() != '\n'){}			// clears buffer
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

typedef struct arbre{
	int n; 		   //entier
	struct arbre* fg; //fils gauche
	struct arbre* fd; //fils droit
	int eq; //equilibre = hauteur sous-abre droit - hauteur sous-arbre gauche
} Arbre;

typedef Arbre* pArbre;	

typedef struct chainon{
	pArbre elmt;
	struct chainon* s;
	
}Chainon;

typedef struct file{
	Chainon* t;//debut
	Chainon* q;//fin
} File;	

Chainon* creerChainon(pArbre a){
	Chainon* c=malloc(sizeof(Chainon));
	if(c==NULL){
		exit(1);
	}
	c->elmt=a;
	c->s=NULL;
	return c;
}

int estVide(pArbre a){
	if (a==NULL){	
		return 1;
	}
	else{
		return 0;
	}
}

int hauteur(pArbre a){
	if(estVide(a)){
		return 0;
	}
	return 1 + max2(hauteur(a->fg),hauteur(a->fd));
}

pArbre creerArbre(int n){
	pArbre a=malloc(sizeof(Arbre));
	if(a==NULL){
		printf("\nErreur creerArbre\n");
		exit(1);
	}
	a->n=n;
	a->fg=NULL;
	a->fd=NULL;
	a->eq=hauteur(a->fd)-hauteur(a->fg);
	return a;
}



File creerFile(){
	File pf;
	pf.t=NULL;
	pf.q=NULL;
	return pf;
}




File enfiler(File pf, pArbre a){
	if(estVide(a)){
		printf("\n erreur enfiler \n");
		exit(1);
	}
	if(pf.q==NULL && pf.t==NULL){ //si file vide
		pf.q=creerChainon(a);
		pf.t=pf.q;
	}
	else{
		pf.q->s=creerChainon(a);
		pf.q=pf.q->s;
	}
	return pf;
}

File defiler(File pf, pArbre* a){
	Chainon* tmp;
	if(pf.t==NULL) {
		printf("\nFile vide\n");
		return pf;
	}
	*a=pf.t->elmt;
	tmp=pf.t;
	pf.t=pf.t->s;
	if(tmp!=NULL){
		free(tmp);
	}	
	return pf;	
}

int element(pArbre a){
	if(estVide(a)){
		printf("\nErreur element\n");
		exit(1);
	}
	return a->n;
}

pArbre modifier(pArbre a, int e){
	if(estVide(a)){
		printf("\nErreur modifier\n");
		exit(1);
	}
	a->n=e;
	return a;
}

int existeFg(pArbre a){
	if(estVide(a)){
		printf("\nErreur existeFg\n");
		exit(1);
	}
	else if (a->fg==NULL){
		return 0;
	}
	else{
		return 1;
	}
}

int existeFd(pArbre a){
	if(estVide(a)){
		printf("\nErreur existeFd\n");
		exit(1);
	}
	else if (a->fd==NULL){
		return 0;
	}
	else{
		return 1;
	}
}


int ajouterFg(pArbre a, int n){ //retourne 1 si fg créé, 0 sinon (si impossible)
	if (estVide(a)){
		a=creerArbre(n);
		return 1;
	 }

	 else if (existeFg(a)!=1){
	 	a->fg=creerArbre(n);
	 	return  1;
	 }
	 else{
	 	return 0;
	 }
}

int ajouterFd(pArbre a, int n){ //retourne 1 si fd créé, 0 sinon (si impossible)
	if (estVide(a)){
		a=creerArbre(n);
		return 1;
	 }
	 else if (existeFd(a)!=1){
	 	a->fd=creerArbre(n);
	 	return  1;
	 }
	 else{
	 	return 0;
	 }
}

void traiter (pArbre a){//affiche valeur de a
	if(estVide(a)){
		printf("\nErreur traiter\n");
		exit(1);
	}
	printf(" %d ", a->n);
}

void prefixe(pArbre a){//parcours prefixe
	if(estVide(a)==0){
		traiter(a);
		prefixe(a->fg);
		prefixe(a->fd);	
	}
}

void infixe(pArbre a){//parcours infixe
	if(estVide(a)==0){
		infixe(a->fg);	
		traiter(a);
		infixe(a->fd);
	
	}
}

void largeur(pArbre a){//parcours en largeur
	pArbre noeud=a;
	if(estVide(a)==0){
		File f=creerFile();
		f=enfiler(f,a);
		while(f.t!=NULL){
			if(existeFg(f.t->elmt)){
				f=enfiler(f, f.t->elmt->fg);
			
			}
			if(existeFd(f.t->elmt)){
				f=enfiler(f, f.t->elmt->fd);
				
			}	
			traiter (f.t->elmt);
			f=defiler(f, &noeud);
		}
	}
}

int nmbFeuille(pArbre a){
	if(estVide(a)){
		return 0;
	}
	int n=0;
	if(existeFg(a)==0 && existeFd(a)==0){
		return 1;
	} 
	else{	
		n+=nmbFeuille(a->fg);
		n+=nmbFeuille(a->fd);
	}
	return n;
}

int taille(pArbre a){
	if(estVide(a)){
		return 0;
	}
	if(existeFg(a) || existeFd(a)){
		return 1+taille(a->fd)+taille(a->fg);
	} 
	else {
		return 0;
	}
}


pArbre rotationG (pArbre a){
	pArbre pivot;
	int eqA;
	int eqP;
	pivot = a->fd;
	a->fd = pivot->fg;
	pivot->fg = a;
	eqA = a->eq;
	eqP = pivot->eq;
	a->eq = eqA - max2(eqP, 0) - 1;
	pivot->eq = min2(min2(eqA-2,eqA+eqP-2), eqP-1);
	a=pivot;
	return a;
}

pArbre rotationD (pArbre a){
	pArbre pivot;
	int eqA;
	int eqP;
	pivot = a->fg;
	a->fg = pivot->fd;
	pivot->fd = a;
	eqA = a->eq;
	eqP = pivot->eq;
	a->eq = eqA - min2(eqP, 0) + 1;
	pivot->eq = max2(max2(eqA+2,eqA+eqP+2), eqP+1);
	a=pivot;
	return a;
}

pArbre doubleRotationG(pArbre a){
	a->fd=rotationD(a->fd);
	return rotationG(a);
}
pArbre doubleRotationD(pArbre a){
	a->fg=rotationG(a->fg);
	return rotationD(a);
}

pArbre eqAVL(pArbre a){
	if(existeFd(a)){
		if(a->eq >= 2){
			if(a->fd->eq >= 0){
				return rotationG(a);
			}
			else {
				return doubleRotationG(a);
			}
		}
	}
	else if (a->eq <= -2){
		if(existeFg(a)){
			if(a->fg->eq <= 0){
				return rotationD(a);
			}
			else {
				return doubleRotationD(a);
			}
		}
	}
	return a;
}

int recherche(pArbre a, int e){ //check si e appartient à a
	if(estVide(a)){
		printf("\n %d n'appartient pas à l'arbre.\n", e);
		return 0;
	}
	else if (a->n==e){
		return 1;
	}
	else if(e < a->n){
		return 1 + recherche(a->fg, e);
	}
	else if(e > a->n){
		return 1 + recherche(a->fd, e);
	}
}

int prefixeCherche(pArbre a, int e){//recherche prefixe
	if(estVide(a)){
		return 0;
	}
	if(estVide(a)==0){
		if(e == a->n){
		printf("\n %d appartient à l'arbre.\n", e);
			return 1;
		}
		return 1 + prefixeCherche(a->fg, e)+ prefixeCherche(a->fd, e);
		
	}
}

pArbre insertABR(pArbre a, int e){
	if(estVide(a)){
		a=creerArbre(e);
		return a;
	}
	if( a->n < e){
		a->fd=insertABR(a->fd, e);
	}
	if( a->n > e){
		a->fg=insertABR(a->fg, e);
	}
	return a;
}

pArbre insertAVL(pArbre a, int e, int* h){
	if (a==NULL){
		*h=1;
		return creerArbre(e);
	}
	else if (e < a->n){
		a->fg=insertAVL(a->fg,e,h);
		*h=-*h;
	}
	else if (e > a->n){
		a->fd=insertAVL(a->fd,e,h);
	}
	else{
		*h=0;
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

/*
pArbre suppMinAVL(pArbre a, int* h, int* pe){
	pArbre tmp;
	if (a->fg==NULL){
		*pe=a->n;
		*h=-1;
		tmp=a;
		a=a->fd;
		free(tmp);
		return a;
	}
	else{
		a->fg=suppMinAVL(a->fg, h ,pe);
		*h=-*h;
	}
	if(*h!=0){
		a->eq=a->eq + *h;
		a=eqAVL(a);
		if(a->eq==0){
			*h=-1;
		}
		else{
			*h=0;
		}
	}
	return a;
}

pArbre suppAVL(pArbre a, int e, int* h){
	pArbre tmp;
	if (a==NULL){
		*h=1;
		return a;
	}
	else if (e > a->n){
		a->fd = suppAVL(a->fd, e, h);
	}
	else if (e < a->n){
		a->fg = suppAVL(a->fg, e, h);
		*h=-*h;
	}
	else if (existeFd(a)){
		a->fg=suppMinAVL(a->fd, h , &(a->n));
	}
	else {
		tmp=a;
		a=a->fg;
		free(tmp);
		*h=-1;
	}
	if(a==NULL){
		*h=0;
	}
	if(*h != 0){
		a->eq = a->eq + *h;
		a=eqAVL(a);
		if(a->eq == 0){
			*h=0;
		}
		else {
			*h=1;
		}
	}
	return a;
}
*/

pArbre supp(pArbre a, int e);
pArbre suppMax(pArbre a, int* p);

pArbre supp(pArbre a, int e){
	pArbre tmp;
	if(estVide(a)){
		return a;
	}
	else if (e > a->n ){
		a->fd=supp(a->fd, e);
	}
	else if (e < a->n ){
		a->fg=supp(a->fg, e);
	}
	else if (existeFg(a)==0){
		tmp=a;
		a=a->fd;
		free(tmp);
	}
	else{
		a->fg=suppMax(a->fg, &(a->n));
	}
	return a;
}

pArbre suppMax(pArbre a, int * p){
	pArbre tmp;
	if(existeFd(a)){
		a->fd=suppMax(a->fd, p);
	}
	else{
		*p=a->n;
		tmp=a;
		a=a->fg;
		free(tmp);
	}
	return a;
}

int estABR(pArbre a){
	if(estVide(a)){
		return 1;
	}
	int n=1;
	if(existeFg(a)){
		if(a->fg->n > a->n){
			return 0;
		}
		else{
			n=estABR(a->fg);
		}
	} 
	if (existeFd(a)){
		if(a->fd->n < a->n){
			return 0;
		}
		else{
			n=estABR(a->fd);
		}
	}
	return n;
}

int estEq(pArbre a){
	if(estVide(a)){
		return 1;
	}
	int n=1;
	if(existeFg(a)){
		if(hauteur(a->fd)-hauteur(a->fg)>1 || hauteur(a->fd)-hauteur(a->fg)<-1){
			return 0;
		}
		else{
			n=estEq(a->fg);
		}
	} 
	if (existeFd(a)){
		if(hauteur(a->fd)-hauteur(a->fg)>1 || hauteur(a->fd)-hauteur(a->fg)<-1){
			return 0;
		}
		else{
			n=estEq(a->fd);
		}
	}
	return n;
}


void suppFg(pArbre a);
void suppFd(pArbre a){
	if(estVide(a)){
		printf("\nerreur suppFd\n");
		exit(1);
	}
	else if (existeFd(a)){	
		if(existeFg(a->fd)){
			suppFg(a->fd);
		}
		if(existeFd(a->fd)){
			suppFd(a->fd);
		}
		free(a->fd);
		a->fd=NULL;
	}
}

void suppFg(pArbre a){
	if(estVide(a)){
		printf("\nerreur suppFg\n");
		exit(1);
	}
	else if (existeFg(a)){	
		if(existeFg(a->fg)){
			suppFg(a->fg);
		}
		if(existeFd(a->fg)){
			suppFd(a->fg);
		}
		free(a->fg);
		a->fg=NULL;
	}
}

pArbre creerABR(pArbre a){
	if(estABR(a)){
		return a;
	}
	pArbre noeud;
	if(estVide(a)!=1){
		File f=creerFile();
		f=enfiler(f,a);
		pArbre b=creerArbre(f.t->elmt->n);
		while(f.t!=NULL){
			if(existeFg(f.t->elmt)){
				f=enfiler(f, f.t->elmt->fg);
			
			}
			if(existeFd(f.t->elmt)){
				f=enfiler(f, f.t->elmt->fd);
			}
			b=insertABR(b, f.t->elmt->n);
			f=defiler(f, &noeud);	
		}
		return b;
	}
}

int tri(pArbre a, int tab[], int i){//parcours infixe
	if(estVide(a)==0){
		i=tri(a->fg,tab,i);	
		tab[i]=a->n;
		i++;
		i=tri(a->fd,tab,i);
	}
	return i;
}

void printArray(int tab[], int size){
	int i;
	printf("\n");
	for (i=0;i<size;i++){
		printf(" | %d ",tab[i]);
	}
	printf("|\n");

}



int main(){ //pb pour supp d'elmts possédant des feuilles
	int h;
	srand( time( NULL ) );
	pArbre a=creerArbre(10);
	a=insertAVL(a,3,&h);
	a=insertAVL(a,5,&h);
	a=insertAVL(a,15,&h);
	a=insertAVL(a,20,&h);
	a=insertAVL(a,12,&h);
	a=insertAVL(a,7,&h);
	a=insertAVL(a,9,&h);
	printf("\n");
	infixe(a);
	printf("\n");
	/*a=suppAVL(a,3,&h);
	printf("\n");
	infixe(a);
	printf("\n");
	a=suppAVL(a, 12,&h);
	printf("\n");
	infixe(a);
	printf("\n");*/
	printf("\n");
	int c=estABR(a);
	printf("\nestABR = %d.\n", c);
	int d=estEq(a);
	printf("\nestEq = %d.\n", d);
	return 0;
}




