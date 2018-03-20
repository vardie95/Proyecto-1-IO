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
	if (argc == 2 || argc == 3) {
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
			slideMatematico(items_value,items_size,6);
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
			fprintf(out,"\\end{document}\n");
			fclose(out);
			system("pdflatex salida/salida.tex");
			system("evince salida.pdf");
				
		} else if ( ( !(strcmp(argv[1], "-E=")))){
			int n = atoi(argv[2]);
			if(n!=0){
				printf("Modo  Cientifico\n");
				experimental(n);
				fprintf(out,"\\end{document}\n");
				fclose(out);
				system("pdflatex salida/salida.tex");
				system("evince salida.pdf");

			}else{
				printf("Error:Give a correct N argument\n");
				}
			
			
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
	fprintf(out,"\\usepackage{verbatim}\n");
	fprintf(out,"\\title{Proyecto 01}\n");
	fprintf(out,"\\subtitle{Investigación de Operaciones}\n");
	fprintf(out,"\\author{Luis Diego Vargas Arroyo- Carlos Villalobos Mora}\n\n");
	fprintf(out,"\\begin{document}\n");
	fprintf(out,"\\frame{\\titlepage}\n");
	fprintf(out,"\\section{Bag Problem}\n");
	
}


void printable(int ** p,int ** c,int n,int m){
	
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
				if(c[i][j]== 0){
					fprintf(out, " \\textcolor{red}{%d} &",p[i][j]);
				}else{
					fprintf(out, " \\textcolor{green}{%d} &",p[i][j]);
				}
						
			}else{
				if(c[i][j]== 0){
					fprintf(out, " \\textcolor{red}{%d}",p[i][j]);
				}else{
					fprintf(out, " \\textcolor{green}{%d}",p[i][j]);
				}
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
void slideMatematico(int items_value[],int items_size[],int len){
	
	fprintf(out,"\\begin{frame}\n");
	fprintf(out,"\\frametitle{Mathematic Form}\n\n");
	fprintf(out,"Maximizar: \n");
	fprintf(out,"\\begin{center}\n");
	fprintf(out,"\\[ ");
	for (int i=0; i < len; i++) {
		if(i!=len-1){
			fprintf(out,"  %d x_{%d} + ",items_value[i],i);
		}else{
			fprintf(out,"  %d x_{%d} ",items_value[i],i);
		}
	}
	fprintf(out,"\\] \n");
	fprintf(out, "\\end{center}\n\n");
	fprintf(out,"Sujeto a: \n");
	fprintf(out,"\\begin{center}\n");
	fprintf(out,"\\[ ");
	for (int i=0; i < len; i++) {
		if(i!=len-1){
			fprintf(out,"  %d x_{%d} + ",items_size[i],i);
		}else{
			fprintf(out,"  %d x_{%d} ",items_size[i],i);
		}
	}
	fprintf(out,"<=15 \\] \n");
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
void createSlide(char array[]){
	fprintf(out,"\\begin{frame}\n");
	fprintf(out,"\\frametitle{%s}\n\n",array);
	fprintf(out,"\\begin{flushleft}\n");	
	fprintf(out,"\\small\n");
	fprintf(out,"\\small\n");

}
void printGreedy(int item,int item_value, int bag_size){
	fprintf(out,"item: %d was added to the bag: Size: %d  Space left in bag: %d \n",item,item_value,bag_size);
	fprintf(out,"\\newline\n");


}

void endSlide(){
	
	fprintf(out, "\\end{flushleft}\n\n");
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
	createSlide("Basic Greedy");
	fprintf(out,"\\large \n");
	fprintf(out,"The Size of the bag is:  %d \n",bag_size);
	fprintf(out,"\\newline \n");
	fprintf(out,"\\newline \n");
        fprintf(out,"\\newline \n");
	fprintf(out, "\\small \n");
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
			printGreedy(temp_index,temp_size,bag_size-temp_size);
			bag_value += temp_higher_value;
			bag_size -= temp_size;
			items_value[temp_index] = 0;
			temp_higher_value = 0;
		}	
	}
	fprintf(out,"\\newline \n");
	fprintf(out,"\\large \n");
	fprintf(out,"Total Bag value is:  %d \n",bag_value);
	endSlide();
}

void proportionalGreedy(int bag_size, int items_value[], int items_size[], int len) {
	printf("%s\n", "Proportional Greedy:");
	int bag_value = 0;
	float temp_higher_proportion = 0;
	int temp_size = 0;
	int temp_index;	
	bool space_available = true;
	createSlide("Proportional Greedy");
	fprintf(out,"\\large \n");
	fprintf(out,"The Size of the bag is:  %d \n",bag_size);
	fprintf(out,"\\newline \n");
	fprintf(out,"\\newline \n");
        fprintf(out,"\\newline \n");
	fprintf(out, "\\small \n");
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
			printGreedy(temp_index,temp_size,bag_size-temp_size);
			bag_value += items_value[temp_index];
			bag_size -= temp_size;
			items_value[temp_index] = 0;
			temp_higher_proportion = 0;
		}	
	}
	fprintf(out,"\\newline \n");
	fprintf(out,"\\large \n");
	fprintf(out,"Total Bag value is:  %d \n",bag_value);
	endSlide();
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
	int **c;
  	int i, j;
  	p = malloc(sizeof(float *) * m); /* Row pointers */
	for(i = 0; i < m; i++) {
		p[i] =  malloc(sizeof(float) * n); /* Rows */
	}
	c = malloc(sizeof(float *) * m); /* Row pointers */
	for(i = 0; i < m; i++) {
		c[i] =  malloc(sizeof(float) * n); /* Rows */
	}

	/* Assign values to array elements */
    for (j = 0; j < n; j++) {
    	for (i = 0; i < m; i++) {
    		if (items_size[j] <= i) {
    			if (j == 0) {
    				p[i][j] = items_value[j];
    			} else if (j > 0 && items_value[j] + p[i - items_size[j]][j-1] >= p[i][j-1]){
    				p[i][j] = items_value[j] + p[i - items_size[j]][j-1];
				c[i][j] =1 ;
    			} else {
    				p[i][j] = p[i][j-1];
				c[i][j] =0;
    			} 
    		} else if (j > 0){
    			p[i][j] = p[i][j-1];
    		} else {
    			p[i][j] = 0;
    		}
    	}
    }
    for (i = 0; i < m ;i++){
		if(p[i][0] !=0){
			c[i][0]=1;
		}
	}
	
    for(i = 0; i < m; i++) {
	    for(j = 0; j < n; j++) {
	      printf("%6d",p[i][j]);
	    }
	    printf("\n");
    }
    
    printable(p,c,n,m);

    /* Deallocate memory */
  	for(i = 0; i < m; i++) {
	    free(p[i]); /* Rows */
	}
	free(p); /* Row pointers */
	/* Deallocate memory */
  	for(i = 0; i < m; i++) {
	    free(c[i]); /* Rows */
	}
	free(c); /* Row pointers */
}

void experimental(int n){
    srand(time(NULL));
    int n_2 = n;
    int **greedy;
    int **prop;
    greedy = malloc(sizeof(float *) * 10); /* Row pointers */
    prop = malloc(sizeof(float *) * 10);
    for(int i = 0; i < 10; i++) {
		greedy[i] = malloc(sizeof(float) * 10);
		prop[i] = malloc(sizeof(float) * 10);
    }
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            greedy[i][j] = 0;
            prop[i][j] = 0;
        }
    }
	while (n > 0) {
		int bag_size = 100;
		int number_items = 10;

		double **greedy_time;
		int **greedy_value;

		double **proportional_time;
		int **proportional_value;

		double **dinamic_time;
		int **dinamic_value;

		greedy_time = (double**) malloc(sizeof(double *) * 10);
		greedy_value = malloc(sizeof(float *) * 10); /* Row pointers */

		proportional_time = (double**) malloc(sizeof(double *) * 10);
		proportional_value = malloc(sizeof(float *) * 10); /* Row pointers */

		dinamic_time = (double**) malloc(sizeof(double *) * 10);
		dinamic_value = malloc(sizeof(float *) * 10); /* Row pointers */		

		for(int i = 0; i < 10; i++) {
			greedy_time[i] =  (double*) malloc(sizeof(double) * 10); /* Rows */
			greedy_value[i] = malloc(sizeof(float) * 10);

			proportional_time[i] =  (double*) malloc(sizeof(double) * 10); /* Rows */
			proportional_value[i] = malloc(sizeof(float) * 10);

			dinamic_time[i] =  (double*) malloc(sizeof(double) * 10); /* Rows */
			dinamic_value[i] = malloc(sizeof(float) * 10);
		}
		struct timeval t_ini, t_fin;
		double secsGreedy;
		double secsProGreedy;
		double secsDynamic;
		for (int i = 0; i < 10; i++){
			for (int j = 0; j < 10; j++){

				int values[number_items];
				int sizes[number_items];

				int values_2[number_items];
				int sizes_2[number_items];

				int values_3[number_items];
				int sizes_3[number_items];

				srand(clock());

				for (int k = 0; k < number_items; k++){
					int rand_value = (rand() % 100) + 1;
					double max = bag_size * 0.4;
					int max_item_size = (int) max;
					int rand_size = (rand() % max_item_size) + 1;

					values[k] = rand_value;
					sizes[k] = rand_size;

					values_2[k] = rand_value;
					sizes_2[k] = rand_size;

					values_3[k] = rand_value;
					sizes_3[k] = rand_size;
				}

				gettimeofday(&t_ini, NULL);
				int p = greedy_exp(bag_size, values, sizes, number_items); // The basic greedy algorithm is execute
				greedy_value[i][j] = p;
				gettimeofday(&t_fin, NULL);
				secsGreedy = timeval_diff(&t_fin, &t_ini);
	  			greedy_time[i][j] = secsGreedy * 1000.0;

	  			gettimeofday(&t_ini, NULL);
				int q = proportional_exp(bag_size, values_2, sizes_2, number_items); // The proportional greedy algorithm is execute
				proportional_value[i][j] = q;
				gettimeofday(&t_fin, NULL);
				secsProGreedy = timeval_diff(&t_fin, &t_ini);
	  			proportional_time[i][j] = secsProGreedy * 1000.0;

	  			gettimeofday(&t_ini, NULL);
				int z = dinamic_exp(bag_size, number_items, values_3, sizes_3); // The proportional greedy algorithm is execute
				dinamic_value[i][j] = z;
				gettimeofday(&t_fin, NULL);
				secsDynamic = timeval_diff(&t_fin, &t_ini);
	  			dinamic_time[i][j] = secsDynamic * 1000.0;
                
                if (p == z) {
                    greedy[i][j] += 1;
                }
                if (q == z) {
                	prop[i][j] += 1;
                }
                
	  			number_items += 10;
			}
			number_items = 10;
			bag_size += 100;
		}
		printTable(1, greedy_time, greedy_value);
		printTable(2, proportional_time, proportional_value);
		printTable(3, dinamic_time, dinamic_value);
		for(int i = 0; i < 10; i++) {
	    	free(greedy_time[i]); /* Rows */
	    	free(greedy_value[i]);

	    	free(proportional_time[i]); /* Rows */
	    	free(proportional_value[i]);

	    	free(dinamic_time[i]); /* Rows */
	    	free(dinamic_value[i]);
		}
		free(greedy_time); /* Row pointers */
		free(greedy_value);

		free(proportional_time); /* Row pointers */
		free(proportional_value);

		free(dinamic_time); /* Row pointers */
		free(dinamic_value);
		n -= 1;
	}
	printFinalTable(n_2, greedy, 1);
	printFinalTable(n_2, prop, 2);
	for(int i = 0; i < 10; i++) {
	    	free(greedy[i]);
	    	free(prop[i]);
    }
    free(greedy);
    free(prop);
}

int greedy_exp(int bag_size, int items_value[], int items_size[], int len){
	int bag_value = 0;
	int temp_higher_value = 0;
	int temp_size = 0;
	int temp_index;	
	bool space_available = true;
	while (space_available) {
		space_available = false;
		for (int i = 0; i < len; i++) {
			// printf("----------------------------\n");
			// for (int i = 0; i < len; i++) {
			// 	printf("Item %d, Size: %d, Value: %d\n", i, items_size[i], items_value[i]);
			// }
			if (items_value[i] > temp_higher_value && items_size[i] <= bag_size) {
				temp_higher_value = items_value[i];
				temp_size = items_size[i];
				temp_index = i;
				space_available = true;
			}
		}
		if (space_available == true) {
			bag_value += temp_higher_value;
			bag_size -= temp_size;
			items_value[temp_index] = 0;
			temp_higher_value = 0;
		}	
	}
	return bag_value;
}

int proportional_exp(int bag_size, int items_value[], int items_size[], int len){
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
			bag_value += items_value[temp_index];
			bag_size -= temp_size;
			items_value[temp_index] = 0;
			temp_higher_proportion = 0;
		}	
	}
	return bag_value;
}

int dinamic_exp(int m, int n, int items_value[], int items_size[]){
	srand(time(NULL));
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
    int bag_value = p[m-1][n-1];
    /* Deallocate memory */
  	for(i = 0; i < m; i++) {
	    free(p[i]); /* Rows */
	}
	free(p); /* Row pointers */
	return bag_value;
}

void printTable(int l, double ** c, int ** d){
	int m = 11;
	int n = 11;
	fprintf(out,"\\begin{frame}\n");
	if (l == 1) {
		fprintf(out,"\\frametitle{Greedy}\n\n");
	} else if (l == 2) {
		fprintf(out,"\\frametitle{Proportional}\n\n");
	} else {
		fprintf(out,"\\frametitle{Dinamic}\n\n");
	}
	fprintf(out, "Bagpack final values:\n");
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
			if (i == 0) {
				if (j == 0) {
					fprintf(out, " %s &", "Bagpack");
				} else {
					if(j!=n-1){
						fprintf(out, " %d &", j*10);		
					} else{
						fprintf(out, " %d ",j*10);
					}
				}
			} else if (j == 0){
				if(j!=n-1){
					fprintf(out, " %d &", i*100);		
				}else{
					fprintf(out, " %d ",i*100);
				}
			} else {
				if(j!=n-1){
				fprintf(out, " %d &", d[i-1][j-1]);		
				}else{
					fprintf(out, " %d ",d[i-1][j-1]);
				}
			}
		}
	 	fprintf(out,"\\\\ \n");
		fprintf(out,"\\hline\n");
	}
	fprintf(out, "\\end{tabular}\n");
	fprintf(out,"\\end{adjustbox}\n");
	fprintf(out, "\\end{center}\n\n");
	fprintf(out,"\\end{frame}\n");

	fprintf(out,"\\begin{frame}\n");
	if (l == 1) {
		fprintf(out,"\\frametitle{Greedy}\n\n");
	} else if (l == 2) {
		fprintf(out,"\\frametitle{Proportional}\n\n");
	} else {
		fprintf(out,"\\frametitle{Dinamic}\n\n");
	}
	fprintf(out, "Bagpack final execution times:\n");
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
			if (i == 0) {
				if (j == 0) {
					fprintf(out, " %s &", "");
				} else {
					if(j!=n-1){
						fprintf(out, " %d &", j*10);		
					} else{
						fprintf(out, " %d ",j*10);
					}
				}
			} else if (j == 0){
				if(j!=n-1){
					fprintf(out, " %d &", i*100);		
				}else{
					fprintf(out, " %d ",i*100);
				}
			} else {
				if(j!=n-1){
				fprintf(out, " %.5g &", c[i-1][j-1]);		
				}else{
					fprintf(out, " %.5g ",c[i-1][j-1]);
				}
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

void printFinalTable(int runs, int ** c, int l){
    int m = 11;
    int n = 11;
    fprintf(out,"\\begin{frame}\n");
	if (l == 1) {
		fprintf(out,"\\frametitle{Greedy optimal }\n\n");
        fprintf(out, "Percentage of greedy algorithm of being optimal\n");
	} else {
		fprintf(out,"\\frametitle{Proportional optimal }\n\n");
        fprintf(out, "Percentage of greedy proportional algorithm of being optimal\n");
	}
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
			if (i == 0) {
				if (j == 0) {
					fprintf(out, " %s &", "");
				} else {
					if(j!=n-1){
						fprintf(out, " %d &", j*10);		
					} else{
						fprintf(out, " %d ",j*10);
					}
				}
			} else if (j == 0){
				if(j!=n-1){
					fprintf(out, " %d &", i*100);		
				}else{
					fprintf(out, " %d ",i*100);
				}
			} else {
 				if(j!=n-1){
                    double k = (double) c[i-1][j-1] / (double) runs;
                    fprintf(out, " %f &", k);
 				} else{
                    double k = (double) c[i-1][j-1] / (double) runs;
                    fprintf(out, " %f ",  k);
				}
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