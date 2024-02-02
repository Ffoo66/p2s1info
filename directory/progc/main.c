#include "library.h"

int max2 (int a, int b){	// determines the highest value between two ints
	int m;
	if (a>=b){
		m=a;
	}
	else{
		m=b;
	}
	return m;
}

int min2 (int a, int b){	// determines the lowest value between two ints
	int m;
	if (a<=b){
		m=a;
	}
	else{
		m=b;
	}
	return m;
}

int main(int argc, char** argv){	// main function
	char arg = atoi(argv[1]);
	int n = 0, h;
	short t = 0;
	FILE* data1 = NULL;
	data1 = fopen(argv[2], "r");
// argv[2] is a realpath, if the realpath has spaces, argv[2] would stop at the space and the remaining part of the realpath would go into the next slot of argv, which means the executable would not work properly
	if (data1 == NULL){
		printf("C file error\n");
		exit(1);
	}
	if (arg == 1){		// -l process
		float x = 0;
		pTreel ai = malloc(sizeof(Treel));
		pTreel ad = malloc(sizeof(Treel));
		if (ai == NULL || ad == NULL){
			printf("C error\n");
			exit(1);
		}
		t = fscanf(data1, "%d", &n);	// gets the route ID from the cut file
		t = fscanf(data1, "%f", &x);	// gets the distance linked with the ID from the cut file
		ai = cTreel(n, x);
		while(t != EOF){				// repeats until the end of the file
			int tmpi = 0;
			float tmpf = 0;
			t = fscanf(data1, "%d", &tmpi);		// gets the route ID from the cut file
			if (t == EOF){
				break;
			}
			t = fscanf(data1, "%f", &tmpf);		// gets the distance linked with the ID from the cut file
			if (t == EOF){
				break;
			}
			insertAVLl(ai, tmpi, tmpf, &h);		// inserts the ID and distance into an AVL sorted by route ID
		}
		ad = cBSTFromTreel(ai);		// creates a BST sorted by total distance from the previous AVL
		infix2l(ad);			// prints the route ID and total distance sorted from highest total distance to lowest
	}
	else if (arg == 2){	// -t process main part
		int m = 0;
		char* c = malloc(40*sizeof(char));
		pTreet1 ai = malloc(sizeof(Treet1));
		pTreet1 ad = malloc(sizeof(Treet1));
		FILE* data2 = NULL;
		data2 = fopen(argv[3], "r");
// argv[3] is a realpath, if the realpath has spaces, argv[3] would stop at the space and the remaining part of the realpath would go into the next slot of argv, which means the executable would not work properly
		if (data2 == NULL || ai == NULL || ad == NULL){
			printf("C error\n");
			exit(2);
		}
		t = fscanf(data1, "%d", &n);	// gets the route ID from the cut file
		t = fscanf(data1, "%d", &m);	// gets the step ID from the cut file
		fgetc(data1);
		c = fgets(c, 39, data1);	// gets the step's departure city's name from the cut file
		if (m == 1){			// if the step ID is 1, the step's departure city is also the route's departure city
			ai = cTreet1(n, c, 1, 1);
		}
		else {
			ai = cTreet1(n, c, 1, 0);
		}
		while(t != EOF){				// repeats until the end of the first file
			int tmpn = 0, tmpm = 0;
			char* tmpc = malloc(40*sizeof(char));
			t = fscanf(data1, "%d", &tmpn);		// gets the route ID from the cut file
			if (t == EOF){
				break;
			}
			t = fscanf(data1, "%d", &tmpm);		// gets the step ID from the cut file
			if (t == EOF){
				break;
			}
			fgetc(data1);
			tmpc = fgets(tmpc, 39, data1);		// gets the step's departure city's name from the cut file
			if (tmpc == NULL){
				break;
			}
			if (tmpm == 1){				// if the step ID is 1, the step's departure city is also the route's departure city
				ai = insertAVLt1(ai, tmpn, tmpc, 1, 1, &h);	// inserts into the AVL and adds one to both counters
			}
			else{
				ai = insertAVLt1(ai, tmpn, tmpc, 1, 0, &h);	// inserts into the AVL and adds one to the total count if unique ID
			}
		}
		t = 0;
		while(t != EOF){				// now reading the second file, only arrival cities (no route's departure city)
			int tmpi = 0;
			char* tmpc = malloc(40*sizeof(char));
			t = fscanf(data2, "%d", &tmpi);		// gets the route ID from the cut file
			if (t == EOF){
				break;
			}
			fgetc(data2);
			tmpc = fgets(tmpc, 39, data2);		// gets the step's arrival city's name from the cut file
			if (tmpc == NULL){
				break;
			}
			ai = insertAVLt1(ai, tmpi, tmpc, 1, 0, &h);	// inserts into the AVL and adds one to the total count if unique ID
		}
		ad = cBSTFromTreet(ai);		// creates a BST sorted by total count from the previous AVL
		infix2t1(ad);			// prints the cities with total count and departure count sorted from highest total count to lowest
		fclose(data2);
	}
	else if (arg == 3){	// -t process to sort the remaining cities by alphabetical order
		int m = 0, i = 1;
		char* c = malloc(40*sizeof(char));
		pTreet2 ai = malloc(sizeof(Treet2));
		if (ai == NULL){
			printf("C error\n");
			exit(1);
		}
		t = fscanf(data1, "%d", &n);		// gets the total count from the cut file
		fgetc(data1);
		t = fscanf(data1, "%d", &m);		// gets the departure count from the cut file
		fgetc(data1);
		c = fgets(c, 39, data1);		// gets the city from the cut file
		ai = cTreet2(c, n, m);
		while(t != EOF){				// repeats until the end of the first file
			int tmpn = 0, tmpm = 0;
			char* tmpc = malloc(40*sizeof(char));
			t = fscanf(data1, "%d", &tmpn);		// gets the total count from the cut file
			if (t == EOF){
				break;
			}
			fgetc(data1);
			t = fscanf(data1, "%d", &tmpm);		// gets the departure count from the cut file
			if (t == EOF){
				break;
			}
			fgetc(data1);
			tmpc = fgets(tmpc, 39, data1);		// gets the city from the cut file
			if (tmpc == NULL){
				break;
			}
			i++;
			ai = insertAVLt2(ai, tmpc, tmpn, tmpm, &h);	// sorts by alphabetical order through an AVL
		}
		infixt2(ai);	// prints the cities with total count and departure count sorted by alphabetical order
	}
	else if (arg == 4){		// -l process
		double x = 0;
		pTrees ai = malloc(sizeof(Trees));
		pTrees ad = malloc(sizeof(Trees));
		if (ai == NULL || ad == NULL){
			printf("C error\n");
			exit(1);
		}
		t = fscanf(data1, "%d", &n);		// gets the route ID from the cut file
		t = fscanf(data1, "%lf", &x);		// gets the distance linked with the ID from the cut file
		ai = cTrees(n, x, x, x, x);
		while(t != EOF){				// repeats until the end of the file
			int tmpi = 0;
			double tmpf = 0;
			t = fscanf(data1, "%d", &tmpi);			// gets the route ID from the cut file
			if (t == EOF){
				break;
			}
			fgetc(data1);
			t = fscanf(data1, "%lf", &tmpf);		// gets the distance linked with the ID from the cut file
			if (t == EOF){
				break;
			}
			fgetc(data1);
			insertAVLs(ai, tmpi, tmpf, &h);			// inserts the ID and distance into an AVL sorted by route ID
		}
		ad = cBSTFromTrees(ai);		// creates a BST sorted by max-min distance from the previous AVL
		infix2s(ad);			// prints the route ID and statistics sorted from highest max-min distance to lowest
	}
	else{
		printf("Error in shell\n");
	}
	fclose(data1);
	return 0;
}
