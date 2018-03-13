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
		if( ( !(strcmp(argv[1], "x")))) {
			printf("Modo Experimental\n");
			int items_value[6];
			int items_size[6];
			int items_value_2[6];
			int items_size_2[6];
			for (int i = 0; i < 6; i++) {
				int rand_value = (rand() % 20) + 1;
				int rand_size = (rand() % 7) + 1;
				items_value[i] = rand_value;
				items_size[i] = rand_size;
				items_value_2[i] = rand_value;
				items_size_2[i] = rand_size;
				printf("%d, %d\n", items_value[i], items_size[i]);
			}
			printf("%d\n", sizeof(items_value) / sizeof(int));
			basicGreedy(15, items_value, items_size);
			printf("\n%s\n", "------------------------------------------");
			proportionalGreedy(15, items_value_2, items_size_2);
		}else if ( ( !(strcmp(argv[1], "y")))){
			printf("Modo  Cientifico\n");
			dinamicExample();
		}else{
			printf("Error:Give a correct argument\n");
		}
	}else {
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

void basicGreedy(int bag_size, int items_value[], int items_size[]){
	makeBeamer();
	int bag_value = 0;
	int temp_higher_value = 0;
	int temp_size = 0;
	int temp_index;	
	bool space_available = true;
	int n = sizeof(items_value) / sizeof(int);
	while (space_available) {
		space_available = false;
		for (int i = 0; i < n; i++) {
			if (items_value[i] > temp_higher_value && items_size[i] <= bag_size) {
				temp_higher_value = items_value[i];
				temp_size = items_size[i];
				temp_index = i;
				space_available = true;
				break;
			}
		}
		if (space_available == true) {
			printf("%s%d%s%d\n", "Item ", temp_index, ": was added to the bag.BAG: ", bag_size);
			bag_value += temp_higher_value;
			bag_size -= temp_size;
			items_value[temp_index] = 0;
			temp_higher_value = 0;
		}	
	}
}

void proportionalGreedy(int bag_size, int items_value[], int items_size[]) {
	int bag_value = 0;
	float temp_higher_proportion = 0;
	int temp_size = 0;
	int temp_index;	
	int n = sizeof(items_value) / sizeof(int);
	bool space_available = true;
	for (int i = 0; i < 6; i++) {
		printf("%s%d%s%d%s%d\n", "Item ", i, " - Value: ", items_value[i], " / Size: ", items_size[i]);
	}
	printf("%s\n", "");
	while (space_available) {
		space_available = false;
		for (int i = 0; i < n; i++) {
			if (items_value[i] > 0){
				if ((items_value[i] / items_size[i]) > temp_higher_proportion && items_size[i] <= bag_size) {
					temp_higher_proportion = items_value[i] / items_size[i];
					temp_size = items_size[i];
					temp_index = i;
					space_available = true;
					break;
				}
			}
		}
		if (space_available == true) {
			printf("%s%d%s\n", "Item ", temp_index, ": was added to the bag.");
			bag_value += items_value[temp_index];
			bag_size -= temp_size;
			items_value[temp_index] = 0;
			temp_higher_proportion = 0;
		}	
	}
}

void dinamicExample() {
	srand(time(NULL));
	int items_value[7];
	int items_size[7];
	items_value[0] = 7;
	items_value[1] = 9;
	items_value[2] = 5;
	items_value[3] = 12;
	items_value[4] = 14;
	items_value[5] = 6;
	items_value[6] = 12;
	items_size[0] = 3;
	items_size[1] = 4;
	items_size[2] = 2;
	items_size[3] = 6;
	items_size[4] = 7;
	items_size[5] = 3;
	items_size[6] = 5;

	/*for (int i = 0; i < 10; i++) {
		items_value[i] = (rand() % 100) + 1;
		items_size[i] = (rand() % 40) + 1;
		printf("%d, %d\n", items_value[i], items_size[i]);
	}*/
	int **p;
  	int i, j;
  	int m = 16;
  	int n = 7;
  	p = malloc(sizeof(float *) * m); /* Row pointers */
	for(i = 0; i < m; i++) {
		p[i] =  malloc(sizeof(float) * n); /* Rows */
	}

	/* Assign values to array elements and print them */
  	/*for(i = 0; i < m; i++) {
	    for(j = 0; j < n; j++) {
	      p[i][j] = (i * 10) + (j + 1);
	      printf("%6d",p[i][j]);
	    }
	    printf("\n");
    }*/
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