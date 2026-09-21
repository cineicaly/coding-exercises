/*
 * The string "PAYPALISHIRING" is written in a zigzag pattern on a given number
of rows like this P   A   H   N A P L S I I G Y   I   R

And then read line by line: "PAHNAPLSIIGYIR"

Example 1:

Input: s = "PAYPALISHIRING", numRows = 3
Output: "PAHNAPLSIIGYIR"

Example 2:

Input: s = "PAYPALISHIRING", numRows = 4
Output: "PINALSIGYAHRPI"
Explanation:
P     I    N
A   L S  I G
Y A   H R
P     I

Example 3:

Input: s = "A", numRows = 1
Output: "A"

    1 <= s.length <= 1000
    s consists of English letters (lower-case and upper-case), ',' and '.'.
    1 <= numRows <= 1000
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN_COL 10

void print_mat(char **mat, size_t numRows, size_t numCols)
{

    for (size_t i = 0; i < numRows; i++) {
        for (size_t j = 0; j < numCols; j++) {
            printf("%c ", mat[i][j]);
        }
        printf("\n");
    }

    printf("matrix of %zu rows x %zu cols\n", numRows, numCols);
}

void read_solution(char **mat, size_t numRows, size_t numCols, char *solution)
{
    size_t idx = 0;
    for (size_t i = 0; i < numRows; i++) {
        for (size_t j = 0; j < numCols; j++) {
            if (isalpha(mat[i][j]) || mat[i][j] == ',' || mat[i][j] == '.') {
                solution[idx++] = mat[i][j];
            }
        }
    }
    solution[idx] = '\0';
}

void free_mat(char **mat, size_t numRows)
{
    for (size_t row = 0; row < numRows; row++) {
        free(mat[row]);
    }
    free(mat);
}

char *convert(char *s, int numRows)
{
    size_t n_rows = (size_t)numRows;

    if (numRows == 1)
        return strdup(s); // strdup so you can free it in main()

    size_t string_length = strlen(s);
    size_t numCols = MIN_COL;

    char **mat = malloc(numRows * sizeof(char *));
    for (size_t i = 0; i < n_rows; i++) {
        mat[i] = calloc(numCols, sizeof(char));
    }

    size_t idx = 0;
    // int BUG = 0;

    size_t last_col;

    // TODO this is a shit solution
    // surely theres a better way to solve this retard

    for (size_t col = 0; col < numCols; col++) {

        // reallocate memory if we're reaching the last column
        // and still have characters in the string
        if ((col + 1 == numCols) && (idx > numCols)) {
            // printf("col = %zu; idx = %zu\n", col, idx);

            numCols *= 2;
            for (size_t i = 0; i < n_rows; i++) {
                mat[i] = realloc(mat[i], numCols * sizeof(char));

                //memset reallocated memory because realloc doesnt initialize
                memset(mat[i] + (numCols / 2), '\0', numCols / 2);
            }
        }

        for (size_t row = 0; row < n_rows; row++) {
            if (idx < string_length) {
                if (col % (n_rows - 1ULL) == 0) {
                    mat[row][col] = s[idx++];
                    last_col = col;
                } else if (row == n_rows - 1ULL - col + last_col) { //i forgot why this works
                    mat[row][col] = s[idx++];
                } else {
                    mat[row][col] = ' ';
                }
            }
        }
    }

    char *solution = malloc(string_length + 1); //+ 1 for '\0'
    read_solution(mat, n_rows, numCols, solution);

    print_mat(mat, n_rows, numCols);
    free_mat(mat, n_rows);

    return solution;
}

int main()
{
    char *sol = convert("PAYPALISHIRINGPROSTITUTES", 3);
    printf("%s\n", sol);

    free(sol);

    return 0;
}
