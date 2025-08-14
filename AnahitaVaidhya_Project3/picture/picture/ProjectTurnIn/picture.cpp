//
//  main.cpp
//  picture
//
//  Created by Anahita Vaidhya on 10/29/23.
//

#include "grid.h"
#include <iostream>
#include <cctype>
#include <string>
#include <cassert>
using namespace std;


//Global Variables
const int HORIZ = 0;
const int VERT = 1;

const int FG = 0;
const int BG = 1;


//Function: Plot Horizontal Line
void plotHorizontalLine(int r, int c, int distance, char ch){
    for (int i = distance; i >= 0; i--){
        setChar(r, c, ch);
        c++;
    }
}

//Function: Plot Vertical Line
void plotVerticalLine(int r, int c, int distance, char ch){
    for (int i = distance; i >= 0; i--){
        setChar(r, c, ch);
        r++;
    }
}

//Function: Plot Rectangle]
//might still be missing things
void plotRectangle(int r, int c, int height, int width, char ch){
    if(height < 0 || width < 0){
        return;
    } else {
        plotVerticalLine(r, c, height, ch);
        plotHorizontalLine(r, c, width, ch);
        plotVerticalLine(r, c + width, height, ch);
        plotHorizontalLine(r + height, c, width, ch);
    }
}

//Plot Line
bool plotLine(int r, int c, int distance, int dir, char plotChar, int fgbg){
    //Variables
    int r2 = r;
    int c2 = c;
    
    //Checking if the inputs are correct
    if(!(dir == HORIZ || dir == VERT)){
            return false;
        }
        if(!(fgbg == FG || fgbg == BG)){
            return false;
        }
        if(dir == HORIZ && ((c+distance) > getCols() || (c+distance) < 1)){
            return false;
        }
        if(dir == VERT && ((r+distance) > getRows() || (r+distance) < 1)){
            return false;
        }
        if(!isprint(plotChar)){
            return false;
        }
    
    //Checking for FGBG and then going through possible options of distance and direction
    if (fgbg == 0){
        if(distance > 0){
            if(dir == 0){
                plotHorizontalLine(r, c, distance, plotChar);
            } else {
                plotVerticalLine(r, c, distance, plotChar);
            }
        } else if (distance < 0){
            if(dir == 0){
                for (int i = 0; i >= distance; i--){
                    setChar(r2, c2, plotChar);
                    c2--;
                }
            }
            if (dir == 1){
                for (int i = 0; i >= distance; i--){
                    setChar(r2, c2, plotChar);
                    r2--;
                }
            }
        }
    } else if (fgbg == 1){
            const char old = getChar(r, c);
            if(distance > 0){
                if(dir == 0){
                    for (int i = distance; i >= 0; i--){
                        if(getChar(r, c) == ' '){
                            setChar(r, c, plotChar);
                        }
                        c++;
                    }
                } else {
                    for (int i = distance; i >= 0; i--){
                        if(getChar(r, c) == ' '){
                            setChar(r, c, plotChar);
                        }
                        r++;
                    }
                }
            } else if (distance < 0){
                if(dir == 0){
                    for (int i = distance; i >= 0; i--){
                        setChar(r, c, plotChar);
                        c2--;
                    }
                    setChar(r, c, old);
                }
                if (dir == 1){
                    for (int i = distance; i >= 0; i--){
                        setChar(r, c, plotChar);
                        r2--;
                    }
                    setChar(r, c, old);
                }
            }
        }
    return true;
}

//Function: ifHorizontal (Used when performCommands detects an 'H' or 'h'
int ifHorizontal(string commandString, int pos, int& distance, int& track, int& badPos){
    //Variables
    string distS = "";
    string currentS = "";
    
    //Check for horizontal and plot
    if(commandString.at(pos) == 'H' || commandString.at(pos) == 'h'){
        if((pos+1) == '-' && !(isdigit(pos+1))){
            badPos = pos+1;
            return 1;
        }
        
        for(int j = pos + 1; j != commandString.size(); j++){
            if(j == '-' || isdigit(commandString.at(j))){
                currentS += commandString.substr(j, 1);
            } else {
                track = j;
                break;
            }
        }
        
        if(currentS.size() == 3){
            if(isdigit(pos+3)){
                if(isdigit(pos+2)){
                    if(commandString.at(pos+1) == '-'){
                        distance = (stoi(commandString.substr(pos+2, 2))) * -1;
                    }
                }
            }
        } else if (currentS.size() == 2){
            if(commandString.at(pos+1) == '-'){
                distance = (commandString.at(pos+2) - '0') * -1;
            } else {
                distS = commandString.substr(pos+1, 2);
                distance = stoi(distS);
            }
        } else {
            distance = commandString.at(pos+1) - '0';
        }
    }
    return 0;
}

//Function: ifVertical (Used when performCommands detects an 'V' or 'v'
int ifVertical(string commandString, int pos, int& distance, int& track, int& badPos){
    //Variables
    string distS = "";
    string currentS = "";
    
    //Check for vertical and plot
    if((pos+1) == '-' && !(isdigit(pos+1))){
        badPos = pos+1;
        return 1;
    }
    
    for(int j = track + 1; j != commandString.size(); j++){
        if(j == '-' || isdigit(commandString.at(j))){
            currentS += commandString.substr(j, 1);
        } else {
            track = j;
            break;
        }
    }
    
    if(currentS.size() == 3){
        if(isdigit(pos+3)){
            if(isdigit(pos+2)){
                if(commandString.at(pos+1) == '-'){
                    distance = (stoi(commandString.substr(pos+2, 2))) * -1;
                }
            }
        }
    } else if (currentS.size() == 2){
    if(commandString.at(pos+1) == '-'){
        distance = (commandString.at(pos+2) - '0') * -1;
    } else {
        distS = commandString.substr(pos+1, 2);
        distance = stoi(distS);
    }
    } else {
        distance = commandString.at(pos+1) - '0';
    }
    return 0;
}

//Function: Perform Commands
int performCommands(string commandString, char& plotChar, int& mode, int& badPos){
    //Variables
    int r = 1;
    int c = 1;
    int distance = 0;
    int track = 0;
    char currentChar = plotChar;
    int currentMode = mode;
    string distS = "";
    string currentS = "";
    
    //Go through string
    for(int i = 0; i != commandString.size(); i++){
        //Check for horizontal and plot
        if(commandString.at(i) == 'H' || commandString.at(i) == 'h'){
            ifHorizontal(commandString, i, distance, track, badPos);
            if(((c+distance) > getCols() || (c+distance) < 1)){
                return 3;
            } else {
                plotLine(r, c, distance, HORIZ, currentChar, currentMode);
                c += distance;
                i++;
            }
        }
        //Check for horizontal and plot
        if(commandString.at(i) == 'V' || commandString.at(i) == 'v') {
            ifVertical(commandString, i, distance, track, badPos);
            if(((r+distance) > getRows() || (r+distance) < 1)){
                return 3;
            } else {
                plotLine(r, c, distance, VERT, currentChar, currentMode);
                r += distance;
                i++;
            }
        }
        
        //Check if mode and char are valid
        if(!(currentMode == 0) && !(currentMode == 1)){
            return 2;
        }
        if(!(isprint(currentChar))){
            return 2;
        }
        
        //Check for foreground and change variables
        if(commandString.at(i) == 'F' || commandString.at(i) == 'f'){
            if(!(isprint(commandString.at(i+1)))){
                badPos = i+1;
                return 1;
            }
            currentMode = 0;
            currentChar = commandString.at(i+1);
            track += 2;
        }
        //Check for background and change mode and char
        if(commandString.at(i) == 'B' || commandString.at(i) == 'b'){
            if(!(isprint(commandString.at(i+1)))){
                badPos = i+1;
                return 1;
            }
            currentMode = 1;
            currentChar = commandString.at(i+1);
            track += 2;
        }
        //Check if clear and make sure nothing incorrect is after C, and reset grid
        if(commandString.at(i) == 'C' || commandString.at(i) == 'c'){
            if(commandString.at(i+1) == 'H' || commandString.at(i+1) == 'h' || commandString.at(i+1) == 'V' || commandString.at(i+1) == 'v' || commandString.at(i+1) == 'F' || commandString.at(i+1) == 'f' || commandString.at(i+1) == 'B' || commandString.at(i+1) == 'b' || commandString.at(i+1) == 'C' || commandString.at(i+1) == 'c'){
                clearGrid();
                r = 1;
                c = 1;
                currentChar = '*';
                currentMode = FG;
                track++;
            }
        }
    }
        return 0;
}

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
          case 0:
            draw();
            break;
          case 1:
            cout << "Syntax error at position " << position << endl;
            break;
          case 2:
            if (!isprint(currentChar))
                cout << "Current character is not printable" << endl;
            if (currentMode != FG  &&  currentMode != BG)
                cout << "Current mode is " << currentMode << ", not FG or BG" << endl;
            break;
          case 3:
            cout << "Cannot perform command at position " << position << endl;
            break;
          default:
              // It should be impossible to get here.
            cout << "performCommands returned " << status << "!" << endl;
        }
    }
}

