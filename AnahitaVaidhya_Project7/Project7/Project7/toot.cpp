// gas.cpp

// Portions you are to complete are marked with a TODO: comment.
// We've provided some incorrect return statements (so indicated) just
// to allow this skeleton program to compile and run, albeit incorrectly.
// The first thing you probably want to do is implement the trivial
// functions (marked TRIVIAL).  Then get City::display going.  That gives
// you more flexibility in the order you tackle the rest of the functionality.
// As you finish implementing each TODO: item, remove its TODO: comment.

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
using namespace std;

///////////////////////////////////////////////////////////////////////////
// Manifest constants
///////////////////////////////////////////////////////////////////////////

const int MAXROWS = 20;               // max number of rows in a city
const int MAXCOLS = 30;               // max number of columns in a city
const int MAXTOOTERS = 125;           // max number of Tooters allowed

const int UP      = 0;
const int DOWN    = 1;
const int LEFT    = 2;
const int RIGHT   = 3;
const int NUMDIRS = 4;

///////////////////////////////////////////////////////////////////////////
// Type definitions
///////////////////////////////////////////////////////////////////////////

class City;  // This is needed to let the compiler know that City is a
             // type name, since it's mentioned in the Tooter declaration.

class Tooter
{
  public:
        // Constructor
    Tooter(City* cp, int r, int c);

        // Accessors
    int  row() const;
    int  col() const;

        // Mutators
    void move();

  private:
    City* m_city;
    int   m_row;
    int   m_col;
};

class Player
{
  public:
        // Constructor
    Player(City *cp, int r, int c);

        // Accessors
    int  row() const;
    int  col() const;
    int  age() const;
    int  health() const;
    bool isPassedOut() const;

        // Mutators
    void  preach();
    void  move(int dir);
    void  getGassed();

  private:
    City* m_city;
    Tooter* m_tooter;
    int   m_row;
    int   m_col;
    int   m_age;
    int   m_health;
      // DONE TODO: You'll probably find that a player object needs an additional
      //       data member to support your implementation of the behavior
      //       affected by the player's being blasted with gas.
};

class City
{
  public:
        // Constructor/destructor
    City(int nRows, int nCols);
    ~City();

        // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    bool    isPlayerAt(int r, int c) const;
    int     tooterCount() const;
    int     nTootersAt(int r, int c) const;
    bool    determineNewPosition(int& r, int& c, int dir) const;
    void    display() const;

        // Mutators
    bool addTooter(int r, int c);
    bool addPlayer(int r, int c);
    void preachToTootersAroundPlayer();
    void moveTooters();

  private:
    int     m_rows;
    int     m_cols;
    Player* m_player;
    Tooter* m_tooters[MAXTOOTERS];
    int     m_nTooters;
    int     count;

      // Helper functions
    bool isInBounds(int r, int c) const;
};

class Game
{
  public:
        // Constructor/destructor
    Game(int rows, int cols, int nTooters);
    ~Game();

        // Mutators
    void play();

  private:
    City* m_city;
};

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function declarations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char dir);
int randInt(int min, int max);
void clearScreen();

///////////////////////////////////////////////////////////////////////////
//  Tooter implementation
///////////////////////////////////////////////////////////////////////////

Tooter::Tooter(City* cp, int r, int c)
{
    if (cp == nullptr)
    {
        cout << "***** A Tooter must be created in some City!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > cp->rows()  ||  c < 1  ||  c > cp->cols())
    {
        cout << "***** Tooter created with invalid coordinates (" << r << ","
             << c << ")!" << endl;
        exit(1);
    }
    m_city = cp;
    m_row = r;
    m_col = c;
}

int Tooter::row() const
{
    return m_row;
}

int Tooter::col() const
{
    // DONE TODO: TRIVIAL:  Return the column the Tooter is at.
    // Delete the following line and replace it with the correct code.
    return m_col;  // This implementation compiles, but is incorrect.
}

void Tooter::move()
{
      // Attempt to move in a random direction; if it can't move, don't move.
      // If the player is there, don't move.
    int dir = randInt(0, NUMDIRS-1);  // dir is now UP, DOWN, LEFT, or RIGHT
                                    //up= 0, down = 1, left = 2, right = 3
    int tempRow = m_row;
    int tempCol = m_col;
    
    //figure out if this is ok or the other way I had it
    if (m_city->determineNewPosition(m_row, m_col, dir) && m_city->isPlayerAt(m_row, m_col)){
        m_row = tempRow;
        m_col = tempCol;
    }
    
    // I think DONE TODO:  Move in the appropriate direction if allowed
}

///////////////////////////////////////////////////////////////////////////
//  Player implementations
///////////////////////////////////////////////////////////////////////////

Player::Player(City* cp, int r, int c)
{
    if (cp == nullptr)
    {
        cout << "***** The player must be created in some City!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > cp->rows()  ||  c < 1  ||  c > cp->cols())
    {
        cout << "**** Player created with invalid coordinates (" << r
             << "," << c << ")!" << endl;
        exit(1);
    }
    m_city = cp;
    m_row = r;
    m_col = c;
    m_age = 0;
    m_health = 12;
      // DONE TODO: You might or might not put something here.
}

int Player::row() const
{
    // DONE TODO: TRIVIAL:  Return the row the player is at.
    // Delete the following line and replace it with the correct code.
    return m_row;  // This implementation compiles, but is incorrect.
}

int Player::col() const
{
    // DONE TODO: TRIVIAL:  Return the column the player is at.
    // Delete the following line and replace it with the correct code.
    return m_col;  // This implementation compiles, but is incorrect.
}

int Player::age() const
{
    // DONE TODO: TRIVIAL:  Return the player's age.
    // Delete the following line and replace it with the correct code.
    return m_age;  // This implementation compiles, but is incorrect.
}

int Player::health() const
{
    // DONE TODO: TRIVIAL:  Return the player's health status.
    // Delete the following line and replace it with the correct code.
    return m_health;  // This implementation compiles, but is incorrect.
}

  
//double check if this is correct
bool Player::isPassedOut() const
{
    // DONE TODO: TRIVIAL:  Return whether the player is passed out.
    // Delete the following line and replace it with the correct code.
    return (m_health <= 0);  // This implementation compiles, but is incorrect.
}

void Player::preach()
{
    m_age++;
    m_city->preachToTootersAroundPlayer();
}

void Player::move(int dir)
{
    m_age++;
    //Move one step up, down, left, or right to an empty position (i.e., one not occupied by a Tooter). If the player attempts to move into the wall of the city (e.g., down, when on the bottom row) or to a position occupied by a Tooter, the player does not move.
    
    int tempRow = m_row;
    int tempCol = m_col;
    
    if (m_city->determineNewPosition(m_row, m_col, dir) && m_city->nTootersAt(m_row, m_col) > 0){
        m_row = tempRow;
        m_col = tempCol;
    }
      // I think DONE TODO:  If there is a grid position in the indicated direction that is
      //        adjacent to the player and vacant, move the player there;
      //        otherwise, don't move.
}

//double check if this is correct
void Player::getGassed()
{
    // DONE TODO: TRIVIAL
    m_health--;
}

///////////////////////////////////////////////////////////////////////////
//  City implementations
///////////////////////////////////////////////////////////////////////////

City::City(int nRows, int nCols)
{
    if (nRows <= 0  ||  nCols <= 0  ||  nRows > MAXROWS  ||  nCols > MAXCOLS)
    {
        cout << "***** City created with invalid size " << nRows << " by "
             << nCols << "!" << endl;
        exit(1);
    }
    m_rows = nRows;
    m_cols = nCols;
    m_player = nullptr;
    m_nTooters = 0;
}

//double check if this is correct
//where thread 1 test case comes from
//last test case maybe
City::~City()
{
    // DONE TODO:  Delete the player and all remaining dynamically allocated Tooters.
    for(int i = 0; i < m_nTooters; i++){
        delete m_tooters[i];
    }
    delete m_player;
}

int City::rows() const
{
    // DONE TODO: TRIVIAL:  Return the number of rows in the city.
    // Delete the following line and replace it with the correct code.
    return m_rows;  // This implementation compiles, but is incorrect.
}

int City::cols() const
{
    // DONE TODO: TRIVIAL:  Return the number of columns in the city.
    // Delete the following line and replace it with the correct code.
    return m_cols;  // This implementation compiles, but is incorrect.
}

Player* City::player() const
{
    return m_player;
}

bool City::isPlayerAt(int r, int c) const
{
    // DONE TODO:  Return true if the player is at row r, column c, otherwise false.
    // Delete the following line and replace it with the correct code.
    if(m_player->row() == r && m_player->col() == c){
        return true;
    } else {
        return false;
    }// This implementation compiles, but is incorrect.
}

int City::tooterCount() const
{
    return m_nTooters;
}

int City::nTootersAt(int r, int c) const
{
    // I think DONE TODO:  Return the number of Tooters at row r, column c.
    // Delete the following line and replace it with the correct code.
    int count = 0;
    for(int i = 0; i < m_nTooters; i++){
        if(m_tooters[i]->row() == r && m_tooters[i]->col() == c){
            count++;
        }
    }
    return count;  // This implementation compiles, but is incorrect.
}

bool City::determineNewPosition(int& r, int& c, int dir) const
{
      // I think DONE TODO:  If a move from row r, column c, one step in direction dir
      //        would go off the edge of the city, leave r and c unchanged and
      //        return false.  Otherwise, set r or c so that row r, column c,
      //        is now the new position resulting from the proposed move, and
      //        return true.
    
    //use the isInBounds
    switch (dir)
    {
      case UP:
            // I think DONE TODO:  Implement the behavior if dir is UP.
            if(isInBounds((r-1), c)){
                r -= 1;
                break;
            } else {
                return false;
            }
      case DOWN:
            if(isInBounds((r+1), c)){
                r += 1;
                break;
            } else {
                return false;
            }
      case LEFT:
            if(isInBounds(r, (c-1))){
                c -= 1;
                break;
            } else {
                return false;
            }
      case RIGHT:
        // I think DONE TODO:  Implement the other directions.
            if(isInBounds(r, (c+1))){
                c += 1;
                break;
            } else {
                return false;
            }
      default:
        return false;
    }
    return true;
}

void City::display() const
{
      // Position (row,col) in the city coordinate system is represented in
      // the array element grid[row-1][col-1]
    char grid[MAXROWS][MAXCOLS];
    int r, c;
    
        // Fill the grid with dots
    for (r = 0; r < rows(); r++)
        for (c = 0; c < cols(); c++)
            grid[r][c] = '.';

        // Indicate each Tooter's position
    // I think DONE TODO:  If one Tooter is at some grid point, set the char to 'T'.
    //        If it's 2 though 8, set it to '2' through '8'.
    //        For 9 or more, set it to '9'.
    
    for(int i = 0; i < m_nTooters; i++){
        r = m_tooters[i]->row() - 1;
        c = m_tooters[i]->col() - 1;
        if(grid[r][c] == '.'){
            grid[r][c] = 'T';
        } else if(grid[r][c] == 'T'){
            grid[r][c] = '2';
        } else if(grid[r][c] <= '8'){
            grid[r][c] = grid[r][c] + 1;
        }
    }
    
        // Indicate player's position
    if (m_player != nullptr)
    {
          // Set the char to '@', unless there's also a Tooter there
          // (which should never happen), in which case set it to '*'.
        char& gridChar = grid[m_player->row()-1][m_player->col()-1];
        if (gridChar == '.')
            gridChar = '@';
        else
            gridChar = '*';
    }

        // Draw the grid
    clearScreen();
    for (r = 0; r < rows(); r++)
    {
        for (c = 0; c < cols(); c++)
            cout << grid[r][c];
        cout << endl;
    }
    cout << endl;

        // Write message, Tooter, and player info
    cout << "There are " << m_nTooters << " unconverted Tooters remaining." << endl;
    if (m_player == nullptr)
        cout << "There is no player." << endl;
    else
    {
        if (m_player->age() > 0)
            cout << "The player has lasted " << m_player->age() << " steps." << endl;
        if (m_player->isPassedOut())
            cout << "The player has passed out." << endl;
        else
            cout << "The player's health level is " << m_player->health() << endl;
    }
}

bool City::addTooter(int r, int c)
{
    if (! isInBounds(r, c))
        return false;

      // Don't add a Tooter on a spot with a player
    if (m_player != nullptr  &&  m_player->row() == r  &&  m_player->col() == c)
        return false;
    
      // If there are MAXTOOTERS unconverted Tooters, return false. (don't need to add anymore)
    if(m_nTooters == 125){
        return false;
    }
      // Otherwise, dynamically allocate a new Tooter at coordinates (r,c).
      // Save the pointer to the newly allocated Tooter and return true.
    
    m_tooters[m_nTooters] = new Tooter(this, r, c);
    m_nTooters++; 

      // Your function must work as specified in the preceding paragraph even
      // in this scenario (which won't occur in this game):  MAXTOOTERS
      // Tooters are added, then some are converted and removed from the city,
      // then more are added.
        // delete m_tooters[];

      // TODO:  Implement this.
    return true;  // This implementation compiles, but is incorrect.
}

bool City::addPlayer(int r, int c)
{
    if (! isInBounds(r, c))
        return false;

      // Don't add a player if one already exists
    if (m_player != nullptr)
        return false;

      // Don't add a player on a spot with a Tooter
    if (nTootersAt(r, c) > 0)
        return false;

      // Dynamically allocate a new Player and add it to the city
    m_player = new Player(this, r, c);
    return true;
}

void City::preachToTootersAroundPlayer()
{
    for(int i = 0; i < m_nTooters; i++){
        if((m_tooters[i]->row() == m_player->row()-1 && m_tooters[i]->col() == m_player->col()) || (m_tooters[i]->row() == m_player->row()+1 && m_tooters[i]->col() == m_player->col()) || (m_tooters[i]->row() == m_player->row() && m_tooters[i]->col() == m_player->col()-1) || (m_tooters[i]->row() == m_player->row() && m_tooters[i]->col() == m_player->col()+1) || (m_tooters[i]->row() == m_player->row()-1 && m_tooters[i]->col() == m_player->col()-1) || (m_tooters[i]->row() == m_player->row()-1 && m_tooters[i]->col() == m_player->col()+1) || (m_tooters[i]->row() == m_player->row()+1 && m_tooters[i]->col() == m_player->col()-1) || (m_tooters[i]->row() == m_player->row()+1 && m_tooters[i]->col() == m_player->col()+1)){
            
            if((randInt(0, 2) < 2)){
                delete m_tooters[i];
                for(int j = i; j < m_nTooters-1; j++){
                    m_tooters[j] = m_tooters[j+1];
                }
                m_nTooters--;
                i--;
            }
        }
    }
      // i think DONE TODO:  Implement this.
}

void City::moveTooters()
{
    for (int k = 0; k < m_nTooters; k++)
    {
        m_tooters[k]->move();
        if(isPlayerAt(m_tooters[k]->row()-1, m_tooters[k]->col()) || isPlayerAt(m_tooters[k]->row()+1, m_tooters[k]->col()) || isPlayerAt(m_tooters[k]->row(), m_tooters[k]->col()-1) || isPlayerAt(m_tooters[k]->row(), m_tooters[k]->col()+1)){
            
            m_player->getGassed();
        }
      // TODO:  Have the k-th Tooter in the city make one move.
      //        If that move results in that Tooter being orthogonally
     //        adjacent to the player, the player suffers a gas blast.
        
    }
}

bool City::isInBounds(int r, int c) const
{
    return (r >= 1  &&  r <= m_rows  &&  c >= 1  &&  c <= m_cols);
}

///////////////////////////////////////////////////////////////////////////
//  Game implementations
///////////////////////////////////////////////////////////////////////////

Game::Game(int rows, int cols, int nTooters)
{
    if (nTooters < 0)
    {
        cout << "***** Cannot create Game with negative number of Tooters!" << endl;
        exit(1);
    }
    if (nTooters > MAXTOOTERS)
    {
        cout << "***** Trying to create Game with " << nTooters
             << " Tooters; only " << MAXTOOTERS << " are allowed!" << endl;
        exit(1);
    }
    if (rows == 1  &&  cols == 1  &&  nTooters > 0)
    {
        cout << "***** Cannot create Game with nowhere to place the Tooters!" << endl;
        exit(1);
    }

        // Create city
    m_city = new City(rows, cols);

        // Add a player
    int rPlayer = randInt(1, rows);
    int cPlayer = randInt(1, cols);
    m_city->addPlayer(rPlayer, cPlayer);

      // Populate with Tooters
    while (nTooters > 0)
    {
        int r = randInt(1, rows);
        int c = randInt(1, cols);
          // Don't put a Tooter where the player is
        if (r == rPlayer  &&  c == cPlayer)
            continue;
        m_city->addTooter(r, c);
        nTooters--;
    }
}

Game::~Game()
{
    delete m_city;
}

void Game::play()
{
    m_city->display();
    Player* p = m_city->player();
    if (p == nullptr)
        return;

    while ( ! p->isPassedOut()  &&  m_city->tooterCount() > 0)
    {
        cout << "Move (u/d/l/r//q): ";
        string action;
        getline(cin,action);
        if (action.size() == 0)  // player preaches
            p->preach();
        else
        {
            switch (action[0])
            {
              default:   // if bad move, nobody moves
                cout << '\a' << endl;  // beep
                continue;
              case 'q':
                return;
              case 'u':
              case 'd':
              case 'l':
              case 'r':
                p->move(decodeDirection(action[0]));
                break;
            }
        }
        m_city->moveTooters();
        m_city->display();
    }
    if (p->isPassedOut())
        cout << "You lose." << endl;
    else
        cout << "You win." << endl;
}

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function implementations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char dir)
{
    switch (dir)
    {
      case 'u':  return UP;
      case 'd':  return DOWN;
      case 'l':  return LEFT;
      case 'r':  return RIGHT;
    }
    return -1;  // bad argument passed in!
}

  // Return a random int from min to max, inclusive
int randInt(int min, int max)
{
    if (max < min)
        swap(max, min);
    static random_device rdv;
    static default_random_engine generator(rdv());
    uniform_int_distribution<> distro(min, max);
    return distro(generator);
}

///////////////////////////////////////////////////////////////////////////
//  main()
///////////////////////////////////////////////////////////////////////////

int main()
{
      // Create a game
      // Use this instead to create a mini-game:   Game g(3, 4, 2);
    Game g(7, 8, 25);

      // Play the game
    g.play();
}

///////////////////////////////////////////////////////////////////////////
//  clearScreen implementation
///////////////////////////////////////////////////////////////////////////

// DO NOT MODIFY OR REMOVE ANYTHING BETWEEN HERE AND THE END OF THE FILE!!!
// THE CODE IS SUITABLE FOR VISUAL C++, XCODE, AND g++/g31 UNDER LINUX.

// Note to Xcode users:  clearScreen() will just write a newline instead
// of clearing the window if you launch your program from within Xcode.
// That's acceptable.  (The Xcode output window doesn't have the capability
// of being cleared.)

#ifdef _WIN32  //  Windows

#pragma warning(disable : 4005)
#include <windows.h>

void clearScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    COORD upperLeft = { 0, 0 };
    DWORD dwCharsWritten;
    FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
                                                        &dwCharsWritten);
    SetConsoleCursorPosition(hConsole, upperLeft);
}

#else  // not Windows

#include <iostream>
#include <cstring>
#include <cstdlib>

void clearScreen()  // will just write a newline in an Xcode output window
{
    static const char* term = getenv("TERM");
    if (term == nullptr  ||  strcmp(term, "dumb") == 0)
        cout << endl;
    else
    {
        static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
        cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << flush;
    }
}

#endif


//Solution
/*// toot.cpp
 
 #include <iostream>
 #include <string>
 #include <random>
 #include <utility>
 #include <cstdlib>
 using namespace std;

 ///////////////////////////////////////////////////////////////////////////
 // Manifest constants
 ///////////////////////////////////////////////////////////////////////////

 const int MAXROWS = 20;               // max number of rows in a city
 const int MAXCOLS = 30;               // max number of columns in a city
 const int MAXTOOTERS = 125;           // max number of Tooters allowed
 const int INITIAL_PLAYER_HEALTH = 12;

 const int UP      = 0;
 const int DOWN    = 1;
 const int LEFT    = 2;
 const int RIGHT   = 3;
 const int NUMDIRS = 4;

 ///////////////////////////////////////////////////////////////////////////
 // Type definitions
 ///////////////////////////////////////////////////////////////////////////

 class City;  // This is needed to let the compiler know that City is a
              // type name, since it's mentioned in the Tooter declaration.

 class Tooter
 {
   public:
         // Constructor
     Tooter(City* cp, int r, int c);

         // Accessors
     int  row() const;
     int  col() const;

         // Mutators
     void move();

   private:
     City* m_city;
     int   m_row;
     int   m_col;
 };

 class Player
 {
   public:
         // Constructor
     Player(City *cp, int r, int c);

         // Accessors
     int  row() const;
     int  col() const;
     int  age() const;
     int  health() const;
     bool isPassedOut() const;

         // Mutators
     void  preach();
     void  move(int dir);
     void  getGassed();

   private:
     City* m_city;
     int   m_row;
     int   m_col;
     int   m_health;
     int   m_age;
 };

 class City
 {
   public:
         // Constructor/destructor
     City(int nRows, int nCols);
     ~City();

         // Accessors
     int     rows() const;
     int     cols() const;
     Player* player() const;
     bool    isPlayerAt(int r, int c) const;
     int     tooterCount() const;
     int     nTootersAt(int r, int c) const;
     bool    determineNewPosition(int& r, int& c, int dir) const;
     void    display() const;

         // Mutators
     bool addTooter(int r, int c);
     bool addPlayer(int r, int c);
     void preachToTootersAroundPlayer();
     void moveTooters();

   private:
     int     m_rows;
     int     m_cols;
     Player* m_player;
     Tooter* m_tooters[MAXTOOTERS];
     int     m_nTooters;

       // Helper functions
     bool isInBounds(int r, int c) const;
 };

 class Game
 {
   public:
         // Constructor/destructor
     Game(int rows, int cols, int nTooters);
     ~Game();

         // Mutators
     void play();

   private:
     City* m_city;
 };

 ///////////////////////////////////////////////////////////////////////////
 //  Auxiliary function declarations
 ///////////////////////////////////////////////////////////////////////////

 int decodeDirection(char dir);
 int randInt(int min, int max);
 void clearScreen();

 ///////////////////////////////////////////////////////////////////////////
 //  Tooter implementation
 ///////////////////////////////////////////////////////////////////////////

 Tooter::Tooter(City* cp, int r, int c)
 {
     if (cp == nullptr)
     {
         cout << "***** A Tooter must be created in some City!" << endl;
         exit(1);
     }
     if (r < 1  ||  r > cp->rows()  ||  c < 1  ||  c > cp->cols())
     {
         cout << "***** Tooter created with invalid coordinates (" << r << ","
              << c << ")!" << endl;
         exit(1);
     }
     m_city = cp;
     m_row = r;
     m_col = c;
 }

 int Tooter::row() const
 {
     return m_row;
 }

 int Tooter::col() const
 {
     return m_col;
 }

 void Tooter::move()
 {
       // Attempt to move in a random direction; if it can't move, don't move.
       // If the player is there, don't move.
     int dir = randInt(0, NUMDIRS-1);  // dir is now UP, DOWN, LEFT, or RIGHT
     int r = m_row;
     int c = m_col;
     m_city->determineNewPosition(r, c, dir);
     if ( ! m_city->isPlayerAt(r, c))
     {
         m_row = r;
         m_col = c;
     }
 }

 ///////////////////////////////////////////////////////////////////////////
 //  Player implementations
 ///////////////////////////////////////////////////////////////////////////

 Player::Player(City* cp, int r, int c)
 {
     if (cp == nullptr)
     {
         cout << "***** The player must be created in some City!" << endl;
         exit(1);
     }
     if (r < 1  ||  r > cp->rows()  ||  c < 1  ||  c > cp->cols())
     {
         cout << "**** Player created with invalid coordinates (" << r
              << "," << c << ")!" << endl;
         exit(1);
     }
     m_city = cp;
     m_row = r;
     m_col = c;
     m_health = INITIAL_PLAYER_HEALTH;
     m_age = 0;
 }

 int Player::row() const
 {
     return m_row;
 }

 int Player::col() const
 {
     return m_col;
 }

 int Player::age() const
 {
     return m_age;
 }

 int Player::health() const
 {
     return m_health;
 }

 bool Player::isPassedOut() const
 {
     return m_health <= 0;
 }

 void Player::preach()
 {
     m_age++;
     m_city->preachToTootersAroundPlayer();
 }

 void Player::move(int dir)
 {
     m_age++;
     int r = m_row;
     int c = m_col;
     if (m_city->determineNewPosition(r, c, dir))
     {
           // If there are no Tooters at the new position
         if (m_city->nTootersAt(r, c) == 0)
         {
             m_row = r;
             m_col = c;
         }
     }
 }

 void Player::getGassed()
 {
     m_health--;
 }

 ///////////////////////////////////////////////////////////////////////////
 //  City implementations
 ///////////////////////////////////////////////////////////////////////////

 City::City(int nRows, int nCols)
 {
     if (nRows <= 0  ||  nCols <= 0  ||  nRows > MAXROWS  ||  nCols > MAXCOLS)
     {
         cout << "***** City created with invalid size " << nRows << " by "
              << nCols << "!" << endl;
         exit(1);
     }
     m_rows = nRows;
     m_cols = nCols;
     m_player = nullptr;
     m_nTooters = 0;
 }

 City::~City()
 {
     for (int k = 0; k < m_nTooters; k++)
         delete m_tooters[k];
     delete m_player;
 }

 int City::rows() const
 {
     return m_rows;
 }

 int City::cols() const
 {
     return m_cols;
 }

 Player* City::player() const
 {
     return m_player;
 }

 bool City::isPlayerAt(int r, int c) const
 {
     return m_player != nullptr  &&
            m_player->row() == r  &&  m_player->col() == c;
 }

 int City::tooterCount() const
 {
     return m_nTooters;
 }

 int City::nTootersAt(int r, int c) const
 {
     int count = 0;
     for (int k = 0; k < m_nTooters; k++)
     {
         const Tooter* tp = m_tooters[k];
         if (tp->row() == r  &&  tp->col() == c)
             count++;
     }
     return count;
 }

 bool City::determineNewPosition(int& r, int& c, int dir) const
 {
     switch (dir)
     {
       case UP:     if (r <= 1)      return false; else r--; break;
       case DOWN:   if (r >= rows()) return false; else r++; break;
       case LEFT:   if (c <= 1)      return false; else c--; break;
       case RIGHT:  if (c >= cols()) return false; else c++; break;
       default:     return false;
     }
     return true;
 }

 void City::display() const
 {
       // Position (row,col) in the city coordinate system is represented in
       // the array element grid[row-1][col-1]
     char grid[MAXROWS][MAXCOLS];
     int r, c;
     
         // Fill the grid with dots
     for (r = 0; r < rows(); r++)
         for (c = 0; c < cols(); c++)
             grid[r][c] = '.';

         // Indicate each Tooter's position
     for (int k = 0; k < m_nTooters; k++)
     {
         const Tooter* tp = m_tooters[k];
         char& gridChar = grid[tp->row()-1][tp->col()-1];
         switch (gridChar)
         {
           case '.':  gridChar = 'T'; break;
           case 'T':  gridChar = '2'; break;
           case '9':  break;
           default:   gridChar++; break;  // '2' through '8'
         }
     }

         // Indicate player's position
     if (m_player != nullptr)
     {
           // Set the char to '@', unless there's also a Tooter there
           // (which should never happen), in which case set it to '*'.
         char& gridChar = grid[m_player->row()-1][m_player->col()-1];
         if (gridChar == '.')
             gridChar = '@';
         else
             gridChar = '*';
     }

         // Draw the grid
     clearScreen();
     for (r = 0; r < rows(); r++)
     {
         for (c = 0; c < cols(); c++)
             cout << grid[r][c];
         cout << endl;
     }
     cout << endl;

         // Write message, Tooter, and player info
     cout << "There are " << m_nTooters << " unconverted Tooters remaining." << endl;
     if (m_player == nullptr)
         cout << "There is no player." << endl;
     else
     {
         if (m_player->age() > 0)
             cout << "The player has lasted " << m_player->age() << " steps." << endl;
         if (m_player->isPassedOut())
             cout << "The player has passed out." << endl;
         else
             cout << "The player's health level is " << m_player->health() << endl;
     }
 }

 bool City::addTooter(int r, int c)
 {
     if ( ! isInBounds(r, c))
         return false;

       // Don't add a Tooter on a spot with a player
     if (m_player != nullptr  &&  m_player->row() == r  &&  m_player->col() == c)
         return false;

       // Dynamically allocate a new Tooter and add it to the city
     if (m_nTooters == MAXTOOTERS)
         return false;
     m_tooters[m_nTooters] = new Tooter(this, r, c);
     m_nTooters++;
     return true;
 }

 bool City::addPlayer(int r, int c)
 {
     if ( ! isInBounds(r, c))
         return false;

       // Don't add a player if one already exists
     if (m_player != nullptr)
         return false;

       // Don't add a player on a spot with a Tooter
     if (nTootersAt(r, c) > 0)
         return false;

       // Dynamically allocate a new Player and add it to the city
     m_player = new Player(this, r, c);
     return true;
 }

 void City::preachToTootersAroundPlayer()
 {
       // Preach to Tooters orthogonally or diagonally adjacent to player.  If a
       // Tooter is converted, then since the order of the Tooters in the array
       // doesn't matter, we can replace the converted Tooter we remove from the
       // game by the last one in the array.
     if (m_player == nullptr)
         return;

     for (int k = 0; k < m_nTooters; )
     {
         Tooter* tp = m_tooters[k];
         int rowdiff = tp->row() - m_player->row();
         int coldiff = tp->col() - m_player->col();

           // if orthogonally or diagonally adjacent and conversion succeeds
         if (rowdiff >= -1  &&  rowdiff <= 1  &&
             coldiff >= -1  &&  coldiff <= 1  &&
             randInt(1, 3) <= 2)  // 2/3 probability
         {
             delete m_tooters[k];
             m_tooters[k] = m_tooters[m_nTooters-1];
             m_nTooters--;
         }
         else
             k++;
     }
 }

 void City::moveTooters()
 {
     for (int k = 0; k < m_nTooters; k++)
     {
         Tooter* tp = m_tooters[k];
         tp->move();
         if (m_player == nullptr)
             continue;
         int rowdiff = tp->row() - m_player->row();
         int coldiff = tp->col() - m_player->col();
           // if orthogonally adjacent
         if  ((rowdiff == 0  &&  (coldiff == 1  ||  coldiff == -1))  ||
              (coldiff == 0  &&  (rowdiff == 1  ||  rowdiff == -1)) )
             m_player->getGassed();
     }
 }

 bool City::isInBounds(int r, int c) const
 {
     return (r >= 1  &&  r <= m_rows  &&  c >= 1  &&  c <= m_cols);
 }

 ///////////////////////////////////////////////////////////////////////////
 //  Game implementations
 ///////////////////////////////////////////////////////////////////////////

 Game::Game(int rows, int cols, int nTooters)
 {
     if (nTooters < 0)
     {
         cout << "***** Cannot create Game with negative number of Tooters!" << endl;
         exit(1);
     }
     if (nTooters > MAXTOOTERS)
     {
         cout << "***** Trying to create Game with " << nTooters
              << " Tooters; only " << MAXTOOTERS << " are allowed!" << endl;
         exit(1);
     }
     if (rows == 1  &&  cols == 1  &&  nTooters > 0)
     {
         cout << "***** Cannot create Game with nowhere to place the Tooters!" << endl;
         exit(1);
     }

         // Create city
     m_city = new City(rows, cols);

         // Add a player
     int rPlayer = randInt(1, rows);
     int cPlayer = randInt(1, cols);
     m_city->addPlayer(rPlayer, cPlayer);

       // Populate with Tooters
     while (nTooters > 0)
     {
         int r = randInt(1, rows);
         int c = randInt(1, cols);
           // Don't put a Tooter where the player is
         if (r == rPlayer  &&  c == cPlayer)
             continue;
         m_city->addTooter(r, c);
         nTooters--;
     }
 }

 Game::~Game()
 {
     delete m_city;
 }

 void Game::play()
 {
     m_city->display();
     Player* p = m_city->player();
     if (p == nullptr)
         return;

     while ( ! p->isPassedOut()  &&  m_city->tooterCount() > 0)
     {
         cout << "Move (u/d/l/r//q): ";
         string action;
         getline(cin,action);
         if (action.size() == 0)  // player preaches
             p->preach();
         else
         {
             switch (action[0])
             {
               default:   // if bad move, nobody moves
                 cout << '\a' << endl;  // beep
                 continue;
               case 'q':
                 return;
               case 'u':
               case 'd':
               case 'l':
               case 'r':
                 p->move(decodeDirection(action[0]));
                 break;
             }
         }
         m_city->moveTooters();
         m_city->display();
     }
     if (p->isPassedOut())
         cout << "You lose." << endl;
     else
         cout << "You win." << endl;
 }

 ///////////////////////////////////////////////////////////////////////////
 //  Auxiliary function implementations
 ///////////////////////////////////////////////////////////////////////////

 int decodeDirection(char dir)
 {
     switch (dir)
     {
       case 'u':  return UP;
       case 'd':  return DOWN;
       case 'l':  return LEFT;
       case 'r':  return RIGHT;
     }
     return -1;  // bad argument passed in!
 }

   // Return a uniformly distributed random int from min to max, inclusive
 int randInt(int min, int max)
 {
     if (max < min)
         swap(max, min);
     static random_device rdv;
     static default_random_engine generator(rdv());
     uniform_int_distribution<> distro(min, max);
     return distro(generator);
 }

 ///////////////////////////////////////////////////////////////////////////
 //  main()
 ///////////////////////////////////////////////////////////////////////////

 int main()
 {
       // Create a game
       // Use this instead to create a mini-game:   Game g(3, 4, 2);
     Game g(7, 8, 25);

       // Play the game
     g.play();
 }

 ///////////////////////////////////////////////////////////////////////////
 //  clearScreen implementation
 ///////////////////////////////////////////////////////////////////////////

 // DO NOT MODIFY OR REMOVE ANYTHING BETWEEN HERE AND THE END OF THE FILE!!!
 // THE CODE IS SUITABLE FOR VISUAL C++, XCODE, AND g++/g31 UNDER LINUX.

 // Note to Xcode users:  clearScreen() will just write a newline instead
 // of clearing the window if you launch your program from within Xcode.
 // That's acceptable.  (The Xcode output window doesn't have the capability
 // of being cleared.)

 #ifdef _WIN32  //  Windows

 #pragma warning(disable : 4005)
 #include <windows.h>

 void clearScreen()
 {
     HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     GetConsoleScreenBufferInfo(hConsole, &csbi);
     DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
     COORD upperLeft = { 0, 0 };
     DWORD dwCharsWritten;
     FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
                                                         &dwCharsWritten);
     SetConsoleCursorPosition(hConsole, upperLeft);
 }

 #else  // not Microsoft Visual C++, so assume UNIX interface

 #include <iostream>
 #include <cstring>
 #include <cstdlib>

 void clearScreen()  // will just write a newline in an Xcode output window
 {
     static const char* term = getenv("TERM");
     if (term == nullptr  ||  strcmp(term, "dumb") == 0)
         cout << endl;
     else
     {
         static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
         cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << flush;
     }
 }

 #endif*/

//Test Data
/*There were 29 test cases; cases 1 through 16 were worth 3 points each, and cases 17 though 29 were worth 4 points each. Each test case is represented by an assertion that must be true for you to pass that test. To run the test cases:

Remove the main routine from your toot.cpp file.
Append the following text to the end of your toot.cpp file, and build the resulting program.
For any test case you wish to try, run the program, providing as input the test number.
#include <iostream>
#include <sstream>
#include <streambuf>
#include <string>
#include <map>
#include <algorithm>
#include <thread>
#include <future>
#include <chrono>
#include <cstdlib>
#include <cassert>
using namespace std;

class StreambufSwitcher
{
  public:
    StreambufSwitcher(ios& dest, streambuf* sb,
                    ios::iostate exceptions = ios::goodbit)
     : dest_stream(dest), oldsb(dest.rdbuf(sb)), oldex(dest.exceptions())
    { dest_stream.exceptions(exceptions); }
    StreambufSwitcher(ios& dest, ios& src)
     : StreambufSwitcher(dest, src.rdbuf(), src.exceptions())
    {}
    ~StreambufSwitcher()
    { dest_stream.rdbuf(oldsb); dest_stream.exceptions(oldex); }
  private:
    ios& dest_stream;
    streambuf* oldsb;
    ios::iostate oldex;
};

map<void*, size_t> allocMap;
bool recordaddrs = false;

inline bool isRecordedSize(size_t n)
{
    return n == sizeof(Tooter)  ||  n == sizeof(Player);
}

void* operator new(size_t n)
{
    void* p = malloc(n);
    fill_n(static_cast<char*>(p), n, 0xca);
    if (recordaddrs  &&  isRecordedSize(n))
    {
        recordaddrs = false;
        allocMap.insert(make_pair(p, n));
        recordaddrs = true;
    }
    return p;
}

void unrecordaddr(void* p)
{
    recordaddrs = false;
    auto it = allocMap.find(p);
    if (it != allocMap.end())
    {
        fill_n(static_cast<char*>(p), it->second, 0xcb);
        allocMap.erase(it);
    }
    recordaddrs = true;
}

#if __cplusplus >= 201402L  &&  ! defined(__clang__)
// Unless clang is supplied the -fsized-deallocation flag, it will
// not call the C++14/17 sized operator delete.

void operator delete(void* p) noexcept
{
    free(p);
}

void operator delete(void* p, size_t n) noexcept
{
    if (recordaddrs  &&  isRecordedSize(n))
        unrecordaddr(p);
    operator delete(p);
}
#else
void operator delete(void* p) noexcept
{
    if (recordaddrs)
        unrecordaddr(p);
    free(p);
}
#endif

void testone(int n)
{
    StreambufSwitcher sso(cout, cerr);

    switch (n)
    {
                     default: {
        cout << "Bad argument" << endl;
            } break; case  1: {
        City c(10, 18);
        c.addPlayer(2, 2);
        Tooter t(&c, 5, 17);
        assert(t.row() == 5  &&  t.col() == 17);
            } break; case  2: {
        bool movedr = false;
        bool movedl = false;
        bool stayed = false;
        for (int k = 0; k < 150; k++)
        {
            City c(1, 30);
            c.addPlayer(1, 1);
            Tooter t(&c, 1, 29);
            assert(t.row() == 1  &&  t.col() == 29);
            for (int n = 0; n < 2; n++)
            {
                int oldc = t.col();
                t.move();
                assert(t.row() == 1  &&  t.col() <= 30);
                int d = t.col() - oldc;
                switch (d)
                {
                  case  0:  stayed = true; break;
                  case  1:  movedr = true; break;
                  case -1:  movedl = true; break;
                  default:  assert(false);
                }
            }
        }
        assert(movedr  &&  movedl  &&  stayed);
            } break; case  3: {
        bool movedd = false;
        bool movedu = false;
        bool stayed = false;
        for (int k = 0; k < 150; k++)
        {
            City c(20, 1);
            c.addPlayer(1, 1);
            Tooter t(&c, 19, 1);
            assert(t.row() == 19  &&  t.col() == 1);
            for (int n = 0; n < 2; n++)
            {
                int oldr = t.row();
                t.move();
                assert(t.col() == 1  &&  t.row() <= 20);
                int d = t.row() - oldr;
                switch (d)
                {
                  case  0:  stayed = true; break;
                  case  1:  movedd = true; break;
                  case -1:  movedu = true; break;
                  default:  assert(false);
                }
            }
        }
        assert(movedd  &&  movedu  &&  stayed);
            } break; case  4: {
        City c(20, 20);
        c.addPlayer(1, 1);
        Tooter t(&c, 12, 12);
        for (int k = 0; k < 8; k++)
        {
            int oldr = t.row();
            int oldc = t.col();
            t.move();
            assert((t.row() == oldr  &&  abs(t.col() - oldc) == 1)  ||
                   (t.col() == oldc  &&  abs(t.row() - oldr) == 1));
        }
            } break; case  5: {
        const int dr[NUMDIRS+1] = { -1,  0,  1,  0,  0 };
        const int dc[NUMDIRS+1] = {  0,  1,  0, -1,  0 };
        for (int k = 0; k < NUMDIRS; k++)
        {
            int nvisits[NUMDIRS+1] = { 0 };
            for (int n = 0; n < 100; n++)
            {
                City c(20, 20);
                c.addPlayer(10, 10);
                int oldr = 10 - dr[k];
                int oldc = 10 - dc[k];
                Tooter t(&c, oldr, oldc);
                t.move();
                int rdiff = t.row() - oldr;
                int cdiff = t.col() - oldc;
                int i;
                for (i = 0; i < NUMDIRS+1; i++)
                {
                    if (rdiff == dr[i]  &&  cdiff == dc[i])
                    {
                        nvisits[i]++;
                        break;
                    }
                }
                assert(i < NUMDIRS+1);
            }
            for (int i = 0; i < NUMDIRS+1; i++)
                assert(k == i ? nvisits[i] == 0 : nvisits[i] > 1);
        }
            } break; case  6: {
        City c(10, 20);
        Player p(&c, 2, 3);
        assert(p.row() == 2  &&  p.col() == 3  &&  !p.isPassedOut());
            } break; case  7: {
        City c(10, 20);
        Player p(&c, 2, 3);
        for (int k = 0; k < 12; k++)
        {
            assert(!p.isPassedOut());
            p.getGassed();
        }
        assert(p.isPassedOut());
            } break; case  8: {
        City c(10, 20);
        Player p(&c, 2, 3);
        for (int k = 0; k < 12; k++)
        {
            assert(p.health() == 12 - k);
            p.getGassed();
        }
        assert(p.isPassedOut());
            } break; case  9: {
        City c(10, 18);
        c.addPlayer(10, 17);
        Player* pp = c.player();
        pp->move(RIGHT);
        assert(pp->row() == 10  &&  pp->col() == 18  &&  !pp->isPassedOut());
        pp->move(DOWN);
        assert(pp->row() == 10  &&  pp->col() == 18  &&  !pp->isPassedOut());
        pp->move(RIGHT);
        assert(pp->row() == 10  &&  pp->col() == 18  &&  !pp->isPassedOut());
            } break; case 10: {
        City c(10, 18);
        c.addPlayer(2, 1);
        Player* pp = c.player();
        pp->move(UP);
        assert(pp->row() == 1  &&  pp->col() == 1  &&  !pp->isPassedOut());
        pp->move(LEFT);
        assert(pp->row() == 1  &&  pp->col() == 1  &&  !pp->isPassedOut());
        pp->move(UP);
        assert(pp->row() == 1  &&  pp->col() == 1  &&  !pp->isPassedOut());
            } break; case 11: {
        City c(10, 20);
        c.addPlayer(8, 12);
        Player* pp = c.player();
        pp->move(UP);
        assert(pp->row() == 7  &&  pp->col() == 12);
        pp->move(DOWN);
        assert(pp->row() == 8  &&  pp->col() == 12);
        pp->move(LEFT);
        assert(pp->row() == 8  &&  pp->col() == 11);
        pp->move(RIGHT);
        assert(pp->row() == 8  &&  pp->col() == 12);
            } break; case 12: {
        City c(10, 18);
        c.addPlayer(5, 7);
        c.addTooter(3, 7);
        c.addTooter(4, 9);
        c.addTooter(6, 8);
        c.addTooter(5, 6);
        Player* pp = c.player();
        pp->move(UP);
        assert(pp->row() == 4  &&  pp->col() == 7  &&  !pp->isPassedOut());
        pp->move(UP);
        assert(pp->row() == 4  &&  pp->col() == 7  &&  !pp->isPassedOut());
        pp->move(RIGHT);
        assert(pp->row() == 4  &&  pp->col() == 8  &&  !pp->isPassedOut());
        pp->move(RIGHT);
        assert(pp->row() == 4  &&  pp->col() == 8  &&  !pp->isPassedOut());
        pp->move(DOWN);
        assert(pp->row() == 5  &&  pp->col() == 8  &&  !pp->isPassedOut());
        pp->move(DOWN);
        assert(pp->row() == 5  &&  pp->col() == 8  &&  !pp->isPassedOut());
        pp->move(LEFT);
        assert(pp->row() == 5  &&  pp->col() == 7  &&  !pp->isPassedOut());
        pp->move(LEFT);
        assert(pp->row() == 5  &&  pp->col() == 7  &&  !pp->isPassedOut());
            } break; case 13: {
        City c(10, 18);
        c.addPlayer(3, 9);
        c.addTooter(4, 9);
        assert(c.tooterCount() == 1);
        for (int k = 0; k < 100  &&  c.tooterCount() == 1; k++)
            c.player()->preach();
        assert(c.tooterCount() == 0);
            } break; case 14: {
        City c(10, 18);
        c.addPlayer(3, 9);
        assert(c.tooterCount() == 0);
        for (int k = 1; k <= 20; k++)
        {
            c.addTooter(3, 8);
            c.addTooter(3, 10);
            assert(c.tooterCount() == 2 * k);
        }
        int prevct = c.tooterCount();
        for (int k = 0; k < 100  &&  prevct > 0; k++)
        {
            c.player()->preach();
            int ct = c.tooterCount();
            assert(ct <= prevct);
            prevct = ct;
        }
        assert(prevct == 0);
            } break; case 15: {
        City c(10, 18);
        c.addPlayer(3, 9);
        c.addTooter(2, 9);
        assert(c.nTootersAt(2, 9) == 1);
        for (int k = 0; k < 100  &&  c.nTootersAt(2, 9) == 1; k++)
            c.player()->preach();
        assert(c.nTootersAt(2, 9) == 0);
            } break; case 16: {
        City c(2, 3);
        c.addPlayer(1, 2);
        c.addTooter(1, 3);
        c.addTooter(2, 2);
        ostringstream oss;
        streambuf *sb = cout.rdbuf(oss.rdbuf());
        c.display();
        cout.rdbuf(sb);
        string s = oss.str();
        assert(s.find(".@T") != string::npos  &&  s.find(".T.") != string::npos);
            } break; case 17: {
        City c(2, 3);
        c.addPlayer(1, 2);
        for (int k = 1; k <= 8; k++)
            c.addTooter(1, 3);
        c.addTooter(2, 2);
        ostringstream oss;
        streambuf *sb = cout.rdbuf(oss.rdbuf());
        c.display();
        cout.rdbuf(sb);
        string s = oss.str();
        assert(s.find(".@8") != string::npos);
            } break; case 18: {
        City c(2, 3);
        c.addPlayer(1, 2);
        for (int k = 1; k <= 10; k++)
            c.addTooter(1, 3);
        c.addTooter(2, 2);
        ostringstream oss;
        streambuf *sb = cout.rdbuf(oss.rdbuf());
        c.display();
        cout.rdbuf(sb);
        string s = oss.str();
        assert(s.find(".@9") != string::npos);
            } break; case 19: {
        City c(10, 18);
        c.addPlayer(3, 9);
        int prevct[3];
        for (int dr = -1; dr <= 1; dr++)
        {
            if (dr == 0)
                continue;
            for (int k = 0; k < MAXTOOTERS/2; k++)
                assert(c.addTooter(3+dr, 9));
            prevct[1+dr] = c.nTootersAt(3+dr, 9);
            assert(prevct[1+dr] == MAXTOOTERS/2);
        }
        bool anyleft = true;
        for (int k = 0; k < 100  &&  anyleft; k++)
        {
            anyleft = false;
            c.preachToTootersAroundPlayer();
            for (int dr = -1; dr <= 1; dr++)
            {
                if (dr == 0)
                    continue;
                int ct = c.nTootersAt(3+dr, 9);
                assert(ct <= prevct[1+dr]);
                prevct[1+dr] = ct;
                if (ct > 0)
                    anyleft = true;
            }
        }
        assert(!anyleft);
            } break; case 20: {
        City c(10, 18);
        c.addPlayer(3, 9);
        int prevct[3][3];
        for (int dr = -1; dr <= 1; dr++)
          for (int dc = -1; dc <= 1; dc++)
          {
            if (dr == 0  &&  dc == 0)
                continue;
            for (int k = 0; k < MAXTOOTERS/8; k++)
                assert(c.addTooter(3+dr, 9+dc));
            prevct[1+dr][1+dc] = c.nTootersAt(3+dr, 9+dc);
            assert(prevct[1+dr][1+dc] == MAXTOOTERS/8);
          }
        bool anyleft = true;
        for (int k = 0; k < 100  &&  anyleft; k++)
        {
            anyleft = false;
            c.preachToTootersAroundPlayer();
            for (int dr = -1; dr <= 1; dr++)
              for (int dc = -1; dc <= 1; dc++)
              {
                if (dr == 0  &&  dc == 0)
                    continue;
                int ct = c.nTootersAt(3+dr, 9+dc);
                assert(ct <= prevct[1+dr][1+dc]);
                prevct[1+dr][1+dc] = ct;
                if (ct > 0)
                    anyleft = true;
              }
        }
        assert(!anyleft);
            } break; case 21: {
        int n = 0;
        for (int k = 0; k < 600; k++)
        {
            City c(10, 18);
            c.addPlayer(3, 9);
            assert(c.tooterCount() == 0);
            c.addTooter(3, 10);
            assert(c.tooterCount() == 1);
            c.preachToTootersAroundPlayer();
            if (c.tooterCount() == 0)
                n++;
        }
        assert(n >= 355 &&  n <= 445);
            } break; case 22: {
        City c(10, 18);
        c.addPlayer(3, 9);
        for (int k = 0; k < MAXTOOTERS; k++)
            assert(c.addTooter(2, 9));
        assert(!c.addTooter(2, 9));
        assert(c.tooterCount() == MAXTOOTERS);
        for (int n = 64; n > 0; n /= 2)
        {
            for (int k = 0; k < 100  &&  c.tooterCount() >= n; k++)
                c.preachToTootersAroundPlayer();
            assert(c.tooterCount() < n);
            for (int k = 0; k < MAXTOOTERS  &&  c.tooterCount() < MAXTOOTERS; k++)
                assert(c.addTooter(2, 9));
            assert(c.tooterCount() == MAXTOOTERS);
        }
            } break; case 23: {
        const int dr[NUMDIRS] = { -1,  0,  1,  0 };
        const int dc[NUMDIRS] = {  0,  1,  0, -1 };
        City c(12, 18);
        c.addPlayer(1, 1);
        const int r[3] = { 3, 6, 9 };
        const int v[3] = { 4, 7, 10 };
        for (int k = 0; k < 3; k++)
            c.addTooter(r[k], v[k]);
        c.moveTooters();
        for (int k = 0; k < 3; k++)
        {
            int ct[2] = { 0 };
            for (int n = 0; n < NUMDIRS; n++)
            {
                int m = c.nTootersAt(r[k]+dr[n], v[k]+dc[n]);
                assert(m == 0  ||  m == 1);
                ct[m]++;
            }
            assert(ct[0] == 3  &&  ct[1] == 1);
        }
            } break; case 24: {
        bool gassed = false;
        for (int n = 0; n < 20; n++)
        {
            City c(10, 20);
            c.addPlayer(5, 9);
            for (int k = 0; k < 11; k++)
                c.addTooter(5, 11);
            c.preachToTootersAroundPlayer();
            c.moveTooters();
            int h = c.player()->health();
            if (h < 12)
                gassed = true;
            assert(c.nTootersAt(5, 10) == 12 - h);
        }
        assert(gassed);
            } break; case 25: {
        bool gassed = false;
        for (int n = 0; n < 20; n++)
        {
            City c(10, 20);
            c.addPlayer(5, 9);
            for (int k = 0; k < 9; k++)
                c.addTooter(5, 10);
            assert(c.player()->health() == 12);
            c.moveTooters();
            int h = c.player()->health();
            if (h < 12)
                gassed = true;
            assert(c.nTootersAt(5, 10) == 12 - h);
        }
        assert(gassed);
            } break; case 26: {
        for (int n = 0; n < 20; n++)
        {
            City c(1, 20);
            c.addPlayer(1, 2);
            for (int k = 0; k < 11; k++)
                c.addTooter(1, 1);
            assert(c.player()->health() == 12);
            c.moveTooters();
            assert(c.player()->health() == 12-11);
            assert(c.nTootersAt(1, 1) == 11);
        }
            } break; case 27: {
        int n;
        for (n = 0; n < 2; n++)
        {
            City c(10, 20);
            c.addPlayer(5, 9);
            for (int k = 0; k < MAXTOOTERS; k++)
                c.addTooter(5, 11);
            assert(c.player()->health() == 12  &&  ! c.player()->isPassedOut());
            c.moveTooters();
            if (c.player()->health() <= 0  &&  c.player()->isPassedOut())
                break;
        }
        assert(n != 2);
            } break; case 28: {
        recordaddrs = true;
        int oldn = allocMap.size();
        {
            City c(10, 20);
            int oldn2 = allocMap.size();
            assert(oldn2 >= oldn);
            c.addPlayer(4, 3);
            c.addTooter(5, 6);
            c.addTooter(5, 7);
            c.addTooter(5, 8);
            assert(allocMap.size() == oldn2 + 4);
        }
        assert(allocMap.size() == oldn);
        recordaddrs = false;
            } break; case 29: {
        recordaddrs = true;
        int oldn = allocMap.size();
        {
            City c(10, 20);
            int oldn2 = allocMap.size();
            assert(oldn2 >= oldn);
            c.addPlayer(4, 3);
            assert(allocMap.size() == oldn2 + 1);
            for (int k = 0; k < MAXTOOTERS; k++)
                c.addTooter(4, 4);
            assert(allocMap.size() == oldn2 + 1 + MAXTOOTERS);
            for (int k = 0; k < 100  &&  c.nTootersAt(4, 4) > 0; k++)
            {
                c.preachToTootersAroundPlayer();
                assert(allocMap.size() == oldn2 + 1 + c.nTootersAt(4, 4));
            }
            assert(c.nTootersAt(4, 4) == 0);
        }
        assert(allocMap.size() == oldn);
        recordaddrs = false;
            } break;
    }
}

int main()
{
    cout << "Enter test number (1-29): ";
    int n;
    cin >> n;
    testone(n);
    cout << "Passed!" << endl;
}
*/
