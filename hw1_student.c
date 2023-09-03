#include "hw1_student.h"  // .h extenssion, not .c

// You do not need to change this print_1D function. It is included here for 
// your convenience, in case you need to call it while debugging.
void print_1D(int sz, int * arr){
	for(int k = 0; k< sz; k++){
		printf("%8d", arr[k]);
	}
	printf("\n");
}


/* dynamically allocates an array and populates it with all values from arr 
	that are strictly smaller than thresh. 
	Returns:
		- the pointer to the dynamically allocated array.
		- NULL if all elements of arr are greater or equal to thres. In this case it does not allocate any memory, and sets content of sz_res to 0.
*/
int* get_scores_below(int thresh, int sz_arr, int * arr, int* sz_res){

//check if arr is NULL
    if(arr == NULL){
        *sz_res = 0;
        return NULL;
    }

//count arr elements less than thresh
int new_array_size = 0;
for(int i=0; i<sz_arr; i++){
    if(arr[i]<thresh)
        {new_array_size++;}
}

//if no elements under thresh
if(new_array_size == 0){
     *sz_res = 0;
        return NULL;
}

//dynamically allocate an array with that much space
int* new_array = calloc(new_array_size, sizeof(int));

//fill that dynamic arr with the correct values

for(int i=0; i<new_array_size;){
    for(int j=0; j<sz_arr; j++){
        if(thresh>arr[j]){
            new_array[i] = arr[j];
            i++;
        }
    }
}
//printf("HERE IS NEW ARR");
//print_1D(new_array_size,new_array);
//printf("new arr size %d", new_array_size);

//return new array 
    *sz_res = new_array_size;
	return new_array;

}



void update_min_max(int num_rows, int num_cols, int* arr2D[], int* arr_min, int* arr_max){
	// write your code here
    int r,c, temp_min, temp_max;
    temp_min = arr2D[0][0];
    temp_max = arr2D[0][0];


    for (r = 0; r<num_rows; r++){
            for(c=0; c<num_cols; c++){
                if(temp_min > arr2D[r][c]){
                    temp_min = arr2D[r][c];
                }
                if(temp_max < arr2D[r][c]){
                    temp_max = arr2D[r][c];
                }
            }
    }
*arr_min = temp_min;
*arr_max = temp_max;

}


// improve this code to print as required in the homework
void print_2D(int num_rows, int num_cols, int* arr2D[]){
	int r,c;
	printf("\n");

    //number of rows
    for(int i=0; i<num_cols+1; i++){
        if(i==0){
            printf("        |");
        }
        else{
            printf("       %d|", i-1);
        }
    }
    	printf("\n");
    
   //the line (roof) above data set
    for(int i=0; i<num_cols*9; i++){
        if(i==0){
             printf("----------");
        }
         else{
              printf("-");
         }
    }
        printf("\n");

    //print table 
	for (r = 0; r<num_rows; r++){
        printf("%8d|", r);
		for(c=0; c<num_cols; c++){
			printf("%8d|", arr2D[r][c]);
		}
		printf("\n");
	}
}

//spaces 5 (none over 10k)
//      data2D_3_5.txt