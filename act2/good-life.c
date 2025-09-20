/// http://www.dreamincode.net/forums/topic/55572-conways-game-of-life/
/// downloaded by copy-paste on 8/19/2015 and modified to use an infinite loop
/// and have different Rule functions.
///
/// This code needs serious work in these areas:
/// <ol>
/// <li>  syntax: there are a number of warnings that cause errors.
/// </li>
/// <li>  semantics: the game algorithm implementation is incorrect.
/// </li>
/// <li>  design: the implementation needs function and value refactoring.
/// </li>
/// <li>  style: formatting is poor; the mix of TAB and spaces indentation
/// needs correction, and spacing between tokens is inconsistent.
/// The course style puts the '{' at the end of the function header, not
/// on a line of its own. You should make the formatting consistent.
/// </li>
/// <li>  documentation: documentation is non-existent except for this block.
/// </li>
/// </ol>
///

/**
CSCI243 - hw3
File: good-life.c
Description: Homework 3 file
@author: Olivier Couthaud
*/

#include <stdio.h>
#include <stdlib.h>

#define GRID_SIZE 20  // fix 15: replaced magic number with constant
#define MAX_GENERATIONS 50  // fix 15: replaced magic number with constant

/**
 * Displays welcome header for the game
 */
void header(void)
{
      printf("\n\t..Welcome to the Game of life..\n");
}

/* fix 12: commented out old separate rule functions (replaced with apply_rules
void survivalRule(char life[][20]) // fix 4: removed unused parameters
{
      int row, col;
      for(row = 1; row<19; row++)
      {
         for(col = 1; col<19; col++)
         {
            if(life[row][col]== '*') // fix 3: removed & and changed string to char comparison
            {
               int neighbors = 0; // fix 10: the neighbors variable is never reset to 0 for each cell
               if(life[row - 1][col - 1] == '*')
                  ++neighbors;
               if(life[row - 1][col] == '*')
                  ++neighbors;
               if(life[row - 1][col + 1] == '*')
                  ++neighbors;
               if(life[row][col - 1] == '*')
                  ++neighbors;
               if(life[row][col + 1] == '*')
                  ++neighbors;
               if(life[row + 1][col - 1] == '*')
                  ++neighbors;
               if(life[row + 1][col] == '*')
                  ++neighbors;
               if(life[row + 1][col + 1] == '*')
                  ++neighbors;
               if(neighbors == 2 || neighbors == 3)
               {
                  life[row][col] = '*'; // fix 2: changed == to = for assignment
               }
               else
               {
                   life[row][col] = ' '; // fix 11: added death condition for cells with wrong neighbor count
               }
            }
         }
      }
      return;
}

void birthRule(char life[][20]) // fix 4: removed unused parameters
{
      int row, col;
      int neighbors = 0;
      for(row = 1; row<19; row++)
      {
         for(col = 1; col<19; col++)
         {
            if(life[row][col]== ' ') // fix 3: removed & and changed string to char comparison
            {
               if(life[row - 1][col - 1] == '*')
                  neighbors++;
               if(life[row - 1][col] == '*')
                  neighbors++;
               if(life[row - 1][col + 1] == '*')
                  neighbors++;
               if(life[row][col - 1] == '*')
                  neighbors++;
               if(life[row][col + 1] == '*')
                  neighbors++;
               if(life[row + 1][col - 1] == '*')
                  neighbors++;
               if(life[row + 1][col] == '*')
                  neighbors++;
               if(life[row + 1][col + 1] == '*')
                  neighbors++;
               if(neighbors == 3)
               {
                   life[row][col] = '*'; // fix 2: changed == to = for assignment
               }
            }
         }
      }
      return;
}
*/

/**
 * Applies Conway's Game of Life rules to update the grid
 * @param size The dimensions of the square grid
 * @param life The grid containing current cell states
 */
void apply_rules(int size, char life[][size]) // fix 12: merged rules and added grid copy to prevent concurrent modification // fix 14: changed camelCase to snake_case // fix 16: proper C array parameter syntax
{
    char copy[GRID_SIZE][GRID_SIZE];
    int row, col;

    for(row = 0; row < GRID_SIZE; row++) {
        for(col = 0; col < GRID_SIZE; col++) {
            copy[row][col] = life[row][col];
        }
    }

    for(row = 0; row < GRID_SIZE; row++) { // fix 13: process all cells including edges
        for(col = 0; col < GRID_SIZE; col++) { // fix 13: process all cells including edges
            int neighbors = 0;

            /*
            if(copy[row - 1][col - 1] == '*') neighbors++;
            if(copy[row - 1][col] == '*') neighbors++;
            if(copy[row - 1][col + 1] == '*') neighbors++;
            if(copy[row][col - 1] == '*') neighbors++;
            if(copy[row][col + 1] == '*') neighbors++;
            if(copy[row + 1][col - 1] == '*') neighbors++;
            if(copy[row + 1][col] == '*') neighbors++;
            if(copy[row + 1][col + 1] == '*') neighbors++;
            */
            int r, c;
            for(int dr = -1; dr <= 1; dr++) {
                for(int dc = -1; dc <= 1; dc++) {
                    if(dr == 0 && dc == 0) continue;
                    r = (row + dr + GRID_SIZE) % GRID_SIZE;  // fix 13: wraparound for rows
                    c = (col + dc + GRID_SIZE) % GRID_SIZE;  // fix 13: wraparound for columns
                    if(copy[r][c] == '*') {
                        neighbors++;
                    }
                }
            }
            // rules
            if(copy[row][col] == '*') {
                // survival
                if(neighbors == 2 || neighbors == 3) {
                    life[row][col] = '*';
                } else {
                    life[row][col] = ' '; // death
                }
            } else {
                // birth
                if(neighbors == 3) {
                    life[row][col] = '*';
                } else {
                    life[row][col] = ' ';
                }
            }
        }
    }
}

/**
 * Main function: implements Conway's Game of Life
 * @param argc Number of command line arguments
 * @param args Array of command line arguments
 * @return 0 on success, 1 on error
 */
int main(int argc, char *args[])
{
      char life[GRID_SIZE][GRID_SIZE];
      int orgs;
      int i, row, col;
      int count = 0;
//       int x = 19; // fix 8: removed unused variables x and y
//       int y = 19;
      // fix 4.2: removed unused variables
      if (argc != 2) { return 1; }
      header();

      // convert command line argument to an int
      orgs = strtol( args[1], NULL, 10 );

      srand( 31 );

      for(i = 0; i<orgs; i++)
      {
          row = rand();
          row %= GRID_SIZE;
          col = rand();
          col %= GRID_SIZE;
          if (life[row][col] != '*') {
              life[row][col] = '*'; // fix 2: changed == to = for assignment
          } else {
              i--;
          } // fix 9: added collision detection to avoid overwriting organisms
      }

      for(row = 0; row<GRID_SIZE; row++)
      {
          for(col = 0; col<GRID_SIZE; col++)
          {
              if(life[row][col] != '*')
                  life[row][col] = ' '; // fix 2: changed == to = for assignment
          }
      }

      for(row = 0; row<GRID_SIZE; row++)
      {
          for(col = 0; col<GRID_SIZE; col++)
          {
              printf("%c", life[row][col]); // fix 1: changed %s to %c for character output
          }
          puts(" ");
      }

      while ( count < MAX_GENERATIONS ) { // fix 5: stop after 50 generations
          // birthRule(life); // fix 7: removed arguments to match function signature
          // survivalRule(life); // fix 7: removed arguments to match function signature
          printf("\ngeneration: %d\n", count);
          for(row = 0; row<GRID_SIZE; row++)
          {
              for(col = 0; col<GRID_SIZE; col++)
              {
                  printf("%c", life[row][col]); // fix 1: changed %s to %c for character output
              }
              puts(" ");
          }
          apply_rules(GRID_SIZE, life); // fix 12: use merged function with grid copy // fix 16: pass size parameter
          count++;
      }

      return 0;
}

