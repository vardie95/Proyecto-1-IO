#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int **matrix = NULL;

int main(int argc, char *argv[] ){
	if (argc == 2) {
		if( ( !(strcmp(argv[1], "x")))) {
			printf("Modo Experimental\n");

		}else if ( ( !(strcmp(argv[1], "y")))){
			printf("Modo  Cientifico\n");

		}else{
			printf("Error:Give a correct argument\n");
		}


	}else {

		printf("Error: Too many arguments\n" );
	}

	return 0; 
	
}