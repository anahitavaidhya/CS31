//
//  main.cpp
//  AnahitaVaidhya_Project5
//
//  Created by Anahita Vaidhya on 11/14/23.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <cstring>
#include <iostream>
using namespace std;

bool isWhitespace(char ch){
    return (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r');
}

int render(int lineLength, istream& inf, ostream& outf);

void testRender(int lineLength, const char input[], const char expectedOutput[], int expectedReturnValue)
{
    istringstream iss(input);
    ostringstream oss;
    ostringstream dummy;
    streambuf* origCout = cout.rdbuf(dummy.rdbuf());
    int retval = render(lineLength, iss, oss);
    cout.rdbuf(origCout);
    if ( ! dummy.str().empty())
        cerr << "WROTE TO COUT INSTEAD OF THIRD PARAMETER FOR: " << input << endl;
    else if (retval != expectedReturnValue)
        cerr << "WRONG RETURN VALUE FOR: " << input << endl;
    else if (retval == 2)
    {
        if ( ! oss.str().empty())
            cerr << "WROTE OUTPUT WHEN LINELENGTH IS " << lineLength << endl;
    }
    else if (oss.str() != expectedOutput)
        cerr << "WRONG RESULT FOR: " << input << endl;
}

int render(int lineLength, istream& inf, ostream& outf) {
    //Variables
    const int MAX = 181;
    char line[MAX];
    size_t remaining = lineLength;
    size_t tokenLength;
    int retVal = 0;
    size_t muchLeft;
    bool isHyphen = false;
    bool first = true;
    bool firstAfter = false;
    bool punc = false;
    
    //Return 2 if the desired maximum length < 1
    if(lineLength < 1){
        return 2;
    }
    
    //Get line by line
    while (inf.getline(line, MAX))
    {
        //Separates each word into tokens split by whitespace
        const char* delimiters = " \f\n\r\t\v"; // Add space to delimiters
        
        // Skip leading whitespace characters
        char* nonWhitespace = line;
        while (*nonWhitespace && strchr(delimiters, *nonWhitespace))
        {
            nonWhitespace++;
        }
        
        // Tokenize using strtok
        char* token = strtok(nonWhitespace, delimiters);
        
        //Loops through each word
        while (token)
        {
            // Calculate the length of the current token
            tokenLength = strlen(token);
            
            //Checks NULL
            if(token == NULL){
                break;
                //what if +1 is greater but -1 is less than? test case? regarding first if
            }
            //Checks Punctuation
            if (strchr(token, '.') || strchr(token, '?') || strchr(token, '!') || strchr(token, ':')){
                punc = true;
            }
            if(strcmp(token, "@P@") == 0){
                if (!first) {
                    outf << endl; // Separate paragraphs with an empty line
                    first = true;
                }
                remaining = lineLength;
            }
            //Checks Hyphen
            if (strchr(token, '-')){
                isHyphen = true;
            }
            
            //Checks if the word has a punctuation
            if(punc)
            {
                //Checks if it is a first word and token can fit in line
                if(first && tokenLength < lineLength){
                    outf << token;
                    remaining = lineLength;
                    remaining -= (tokenLength);
                    first = false;
                    firstAfter = true;
                    punc = true;
                //Checks if it is a first word and token can't fit in line so gotta wrap
                } else if(first && tokenLength > lineLength){
                    if(tokenLength % lineLength == 0){
                        first = true;
                        firstAfter = false;
                        //punc = false;
                    } else {
                        first = false;
                        firstAfter = true;
                        punc = false;
                    }
                    //wrap
                    while(tokenLength > lineLength){
                        for(int i = 0; i < lineLength; i++){
                            outf << token[i];
                            remaining -= 1;
                        }
                        outf << endl;
                        token += lineLength;
                        tokenLength -= lineLength;
                    }
                    outf << token;
                    remaining = lineLength;
                    remaining -= tokenLength;
                    retVal = 1;
                //Checks if word is less than remaining even with spaces
                } else if ((tokenLength+2 < remaining) || (tokenLength+1 < remaining))
                {
                    if (first && !firstAfter){ //firstAfter is true only when you can write on same line after punctuation, first is true on new line, punc is true after punctuation
                        outf << token;
                        first = false;
                        firstAfter = false;
                        punc = false;
                        remaining -= tokenLength;
                    } else if (!first && firstAfter){
                        outf << "  " << token;
                        first = false;
                        firstAfter = false;
                        punc = false;
                        remaining -= tokenLength+2;
                    } else {
                        outf << " " << token;
                        first = false;
                        firstAfter = true;
                        punc = true;
                        remaining -= tokenLength+1;
                    }
                //Checks if word is equal to remaining
                } else if (tokenLength+1 == remaining)
                {
                    if (first && !firstAfter){
                        outf << token << endl;
                        first = false;
                        firstAfter = false;
                        punc = false;
                        remaining -= tokenLength;
                    }
                    else{
                        outf << " " << token << endl;
                        first = true;
                        firstAfter = false;
                        punc = false;
                        remaining -= tokenLength;
                    }
                }
                //Checks if it is not a first word and is the firstAfter a punctuation and token is exactly remaining
                else if (!first && firstAfter && tokenLength+2 == remaining)
                {
                    outf << "  " << token << endl;
                    first = true;
                    firstAfter = false;
                    punc = false;
                    remaining -= tokenLength+2;
                //Checks if token has to wrap
                } else if (tokenLength > lineLength){
                    if(!first){
                        outf << " ";
                    } else if (firstAfter){
                        outf << "  ";
                    }
                    muchLeft = remaining;
                    //wrap
                    while(tokenLength > lineLength){
                        for(int i = 0; i < remaining; i++){ //remaining
                            outf << token[i];
                            muchLeft--;
                        }
                        outf << endl;
                        token += remaining;
                        tokenLength -= remaining;
                    }
                    remaining = muchLeft;
                    outf << token;
                    firstAfter = true;
                    retVal = 1;
                //Checks if token has to go on next line
                } else if ((tokenLength+1 > remaining)) //added a +1
                {
                    if(first){
                        outf << endl << token;
                        first = false;
                        remaining = lineLength;
                        remaining -= tokenLength; //why +1?
                    } else {
                        outf << endl << token;
                        remaining = lineLength;
                        remaining -= (tokenLength);
                        firstAfter = true; //changed this check it out
                        punc = true;
                        first = false;
                    }
                }
            //If not punctuation
            } else {
                //Checks if token is first and less than line length
                if(first && tokenLength < lineLength){
                    outf << token;
                    remaining = lineLength;
                    remaining -= (tokenLength);
                    first = false;
                //Checks if token is first and greater than line length so we can wrap
                } else if(first && tokenLength > lineLength){
                    if(tokenLength % lineLength == 0){
                        first = true;
                    } else {
                        first = false;
                    }
                    //Wrap
                    while(tokenLength > lineLength){
                        for(int i = 0; i < lineLength; i++){
                            outf << token[i];
                            remaining -= 1;
                        }
                        outf << endl;
                        token += lineLength;
                        tokenLength -= lineLength;
                    }
                    outf << token;
                    remaining = lineLength;
                    remaining -= tokenLength;
                    retVal = 1;
                //check if space and token length can fit in remaining
                } else {
                    if (tokenLength+1 < remaining){
                        outf << " " << token;
                        remaining -= (tokenLength+1);
                    }
                    //check if space and token length can fit in remaining
                    else if (tokenLength+1 == remaining){
                        outf << " " << token << endl;
                        remaining = lineLength;
                        first = true;
                    //check if space and token length have to wrap
                    } else if (tokenLength > lineLength){
                        muchLeft = remaining;
                        //wrap
                        while(tokenLength > lineLength){
                            for(int i = 0; i < remaining; i++){
                                outf << token[i];
                            }
                            outf << endl;
                            token += remaining;
                            tokenLength -= remaining;
                        }
                        remaining = muchLeft;
                        outf << token;
                        retVal = 1;
                    //check if space and token length are greater than remaining so write on a new line
                    } else if (tokenLength+1 > remaining){
                        outf << endl << token;
                        remaining = lineLength;
                        remaining -= (tokenLength);
                    }
                }
            }
                // Get the next token
                token = strtok(nullptr, delimiters);
                
        }
            //Checks for end of file
            if(inf.eof()){
                outf << endl;
            }
        }
        //Returns Value
        return retVal;
    }
    
    
int main()
    {
        testRender(7, "This\n\t\tis a\ntest\n", "This is\na test\n", 0);
        testRender(8, "  This is a test  \n", "This is\na test\n", 0);
        testRender(6, "Testing it\n", "Testin\ng it\n", 1);
        testRender(-5, "irrelevant", "irrelevant", 2);
        cerr << "Tests complete" << endl;
    }
    // /Users/anahitavaidhya/Desktop/UCLA/CS31/AnahitaVaidhya_Project5/data.rtf
    /*
     
     //code that never worked :(
     outf << "2:tokenLength=" << tokenLength << " remaining=" <<remaining;
     if ((tokenLength+2 < remaining) || (tokenLength+1 < remaining))
     {
     if (punc){
     firstAfter = true;
     first = false;
     }
     
     if (first && !firstAfter && !punc){ //firstAfter is true only when you can write on same line after punctuation, first is true on new line, punc is true after punctuation
     outf << token;
     first = false;
     firstAfter = false;
     punc = false;
     remaining -= tokenLength;
     } else if (first && !firstAfter && punc){
     outf << token;
     first = false;
     firstAfter = false;
     punc = false;
     remaining -= tokenLength;
     } else if (!first && firstAfter && punc){
     outf << "  " << token;
     first = false;
     firstAfter = false;
     punc = false;
     remaining -= tokenLength+2;
     }
     
     } else if((tokenLength+2 == remaining) || (tokenLength+1 == remaining)){
     firstAfter = false;
     first = true;
     
     if (first && !firstAfter && !punc){
     outf << token << endl;
     first = true;
     firstAfter = false;
     punc = false;
     remaining -= tokenLength;
     } else if (first && !firstAfter && punc){
     outf << token << endl;
     first = false;
     firstAfter = false;
     punc = false;
     remaining -= tokenLength;
     } else if (!first && firstAfter && punc){
     outf << "  " << token << endl;
     first = false;
     firstAfter = false;
     punc = false;
     remaining -= tokenLength+2;
     } else if (strchr(token, '.') || strchr(token, '?') || strchr(token, '!') || strchr(token, ':')){
     outf << " " << token << endl;
     remaining = lineLength;
     remaining -= (tokenLength);
     first = true;
     punc = true;
     } else if((tokenLength + 2 == remaining) && punc){
     outf << "  " << token << endl;
     remaining = lineLength;
     remaining -= tokenLength+2;
     punc = false;
     } else {
     outf << " " << token << endl;
     remaining = lineLength;
     remaining -= (tokenLength+1); //(+1) ??
     first = true;
     }
     } else if ((tokenLength > remaining)){
     
     
     if(first){
     outf << endl << token;
     first = false;
     remaining = lineLength;
     remaining -= tokenLength; //why +1?
     } else if (strchr(token, '.') || strchr(token, '?') || strchr(token, '!') || strchr(token, ':')){
     outf << endl << token;
     remaining = lineLength;
     remaining -= (tokenLength);
     firstAfter = true;
     punc = true;
     first = false;
     } else if((tokenLength > remaining) && punc){
     outf << endl << token;
     remaining = lineLength;
     remaining -= tokenLength;
     firstAfter = false;
     punc = false;
     first = false;
     } else {
     outf << endl << token;
     remaining = lineLength;
     remaining -= (tokenLength);
     first = false;
     punc = false;
     first = false;
     }
     
     }
     if (first && !firstAfter && !punc){ //firstAfter is true only when you can write on same line after punctuation, first is true on new line, punc is true after punctuation
     outf << token;
     first = false;
     firstAfter = false;
     punc = false;
     remaining -= tokenLength;
     } else if (first && !firstAfter && punc){
     outf << token;
     first = false;
     firstAfter = false;
     punc = false;
     remaining -= tokenLength;
     } else if (!first && firstAfter && punc){
     outf << "  " << token;
     first = false;
     firstAfter = false;
     punc = false;
     remaining -= tokenLength+2;
     }
     //why can't first have punctuation? figure that out afterwards
     else if (strchr(token, '.') || strchr(token, '?') || strchr(token, '!') || strchr(token, ':')){
     //check for last word in line and if it is last word, don't add spaces (figure!!)
     outf << " " << token;
     remaining -= (tokenLength+1);
     firstAfter = true;
     punc = true;
     first = false;
     } else if((tokenLength + 2 <= remaining) && punc){
     outf << "  " << token;
     remaining -= tokenLength + 2;
     punc = false;
     firstAfter = false;
     } else if ((tokenLength + 2 > remaining) && punc){
     outf << endl << token;
     remaining = lineLength;
     remaining -= tokenLength;
     punc = false;
     first = false;
     firstAfter = false;
     } else {
     outf << " " << token;
     remaining -= (tokenLength+1);
     //maybe only count the space before
     //make sure it is not the last in the line (not two spaces at the end)
     }
     } else if ((tokenLength > remaining)){
     if(first){
     outf << endl << token;
     first = false;
     remaining = lineLength;
     remaining -= tokenLength; //why +1?
     } else if (strchr(token, '.') || strchr(token, '?') || strchr(token, '!') || strchr(token, ':')){
     outf << endl << token;
     remaining = lineLength;
     remaining -= (tokenLength);
     firstAfter = true;
     punc = true;
     first = false;
     } else if((tokenLength > remaining) && punc){
     outf << endl << token;
     remaining = lineLength;
     remaining -= tokenLength;
     firstAfter = false;
     punc = false;
     first = false;
     } else {
     outf << endl << token;
     remaining = lineLength;
     remaining -= (tokenLength);
     first = false;
     punc = false;
     first = false;
     }
     } else if ((tokenLength+2 == remaining) || (tokenLength+1 == remaining)) {
     if (first && !firstAfter && !punc){
     outf << token << endl;
     first = true;
     firstAfter = false;
     punc = false;
     remaining -= tokenLength;
     } else if (first && !firstAfter && punc){
     outf << token << endl;
     first = false;
     firstAfter = false;
     punc = false;
     remaining -= tokenLength;
     } else if (!first && firstAfter && punc){
     outf << "  " << token << endl;
     first = false;
     firstAfter = false;
     punc = false;
     remaining -= tokenLength+2;
     } else if (strchr(token, '.') || strchr(token, '?') || strchr(token, '!') || strchr(token, ':')){
     outf << " " << token << endl;
     remaining = lineLength;
     remaining -= (tokenLength);
     first = true;
     punc = true;
     } else if((tokenLength + 2 == remaining) && punc){
     outf << "  " << token << endl;
     remaining = lineLength;
     remaining -= tokenLength+2;
     punc = false;
     } else {
     outf << " " << token << endl;
     remaining = lineLength;
     remaining -= (tokenLength+1); //(+1) ??
     first = true;
     }
     }*/
    
    //if remaining = 0, set remaining to lineLength again

//@P@
/*if(strcmp(token, "@P@") == 0){
     if (!first) {
         outf << endl; // Separate paragraphs with an empty line
     } else {
         //remaining = lineLength;
         first = true;
     }
    remaining = lineLength;
    first = true;
// Handle paragraph break
if (first) {
 outf << endl; // Separate paragraphs with an empty line
 remaining = lineLength;
 first = true;
 } else {
 outf << endl;
 remaining = lineLength;
 remaining = lineLength;
 first = true;
 }
} else {
 outf << endl;
 remaining = lineLength;
 }*/


/*if(numChars < (lineLength - 1)){
 if(numChars)
 }
 
 if(isWhitespace(ch)){
 outf << ' ';
 }
 if(strcmp(word, " @P@ ")){
 outf << endl;
 }
 if(strchr(word, '.') || strchr(word, '?') || strchr(word, '!') || strchr(word, ':')){
 outf << ch << ' ' << ' ';
 }
 if(isalpha(ch)){
 outf << ch;
 }
 if(total > lineLength){
 //strcpy(line, word);
 outf << '\n';
 }*/

/*outf << word;
 //Return 2 if the desired maximum length < 1
 if(lineLength < 1){
 return 2;
 }
 }
 return 0;
 }*/

/*if(isHyphen){
 if(tokenLength <= remaining){
 for(int i = 0; i < tokenLength; i++){
 outf << token[i];
 remaining -= 1;
 }
 } else if (tokenLength > remaining){
 while(tokenLength > lineLength){
 for(int i = 0; i < lineLength; i++){
 outf << token[i];
 remaining -=1;
 }
 if(tokenLength)
 //if(first  && first after @P@ ){
 //outf << token[count];
 //new line for an
 //make a signal earlier to see if it was first word of para, or if previous is @P@
 //decide in next token whether you should start newLine
 //}
 }
 for(int j = 0; j < lineLength; j++){
 if(remaining == 0){
 outf << endl;
 remaining = lineLength;
 
 } else if (tokenLength != 0 && remaining == 0){
 outf << token[j];
 } else {
 outf << token[j];
 remaining -= 1;
 }//make sure hyphen is before ending new line
 }
 }*/

//outf << token[i];
//remaining -= 1;
//if((remaining-1) == 0 && isalnum(token[i+1])){
// outf << token << endl;
//}
//}
/*lineLength = 5
 birth-day
 birth
 -day
 
 bir-day
 bir-
 day
 
 bir-dayshko
 bir-
 daysh
 ko
 
 */

//const char* deHyphen = "-"; // Add space to delimiters
//char* hyphen = strtok(nonWhitespace, deHyphen);

/*if (strchr(token, '-')){
 while(hyphen){
 if(first){
 outf << hyphen;
 first = false;
 }
 outf << "-" << hyphen;
 hyphen = strtok(nullptr, delimiters);
 }
 }*/

/*char* forHyphen = "";
strcpy(forHyphen, nonWhitespace);*/

//char* nextTokenPos = strtok(nullptr, delimiters);
//size_t nextTokenLength = (nextTokenPos) ? strlen(nextTokenPos) : 0;


//Solution
/*// Project 5 -- Word Renderer
 
 #include <iostream>
 #include <fstream>
 #include <cstring>
 #include <cctype>

 using namespace std;

   // render function return values

 const int RENDER_OK = 0;
 const int RENDER_WORD_PORTION_BROKEN = 1;
 const int RENDER_SHORT_LINE_LENGTH = 2;

   // arbitrary values from problem spec

 const int MAX_INPUT_LINE_LEN = 180;

   // paragraph break indicator

 const char PARAGRAPH_BREAK[4] = "@P@";

   // function prototypes

 bool getNextWord(istream& inf, char word[], int wordLimit);
 bool emitWord(ostream& outf, char word[], int lineLen, int& nPrecedingSpaces,
                                                                       int& pos);
 void writeText(ostream& outf, const char word[], int startPos, int len,
                                                 int nPrecedingSpaces, int& pos);
 void writeChar(ostream& outf, char ch, int& pos);

   // render function

 int render(int lineLen, istream& inf, ostream& outf)
 {
     if (lineLen < 1)
         return RENDER_SHORT_LINE_LENGTH;

     char word[MAX_INPUT_LINE_LEN+1];

       // The first word is special, in that no output must appear before it

       // Get first word

     word[0] = '\0';
     while (getNextWord(inf, word, sizeof(word))  &&
                                         strcmp(word, PARAGRAPH_BREAK) == 0)
         ;
     if (word[0] == '\0')
         return RENDER_OK;  // No words in input, so no output at all

     int returnValue = RENDER_OK;
     bool precededByBreak = false;
     int nPrecedingSpaces = 0;
     int pos = 0;  // position of next character to be written on output line

       // Write first word

     if ( ! emitWord(outf, word, lineLen, nPrecedingSpaces, pos))
         returnValue = RENDER_WORD_PORTION_BROKEN;

       // Process each subsequent input word until end of file

     while (getNextWord(inf, word, sizeof(word)))
     {
         if (strcmp(word, PARAGRAPH_BREAK) == 0)
             precededByBreak = true;
         else // it's an input word
         {
               // Handle end/start of paragraph

             if (precededByBreak)
             {
                 writeChar(outf, '\n', pos);  // end current line
                 writeChar(outf, '\n', pos);  // empty line between paragraphs
                 nPrecedingSpaces = 0;
             }

               // Write word along with any preceding spaces

             if ( ! emitWord(outf, word, lineLen, nPrecedingSpaces, pos))
                 returnValue = RENDER_WORD_PORTION_BROKEN;
         }
     }

     writeChar(outf, '\n', pos);  // end last line

     return returnValue;
 }

   // getNextWord function
   //   If there is no next word (end of file encountered), return false.
   //   Otherwise, put the next word in the word array (a word that is too
   //   long is silently truncated) and return true.

 bool getNextWord(istream& inf, char word[], int wordLimit)
 {
       // skip whitespace

     char ch;
     do
     {
         if ( ! inf.get(ch))
             return false;
     } while (isspace(ch));

       // accumulate nonwhitespace characters into word

     int pos = 0;
     do
     {
           // store the character if there's room for it and the eventual '\0'

         if (pos < wordLimit-1)
         {
             word[pos] = ch;
             pos++;
         }
     } while(inf.get(ch)  &&  ! isspace(ch));
     if (wordLimit > 0)
         word[pos] = '\0';

     return true;
 }

   // emitWord function
   //   write a word along with any preceding space.  Split the word if
   //   necessary.  Update the current output line position.

 bool emitWord(ostream& outf, char word[], int lineLen, int& nPrecedingSpaces,
                                                                 int& pos)
 {
     bool returnValue = true;  // will set to false if long word was split

       // At all times, the remaining part of the word to write will start
       // at position wordStart of the word array, and extend for wordLen
       // characters.

     int wordStart = 0;
     int wordLen = strlen(word);

       // Repeat as long as the remaining part of the word won't fit

     while (pos + nPrecedingSpaces + wordLen > lineLen)
     {
           // See if there's a hyphen in the part that fits

         int firstPartLen;
         for (firstPartLen = lineLen - (pos + nPrecedingSpaces);
               firstPartLen > 0  &&  word[wordStart + firstPartLen-1] != '-';
                                                                firstPartLen--)
             ;
         int segmentLen = 0;  // length of part of word to be written
         if (firstPartLen > 0)
             segmentLen = firstPartLen;
         else if (pos + nPrecedingSpaces == 0)  // portion too long
         {
             segmentLen = lineLen;  // will write as much as fits
             returnValue = false;
         }

           // Write segment of word and determine remaining part of word

         if (segmentLen > 0)
         {
             writeText(outf, word, wordStart, segmentLen, nPrecedingSpaces, pos);
             wordStart += segmentLen;
             wordLen -= segmentLen;
         }

           // Write newline; remaining part of word will start on next line

         writeChar(outf, '\n', pos);
         nPrecedingSpaces = 0;
     }

       // Remaining part of word fits, so write it

     writeText(outf, word, wordStart, wordLen, nPrecedingSpaces, pos);

       // Set nPrecedingSpaces for next word to be emitted

     char lastChar = word[wordStart + wordLen-1];
     if (lastChar == '.'  ||  lastChar == '?'  ||  lastChar == '!'  ||  lastChar == ':')
         nPrecedingSpaces = 2;
     else
         nPrecedingSpaces = 1;

     return returnValue;
 }

   // writeText function
   //   write text from a word, preceded by spaces.  Update output line position.

 void writeText(ostream& outf, const char word[], int startPos, int len,
                                                 int nPrecedingSpaces, int& pos)
 {
     for ( ; nPrecedingSpaces > 0; nPrecedingSpaces--)
         writeChar(outf, ' ', pos);
     for (int k = startPos; k < startPos + len; k++)
         writeChar(outf, word[k], pos);
 }

   // writeChar function
   //   write one character.  Update output line position.

 void writeChar(ostream& outf, char ch, int& pos)
 {
     outf << ch;
     if (ch == '\n')
         pos = 0;
     else
         pos++;
 }

   // test driver for render function

 int main()
 {
     for (;;)
     {
         cout << "Enter an input filename (or empty line to quit): ";
         char inputFilename[500];
         cin.getline(inputFilename, sizeof(inputFilename));
         if (inputFilename[0] == '\0')
             break;
         ifstream inf(inputFilename);
         if ( ! inf)
         {
             cerr << "Cannot open " << inputFilename << endl;
             continue;
         }

         cout << "Enter a line length: ";
         int lineLen;
         cin >> lineLen;
         cin.ignore(10000, '\n');

         cout << "Enter an output filename (or empty line for the screen): ";
         char outputFilename[500];
         cin.getline(outputFilename, sizeof(outputFilename));
         int returnValue;
         if (outputFilename[0] == '\0')
             returnValue = render(lineLen, inf, cout);
         else
         {
             ofstream outf(outputFilename);
             if ( ! outf)
             {
                 cerr << "Cannot create " << outputFilename << endl;
                 continue;
             }
             returnValue = render(lineLen, inf, outf);
         }

         cout << "render returned " << returnValue << endl;
     }
 }*/

//Test Cases
/*There were 42 test cases; the first 41 were worth 2.073 points each; the last was the bonus, worth 5 points if you passed that test and at least 36 of all the others. Each test case is represented by an assertion that must be true for you to pass that test. Each test case was run independently. We renamed your main routine to something harmless, and appended this code to your program:
 
 #include <iostream>
 #include <sstream>
 #include <streambuf>
 #include <string>
 #include <cassert>
 using namespace std;

 class LimitOutputStreambuf : public streambuf
 {
     public:
         LimitOutputStreambuf(streambuf* sb, size_t lim)
          : real_streambuf(sb), limit(lim)
         {
                 static char dummy;
                 setp(&dummy, &dummy);
         }
     private:
         streambuf* real_streambuf;
         size_t limit;

         int overflow(int c)
         {
                 if (limit == 0)
                         return traits_type::eof();
                 limit--;
                 return real_streambuf->sputc(c);
         }
 };

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

 string repeat(size_t n, string s)
 {
     string result;
     result.reserve(n * s.size());
     for ( ; n > 0; n--)
         result += s;
     return result;
 }

 int render(int lineLength, istream& inf, ostream& outf);

 void testone(int n)
 {
     istringstream iss;
     StreambufSwitcher ssi(cin, iss.rdbuf());

     ostringstream oss;
     LimitOutputStreambuf lob(oss.rdbuf(), 1000*1000+10);
     StreambufSwitcher sso(cout, &lob);

     LimitOutputStreambuf lob2(cerr.rdbuf(), 0);
     StreambufSwitcher sse(cerr, &lob2);

     switch (n)
     {
                                  default: {
         cout << "Bad argument" << endl;
                         } break; case  1: {
         iss.str("hello there\n\nthis is a test\n");
         assert(render(0, iss, oss) == 2);
                         } break; case  2: {
         iss.str("hello there\n\nthis is a test\n");
         render(0, iss, oss);
         assert(oss.str().empty());
                         } break; case  3: {
         iss.str("hello there\n\nthis is a test\n");
         ostringstream oss2;
         StreambufSwitcher sso2(cout, oss2.rdbuf());
         render(11, iss, oss);
         assert(oss2.str().empty());
                         } break; case  4: {
         iss.str("hello there\n\nthis is a test\n");
         istringstream iss2("Z Y X W V\n");
         StreambufSwitcher ssi2(cin, iss2.rdbuf());
                 render(11, iss, oss);
         string s = oss.str();
         assert(s.find_first_of("ZYXWV") == string::npos  &&
         s.find("hello") != string::npos);
                         } break; case  5: {
         iss.str("");
         assert(render(10, iss, oss) == 0  &&  oss.str().empty());
                         } break; case  6: {
         iss.str("     \n\n    \n\n");
         assert(render(10, iss, oss) == 0  &&  oss.str().empty());
                         } break; case  7: {
         iss.str("abcdefghi abcdefghijk\n");
         assert(render(10, iss, oss) == 1);
                         } break; case  8: {
         iss.str("abcdefghi abcdefghijk abc abc abc abc abc abc abc\n");
         assert(render(10, iss, oss) == 1);
                         } break; case  9: {
         iss.str("abcdefghi abcdefghij\n");
         assert(render(10, iss, oss) == 0);
                         } break; case 10: {
         iss.str("abcdefghi abcdefgh-ijk\n");
         assert(render(10, iss, oss) == 0);
                         } break; case 11: {
         iss.str("hello there\n");
         render(30, iss, oss);
         assert(oss.str().find("hello there") != string::npos);
                         } break; case 12: {
         iss.str("hello       there\n");
         render(30, iss, oss);
         assert(oss.str().find("hello there") != string::npos);
                         } break; case 13: {
         iss.str("hello. there? bye\n");
         render(30, iss, oss);
         assert(oss.str().find("hello.  there?  bye") != string::npos);
                         } break; case 14: {
         iss.str("hello! there: bye\n");
         render(30, iss, oss);
         assert(oss.str().find("hello!  there:  bye") != string::npos);
                         } break; case 15: {
         iss.str("hello? there\n");
         render(30, iss, oss);
         assert(oss.str().find("hello?  there") != string::npos);
                         } break; case 16: {
         iss.str("hello. abcdefghi\n");
         render(10, iss, oss);
         assert(oss.str().find("hello.\na") != string::npos);
                         } break; case 17: {
         iss.str("hello.there\n");
         render(30, iss, oss);
         assert(oss.str().find("hello.there") != string::npos);
                         } break; case 18: {
         iss.str("hello'3*%there\n");
         render(30, iss, oss);
         assert(oss.str().find("hello'3*%there") != string::npos);
                         } break; case 19: {
         iss.str("hello-there\n");
         render(30, iss, oss);
         assert(oss.str().find("hello-there") != string::npos);
                         } break; case 20: {
         iss.str("hello\nthere\n");
         render(30, iss, oss);
         assert(oss.str().find("hello there") != string::npos);
                         } break; case 21: {
         iss.str("abcdefg hijkl\n");
         render(10, iss, oss);
         assert(oss.str().find("abcdefg\n") != string::npos);
                         } break; case 22: {
         iss.str("abcdefg hijkl\n");
         render(10, iss, oss);
         assert(oss.str().find("\nhijkl") != string::npos);
                         } break; case 23: {
         iss.str("hellohello abcdef ghi jklmnop\n");
         render(10, iss, oss);
         assert(oss.str().find("\nabcdef ghi\n") != string::npos);
                         } break; case 24: {
         iss.str("hellohello abcdef ghi jklmnop qrst\n");
         render(10, iss, oss);
         assert(oss.str().find("\nqrst") != string::npos);
                         } break; case 25: {
         iss.str("abcdefg x-ray\n");
         render(10, iss, oss);
         assert(oss.str().find("x-\nray") != string::npos);
                         } break; case 26: {
         iss.str("abcdefg abc xyz-pq-rs\n");
         render(10, iss, oss);
         assert(oss.str().find("xyz-\npq-rs") != string::npos);
                         } break; case 27: {
         iss.str("abcdefg abc x-yz-pqr\n");
         render(10, iss, oss);
         assert(oss.str().find("x-yz-\npqr") != string::npos);
                         } break; case 28: {
         iss.str("abcdefg abc xyz----yz\n");
         render(10, iss, oss);
         assert(oss.str().find("xyz---\n-yz") != string::npos);
                         } break; case 29: {
         iss.str("abcdefg -xyz\n");
         render(10, iss, oss);
         assert(oss.str().find(" -\nxyz") != string::npos);
                         } break; case 30: {
         iss.str("abcdefg abc abcdefghijklmnopqrstuvw\n");
         render(10, iss, oss);
         assert(oss.str().find("\nabcdefghij\nklmnopqrst\nuvw") != string::npos);
                         } break; case 31: {
         iss.str("abc\n");
         render(10, iss, oss);
         assert(oss.str() == "abc\n");
                         } break; case 32: {
         iss.str("abc @P@ def\n");
         render(10, iss, oss);
         assert(oss.str().find("abc\n\ndef") != string::npos);
                         } break; case 33: {
         iss.str("abc @P@  @P@ def\n");
         render(10, iss, oss);
         assert(oss.str().find("abc\n\ndef") != string::npos);
                         } break; case 34: {
         iss.str("abc\n@P@\ndef\n");
         render(10, iss, oss);
         assert(oss.str().find("abc\n\ndef") != string::npos);
                         } break; case 35: {
         iss.str("@P@ abc @P@ def\n");
         render(10, iss, oss);
         string result("abc\n\ndef\n");
         assert(oss.str() == result  ||
                 result.compare(0, 8, oss.str()) == 0);
                         } break; case 36: {
         iss.str("abc @P@ def\n@P@\n");
         render(10, iss, oss);
         assert(oss.str() == "abc\n\ndef\n");
                         } break; case 37: {
         iss.str("@P@ @P@ @P@ abc @P@ def @P@ @P@ @P@\n");
         render(30, iss, oss);
         assert(oss.str() == "abc\n\ndef\n");
                         } break; case 38: {
         string s25 = "abcdefghijklmnopqrstuvwxy";
         string s178(repeat(7, s25) + "abc");
         iss.str(s178 + "\n");
         assert(render(179, iss, oss) == 0);
         string result(s178 + "\n");
         assert(oss.str() == result  ||
                 result.compare(0, 178, oss.str()) == 0);
                         } break; case 39: {
         string s24 = "abcdefghijklmnopqrstuvwx";
         string s123(repeat(5, s24) + "abc");
         iss.str(s123 + "\n" + s123 + "\n");
         assert(render(249, iss, oss) == 0);
         string result(s123 + " " + s123 + "\n");
         assert(oss.str() == result  ||
                 result.compare(0, 247, oss.str()) == 0);
                         } break; case 40: {
         string s10 = "a\na\na\na\na\na\na\na\na\na\n";
         string s100(repeat(10, s10));
         string s20000(repeat(200, s100)); // For some people, 200 was 20000
         iss.str(s20000);
         render(2, iss, oss);
         assert(oss.str() == s20000  ||
                 s20000.compare(0, 19999, oss.str()) == 0);
                         } break; case 41: {
         string s25 = "abcdefghijklmnopqrstuvwxy";
         string s178(repeat(7, s25) + "abc");
         iss.str(repeat(11, s178 + "\n"));
         int n = render(2000, iss, oss);
         string result(repeat(11-1, s178 + " ") + s178 + "\n");
         assert((n == 2  &&  oss.str().empty())  ||  (n == 0  &&
                 (oss.str() == result  ||
                  result.compare(0, 11*(178+1)-1, oss.str()) == 0)));
                         } break; case 42: {
         string s25 = "abcdefghijklmnopqrstuvwxy";
         string s178(repeat(7, s25) + "abc");
         iss.str(repeat(550, s178 + "\n"));
         assert(render(99000, iss, oss) == 0);
         string result(repeat(550-1, s178 + " ") + s178 + "\n");
         assert(oss.str() == result  ||
                  result.compare(0, 550*(178+1)-1, oss.str()) == 0);
                         } break;
     }
 }

 int main()
 {
     cout << "Enter test number: ";
     int n;
     cin >> n;
     testone(n);
     cout << "Passed" << endl;
 }*/
