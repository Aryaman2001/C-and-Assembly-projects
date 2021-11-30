/******************************************************************************
 * @file: latin_square_functions.c
 *
 * agarwal59
 * ARYAMAN AGARWAL
 * 9081576937
 * OTHER COMMENTS FOR THE GRADER (OPTIONAL)
 *
 * @creator: Aryaman Agarwal (agarwal59@wisc.edu)
 * @modified: 11/13/2021
 *****************************************************************************/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "latin_square_functions.h"

// Set this to 1 to enable dbgprintf statements, make sure to set it back to 0 
// before submitting!
#define DEBUG               0 
#define dbgprintf(...)      if (DEBUG) { printf(__VA_ARGS__); }
#define dbgprint_latin_square(n, LS) if (DEBUG) { Print_Latin_Square(n, LS); }

/******************************************************************************
 * Data Types and Structures
 *****************************************************************************/

// ADD ANY ADDITIONAL DATA TYPES OR STRUCTSvHERE 

/******************************************************************************
 * Globals
 *****************************************************************************/
extern void Print_Latin_Square(const size_t n, char **latin_square);

/******************************************************************************
 * Helper functions
 *****************************************************************************/

// ADD ANY HELPER FUNCTIONS YOU MIGHT WRITE HERE 

/******************************************************************************
 * Verificaiton functions
 *****************************************************************************/

/* 
 * This function takes the name of the file containing the latin square
 * and reads in the data to the the latin_square parameter.  
 *
 * There are many approaches that will work to read in the latin square data.
 * In any approach you choose, you will need to do at least the following:
 *     1) open the file 
 *     2) read in the text from the file
 *     3) figure out the dimensions of the latin square (n)
 *     4) reserve memory for the latin_square. This requires 2 steps
 *         4a) reserve an array of pointers to the rows
 *         4b) reserve an array of characters for each row
 *     5) fill in the latin_square data structure 
 *     6) close the file
 *
 * @param filename The name of the file to read in
 * @param latin_square_in A pointer to the latin square variable in main
 * @param n The value of both dimensions of the latin square (i.e. nxn)
 */
void Read_Latin_Square_File(const char *filename, 
                            char ***latin_square_in, 
                            size_t *n) {
    /* BEGIN MODIFYING CODE HERE */

    // read file, get no. of chars on 1st row, assign it to *n
    // DOUBT - max chars on each file line? used 1000 for now
    FILE *fp;
    int size = 0;
    char *buffPtr;
    buffPtr = (char *)malloc(1002*sizeof(char));
    fp = fopen(filename, "r");

    fgets(buffPtr, 1002, fp);
    for (int i = 0; (int)*(buffPtr + i) != 10; i++) {
        size++;        
    }
    //printf("size  = %d\n", size);
    *n = size;

    // allocate 2d matrix according to n
    *latin_square_in = malloc(size * sizeof(char *));

    for (int i = 0; i < *n; i++) {
        *(*(latin_square_in) + i) = malloc(size * sizeof(char *));
    }
    
    // read from file and store in data structure
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *n; j++) {
            // store each char from buff
            *(*(*latin_square_in + i) + j) = *(buffPtr + j);
        }    
        fgets(buffPtr, 1002, fp);
    }
    
    fclose(fp);
    free(buffPtr);

    /* END MODIFYING CODE HERE */
}

/* 
 * This function checks to see that exactly n symbols are used and that 
 * each symbol is used exactly n times.
 *
 * @param n The value of both dimensions of the latin square (i.e. nxn)
 * @param latin_square_in A pointer to the latin square variable in main
 * @return 1 if valid, 0 if not
 */
int Verify_Alphabet(const size_t n, char **latin_square) {
    if (latin_square == NULL) {
        printf("Verify_Alphabet - latin_square is NULL\n"); 
        return 0;
    }
    /* BEGIN MODIFYING CODE HERE */

    // Valid symbols or characters include all printable symbols. 
    // Those with ascii codes 33 (!) to 126 (~) inclusive.
    
    // declaring int array
    int *arrPtr = (int *)(malloc(94*sizeof(int)));
    for (int a = 0; a < 94; a++) {
        *(arrPtr + a) = 0;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // increment array at corresponding index
            char c = *(*(latin_square + i) + j); 
            (*(arrPtr + ((int)c - 33)))++;
        }
    }

    // traverse array and keep track of no. of characters
    int uniqueChars = 0;
    for (int i = 0; i < 94; i++) {
        //printf("%d: %d\n", i, arr[i]);
        if (*(arrPtr + i) == 0) {
            continue;
        } else if (*(arrPtr + i) == n) {
            uniqueChars++;
        } else {
            return 0;
        }
    }

    if (uniqueChars != n) {
        //printf("%d\n", uniqueChars);
        return 0;
    }
    free(arrPtr);
    /* END MODIFYING CODE HERE */
    return 1;
}

/* 
 * This function verifies that no symbol is used twice in a row or column.
 * It prints an error message alerting the user which rows or columns have 
 * duplicate symbols. This means that you will have at most n row error prints
 * and n column error prints.
 * 
 * Note: Test all rows first then test all columns.
 * 
 * Error messages have been included for you. Do not change the format out the 
 * print statements, as our grading scripts will use exact string matching. You
 * change the variable passed as the formatting argument to printf.
 * 
 * @param n The value of both dimensions of the latin square (i.e. nxn)
 * @param latin_square_in A pointer to the latin square variable in main
 * @return 1 if valid, 0 if not
 */
 int Verify_Rows_and_Columns(const size_t n, char **latin_square){
    if (latin_square == NULL) {
        printf("Verify_Rows_and_Columns - latin_square is NULL\n"); 
        return 0;
    }
    /* BEGIN MODIFYING CODE HERE */

 
    int error = 1; 
    int print = 0;
    int *arrPtr = (int *)(malloc(94*sizeof(int)));
    for (int a = 0; a < 94; a++) {
        *(arrPtr + a) = 0;
    }

    //rows
    for (int i = 0; i < n; i++) {
        // loop through each row
        print = 0;
        // clean the array before going to next row
        for (int a = 0; a < 94; a++) {
            *(arrPtr + a) = 0;
        }

        for (int j = 0; j < n; j++) {
            char c = *(*(latin_square + i) + j);

            // check arr for repeated character
            
            if ((*(arrPtr + ((int)c - 33)) == 1) && print == 0) {
                printf("Error in row %d\n", i);
                print = 1;
                error = 0;
            } else {
                // store the character
                *(arrPtr + ((int)c - 33)) = 1;
            }
        }
    }

    //columns
    for (int i = 0; i < n; i++) {
        // loop through each columnn
        print = 0;
        // clean the array before going to next row
        for (int a = 0; a < 94; a++) {
            *(arrPtr + a) = 0;
        }

        for (int j = 0; j < n; j++) {
            char c = *(*(latin_square + j) + i);

            // check arr for repeated character
            if ((*(arrPtr + ((int)c - 33)) == 1) && print == 0) {
                printf("Error in column %d\n", i);
                print = 1;
                error = 0;
            } else {
                // store the character
                *(arrPtr + ((int)c - 33)) = 1;
            }
        }
    }
    free(arrPtr);
    return error;
    
    /* END MODIFYING CODE HERE */
    return 1;
}

/* 
 * This function calls free to allow all memory used by the latin_square 
 * verification program to be reclaimed.
 *
 * Note: you will have n+1 calls to free
 *
 * @param n The value of both dimensions of the latin square (i.e. nxn)
 * @param latin_square_in A pointer to the latin square variable in main
 */ 
void Free_Memory(const size_t n, char **latin_square) {
    /* BEGIN MODIFYING CODE HERE */
    // TODO: use pointers
    for (int i = 0; i < n; i++) {
        free(*(latin_square + i));
    }
    free(latin_square);
    /* END MODIFYING CODE HERE */
}


