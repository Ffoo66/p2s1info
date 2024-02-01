#include "library.h"

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
		ai = cTreel(n, x);
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
		ad = cBSTFromTreel(ai);
		infix2l(ad);
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
			ai = cTreet1(n, c, 1, 1);
		}
		else {
			ai = cTreet1(n, c, 1, 0);
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
		ad = cBSTFromTreet(ai);
		infix2t1(ad);
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
		ai = cTreet2(c, n, m);
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
		infixt2(ai);
	}
	else if (arg == 4){
		double x = 0;
		pTrees ai = malloc(sizeof(Trees));
		pTrees ad = malloc(sizeof(Trees));
		if (ai == NULL || ad == NULL){
			printf("C error\n");
			exit(1);
		}
		t = fscanf(data1, "%d", &n);
		t = fscanf(data1, "%lf", &x);
		ai = cTrees(n, x, x, x, x);
		while(t != EOF){
			int tmpi = 0;
			double tmpf = 0;
			t = fscanf(data1, "%d", &tmpi);
			if (t == EOF){
				break;
			}
			fgetc(data1);
			t = fscanf(data1, "%lf", &tmpf);
			if (t == EOF){
				break;
			}
			fgetc(data1);
			insertAVLs(ai, tmpi, tmpf, &h);
		}
		ad = cBSTFromTrees(ai);
		infix2s(ad);
	}
	else{
		printf("Error in shell\n");
	}
	fclose(data1);
	return 0;
}
