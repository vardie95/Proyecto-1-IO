#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
FILE *out;
int **matrix = NULL;





int main(int argc, char *argv[] ){
	float x = 0 / 2;
	srand(time(NULL));
	
	if (argc == 2) {
		if( ( !(strcmp(argv[1], "x")))) { // If user passes the value x - Experimental mode starts
			printf("Modo Experimental\n");

			int items_value[6];     // Variables values for basic greedy 
			int items_size[6];      // Variables sizes for basic greedy

			int items_value_2[6];   // Variables values for proportional greedy
			int items_size_2[6];    // Variables size for proportional greedy

			int items_value_3[6];   // Variables values for dinamic programming solution
			int items_size_3[6];    // Variables size for dinamic programming solution

			for (int i = 0; i < 6; i++) {
				int rand_value = (rand() % 20) + 1; // Variable value randomizer
				int rand_size = (rand() % 7) + 1;   // Variable size randomizer
				items_value[i] = rand_value;
				items_size[i] = rand_size;
				items_value_2[i] = rand_value;
				items_size_2[i] = rand_size;
				items_value_3[i] = rand_value;
				items_size_3[i] = rand_size;
				printf("%s%d%s%d%s%d\n", "Item ", i, " - Value: ", items_value[i], " / Size: ", items_size[i]);
			}

			printf("%s\n", "");

			basicGreedy(15, items_value, items_size, 6); // The basic greedy algorithm is execute

			printf("\n%s\n", "------------------------------------------");

			proportionalGreedy(15, items_value_2, items_size_2, 6); // The proportional greedy algorithm is execute

			printf("\n%s\n", "------------------------------------------");

			dinamicProgramming(16, 6, items_value_3, items_size_3); // The dinamic programming algorithm is execute (We pass a value of 16 because we need 0 to 15 rows)


		} else if ( ( !(strcmp(argv[1], "y")))){
			printf("Modo  Cientifico\n");
			//dinamicExample();
		} else{
			printf("Error:Give a correct argument\n");
		}
	} else {
		printf("Error: Please provide the correct argument\n" );
	}
	return 0; 
}

void createOutFile()
{
	out = fopen ("salida.tex", "w");
}

void writeHeader(){
	fprintf(out,"\\documentclass[12]{beamer}\n");
    fprintf(out,"\\usetheme{Oxygen}\n");
	fprintf(out,"\\hypersetup{pdfpagemode=FullScreen}\n");
	fprintf(out,"\\usepackage{thumbpdf}\n");
	fprintf(out,"\\usepackage{wasysym}\n");
	fprintf(out,"\\usepackage{ucs}\n");
	fprintf(out,"\\usepackage[utf8]{inputenc}\n");
	fprintf(out,"\\usepackage{verbatim}\n\n");
	fprintf(out,"\\title{Proyecto 01}\n");
	fprintf(out,"\\subtitle{Investigación de Operaciones}\n");
	fprintf(out,"\\author{Luis Diego Vargas Arroyo- Carlos Villalobos Mora}\n\n");
	fprintf(out,"\\begin{document}\n");
	fprintf(out,"\\frame{\\titlepage}\n");
	fprintf(out,"\\section{Introducción}\n");
	fprintf(out,"\\begin{frame}\n");
	fprintf(out,"\\frametitle{Introducción}\n");

	fprintf(out,"\\end{frame}\n");
}

void makeBeamer(){
	createOutFile();
	writeHeader();
	//system("evince salida/salida.pdf");
	fprintf(out,"\\end{document}\n");

}

void basicGreedy(int bag_size, int items_value[], int items_size[], int len){ // Basic greedy algorithm
	printf("%s\n", "Basic Greedy:");
	makeBeamer();
	int bag_value = 0;
	int temp_higher_value = 0;
	int temp_size = 0;
	int temp_index;	
	bool space_available = true;
	while (space_available) {
		space_available = false;
		for (int i = 0; i < len; i++) {
			if (items_value[i] > temp_higher_value && items_size[i] <= bag_size) {
				temp_higher_value = items_value[i];
				temp_size = items_size[i];
				temp_index = i;
				space_available = true;
			}
		}
		if (space_available == true) {
			printf("%s%d%s%d%s%d\n", "Item ", temp_index, ": was added to the bag.BAG: ", bag_size, " -> ", bag_size - temp_size);
			bag_value += temp_higher_value;
			bag_size -= temp_size;
			items_value[temp_index] = 0;
			temp_higher_value = 0;
		}	
	}
}

void proportionalGreedy(int bag_size, int items_value[], int items_size[], int len) {
	printf("%s\n", "Proportional Greedy:");
	int bag_value = 0;
	float temp_higher_proportion = 0;
	int temp_size = 0;
	int temp_index;	
	bool space_available = true;
	while (space_available) {
		space_available = false;
		for (int i = 0; i < len; i++) {
			if (items_value[i] > 0){
				if ((items_value[i] / items_size[i]) > temp_higher_proportion && items_size[i] <= bag_size) {
					temp_higher_proportion = items_value[i] / items_size[i];
					temp_size = items_size[i];
					temp_index = i;
					space_available = true;
				}
			}
		}
		if (space_available == true) {
			printf("%s%d%s%d%s%d\n", "Item ", temp_index, ": was added to the bag.BAG: ", bag_size, " -> ", bag_size - temp_size);
			bag_value += items_value[temp_index];
			bag_size -= temp_size;
			items_value[temp_index] = 0;
			temp_higher_proportion = 0;
		}	
	}
}

void dinamicProgramming(int m, int n, int items_value[], int items_size[]) {
	printf("%s\n", "Dinamic Programming:");
	srand(time(NULL));
	/*for (int i = 0; i < 10; i++) {
		items_value[i] = (rand() % 100) + 1;
		items_size[i] = (rand() % 40) + 1;
		printf("%d, %d\n", items_value[i], items_size[i]);
	}*/
	int **p;
  	int i, j;
  	p = malloc(sizeof(float *) * m); /* Row pointers */
	for(i = 0; i < m; i++) {
		p[i] =  malloc(sizeof(float) * n); /* Rows */
	}

	/* Assign values to array elements */
    for (j = 0; j < n; j++) {
    	for (i = 0; i < m; i++) {
    		if (items_size[j] <= i) {
    			if (j == 0) {
    				p[i][j] = items_value[j];
    			} else if (j > 0 && items_value[j] + p[i - items_size[j]][j-1] >= p[i][j-1]){
    				p[i][j] = items_value[j] + p[i - items_size[j]][j-1];
    			} else {
    				p[i][j] = p[i][j-1];
    			} 
    		} else if (j > 0){
    			p[i][j] = p[i][j-1];
    		} else {
    			p[i][j] = 0;
    		}
    	}
    }

    for(i = 0; i < m; i++) {
	    for(j = 0; j < n; j++) {
	      printf("%6d",p[i][j]);
	    }
	    printf("\n");
    }



    /* Deallocate memory */
  	for(i = 0; i < m; i++) {
	    free(p[i]); /* Rows */
	}
	free(p); /* Row pointers */

}