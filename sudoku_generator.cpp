#include <iostream>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <string.h>
using namespace std;
/*
1. Fill 3 x 3 grid diagonally
2. Fill the rest
3. Remove the number of slots wanted

Source: 
https://www.geeksforgeeks.org/program-sudoku-generator/
https://www.geeksforgeeks.org/sudoku-backtracking-7/
*/


class Sudoku
{
public:
    int SIZE;
    int grid[9][9];
    int Empty;

    Sudoku(int empty)
    {
        Empty = empty;
        SIZE = 9;
        // initiallize a empty 9 x 9 sudoku grid
        int size = sizeof(grid) / sizeof(grid[0]);
        memset(grid, 0, size * sizeof(grid[0]));

        generate_sudoku();
        print_sudoku();

        /* Display each step
        fill_diagonal();
        print_sudoku();
        solve(0, 0);
        print_sudoku();
        remove_slots();
        print_sudoku();
        */
        }

    // random generate number from 1 - 9
    int random_number()
    {
        return rand() % SIZE + 1;
    }

    // check if the guessed number is already in the 3 x 3 box
    bool repeat(int start, int num) // start at 0, 3, 6
    {
        for (int x = 0; x < 3; x++)
        {
            for (int y = 0; y < 3; y++)
            {
                if (grid[start + x][start + y] == num)
                {
                    return true;
                }
            }
        }
        return false;
    }

    // fill 3 x 3 grids diagonally
    void fill_diagonal()
    {
        // diagonal boxes
        int num;
        for (int start = 0; start < SIZE; start += 3) // 0, 3, 6
        {

            for (int i = 0; i < 3; i++)
            {

                for (int j = 0; j < 3; j++)
                {
                    // generate a random number as long as it repeated a existed number in the 3 x 3 block
                    do
                    {
                        num = random_number();
                    } while (repeat(start, num) == true);

                    //if not repeat then place the guessed number in the slot
                    grid[start + i][start + j] = num;
                }
            }
        }
    }

    // function that check if it is possible to place a number in a slot
    bool possible(int row, int col, int number)
    {

        // is the number existed in the given row
        for (int n = 0; n < 9; n++)
        {
            if (grid[row][n] == number)
            {
                return false;
            }
        }

        // is the number existed in the given column
        for (int n = 0; n < 9; n++)
        {
            if (grid[n][col] == number)
            {
                return false;
            }
        }
        // is the number existed in the given grid
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
        // if not violate any sudoku rule then return true 
        return true;
    }

    // recursive function to fill in the rest of the sudoku
    bool solve(int row, int col)
    {
        // check if the program reach the end of the grid
        if (col >= 8 && row == 8)
        {
            return true;
        }

        // if reach the last collumn, got to the next row
        if (col > 8)
        {
            col = 0; // reset to collumn 0
            row++;
        }

        // if see a number, skip 3 slots (because we already filled the diagonal 3 x 3 grid)
        if (grid[row][col] != 0)
        {
            return solve(row, col + 3);
        }

        // check for empty spots and fill them with valid number
        if (grid[row][col] == 0)
        {
            for (int n = 1; n < 10; n++) // guess from 1 to 9
            {
                if (possible(row, col, n))
                {
                    grid[row][col] = n;

                    // check for the next slot, if the guessed number is alright to be placed and move on
                    if (solve(row, col + 1))
                    {
                        return true;
                    }
                }
                // if not, reset the current number to zero and repeat 
                grid[row][col] = 0;
            }
        }
        // repeat if slot return to 0, try again until good
        return false;
    }

    //function to randomly select and zeros slots according to the instructed amount
    void remove_slots(){
        int count = 0;
        int col, row;

        // fill in zeros according to the user's amount
        while (count < Empty){
            col = rand() % SIZE;
            row = rand() % SIZE;
            //place zero to nonzero spots
            if(grid[row][col] != 0){
                grid[row][col] = 0;
                count++;
            }
            
        }
    }
    // sudoku generator
    void generate_sudoku()
    {
        fill_diagonal();

        solve(0, 0);

        remove_slots();
    }

    void print_sudoku()
    {
        std::cout << " -----------------------\n"; // print the on top of line 0
        for (int row = 0; row < SIZE; row++)
        {
            for (int col = 0; col < SIZE; col++)
            {

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
};

int main()
{
    srand(time(0));
    int empty;
    char more;

    do{
        std::cout << "==Sudoku Generator==\n\n";
        std::cout << "Enter the amount of empty slots you want for your sudoku board (EX: 20): \n";
        std::cin >> empty;

        //generate and display board
        std::cout << "Here is your board:\n\n";
        Sudoku board = Sudoku(empty);
        std::cout << "\nFinished.\n";
        
        //ask if use want to create another board
        std::cout << "Do you want to create another board? (Y/N)\n";
        std::cin >> more;
        std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
        std::cout << "\n\n";

    } while (more == 'Y' || more == 'y');
}
