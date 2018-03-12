#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int **matrix = NULL;

int main(int argc, char *argv[] ){
	srand(time(NULL));
	if (argc == 2) {
		if( ( !(strcmp(argv[1], "x")))) {
			printf("Modo Experimental\n");
			int bag_size = 15;
			int items_value[6];
			int items_size[6];
			for (int i = 0; i < 6; i++) {
				items_value[i] = (rand() % 21);
				items_size[i] = (rand () % 8);
				printf("%d, %d\n", items_value[i], items_size[i]);
			}
			basicGreedy(bag_size, items_value, items_size);
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

void basicGreedy(int bag_size, int items_value[], int items_size[]){
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
			}
		}
		if (space_available == true) {
			printf("%s%d%s\n", "Item ", temp_index, ": was added to the bag.");
			bag_value += temp_higher_value;
			bag_size -= temp_size;
			items_value[temp_index] = 0;
			temp_higher_value = 0;
		}
		
	}

}