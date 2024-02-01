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
	short i;	// to be checked
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
	char* city;	// to be checked
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



// List of general functions
int max2 (int a, int b);		// determines the highest value between two ints
int min2 (int a, int b);		// determines the lowest value between two ints
int main(int argc, char** argv);	// main function



// List of functions and processes for the -l process
short isEmptyl(pTreel a);				// checks if the tree is empty
int heightl(pTreel a);					// calculates the height of the tree
pTreel cTreel(int e, float f);				// creates a tree which stores the route ID and total distance
Chainl* cChainl(pTreel a);				// creates a linked list for the queue
Queuel cQueuel(pTreel a);				// creates a queue which contains a tree
Queuel enterl(Queuel f, pTreel a);			// enters the tree in the queue
pTreel rmQueuel(Queuel* f);				// removes a slot from the queue and returns the tree which was inside
short existLBl(pTreel a);				// checks if the left branch of the tree exists
short existRBl(pTreel a);				// checks if the right branch of the tree exists
pTreel lRotl (pTreel a);				// left rotation for the AVL
pTreel rRotl (pTreel a);				// right rotation for the AVL
pTreel doubleLRotl(pTreel a);				// right-left rotation for the AVL
pTreel doubleRRotl(pTreel a);				// left-right rotation for the AVL
pTreel eqAVLl(pTreel a);				// checks the tree's balance to determine if a rotation is needed and makes the correct rotation
pTreel insertAVLl(pTreel a, int e, float x, int* h);	// inserts a route ID and distance into an AVL, if the ID is already in the tree, the distance will add to the ID's distance value
void infix1l(pTreel a, Queuel* f);			// fills a queue with the tree which was sorted by route ID
pTreel addBSTl(pTreel a, int e, float x);		// sorts the route IDs by their total distance from shortest to longest
short isBSTl(pTreel a);					// checks if the tree is already sorted
pTreel cBSTFromTreel(pTreel a);				// creates a tree sorted by total distance from the tree which was sorted by route ID
void processl(pTreel a);				// writes down the route ID and distance into a file which will be used to draw the graph
void infix2l(pTreel a);					// writes down the route ID and distance from longest distance to shortest



// List of functions and processes for the -t process
// List of functions linked to the AVL which sorts by route ID
short isEmptyi(pTreei a);				// checks if the ID tree is empty
int heighti(pTreei a);					// calculates the height of the ID tree
pTreei cTreei(int e);					// creates a tree which stores route IDs
short existLBi(pTreei a);				// checks if the left branch of the ID tree exists
short existRBi(pTreei a);				// checks if the right branch of the ID tree exists
pTreei lRoti (pTreei a);				// left rotation for the ID AVL
pTreei rRoti (pTreei a);				// right rotation for the ID AVL
pTreei doubleLRoti(pTreei a);				// right-left rotation for the ID AVL
pTreei doubleRRoti(pTreei a);				// left-right rotation for the ID AVL
pTreei eqAVLi(pTreei a);				// checks the ID tree's balance to determine if a rotation is needed
pTreei insertAVLi(pTreei a, int e, int* i, int* h);	// inserts a route ID into an AVL

// Main list of functions and processes 
short isEmptyt1(pTreet1 a);								// checks if the main tree is empty
int heightt1(pTreet1 a);								// calculates the height of the main tree
pTreet1 cTreet1(int e, char* city, int count, int fcount);				// creates a tree which stores the cities along with an ID AVL and counters
Chaint* cChaint(pTreet1 a);								// creates a linked list
Queuet cQueuet(pTreet1 a);								// creates a queue
Queuet entert(Queuet f, pTreet1 a);							// enters the tree in the queue
pTreet1 rmQueuet(Queuet* f);								// removes a slot from the queue and returns the tree which was inside
short existLBt1(pTreet1 a);								// checks if the left branch of the tree exists
short existRBt1(pTreet1 a);								// checks if the right branch of the tree exists
void processt1(pTreet1 a);								// writes down how many times a city is visited and how many times it was the departure city along with its name itself into a file which will be sorted by alphabetical order
void infix1t1(pTreet1 a, Queuet* f);							// fills a queue with the tree which was sorted by alphabetical order
void infix2t1(pTreet1 a);								// writes down both counters and the city's name from highest total count to lowest
pTreet1 addBSTt(pTreet1 a, int e, char* city, int count, int fcount);			// sorts the cities from lowest total count to highest
short isBSTt(pTreet1 a);								// checks if the tree is already sorted
pTreet1 lRott1 (pTreet1 a);								// left rotation for the main AVL
pTreet1 rRott1 (pTreet1 a);								// right rotation for the  main AVL
pTreet1 doubleLRott1(pTreet1 a);							// right-left rotation for the  main AVL
pTreet1 doubleRRott1(pTreet1 a);							// left-right rotation for the  main AVL
pTreet1 eqAVLt1(pTreet1 a);								// checks the main tree's balance to determine if a rotation is needed
pTreet1 insertAVLt1(pTreet1 a, int e, char* city, int count, int fcount, int* h);	// inserts a city and a route ID into an AVL, the right counters would be modified depending on whether a city/ID duo already exists in the AVL or not
pTreet1 cBSTFromTreet(pTreet1 a);							// creates a tree sorted by total count from the tree which was sorted by alphabetical order

// List of functions and processes linked to the AVL which sorts by alphabetical order
short isEmptyt2(pTreet2 a);							// checks if the final tree is empty
int heightt2(pTreet2 a);							// calculates the height of the final tree
pTreet2 cTreet2(char* city, int count, int fcount);				// creates a tree which stores the city and counters
short existLBt2(pTreet2 a);							// checks if the left branch of the final tree exists
short existRBt2(pTreet2 a);							// checks if the right branch of the final tree exists
void processt2(pTreet2 a);							// writes down how many times a city is visited and how many times it was the departure city along with its name into a file which will be used to draw the graph
void infixt2(pTreet2 a);							// writes down both counters and the city's name by alphabetical order
pTreet2 lRott2 (pTreet2 a);							// left rotation for the final AVL
pTreet2 rRott2 (pTreet2 a);							// right rotation for the final AVL
pTreet2 doubleLRott2(pTreet2 a);						// right-left rotation for the final AVL
pTreet2 doubleRRott2(pTreet2 a);						// left-right rotation for the final AVL
pTreet2 eqAVLt2(pTreet2 a);							// checks the final tree's balance to determine if a rotation is needed
pTreet2 insertAVLt2(pTreet2 a, char* city, int count, int fcount, int* h);	// inserts a city and a route ID into an AVL sorted by alphabetical order



// List of functions and processes for the -s process
short isEmptys(pTrees a);							// checks if the tree is empty
int heights(pTrees a);								// calculates the height of the tree
pTrees cTrees(int e, double f, double min, double max, double av);		// creates a tree which stores the route ID and a few statistics
Chains* cChains(pTrees a);							// creates a linked list
Queues cQueues(pTrees a);							// creates a queue
Queues enters(Queues f, pTrees a);						// enters the tree in the queue
pTrees rmQueues(Queues* f);							// removes a slot from the queue and returns the tree which was inside
short existLBs(pTrees a);							// checks if the left branch of the tree exists
short existRBs(pTrees a);							// checks if the right branch of the tree exists
void process1s(pTrees a);							// calculates the average distance per step and the max-min value
void infix1s(pTrees a, Queues* f);						// fills a queue with the tree which was sorted by route ID and calculates the average distance and the max-min value
void process2s(pTrees a);							// writes down the route ID and stats into a file which will be used to draw the graph
void infix2s(pTrees a);								// writes down the route ID and stats by max-min value from highest to lowest
pTrees addBSTs(pTrees a, int e, double x, double min, double max, double av);	// sorts the route IDs by max-min value from lowest to highest
pTrees lRots (pTrees a);							// left rotation for the AVL
pTrees rRots (pTrees a);							// right rotation for the AVL
pTrees doubleLRots(pTrees a);							// right-left rotation for the AVL
pTrees doubleRRots(pTrees a);							// left-right rotation for the AVL
pTrees eqAVLs(pTrees a);							// checks the tree's balance to determine if a rotation is needed
pTrees insertAVLs(pTrees a, int e, double x, int* h);				// inserts a route ID with a distance into an AVL sorted by route ID, the stats are modified if the ID is already in the AVL
pTrees cBSTFromTrees(pTrees a);							// creates a tree sorted by max-min from the tree which was sorted by route ID
