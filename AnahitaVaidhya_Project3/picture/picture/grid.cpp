//
//  grid.cpp
//  picture
//
//  Created by Anahita Vaidhya on 10/29/23.
//

#include "grid.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cctype>
using namespace std;

static char grid[MAXROWS][MAXCOLS];
static int nRows;
static int nCols;
static bool isGridInitialized = false;

static void drawHorizBorder();
static void checkPos(int r, int c, string func);

void setSize(int nr, int nc)
{
    if (nr < 1  ||  nr > MAXROWS)
    {
        cerr << "setSize: invalid number of rows " << nr << endl;
        exit(1);
    }
    if (nc < 1  ||  nc > MAXCOLS)
    {
        cerr << "setSize: invalid number of columns " << nc << endl;
        exit(1);
    }
    nRows = nr;
    nCols = nc;
    isGridInitialized = true;
    clearGrid();
}

int getRows()
{
    if (!isGridInitialized)
    {
        cerr << "getRows: You must first call setSize." << endl;
        exit(1);
    }
    return nRows;
}

int getCols()
{
    if (!isGridInitialized)
    {
        cerr << "getCols: You must first call setSize." << endl;
        exit(1);
    }
    return nCols;
}

void clearGrid()
{
    if (!isGridInitialized)
    {
        cerr << "clearGrid: You must first call setSize." << endl;
        exit(1);
    }
    for (int r = 0; r < nRows; r++)
        for (int c = 0; c < nCols; c++)
            grid[r][c] = ' ';
}

void setChar(int r, int c, char ch)
{
    checkPos(r, c, "setChar");
    grid[r-1][c-1] = ch;
}

char getChar(int r, int c)
{
    checkPos(r, c, "getChar");
    return grid[r-1][c-1];
}

void draw()
{
    if (!isGridInitialized)
    {
        cerr << "draw: You must first call setSize." << endl;
        exit(1);
    }

      // Write header lines of column numbers

    if (nCols >= 10)
    {
        cout << "   ";
        for (int c = 1; c <= nCols; c++)
        {
            int t = c / 10;
            if (t == 0)
                cout << ' ';
            else
                cout << t;
        }
        cout << endl;
    }
    cout << "   ";
    for (int c = 1; c <= nCols; c++)
        cout << (c % 10);
    cout << endl;

      // Draw grid

    drawHorizBorder();
    for (int r = 1; r <= nRows; r++)
    {
        cout << setw(2) << r << '|';
        for (int c = 1; c <= nCols; c++)
        {
            char ch = grid[r-1][c-1];
            if (isprint(ch))
                cout << ch;
            else
                cout << '?';
        }
        cout << '|' << endl;
    }
    drawHorizBorder();
}

static void drawHorizBorder()
{
    cout << "  +";
    for (int c = 1; c <= nCols; c++)
        cout << '-';
    cout << '+' << endl;
}

static void checkPos(int r, int c, string func)
{
    if (!isGridInitialized)
    {
        cout << func << ": You must first call setSize." << endl;
        exit(1);
    }
    if (r < 1  ||  r > nRows  ||  c < 1  ||  c > nCols)
    {
        cout << func << ": invalid position (" << r << "," << c << ")"
                 << endl;
        exit(1);
    }
}


//Solution
/*  // Project 3 solution
 
 #include "grid.h"
 #include <iostream>
 #include <string>
 #include <cctype>
 #include <cmath>
 using namespace std;

 const int HORIZ = 0;
 const int VERT = 1;

 const int FG = 0;
 const int BG = 1;

 const int COMMAND_OK = 0;
 const int SYNTAX_ERROR = 1;
 const int BAD_ARG = 2;
 const int EXECUTION_ERROR = 3;

 int performCommands(string cmd, char& plotChar, int& mode, int& badPos);
 bool hasCorrectSyntax(string cmd, int& pos);
 bool performOneCommand(string cmd, int& pos, int& r, int& c, char& plotChar, int& mode);
 int consumeNumber(string cmd, int& pos);
 bool plotLine(int r, int c, int distance, int dir, char plotChar, int fgbg);

 int main()
 {
     for (;;)
     {
         cout << "Enter the number of grid rows and columns (max 30 each): ";
         int nRows;
         int nCols;
         cin >> nRows >> nCols;
         cin.ignore(10000, '\n');
         if (nRows >= 1  &&  nRows <= MAXROWS  &&  nCols >= 1  &&  nCols <= MAXCOLS)
         {
             setSize(nRows, nCols);
             break;
         }
         cout << "The numbers must be between 1 and 30." << endl;
     }
     char currentChar = '*';
     int currentMode = FG;
     for (;;)
     {
         cout << "Enter a command string (empty line to quit): ";
         string cmd;
         getline(cin, cmd);
         if (cmd == "")
             break;
         int position;
         int status = performCommands(cmd, currentChar, currentMode, position);
         switch (status)
         {
           case COMMAND_OK:
             draw();
             break;
           case SYNTAX_ERROR:
             cout << "Syntax error at position " << position << endl;
             break;
           case BAD_ARG:
             if (!isprint(currentChar))
                 cout << "Current charaacter is not printable" << endl;
             if (currentMode != FG  ||  currentMode != BG)
                 cout << "Current mode is " << currentMode << ", not FG or BG" << endl;
             break;
           case EXECUTION_ERROR:
             cout << "Cannot perform command at position " << position << endl;
             break;
           default:
               // It should be impossible to get here.
             cout << "performCommands returned " << status << "!" << endl;
         }
     }
 }

 int performCommands(string cmd, char& plotChar, int& mode, int& badPos)
 {
     if (!isprint(plotChar)  ||  (mode != FG  &&  mode != BG))
         return BAD_ARG;

     int pos;
     if ( ! hasCorrectSyntax(cmd, pos))
     {
         badPos = pos;
         return SYNTAX_ERROR;
     }

     int r = 1;
     int c = 1;
     pos = 0;

       // At the start of each loop iteration, pos is the position of the
       // start of the next plotting command within the command string, or
       // the end of that string.

     while (pos != cmd.size())
     {
         if (!performOneCommand(cmd, pos, r, c, plotChar, mode))
         {
             badPos = pos;
             return EXECUTION_ERROR;
         }
     }
     return COMMAND_OK;
 }

 //*****************************************************************************
 //  Determine whether cmd has correct syntax.
 //  If it does, return true (and pos will have been modified); if not, return
 //    false, and pos will be set to the position of the syntax error.
 //*****************************************************************************

 bool hasCorrectSyntax(string cmd, int& pos)
 {
     pos = 0;
     while (pos != cmd.size())
     {
         switch (toupper(cmd[pos]))
         {
           default:
             return false;
           case 'C':
             pos++;
             break;
           case 'F':
           case 'B':  // must be followd by a printable character
             pos++;
             if (pos == cmd.size()  ||  !isprint(cmd[pos]))
                 return false;
             pos++;
             break;
           case 'H':
           case 'V':
             pos++;
             if (pos == cmd.size())
                 return false;
             if (cmd[pos] == '-')  // optional minus sign
             {
                 pos++;
                 if (pos == cmd.size())
                     return false;
             }
             if (!isdigit(cmd[pos]))  // first digit
                 return false;
             pos++;
             if (pos != cmd.size()  &&  isdigit(cmd[pos]))  // optional second digit
                 pos++;
             break;
         }
     }
     return true;
 }

 //*****************************************************************************
 //  Execute the command starting at position pos of the cmd.  (r,c), plotChar,
 //  and mode are the current position, character, and mode.
 //  If successful, return true and update (r,c), plotChar, and/or mode.
 //  If the command can not be performed (because it would try to plot a point
 //    outside the grid), set pos to the position of the start of the command
 //    and return false.
 //  Precondition: cmd must be a syntactically valid command string.
 //*****************************************************************************

 bool performOneCommand(string cmd, int& pos, int& r, int& c, char& plotChar, int& mode)
 {
       // Get the character indicating the action

     char action = toupper(cmd[pos]);
     if (action == 'C')
     {
         pos++;
         clearGrid();
         r = 1;
         c = 1;
         plotChar = '*';
         mode = FG;
     }
     else if (action == 'F'  ||  action == 'B')
     {
         pos++;

           // Set the current character and the curent mode

         plotChar = cmd[pos];
         pos++;

         if (action == 'F')
             mode = FG;
         else
             mode = BG;
     }
     else if (action == 'H'  ||  action == 'V')
     {
         int commandStartPos = pos;
         pos++;

           // Get the number argument

         int distance = consumeNumber(cmd, pos);

           // Plot the line

         int dir = HORIZ;
         if (action == 'V')
             dir = VERT;
         if (!plotLine(r, c, distance, dir, plotChar, mode))
         {
             pos = commandStartPos;
             return false;
         }

           // Adjust the current position to the end of the plotted line

         if (dir == HORIZ)
             c += distance;
         else
             r += distance;
     }
     else
     {
           // It should be impossible to get here, since cmd is required to be
           // syntactically valid.
         cerr << "Plotting command action is " << action << " at position "
              << pos << "!" << endl;
         return false;  // Doesn't matter what we do here.
     }

     return true;
 }

 //*****************************************************************************
 //  Consume a number starting at position pos of the cmd.  Set pos to the
 //    position just past the number and return the integer value the numeric
 //    string represents.
 //  Precondition:  Starting at pos, there must be an optional minus sign
 //    followed by one or two digits.
 //*****************************************************************************

 int consumeNumber(string cmd, int& pos)
 {
       // Assume nonnegative to start with

     bool isNegative = false;

       // Consume optional minus sign

     if (cmd[pos] == '-')
     {
         isNegative = true;
         pos++;
     }
     int value = cmd[pos] - '0';
     pos++;

       // If there's a second digit, consume it and adjust value

     if (pos != cmd.size()  &&  isdigit(cmd[pos]))
     {
         value = 10 * value + (cmd[pos] - '0');
         pos++;
     }

       // Adjust value if there was a minus sign

     if (isNegative)
         return -value;
     else
         return value;
 }

 //*****************************************************************************
 //  plotLine
 //    Using plotChar and the mode fgbg, plot a line in direction dir
 //    (horizontal or vertical) starting at (r,c).  If distance is nonnegative,
 //    it will extend rightward or downward; if negative, upward or leftward.
 //    The other endpoint is distance units away from (r,c).  Return true if
 //    successful; otherwise, plot nothing at all and return false.
 //*****************************************************************************

 bool plotLine(int r, int c, int distance, int dir, char plotChar, int fgbg)
 {
       // Validate arguments

     if (r < 1  ||  r > getRows()  ||  c < 1  ||  c > getCols())
         return false;
     switch (dir)
     {
       case HORIZ:
         if (c+distance < 1  ||  c+distance > getCols())
             return false;
         break;
       case VERT:
         if (r+distance < 1  ||  r+distance > getRows())
             return false;
         break;
       default:
         return false;
     }
     if (fgbg != FG  &&  fgbg != BG)
         return false;
     if (!isprint(plotChar))
         return false;

       // Establish the deltas for line plotting; set (dr,dc) to
       //   ( 0,  1) to plot rightward
       //   ( 0, -1) to plot leftward
       //   ( 1,  0) to plot downward
       //   (-1,  0) to plot upward
       // and set nSteps to absolute value of distance

     int dr = 0;
     int dc = 0;
     if (dir == HORIZ)
         dc = 1;
     else
         dr = 1;
     int nSteps = distance;
     if (distance < 0)
     {
         dr = -dr;
         dc = -dc;
         nSteps = -nSteps;
     }

       // Plot the line

     for (;;)
     {
           // Plot character if foreground, or if background replacing space
         if (fgbg == FG  ||  getChar(r, c) == ' ')
             setChar(r, c, plotChar);
         if (nSteps == 0)
             break;
         nSteps--;
         r += dr;
         c += dc;
     }
     return true;
 }*/

//Test Cases
/*You had to implement the functions with the specified signatures. In particular, you could not change the number or types of the parameters (e.g., changing int to int&).

There were 54 test cases, worth 85 points in all:

performCommands, error cases

Test #    Points    Command    plotChar    mode    Return
value    Resulting
bad position
1    2    HCCC    *    0 (FG)    1    1
2    2    H-CCC    *    0 (FG)    1    2
3    2    H123    *    0 (FG)    1    3
4    2    F\tC    *    0 (FG)    1    1
5    2    @CCC    *    0 (FG)    1    0
6    2    CCCV    *    0 (FG)    1    4
7    2    CCCV-    *    0 (FG)    1    5
8    2    CCCB    *    0 (FG)    1    4
18    2    H4H4H4H4    *    0 (FG)    3    6
19    2    V10V02    *    0 (FG)    3    3
20    2    H03H-04    *    0 (FG)    3    3
21    2    V3V-4    *    0 (FG)    3    2
22    1    H1    \t    1 (BG)    2    unchanged
23    1    B\t    \t    1 (BG)    2    unchanged
24    1    H1    *    7    2    unchanged
25    1    HX    \t    7    2    unchanged
Notes

In the above cases, performCommands was called for a grid of 12 rows and 16 columns.

For test 4, note that isprint('\t') is false.

It was your choice whether test cases 3 and 18 through 21 plot anything. The other test cases above must not plot any nonblank characters.

Test cases 22 through 25 must not change plotChar and mode.

performCommands, valid cases

Test #    Points    Command    plotChar    mode    Return
value    Resulting
bad position    Resulting
plotChar    Resulting
mode    Points plotted
9    2    FBCBFH1    *    0 (FG)    0    unchanged    *    0 (FG)    F at (1,1), (1,2)
10    2    H3V2    *    0 (FG)    0    unchanged    *    0 (FG)    * at (1,1), (1,2), (1,3), (1,4), (2,4), (3,4)
11    2    H3V2CV1    *    0 (FG)    0    unchanged    *    0 (FG)    * at (1,1), (2,1)
12    2    H3F%V2    *    0 (FG)    0    unchanged    *    0 (FG)    * at (1,1), (1,2), (1,3);
% at (1,4), (2,4), (3,4)
13    2    V3B%H2    *    0 (FG)    0    unchanged    *    0 (FG)    * at (1,1), (2,1), (3,1), (4,1);
% at (4,2), (4,3)
14    2    H3F%V2B$H1    *    0 (FG)    0    unchanged    *    0 (FG)    * at (1,1), (1,2), (1,3);
% at (1,4), (2,4), (3,4);
$ at (3,5)
15    2    H3B%V2CH1    *    0 (FG)    0    unchanged    *    0 (FG)    * at (1,1), (1,2)
16    2    H1F%    #    1 (BG)    0    unchanged    %    0 (FG)    # at (1,1), (1,2)
17    2    H1    #    1 (BG)    0    unchanged    #    1 (BG)    # at (1,1), (1,2)
26    1    H1    *    0 (FG)    0    unchanged    *    0 (FG)    * at (1,1), (1,2)
27    1    F#    *    0 (FG)    0    unchanged    #    0 (FG)    none
28    1    B$    *    0 (FG)    0    unchanged    $    1 (BG)    none
29    1    H0    *    0 (FG)    0    unchanged    *    0 (FG)    * at (1,1)
30    1    v02    *    0 (FG)    0    unchanged    *    0 (FG)    * at (1,1), (2,1), (3,1)
31    1    F (blank after the F)    *    0 (FG)    0    unchanged    (blank)    0 (FG)    none
32    1    C    #    1 (BG)    0    unchanged    *    0 (FG)    none
33    1    H1C    *    0 (FG)    0    unchanged    *    0 (FG)    none
Notes

In the above cases, performCommands was called for a grid of 12 rows and 16 columns.

plotLine

Test #    Points    Row    Column    Distance    Direction    Plot char    mode    Return
value    Points plotted
34    1    0    1    1    1 (VERT)    #    0 (FG)    false    none
35    1    -1    1    1    1 (VERT)    #    0 (FG)    false    none
36    1    1    0    1    0 (HORIZ)    #    0 (FG)    false    none
37    1    1    -1    1    1 (HORIZ)    #    0 (FG)    false    none
38    1    15    1    -1    1 (VERT)    #    0 (FG)    true    # at (15,1), (14,1)
39    1    16    1    -1    1 (VERT)    #    0 (FG)    false    none
40    1    1    22    -1    0 (HORIZ)    #    0 (FG)    true    # at (1,22), (1,21)
41    1    1    23    -1    0 (HORIZ)    #    0 (FG)    false    none
42    1    1    1    1    2    #    0 (FG)    false    none
43    1    1    1    1    0 (HORIZ)    \t    0 (FG)    false    none
44    1    1    1    1    0 (HORIZ)    #    2    false    none
45    2    10    15    2    0 (HORIZ)    #    0 (FG)    true    # at (10,15), (10,16), (10,17)
46    2    10    15    -2    0 (HORIZ)    $    0 (FG)    true    $ at (10,15), (10,14), (10,13)
47    2    10    15    2    1 (VERT)    #    0 (FG)    true    # at (10,15), (11,15), (12,15)
48    2    10    15    -2    1 (VERT)    $    0 (FG)    true    $ at (10,15), (9,15), (8,15)
49    2    10    15    0    0 (HORIZ)    #    0 (FG)    true    # at (10,15)
50    2    10    15    0    1 (VERT)    #    0 (FG)    true    # at (10,15)
51    2    10    15    1    1 (VERT)    A    0 (FG)    true    A at (10,15), (11,15)
52    2    10    15    2    0 (HORIZ)    (blank)    0 (FG)    true    none (see note)
53    2    10    15    2    0 (HORIZ)    (blank)    1 (BG)    true    none
54    2    10    15    2    0 (HORIZ)    (blank)    1 (BG)    true    X at (10,16) (see note)
Notes

In the above cases, plotLine was called for a grid of 15 rows and 22 columns.

For test 43, note that isprint('\t') is false.

For tests 52 and 54, an X was placed at (10,16) before plotLine was called.*/
