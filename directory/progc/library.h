#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

typedef struct Treel{	// -l process tree, int n is the route ID, float f is the distance
	struct Treel* l;
	struct Treel* r;
	int n;
	float f;
	short eq;
}Treel;

typedef struct Treel* pTreel;

typedef struct Treei{	// -t process tree to make sure a city isn't counted twice with the same route ID, int n is the route ID
	struct Treei* l;
	struct Treei* r;
	int n;
	short eq;
}Treei;

typedef struct Treei* pTreei;

typedef struct Treet1{	// -t process tree to count how many times the city (char* city) is visited (int count) and how many times it's a departure city (int fcount), pTreei a checks if the ID wasn't already linked to the city
	struct Treet1* l;
	struct Treet1* r;
	char* city;
	int count;
	int fcount;
	pTreei a;
	short i;
	short eq;
}Treet1;

typedef struct Treet1* pTreet1;

typedef struct Treet2{	// -t process tree to order the cities by alphabetical order, int count and int fcount are the same as before
	struct Treet2* l;
	struct Treet2* r;
	char* city;
	int count;
	int fcount;
	short eq;
}Treet2;

typedef struct Treet2* pTreet2;

typedef struct Trees{	// -s process tree, int count will be used to calculate the average distance, int n is the route ID, double f is the total distance, double min is the shortest step, double max is the longest one, double av is the average step distance, double rank is max - min
	struct Trees* l;
	struct Trees* r;
	char* city;
	int count;
	int n;
	double f;
	double min;
	double max;
	double av;
	double rank;
	short eq;
}Trees;

typedef struct Trees* pTrees;

typedef struct Chainl{	// linked list for the -l process
	struct Chainl* last;
	pTreel a;
	struct Chainl* next;
}Chainl;

typedef struct Queuel{	// queue for the -l process
	Chainl* head;
	Chainl* tail;
}Queuel;

typedef struct Chaint{	// linked list for the -t process
	struct Chaint* last;
	pTreet1 a;
	struct Chaint* next;
}Chaint;

typedef struct Queuet{	// queue for the -t process
	Chaint* head;
	Chaint* tail;
}Queuet;

typedef struct Chains{	// linked list for the -s process
	struct Chains* last;
	pTrees a;
	struct Chains* next;
}Chains;

typedef struct Queues{	// queue for the -s process
	Chains* head;
	Chains* tail;
}Queues;

int max2 (int a, int b);
int min2 (int a, int b);
int main(int argc, char** argv);


short isEmptyl(pTreel a);
int heightl(pTreel a);
pTreel cTreel(int e, float f);
Chainl* cChainl(pTreel a);
Queuel cQueuel(pTreel a);
Queuel enterl(Queuel f, pTreel a);
pTreel rmQueuel(Queuel* f);
short existLBl(pTreel a);
short existRBl(pTreel a);
void processl(pTreel a);
void infix1l(pTreel a, Queuel* f);
void infix2l(pTreel a);
pTreel addBSTl(pTreel a, int e, float x);
short isBSTl(pTreel a);
pTreel lRotl (pTreel a);
pTreel rRotl (pTreel a);
pTreel doubleLRotl(pTreel a);
pTreel doubleRRotl(pTreel a);
pTreel eqAVLl(pTreel a);
pTreel insertAVLl(pTreel a, int e, float x, int* h);
pTreel cBSTFromTreel(pTreel a);


short isEmptyi(pTreei a);
int heighti(pTreei a);
pTreei cTreei(int e);
short existLBi(pTreei a);
short existRBi(pTreei a);
pTreei lRoti (pTreei a);
pTreei rRoti (pTreei a);
pTreei doubleLRoti(pTreei a);
pTreei doubleRRoti(pTreei a);
pTreei eqAVLi(pTreei a);
pTreei insertAVLi(pTreei a, int e, int* i, int* h);

short isEmptyt1(pTreet1 a);
int heightt1(pTreet1 a);
pTreet1 cTreet1(int e, char* city, int count, int fcount);
Chaint* cChaint(pTreet1 a);
Queuet cQueuet(pTreet1 a);
Queuet entert(Queuet f, pTreet1 a);
pTreet1 rmQueuet(Queuet* f);
short existLBt1(pTreet1 a);
short existRBt1(pTreet1 a);
void processt1(pTreet1 a);
void infix1t1(pTreet1 a, Queuet* f);
void infix2t1(pTreet1 a);
pTreet1 addBSTt(pTreet1 a, int e, char* city, int count, int fcount);
short isBSTt(pTreet1 a);
pTreet1 lRott1 (pTreet1 a);
pTreet1 rRott1 (pTreet1 a);
pTreet1 doubleLRott1(pTreet1 a);
pTreet1 doubleRRott1(pTreet1 a);
pTreet1 eqAVLt1(pTreet1 a);
pTreet1 insertAVLt1(pTreet1 a, int e, char* city, int count, int fcount, int* h);
pTreet1 cBSTFromTreet(pTreet1 a);

short isEmptyt2(pTreet2 a);
int heightt2(pTreet2 a);
pTreet2 cTreet2(char* city, int count, int fcount);
short existLBt2(pTreet2 a);
short existRBt2(pTreet2 a);
void processt2(pTreet2 a);
void infixt2(pTreet2 a);
pTreet2 lRott2 (pTreet2 a);
pTreet2 rRott2 (pTreet2 a);
pTreet2 doubleLRott2(pTreet2 a);
pTreet2 doubleRRott2(pTreet2 a);
pTreet2 eqAVLt2(pTreet2 a);
pTreet2 insertAVLt2(pTreet2 a, char* city, int count, int fcount, int* h);


short isEmptys(pTrees a);
int heights(pTrees a);
pTrees cTrees(int e, double f, double min, double max, double av);
Chains* cChains(pTrees a);
Queues cQueues(pTrees a);
Queues enters(Queues f, pTrees a);
pTrees rmQueues(Queues* f);
short existLBs(pTrees a);
short existRBs(pTrees a);
void process1s(pTrees a);
void infix1s(pTrees a, Queues* f);
void process2s(pTrees a);
void infix2s(pTrees a);
pTrees addBSTs(pTrees a, int e, double x, double min, double max, double av);
short isBSTs(pTrees a);
pTrees lRots (pTrees a);
pTrees rRots (pTrees a);
pTrees doubleLRots(pTrees a);
pTrees doubleRRots(pTrees a);
pTrees eqAVLs(pTrees a);
pTrees insertAVLs(pTrees a, int e, double x, int* h);
pTrees cBSTFromTrees(pTrees a);
