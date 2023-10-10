#include <stdio.h>
#include "C:/Users/fdrff/Downloads/Profiler.h"
using namespace std;

#define MAX_SIZE 10000
#define STEP_SIZE 100
#define NR_OPERATII 10

Profiler p ("Sortari");

void sortare_v1 (int v[], int n) {
	 
	Operation comp = p.createOperation("v1_comp", n);
	Operation atribuire = p.createOperation("v1_atribuiri", n);
	int k = 0;
	while (!k) {

		k = 1;
		
		for (int i = 0; i < n - 1; i++) {
			comp.count();
			if (v[i] > v[i + 1]) {
				atribuire.count(3);
				swap(v[i], v[i + 1]);
				k = 0;

			}

		}
		n--;

	}
}


void sortare_v2 (int v[], int n) {

	Operation comp = p.createOperation("v2_comp", n);
	Operation atribuire = p.createOperation("v2_atribuiri", n);
	int val = 0;
	int j = 0;
	for (int i = 1; i < n; i++) {
		atribuire.count();
		val = v[i];
		j = i - 1;
		comp.count();
		while ((j >= 0) && (v[j] > val)) {
			atribuire.count(2);
			v[j + 1] = v[j];
			j--;
			v[j + 1] = val;
	   }
	}
}

void sortare_v3(int v[], int n) {

	Operation comp = p.createOperation("v3_comp", n);
	Operation atribuire = p.createOperation("v3_atribuiri", n);
	int minimul = 0;
	for (int i = 0; i < n-1; i++) {
		minimul = i;
		for (int j = i+1; j < n; j++){
			comp.count();
			if (v[j] < v[minimul]) {
				atribuire.count();
				minimul = j;
			}
		}
		if (minimul != i) {
			atribuire.count(3);
			swap(v[i], v[minimul]);
		}
	}
}

void demo () {

	int v[] = { 7, 6, 1, 5, 9, 2, 4 };
	int n = sizeof(v) / sizeof(v[0]) ;
	sortare_v1 (v,n);
	printf("v1:-> ");
	for (int i = 0; i < n; i++) {
		printf("%d ", v[i]);
	}
	printf("\n");
	sortare_v2(v, n);
	printf("v2:-> ");
	for (int i = 0; i < n; i++) {
		printf("%d ", v[i]);
	}
	printf("\n");
	sortare_v3(v, n);
	printf("v3:-> ");
	for (int i = 0; i < n; i++) {
		printf("%d ", v[i]);
	}

}



void grafic (int order) {

	int v1 [MAX_SIZE];
	int v2[MAX_SIZE];
	int v3[MAX_SIZE];
	int n;
	for (n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE) {
		for (int test = 0; test < NR_OPERATII; test++) {
			FillRandomArray(v1, n, 10, 10000, false, order);
			FillRandomArray(v2, n, 10, 10000, false, order);
			FillRandomArray(v3, n, 10, 10000, false, order);
			sortare_v1(v1, n);
			sortare_v2(v2, n);
			sortare_v3(v3, n);
		}
	}
	p.divideValues("v1_comp", NR_OPERATII);
	p.divideValues("v1_atribuiri", NR_OPERATII);
	p.addSeries("v1", "v1_comp", "v1_atribuiri");

	p.divideValues("v2_comp", NR_OPERATII);
	p.divideValues("v2_atribuiri", NR_OPERATII);
	p.addSeries("v2", "v2_comp", "v2_atribuiri");

	p.divideValues("v3_comp", NR_OPERATII);
	p.divideValues("v3_atribuiri", NR_OPERATII);
	p.addSeries("v3", "v3_comp", "v3_atribuiri");

	p.createGroup("v", "v1", "v2","v3");
	p.createGroup("Atribuiri", "v1_atribuiri", "v2_atribuiri","v3_atribuiri");
	p.createGroup("Comparari", "v1_comp", "v2_comp","v3_comp");

}

void grafic_all() {

	grafic(UNSORTED);
	p.reset("best");
	grafic(ASCENDING);
	p.reset("worst");
	grafic(DESCENDING);

	p.showReport();

}


int main() {

	//demo();
	grafic_all();
	return 0;
}
