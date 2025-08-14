//
//  main.cpp
//  prac
//
//  Created by Anahita Vaidhya on 11/16/23.
//

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int render(int lineLength, istream& inf, ostream& outf) {
    const int MAX = 181;
    char line[MAX];

    while (inf.getline(line, MAX)) {
        const char* delimiters = " \f\n\r\t\v"; // Add space to delimiters

        // Skip leading whitespace characters
        char* nonWhitespace = line;
        while (*nonWhitespace && strchr(delimiters, *nonWhitespace)) {
            nonWhitespace++;
        }

        // Initialize the current line
        char currentLine[MAX] = "";
        int remaining = lineLength;

        // Tokenize using strtok
        char* token = strtok(nonWhitespace, delimiters);

        while (token) {
            // Calculate the length of the current token
            int tokenLength = strlen(token);

            // Check if the token can fit in the remaining space of the line
            if (tokenLength + 1 <= remaining) { // +1 for space between words
                if (remaining < lineLength) {
                    strcat(currentLine, " ");
                    remaining--;
                }

                // Append the token to the current line
                strcat(currentLine, token);
                remaining -= tokenLength;
            } else {
                // Output the current line and start a new line with the token
                outf << currentLine << endl;
                strcpy(currentLine, token);
                remaining = lineLength - tokenLength;
            }

            // Get the next token
            token = strtok(nullptr, delimiters);
        }

        // Output the last line if any
        if (currentLine[0] != '\0') {
            outf << currentLine << endl;
        }
    }

    return 0; // You may need to handle errors and return appropriate codes
}

int main() {
    // insert code here...
    const int MAX_FILENAME_LENGTH = 100;
            for (;;)
            {
                cout << "Enter input file name (or q to quit): ";
                char filename[MAX_FILENAME_LENGTH];
                cin.getline(filename, MAX_FILENAME_LENGTH);
                if (strcmp(filename, "q") == 0)
                    break;
                ifstream infile(filename);
                if (!infile)
                {
                    cerr << "Cannot open " << filename << "!" << endl;
                    continue;
                }
                cout << "Enter maximum line length: ";
                int len;
                cin >> len;
                cin.ignore(10000, '\n');
                int returnCode = render(len, infile, cout);
                cout << "Return code is " << returnCode << endl;
            }
    
    
    return 0;
}
