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
			basicGreedy(15, items_value, items_size);
			printf("\n%s\n", "------------------------------------------");
			proportionalGreedy(15, items_value_2, items_size_2);
		}else if ( ( !(strcmp(argv[1], "y")))){
			printf("Modo  Cientifico\n");
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
	while (space_available) {
		space_available = false;
		for (int i = 0; i < 6; i++) {
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
	bool space_available = true;
	for (int i = 0; i < 6; i++) {
		printf("%s%d%s%d%s%d\n", "Item ", i, " - Value: ", items_value[i], " / Size: ", items_size[i]);
	}
	printf("%s\n", "");
	while (space_available) {
		space_available = false;
		for (int i = 0; i < 6; i++) {
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