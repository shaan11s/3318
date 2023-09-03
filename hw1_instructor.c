/*
compile:
gcc -g hw1_instructor.c hw1_student.c
run with valgrind:
valgrind --leak-check=full ./a.out
*/

#include "hw1_student.h"  // .h extenssion, not .c

// Functions that work with a dynamically allocated 2D array .
int** make_array_from_file(int* nrp, int* ncp);
void populate_array(int num_rows, int num_cols, int* arr2D[], FILE *fp);
void free_array(int num_rows, int* arr2D[]);

// function that reads and creates a 2D array from a file, 
// and calls the student functions for 2D arrays
void test_2D_array();

// functions that work with a 1D array to test the student function
void test_scores();
int test_scores_1(int thresh, int sz_in, int* arr_in, int sz_e_res, int* e_res);



int main(){	
	test_scores();
	test_2D_array();
}

// runs 4 hardcoded tests and prints failed or passed for each of them
void test_scores(){    
	printf("\n---------- test_scores - started -----------\n");
	int arr1[9] = {92, 57, 100, 95, 38, 10, 85, 91, 20};
	int res1[4] = {57, 38, 10, 20};  // expected array returned by get_scores_below(60,..., arr1 ) 
	
	int arr2[5] = {22, 45, 30, 49, 38};
	int res2[5] = {22, 45, 30, 49, 38};    // expected array returned by get_scores_below(50 , ..., arr2 ) 
		
	int arr3[5] = {3, 0, 3, 1, 3};
	int res3[2] = {0, 1};              // expected array returned by get_scores_below(2, ... , arr3 ) 

	int total_tests = 4;
	int passed_ct = 0;
	passed_ct += test_scores_1(60, 9, arr1, 4, res1);
	passed_ct += test_scores_1(50, 5, arr2, 5, res2);
	passed_ct += test_scores_1(22, 5, arr2, 0, NULL);  // here the expected result array is empty (there is no score under threshold 22)
	passed_ct += test_scores_1(2,  5, arr3, 2, res3);
	
	printf ("\nPassed tests:  %d out of %d\n", passed_ct, total_tests);
	printf("\n---------- test_scores - finished -----------\n");
}


/* runs one test where arr_in is the input array, and it has size sz_in and
   e_res is the expected result array and sz_e_res is the size of the expected result array
   It calls get_fail_grades() on arr_in and compares the content of the array returned by it
   with the content of the array e_res.
   It will free the dynamic array returned by get_fail_grades().
   Returns:
   1 - if passed given test
   0 - if falied given test
*/
int test_scores_1(int thresh, int sz_in, int* arr_in, int sz_e_res, int* e_res){
	int k, passed=0, size_res = -1;
	int * student_res;	// will store pointer to result array
	
	// call student function
	student_res = get_scores_below(thresh, sz_in, arr_in, &size_res);
	
	// print array retruned by student function
	print_1D(size_res, student_res);
	
	// check that every item returned matches what is expected
	if (size_res == sz_e_res) {
		passed = 1;
		for(k = 0; k<size_res; k++){
			if (student_res[k] != e_res[k] ) {  // missmatch found
				passed = 0;     // mark that this test failed
			}
		}
	}
	else {
		passed = 0; // test failed because student result did not find as many values as expected
	}
	
	if (passed==1) {  // this test passed
		printf("get_scores_below passed the sample test. \n");
	}
	else {            // this test failed
		printf("get_scores_below *** failed *** the sample test.\n");
	}	
		
	free (student_res);
	
	return passed;
}




/*
============== 2D array functions ===================
*/

void test_2D_array(){
	printf("\n---------- test_2D_array - started -----------\n");
	int nr = 0, nc = 0, mn = -9999, mx = -9999;
	
	int** my_arr = make_array_from_file(&nr, &nc);  // my_arr = 1b1b;
	
	if (my_arr == NULL) return;
	
	print_2D(nr,nc, my_arr);   // call student function
	
	update_min_max(nr,nc, my_arr, &mn, &mx);   // call student function
	printf("min value: %d, max value: %d\n", mn, mx);
	
	free_array(nr, my_arr);	
	printf("\n---------- test_2D_array - finished -----------\n");
}


int** make_array_from_file(int* nrp, int* ncp){
	char fname[101]; // max length for file name? 99 + \0
	int num_rows, num_cols, r;
	FILE *fp;

	printf("Enter the filename: ");
	scanf("%s", fname);
	fp =fopen(fname, "r");
	if (fp == NULL){
		printf("File could not be opened.\n");
		return NULL;
	}
	fscanf(fp, "%d %d", &num_rows, &num_cols);	
	
	//int* arr2[num_rows];
	int** arr2;
	arr2 = calloc(num_rows, sizeof(int*) );	
	
	for(r = 0; r<num_rows; r++){
		arr2[r] = calloc( num_cols, sizeof(int) );
	}

	populate_array(num_rows, num_cols, arr2, fp);
	//print_array(num_rows, num_cols, arr2);
	
	(*nrp) = num_rows;
	(*ncp) = num_cols;
	
	fclose(fp);
	
	return arr2;
}

void free_array(int num_rows, int* arr2D[]){
	for(int r = 0; r<num_rows; r++){
		free( arr2D[r] );
	}
	free( arr2D );
}

void populate_array(int num_rows, int num_cols, int* arr2D[], FILE *fp){
	for (int r = 0; r<num_rows; r++){
		for(int c=0; c<num_cols; c++){
			fscanf(fp, "%d", &arr2D[r][c]);
		}
	}	
}
