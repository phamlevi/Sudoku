#include <iostream>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <string.h>
using namespace std;

//first attempt to generate sudoku grids by following these rules:
// 1 - no repeated numbers in the same columns
// 2 - no repeated numbers in the same rows
// no repeated numbers in the same 3 x 3 grids
// RESULT: unsolvable sudoku grids

int SIZE = 9;
int grid[9][9]; // global

// generate a 9 x 9 sudoku grid from 1 - 9 for every row
void generate_sudoku()
{

    int num = 0;
    for (int row = 0; row < SIZE; row++)
    {
        num = 1;
        for (int col = 0; col < SIZE; col++)
        {
            // generate and print numbers in grid
            grid[row][col] = num++;
        }
    }
}

// shuffle the whole board
void shuffle()
{
    srand(time(0));

    int i1, j1, temp;
    for (int row = 0; row < SIZE; row++)
    {

        for (int col = 0; col < SIZE; col++)
        {
            // shuffle
            i1 = rand() % SIZE;
            j1 = rand() % SIZE;

            temp = grid[row][col];
            grid[row][col] = grid[i1][j1];
            grid[i1][j1] = temp;
        }
    }
}

// check for repeating number in rows & columns and replace with 0 if it is
void replace()
{

    // replacing
    for (int i = 0; i < SIZE; i++)
    {

        for (int j = 0; j < SIZE; j++)
        {
            //check from backward
            for (int k = 8; k > j; k--)
            {

                // check if the same number is appear in the given row
                if (grid[i][j] == grid[i][k])
                {
                    //replace the number to 0
                    grid[i][k] = 0;
                }

                // check if the same number is appear in the given collumn
                if (grid[j][i] == grid[k][i])
                {
                    //replace the number to 0
                    grid[k][i] = 0;
                }
            }
        }
    }
}

// check for repeating number in 3x3 grids
void replace_grid()
{
    int count[9]; // this is use to count for repeating number
    int count_arr[9]; // this is use to check for repeating number
    int x0, y0;
    int size = sizeof(count) / sizeof(count[0]); // size for array? late use in memset() line

    // initialize count array
    for (int n = 0; n < 9; n++)
    {
        count_arr[n] = n + 1;
    }

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            x0 = (j / 3) * 3;                          // starting collumn (0, 3, 6)
            y0 = (i / 3) * 3;                          // starting row (0, 3, 6)
            memset(count, 0, size * sizeof(count[0])); // reset the array to 0

            // check if number is appear in the given square
            for (int x = 0; x < 3; x++)
            {
                for (int y = 0; y < 3; y++)
                {
                    int num_grid = grid[y0 + x][x0 + y]; // in 3 x 3 grid
                    // checking for 1 - 9 number
                    for (int n = 0; n < 9; n++)
                    {
                        // if the slot is not 0 and count the numbers that are repeating
                        if ((num_grid != 0) && (num_grid == count_arr[n]))
                        {
                            count[count_arr[n] - 1]++;       // count_arr[n] - 1 so that it can give the right position in count or else it will miss count[0]
                            if (count[count_arr[n] - 1] > 1) // if repeated
                            {
                                grid[y0 + x][x0 + y] = 0; // replace number w/ 0
                            }
                        }
                    }
                }
            }
        }
    }
}

bool possible(int row, int col, int number)
{
    
    // is the number appearing in the given row
    for (int n = 0; n < 9; n++)
    {
        if (grid[row][n] == number)
        {
            return false;
        }
    }

    // is the number appearing in the given column
    for (int n = 0; n < 9; n++)
    {
        if (grid[n][col] == number)
        {
            return false;
        }
    }
    // is the number appearing in the given grid
    int x0 = (col / 3) * 3; // starting collumn (0, 3, 6)
    int y0 = (row / 3) * 3; // starting row (0, 3, 6)
    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            if (grid[y0 + x][x0 + y] == number)
            {
                return false;
            }
        }
    }
    return true;
}

void solve()
{
    for (int row = 0; row < SIZE; row++)
    {
        for (int col = 0; col < SIZE; col++)
        {

            // check for empty spot
            if (grid[row][col] == 0)
            {
                for (int n = 1; n < 10; n++) // guess from 1 to 9
                {
                    if (possible(row, col, n))
                    {
                        grid[row][col] = n;
                        solve(); 
                        grid[row][col] = 0;
                    }
                    
                }
            }
        }
    }

}

void print_sudoku()
{
    std::cout << " -----------------------\n"; // print the on top of line 0
    for (int row = 0; row < SIZE; row++)
    {
        for (int col = 0; col < SIZE; col++)
        {
            int x0 = (col % 3) * 3; // starting collumn (0, 3, 6)
            int y0 = (row % 3) * 3; // starting row (0, 3, 6)
            // outside fences

            if (col == 0)
            {
                std::cout << "| ";
            }

            std::cout << grid[row][col] << " ";

            if (col == 2 || col == 5 || col == 8)
            {
                std::cout << "| ";
            }
        }

        if (row == 2 || row == 5 || row == 8)
            {
                std::cout << "\n -----------------------";
            }
        std::cout << endl;
    }
}

int main()
{
    std::cout << "Original Generated Board" << std::endl;
    generate_sudoku();
    print_sudoku();

    std::cout << "\n";
    std::cout << "Shuffled Board" << std::endl;
    shuffle();
    print_sudoku();

    std::cout << "\n";
    std::cout << "Replaced Repetive Values in Row/Column" << std::endl;
    replace();
    print_sudoku();

    std::cout << "\n";
    std::cout << "Replaced Repetive Values in Squares" << std::endl;
    replace_grid();
    print_sudoku();

/*
 std::cout << "\n";
    std::cout << "Solve" << std::endl;
    solve();
    print_sudoku();
    return 0;
*/
   

  
}
