#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h> //cambio
FILE *out;
int **matrix = NULL;

#include <sys/time.h>

/* retorna "a - b" en segundos */
double timeval_diff(struct timeval *a, struct timeval *b)
{
  return
    (double)(a->tv_sec + (double)a->tv_usec/1000000) -
    (double)(b->tv_sec + (double)b->tv_usec/1000000);
}



int main(int argc, char *argv[] ){
	float x = 0 / 2;
	srand(time(NULL));
	makeBeamer();
	if (argc == 2) {
		if( ( !(strcmp(argv[1], "x")))) { // If user passes the value x - Experimental mode starts
			printf("Modo Experimental\n");

			int items_value[6];     // Variables values for basic greedy 
			int items_size[6];      // Variables sizes for basic greedy

			int items_value_2[6];   // Variables values for proportional greedy
			int items_size_2[6];    // Variables size for proportional greedy

			int items_value_3[6];   // Variables values for dinamic programming solution
			int items_size_3[6];    // Variables size for dinamic programming solution
			struct timeval t_ini, t_fin;
			double secsGreedy;
			double secsProGreedy;
			double secsDynamic;

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
			slideValues(items_value,items_size,6);
			printf("%s\n", "");
			gettimeofday(&t_ini, NULL);
			basicGreedy(15, items_value, items_size, 6); // The basic greedy algorithm is execute
			gettimeofday(&t_fin, NULL);
			secsGreedy = timeval_diff(&t_fin, &t_ini);
  			printf("\n\n %.16g milisegundos\n", secsGreedy * 1000.0);


			printf("\n%s\n", "------------------------------------------");

			gettimeofday(&t_ini, NULL);
			proportionalGreedy(15, items_value_2, items_size_2, 6); // The proportional greedy algorithm is execute
			gettimeofday(&t_fin, NULL);
			secsProGreedy = timeval_diff(&t_fin, &t_ini);
			printf("\n\n %.16g milisegundos\n", secsProGreedy * 1000.0);
			
			printf("\n%s\n", "------------------------------------------");
			gettimeofday(&t_ini, NULL);
			dinamicProgramming(16, 6, items_value_3, items_size_3); // The dinamic programming algorithm is execute (We pass a value of 16 because we need 0 to 15 rows)
			gettimeofday(&t_fin, NULL);
			secsDynamic = timeval_diff(&t_fin, &t_ini);			
			printf("\n\n %.16g milisegundos\n", secsDynamic * 1000.0);
			printTimesPractice(secsGreedy,secsProGreedy,secsDynamic);
			

		} else if ( ( !(strcmp(argv[1], "y")))){
			printf("Modo  Cientifico\n");
			int experiments_left = 100;
			while (experiments_left > 0) {
				int bag_size = (rand() % 901) + 100; // Defines this round bag size
				double max = bag_size * 0.4; // Get 40% of the total bag size
				int max_item_size = (int) max; // Converts the 40% into an integer
				int number_items = (rand() % 91) + 10; // Defines the number of items in this round
				
				int items_value[number_items];     // Variables values for basic greedy 
				int items_size[number_items];      // Variables sizes for basic greedy

				int items_value_2[number_items];   // Variables values for proportional greedy
				int items_size_2[number_items];    // Variables size for proportional greedy

				int items_value_3[number_items];   // Variables values for dinamic programming solution
				int items_size_3[number_items];    // Variables size for dinamic programming solution

				printf("%s%d, bag = %d, items # = %d\n", "Items for round ", experiments_left, bag_size, number_items);
				for (int i = 0; i < number_items; i++) {
					int value = (rand() % 100) + 1;
					int size = (rand() % max_item_size) + 1;
					items_value[i] = value;
					items_size[i] = size;
					items_value_2[i] = value;
					items_size_2[i] = size;
					items_value_3[i] = value;
					items_size_3[i] = size;
					printf("%s%d%s%d%s%d\n", "Item ", i, " - Value: ", items_value[i], " / Size: ", items_size[i]);
				}
				basicGreedy(bag_size, items_value, items_size, number_items);
				dinamicProgramming(bag_size + 1, number_items, items_value_3, items_size_3);
				printf("\n%s\n", "<<<<<<---------------------------------->>>>>>");
				experiments_left -= 1;
			//dinamicExample();
				}
		} else{
			printf("Error:Give a correct argument\n");
		}
	} else {
		printf("Error: Please provide the correct argument\n" );
	}
	fprintf(out,"\\end{document}\n");
	fclose(out);
	system("pdflatex salida/salida.tex");
	//system("evince salida.pdf");
	return 0; 
}

void createOutFile()
{
	out = fopen ("salida/salida.tex", "w");
}

void writeHeader(){
	fprintf(out,"\\documentclass[12]{beamer}\n");
        fprintf(out,"\\usetheme{Oxygen}\n");
	fprintf(out,"\\hypersetup{pdfpagemode=FullScreen}\n");
	fprintf(out,"\\usepackage{thumbpdf}\n");
	fprintf(out,"\\usepackage{wasysym}\n");
	fprintf(out,"\\usepackage{adjustbox}\n");
	fprintf(out,"\\usepackage{ucs}\n");
	fprintf(out,"\\usepackage[utf8]{inputenc}\n");
	fprintf(out,"\\usepackage{verbatim}\n\n");
	fprintf(out,"\\title{Proyecto 01}\n");
	fprintf(out,"\\subtitle{Investigación de Operaciones}\n");
	fprintf(out,"\\author{Luis Diego Vargas Arroyo- Carlos Villalobos Mora}\n\n");
	fprintf(out,"\\begin{document}\n");
	fprintf(out,"\\frame{\\titlepage}\n");
	fprintf(out,"\\section{Greedy}\n");
	
}


void printable(int ** c,int n,int m){
	
	fprintf(out,"\\begin{frame}\n");
	fprintf(out,"\\frametitle{Dynamic}\n\n");
	fprintf(out,"\\begin{center}\n");
	fprintf(out,"\\begin{adjustbox}{max width=\\textwidth}\n");
	fprintf(out,"\\small\n");
	fprintf(out,"\\begin{tabular}{ |");
	for (int i=0; i < n;i++) {
		fprintf(out,"c|");
	}
	fprintf(out,"}\n");
 	fprintf(out,"\\hline\n");
	for (int i=0; i < m;i++) {
		for(int j=0; j< n; j++){
			if(j!=n-1){
				fprintf(out, " %d &",c[i][j]);		
			}else{
				fprintf(out, " %d ",c[i][j]);
			}
		}
	 	fprintf(out,"\\\\ \n");
		fprintf(out,"\\hline\n");
	}
	fprintf(out, "\\end{tabular}\n");
	fprintf(out,"\\end{adjustbox}\n");
	fprintf(out, "\\end{center}\n\n");
	fprintf(out,"\\end{frame}\n");

}

void slideValues(int items_value[],int items_size[],int len){
	
	fprintf(out,"\\begin{frame}\n");
	fprintf(out,"\\frametitle{Objects Information}\n\n");
	fprintf(out,"\\begin{center}\n");
	fprintf(out,"\\begin{adjustbox}{max width=\\textwidth}\n");
	fprintf(out,"\\small\n");
	fprintf(out,"\\begin{tabular}{ |c|c| }\n");
	fprintf(out,"\\hline\n");
	fprintf(out,"    Value     &     Size     \\\\");
	fprintf(out,"\\hline\n");
	fprintf(out,"\\hline\n");
	for (int i=0; i < len; i++) {
		fprintf(out,"  %d  & %d \\\\ \n",items_value[i],items_size[i]);
		fprintf(out,"\\hline\n");
	}
	fprintf(out, "\\end{tabular}\n");
	fprintf(out,"\\end{adjustbox}\n");
	fprintf(out, "\\end{center}\n\n");
	fprintf(out,"\\end{frame}\n");

}

void printTimesPractice(double time_greedy,double time_proGreedy,double time_Dynamic){
	
	fprintf(out,"\\begin{frame}\n");
	fprintf(out,"\\frametitle{Times of Execution Algorithms}\n\n");
	fprintf(out,"\\begin{center}\n");
	fprintf(out,"Greedy Execution time was:  %f miliseconds \n",time_greedy);
	fprintf(out,"\\newline\n");
	fprintf(out,"Proporcional Greedy Execution time was:  %f    miliseconds\n",time_proGreedy);
	fprintf(out,"Dynamic Execution time was:  %f  miliseconds \n",time_Dynamic);
	fprintf(out, "\\end{center}\n\n");
	fprintf(out,"\\end{frame}\n");

}




void makeBeamer(){
	createOutFile();
	writeHeader();
	
	

}

void basicGreedy(int bag_size, int items_value[], int items_size[], int len){ // Basic greedy algorithm
	printf("%s\n", "Basic Greedy:");
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
    printable(p,n,m);

    /* Deallocate memory */
  	for(i = 0; i < m; i++) {
	    free(p[i]); /* Rows */
	}
	free(p); /* Row pointers */

}