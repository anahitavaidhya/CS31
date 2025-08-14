//
//  array.cpp
//  AnahitaVaidhya_Project4
//
//  Created by Anahita Vaidhya on 11/6/23.
//

//Libraries and Namespaces
#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <cassert>
using namespace std;

/*all functions that return an int must return −1 if they are passed any bad arguments (e.g. a negative array size, or a position that would require looking at the contents of an element past the last element we're interested in). Unless otherwise noted, passing 0 to the function as the array size is not itself an error; it merely indicates the function should examine no elements of the array.*/

//Reduplicate Function
int reduplicate(string a[], int n){
    //Check if arguments are valid
    if(n < 0){
        return -1;
    }
    
    //For loop to duplicate each index in the array
    for(int i = 0; i < n; i++){
        a[i] = a[i] + a[i];
    }
    
    for(int i = 0; i < n; i++){
        //cout << a[i] << endl;
    }
    return n;
}

int locate(const string a[], int n, string target){
    //Check if valid argument
    if(n < 0){
        return -1;
    }
    
    //For loop to check if there is any index in the array equal to target (returns smallest index)
    for(int i = 0; i < n; i++){
        if(a[i] == target){
            return i;
        }
    }
    
    //If no string equal to target
    return -1;
}

int locationOfMax(const string a[], int n){
    //Check if valid arguments passed
    if(n <= 0){
        return -1;
    }
    
    //Variables
    string store = "";
    int minInd = 0;
    int pos = 0;
    bool isNotRepeat=false;
    
    //Check every index to see which one is the latest in alphabetic order
    for(int i = pos; i < n; i=i+pos){
        for(int j = i + 1; j < n; j++){
            if(a[i] < a[j]){
                minInd = j;
            } else if (a[i] == a[j] && isNotRepeat==false){
                minInd = i;
                pos = j;
                isNotRepeat = true;
                break;
            } else if (a[i] > a[j]) {
                if (isNotRepeat == false)
                {
                    minInd = i;
                }
                pos = i;
            }
        }
    }
    
    return minInd;
}

int circleLeft(string a[], int n, int pos){
    //Variables
    string store = a[pos];
    string temp = "";
    
    //Check if arguments are correct
    if(n <= 0){
        return -1;
    }
    
    //Moves each index to the left
    for(int i = pos; i < n-1; i++){
        a[i] = a[i+1];
    }
    //Sets last index to position
    a[n-1] = store;
    
    return pos;
}

int enumerateRuns(const string a[], int n){
    //Variables
    int count = 0;
    int pos = 0;
    bool isCounted = false;
    
    //Check if arguments are correct
    if(n <= 0){
        return -1;
    }
    
    //Running two loops to check for new one or more consecutive items
    for(int i = pos; i < n; i++){
        for(int j = pos + 1; j < n; j++){
            //New run
            if(a[i] != a[j]){
                count++;
                pos = j;
                break;
            //New run when same element first time
            } else if (a[i] == a[j] && isCounted == false){
                isCounted = true;
                count++;
                pos = j;
                break;
            }
            //Don't count because same run
            else if (a[i] == a[j] && isCounted == true){
                pos = j;
                break;
            }
        }
        
    }
    return count;
}

int flip(string a[], int n){
    //Variables
    string store = "";
    
    //Check if arguments are valid
    if(n <= 0){
        return -1;
    }
    
    //Run through half the array and flip values
    for(int i = 0; i < n/2; i++){
        store = a[i];
        a[i] = a[n-(i+1)];
        a[n-(i+1)] = store;
    }
    
    return n;
}

int locateDifference(const string a1[], int n1, const string a2[], int n2){
    //Check if n1 is valid
    if(n1 <= 0){
        return -1;
    }
    //Check if n2 is valid
    if(n2 <= 0){
        return -1;
    }
    
    //Run through only n1 times to check for differences
    if(n1 < n2){
        for(int i = 0; i < n1; i++){
            if(a1[i] != a2[i])
                return i;
        }
    //Run through n2 times to check for differences
    } else if (n1 > n2){
        for(int i = 0; i < n2; i++){
            if(a1[i] != a2[i])
                return i;
        }
    //Run through either n1 or n2 times, doesn't matter bc =, to check for differences
    } else if (n1 == n2){
        for(int i = 0; i < n2; i++){
            if(a1[i] != a2[i])
                return i;
            }
    }
    
    //Return whichever value of n1 and n2 is less than or equal to the other
    if(n1 <= n2){
        return n1;
    } else {
        return n2;
    }
    
    return 0;
}

int subsequence(const string a1[], int n1, const string a2[], int n2)
{
    //Variables
    int count = 0;
    int store = 0;
    bool sameStrVal = true;
    //Check if n1 is valid
    if(n1 <= 0){
        return -1;
    }
    //Check if n2 is valid
    if(n2 <= 0){
        return -1;
    }
    
    //Run through only n1 times to check for consecutive and identical
    if(n1 < n2){
        for(int i = 0; i < n1; i++){
            for(int j = 0; j < n1; j++){
                if(a1[i] != a2[j]){
                    sameStrVal = false;
                    break;
                } else if (a1[i] == a2[j]){
                    sameStrVal = true;
                }
            }
            if(sameStrVal){
                return i;
            }
        }
    //Run through only n2 times to check for consecutive and identical
    } else if (n1 > n2){
        for(int i = 0; i < n1-n2; i++){
            for(int j = 0; j < n2; j++){
                if(a1[i+j] != a2[j]){
                    sameStrVal = false;
                    break;
                } else if (a1[i] == a2[j]){
                    sameStrVal = true;
                }
                
            }
            if(sameStrVal){
                return i;
            }
        }
    //Run through either n1 or n2 times to check for consecutive and identical
    } else if (n1 == n2){
        for(int i = 0; i < n1; i++){
            if(a1[i] == a2[i]){
                sameStrVal = true;
                //store = i;
                //count++;
                break;
            }
            if(sameStrVal){
                return i;
            }
        }
        
    }
    
    //cout << count << endl;
    if(count > 0){
        //cout << "in store :" << store << endl;
        return store;
    } else {
        return -1;
    }
}

int locateAny(const string a1[], int n1, const string a2[], int n2){
    //Check if n1 is valid
    if(n1 <= 0){
        return -1;
    }
    //Check if n2 is valid
    if(n2 <= 0){
        return -1;
    }
    
    //Go through loop to check if any of the a1 values are equal to a2
    for(int i = 0; i < n1; i++){
        for(int j = 0; j < n2; j++){
            if(a1[i] == a2[j]){
                return i;
            }
        }
    }
    //None are equal
    return -1;
}

int divide(string a[], int n, string divider){
    //Variables
    string store = "";
    int count = 1;
    int ind = 0;
    
    //Check if arguments are valid
    if(n <= 0){
        return -1;
    }
    
    //While loop goes through multiple times until the array is sorted so that it's divided properly
    while(count >= 1){
        count = 0;
        for(int i = 0; i < n-1; i++){
            if(a[i] > divider && a[i+1] < divider){
                store = a[i];
                a[i] = a[i+1];
                a[i+1] = store;
                count++;
            }
        }
    }
    
    //Checking for the element when a[i] is greater than divider and returning that OR nothing divided and returns n
    for(int i = 0; i < n; i++){
        if(a[i] > divider){
            ind = i;
            break;
        } else {
            ind = n;
        }
    }

    return ind;
}


//int main() {
//    string h[7] = { "nikki", "ron", "asa", "vivek", "", "chris", "donald" };
//    /*int j = locationOfMax(h, 7);
//    cout << j;*/
//            /*assert(locate(h, 7, "chris") == 5);
//            assert(locate(h, 7, "asa") == 2);
//            assert(locate(h, 2, "asa") == -1);
//            **assert(locationOfMax(h, 7) == 3);*/
//    
//            string g[4] = { "nikki", "ron", "chris", "tim" };
//            
//            /*assert(locateDifference(h, 4, g, 4) == 2);
//            assert(circleLeft(g, 4, 1) == 1 && g[1] == "chris" && g[3] == "ron");*/
//
//            string c[4] = { "ma", "can", "tu", "do" };
//            /*assert(reduplicate(c, 4) == 4 && c[0] == "mama" && c[3] == "dodo");*/
//    /*int j = reduplicate(c, 4);
//    cout << j;*/
//    
//            string e[4] = { "asa", "vivek", "", "chris" };
//            //assert(subsequence(h, 7, e, 4) == 2);
//
//            string d[5] = { "ron", "ron", "ron", "chris", "chris" };
//            //assert(enumerateRuns(d, 5) == 2);
//    
//        
//            string f[3] = { "vivek", "asa", "tim" };
//            //assert(locateAny(h, 7, f, 3) == 2);
//            //assert(flip(f, 3) == 3 && f[0] == "tim" && f[2] == "vivek");
//   
//            //assert(divide(h, 7, "donald") == 3);
//            cout << "All tests succeeded" << endl;
//}
//
string c[6] = {
    "alpha", "beta", "beta", "delta", "gamma", "gamma"
};

bool dividecheck(const string a[], int n, int p, string divider)
{
    for (int k = 0; k < p; k++)
        if (a[k] >= divider)
            return false;
    for ( ; p < n  &&  a[p] == divider; p++)
        ;
    for (int k = p; k < n; k++)
        if (a[k] <= divider)
            return false;
    string b[100];
    copy(a, a+n, b);
    sort(b, b+n);
    return equal(b, b+n, c);
}

void testone(int n)
{
    const int N = 6;

    string aa[1+N+1] = {
        "", "alpha", "beta", "gamma", "gamma", "beta", "delta", ""
    };
    string* a = &aa[1];
    string* z = aa;
    a[-1].string::~string();
    a[N].string::~string();
    fill_n(reinterpret_cast<char*>(&a[-1]), sizeof(a[-1]), 0xEF);
    fill_n(reinterpret_cast<char*>(&a[N]), sizeof(a[N]), 0xEF);

    string b[N] = {
        "alpha", "beta", "gamma", "delta", "beta", "delta"
    };

    string d[9] = {
        "alpha", "beta",  "beta", "beta", "alpha",
        "alpha", "delta", "beta", "beta"
    };

    switch (n)
    {
                     case  1: {
        assert(reduplicate(z, -1) == -1 && a[0] == "alpha");
            } break; case  2: {
        assert(reduplicate(z, 0) == 0 && a[0] == "alpha");
            } break; case  3: {
        assert(reduplicate(a, 1) == 1 && a[0] == "alphaalpha" &&
                            a[1] == "beta");
            } break; case  4: {
        a[4] = "";
        assert(reduplicate(a, 6) == 6 && a[0] == "alphaalpha" &&
            a[1] == "betabeta" && a[2] == "gammagamma" &&
            a[3] == "gammagamma" && a[4] == "" &&  a[5] == "deltadelta");
            } break; case  5: {
        assert(locate(z, -1, "alpha") == -1);
            } break; case  6: {
        assert(locate(z, 0, "alpha") == -1);
            } break; case  7: {
        assert(locate(a, 1, "alpha") == 0);
            } break; case  8: {
        assert(locate(a, 6, "delta") == 5);
            } break; case  9: {
        assert(locate(a, 6, "beta") == 1);
            } break; case 10: {
        assert(locate(a, 6, "zeta") == -1);
            } break; case 11: {
        assert(locationOfMax(z, -1) == -1);
            } break; case 12: {
        assert(locationOfMax(z, 0) == -1);
            } break; case 13: {
        assert(locationOfMax(a, 1) == 0);
            } break; case 14: {
        assert(locationOfMax(a, 3) == 2);
            } break; case 15: {
        assert(locationOfMax(a, 6) == 2);
            } break; case 16: {
        assert(locationOfMax(a+3, 3) == 0);
            } break; case 17: {
        a[0] = "";
        a[1] = " ";
        a[2] = "";
        assert(locationOfMax(a, 3) == 1);
            } break; case 18: {
        assert(circleLeft(z, -1, 0) == -1 &&
                a[0] == "alpha" && a[1] == "beta");
            } break; case 19: {
        assert(circleLeft(a, 6, -1) == -1 &&
            a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
            a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
            } break; case 20: {
        assert(circleLeft(a, 6, 6) == -1 &&
            a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
            a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
            } break; case 21: {
        assert(circleLeft(z, 0, 0) == -1 &&
                a[0] == "alpha" && a[1] == "beta");
            } break; case 22: {
        assert(circleLeft(a, 1, 0) == 0 &&
                a[0] == "alpha" && a[1] == "beta");
            } break; case 23: {
        assert(circleLeft(a, 6, 0) == 0 &&
            a[0] == "beta" && a[1] == "gamma" && a[2] == "gamma" &&
            a[3] == "beta" && a[4] == "delta" && a[5] == "alpha");
            } break; case 24: {
        assert(circleLeft(a, 6, 5) == 5 &&
            a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
            a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
            } break; case 25: {
        assert(circleLeft(a, 6, 3) == 3 &&
            a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
            a[3] == "beta" && a[4] == "delta" && a[5] == "gamma");
            } break; case 26: {
        assert(circleLeft(a, 5, 3) == 3 &&
            a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
            a[3] == "beta" && a[4] == "gamma" && a[5] == "delta");
            } break; case 27: {
        assert(enumerateRuns(z, -1) == -1);
            } break; case 28: {
        assert(enumerateRuns(z, 0) == 0);
            } break; case 29: {
        assert(enumerateRuns(a, 1) == 1);
            } break; case 30: {
        assert(enumerateRuns(a, 3) == 3);
            } break; case 31: {
        assert(enumerateRuns(a, 4) == 3);
            } break; case 32: {
        assert(enumerateRuns(a+2, 4) == 3);
            } break; case 33: {
        assert(enumerateRuns(d, 9) == 5);
            } break; case 34: {
        assert(flip(z, -1) == -1 && a[0] == "alpha");
            } break; case 35: {
        assert(flip(z, 0) == 0 && a[0] == "alpha");
            } break; case 36: {
        assert(flip(a, 1) == 1 && a[0] == "alpha" &&
                    a[1] == "beta");
            } break; case 37: {
        assert(flip(a, 2) == 2 && a[0] == "beta" &&
                    a[1] == "alpha" && a[2] == "gamma");
            } break; case 38: {
        assert(flip(a, 5) == 5 && a[0] == "beta" &&
            a[1] == "gamma" && a[2] == "gamma" && a[3] == "beta" &&
            a[4] == "alpha" && a[5] == "delta");
            } break; case 39: {
        a[2] = "zeta";
        assert(flip(a,6) == 6 && a[0] == "delta" && a[1] == "beta" &&
            a[2] == "gamma" && a[3] == "zeta" && a[4] == "beta" &&
            a[5] == "alpha");
            } break; case 40: {
        assert(locateDifference(z, -1, b, 6) == -1);
            } break; case 41: {
        assert(locateDifference(a, 6, z, -1) == -1);
            } break; case 42: {
        assert(locateDifference(z, 0, b, 0) == 0);
            } break; case 43: {
        assert(locateDifference(a, 3, b, 3) == 3);
            } break; case 44: {
        assert(locateDifference(a, 3, b, 2) == 2);
            } break; case 45: {
        assert(locateDifference(a, 2, b, 3) == 2);
            } break; case 46: {
        assert(locateDifference(a, 6, b, 6) == 3);
            } break; case 47: {
        assert(subsequence(z, -1, b, 6) == -1);
            } break; case 48: {
        assert(subsequence(a, 6, z, -1) == -1);
            } break; case 49: {
        assert(subsequence(z, 0, b, 6) == -1);
            } break; case 50: {
        assert(subsequence(a, 6, z, 0) == 0);
            } break; case 51: {
        assert(subsequence(a, 6, b, 1) == 0);
            } break; case 52: {
        assert(subsequence(a, 6, b+4, 2) == 4);
            } break; case 53: {
        assert(subsequence(a, 6, b+3, 1) == 5);
            } break; case 54: {
        assert(subsequence(a, 6, b+3, 2) == -1);
            } break; case 55: {
        assert(subsequence(a, 6, b+2, 2) == -1);
            } break; case 56: {
        assert(subsequence(a, 6, a, 6) == 0);
            } break; case 57: {
        assert(locateAny(a, 6, z, -1) == -1);
            } break; case 58: {
        assert(locateAny(z, -1, b, 6) == -1);
            } break; case 59: {
        assert(locateAny(z, 0, b, 1) == -1);
            } break; case 60: {
        assert(locateAny(a, 6, z, 0) == -1);
            } break; case 61: {
        assert(locateAny(a, 1, b, 1) == 0);
            } break; case 62: {
        assert(locateAny(a, 6, b+3, 3) == 1);
            } break; case 63: {
        assert(locateAny(a, 4, b+3, 3) == 1);
            } break; case 64: {
        assert(locateAny(a, 2, b+2, 2) == -1);
            } break; case 65: {
        assert(divide(z, -1, "beta") == -1 &&
            a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
            a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
            } break; case 66: {
        assert(divide(z, 0, "beta") == 0 &&
            a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
            a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
            } break; case 67: {
        assert(divide(a, 1, "aaa") == 0 &&
            a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
            a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
            } break; case 68: {
        assert(divide(a, 1, "alpha") == 0 &&
            a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
            a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
            } break; case 69: {
        assert(divide(a, 1, "zeta") == 1 &&
            a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
            a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
            } break; case 70: {
        assert(divide(a, 2, "aaa") == 0 &&
            dividecheck(a, 2, 0, "aaa") && a[2] == "gamma" &&
            a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
            } break; case 71: {
        assert(divide(a, 2, "alpha") == 0 &&
            dividecheck(a, 2, 0, "alpha") && a[2] == "gamma" &&
            a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
            } break; case 72: {
        assert(divide(a, 2, "beta") == 1 &&
            dividecheck(a, 2, 1, "beta") && a[2] == "gamma" &&
            a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
            } break; case 73: {
        assert(divide(a, 2, "zeta") == 2 &&
            dividecheck(a, 2, 2, "zeta") && a[2] == "gamma" &&
            a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
            } break; case 74: {
        assert(divide(a, 6, "aaa") == 0 && dividecheck(a, 6, 0, "aaa"));
            } break; case 75: {
        assert(divide(a, 6, "alpha") == 0 &&
            dividecheck(a, 6, 0, "alpha"));
            } break; case 76: {
        assert(divide(a, 6, "beta") == 1 &&
            dividecheck(a, 6, 1, "beta"));
            } break; case 77: {
        assert(divide(a, 6, "delta") == 3 &&
            dividecheck(a, 6, 3, "delta"));
            } break; case 78: {
        assert(divide(a, 6, "gamma") == 4 &&
            dividecheck(a, 6, 4, "gamma"));
            } break; case 79: {
        assert(divide(a, 6, "zeta") == 6 &&
            dividecheck(a, 6, 6, "zeta"));
            } break; case 80: {
        a[2] = "mu";
        c[5] = "mu";
        assert(divide(a, 6, "mu") == 5 && dividecheck(a, 6, 5, "mu"));
            } break; case 81: {
        assert(divide(a, 6, "chi") == 3 && dividecheck(a, 6, 3, "chi"));
            } break; case 82: {
          // To earn the bonus point for circleLeft, this and all other
          // circleLeft tests must pass, and that function must not
          // use any additional arrays.
        const int BIG = 500;
        string h[BIG];
        for (int k = 0; k < BIG; k++)
            h[k] = (k % 2 == 0 ? "alpha" : "beta");
        h[BIG-2] = "gamma";
        h[BIG-1] = "delta";
        circleLeft(h, BIG, 0);
        assert(h[BIG-3] == "gamma"  &&  h[BIG-2] == "delta");
            } break; case 83: {
          // To earn the bonus point for flip, this and all other
          // flip tests must pass, and that function must not
          // use any additional arrays.
        const int BIG = 500;
        string h[BIG];
        for (int k = 0; k < BIG; k++)
            h[k] = (k % 2 == 0 ? "alpha" : "beta");
        h[0] = "gamma";
        h[BIG-1] = "delta";
        flip(h, BIG);
        assert(h[0] == "delta"  &&  h[BIG-1] == "gamma");
            } break; case 84: {
          // To earn the bonus point for divide, this and all other
          // divide tests must pass, and that function must not
          // use any additional arrays.
        const int BIG = 500;
        string h[BIG];
        string i[3] = { "alpha", "beta", "gamma" };
        for (int k = 0; k < BIG; k++)
            h[k] = i[k % 3];
        divide(h, BIG, "beta");
        int m;
        for (m = 0; m < (BIG+2)/3; m++)
            assert(h[m] == "alpha");
        for ( ; m < 2*(BIG+1)/3; m++)
            assert(h[m] == "beta");
        for ( ; m < BIG; m++)
            assert(h[m] == "gamma");
            } break;
    }

    new (&a[-1]) string;
    new (&a[N]) string;
}

int main()
{
    cout << "Enter a test number (1 to 84): ";
    int n;
    cin >> n;
    if (n < 1  ||  n > 84)
    {
    cout << "Bad test number" << endl;
    return 1;
    }
    testone(n);
    cout << "Passed test " << n << endl;
}


//Solution
/*// Project 4 Solution
 
 #include <string>

 using namespace std;

 void exchange(string& s1, string& s2)
 {
     string t = s1;
     s1 = s2;
     s2 = t;
 }

 int reduplicate(string a[], int n)
 {
     if (n < 0)
         return -1;
     for (int k = 0; k < n; k++)
         a[k] += a[k];
     return n;
 }

 int locate(const string a[], int n, string target)
 {
     if (n < 0)
         return -1;
     for (int k = 0; k < n; k++)
         if (a[k] == target)
             return k;
     return -1;
 }

 int locationOfMax(const string a[], int n)
 {
     if (n <= 0)
         return -1;
     int maxPos = 0;  //  assume to start that the max is at position 0
     for (int k = 1; k < n; k++)  // so start at position 1 to look at the rest
         if (a[k] > a[maxPos])
             maxPos = k;
     return maxPos;
 }

 int circleLeft(string a[], int n, int pos)
 {
     if (n < 0  ||  pos < 0  ||  pos >= n)
         return -1;

       // save the element that is to be moved
     string toBeMoved = a[pos];

       // shift left the elements that are after the one to be moved
     for (int k = pos; k < n-1; k++)
         a[k] = a[k+1];

       // place the moved element at the end
     a[n-1] = toBeMoved;
     return pos;
 }

 int enumerateRuns(const string a[], int n)
 {
     if (n < 0)
         return -1;
     if (n == 0)
         return 0;
     int nRuns = 1;  // there's at least one element, so at least one run
     for (int k = 1; k < n; k++)  // start at 1, not 0
         if (a[k] != a[k-1])  // start of new run?
             nRuns++;
     return nRuns;
 }

 int flip(string a[], int n)
 {
     if (n < 0)
         return -1;
       // exchange elements at positions 0 and n-1, then 1 and n-2, then 2 and
       // n-3, etc., stopping in the middle of the array
     for (int k = 0; k < n/2; k++)
         exchange(a[k], a[n-1-k]);
     return n;
 }

 int locateDifference(const string a1[], int n1, const string a2[], int n2)
 {
     if (n1 < 0  ||  n2 < 0)
         return -1;
     int n = (n1 < n2 ? n1 : n2);  // minimum of n1 and n2
     for (int k = 0; k < n; k++)
         if (a1[k] != a2[k])
             return k;
     return n;
 }

 int subsequence(const string a1[], int n1, const string a2[], int n2)
 {
     if (n1 < 0  ||  n2 < 0)
         return -1;

       // Try matching the a2 sequence starting at each position of a1 that
       // could be the start of sequence of length n2

     for (int k1 = 0; k1 < n1 - n2 + 1; k1++)
     {
           // See if the a2 sequence matches starting at k1 in a1

         bool match = true;  // Assume they match until proved otherwise
         for (int k2 = 0; k2 < n2; k2++)
         {
             if (a1[k1+k2] != a2[k2])
             {
                 match = false;
                 break;
             }
         }
         if (match)  // We never found a mismatch, so they match
             return k1;
     }
     return -1;
 }

 int locateAny(const string a1[], int n1, const string a2[], int n2)
 {
     if (n1 < 0  ||  n2 < 0)
         return -1;
     for (int k = 0; k < n1; k++)
         if (locate(a2, n2, a1[k]) != -1)
             return k;
     return -1;
 }

 int divide(string a[], int n, string divider)
 {
     if (n < 0)
         return -1;

       // It will always be the case that just before evaluating the loop
       // condition:
       //  firstNotLess <= firstUnknown and firstUnknown <= firstGreater
       //  Every element earlier than position firstNotLess is < divider
       //  Every element from position firstNotLess to firstUnknown-1 is
       //    == divider
       //  Every element from position firstUnknown to firstGreater-1 is
       //     not known yet
       //  Every element at position firstGreater or later is > divider

     int firstNotLess = 0;
     int firstUnknown = 0;
     int firstGreater = n;

     while (firstUnknown < firstGreater)
     {
         if (a[firstUnknown] > divider)
         {
             firstGreater--;
             exchange(a[firstUnknown], a[firstGreater]);
         }
         else
         {
             if (a[firstUnknown] < divider)
             {
                 exchange(a[firstNotLess], a[firstUnknown]);
                 firstNotLess++;
             }
             firstUnknown++;
         }
     }
     return firstNotLess;
 }*/

//Test Cases
/*There were 84 test cases. The first 64 were worth 1.11 point each; the next 17 were worth .82 points each; the last three, worth one point each, were the bonuses you earned for certain functions that passed all tests but did not use an additional array. To run the test cases:
 
 Remove the main routine from your array.cpp file.
 Append the following text to the end of your array.cpp file, and build the resulting program.
 For any test case you wish to try, run the program, providing as input the test number.
 #include <iostream>
 #include <string>
 #include <algorithm>
 #include <cstdlib>
 #include <cassert>

 using namespace std;

 string c[6] = {
     "alpha", "beta", "beta", "delta", "gamma", "gamma"
 };

 bool dividecheck(const string a[], int n, int p, string divider)
 {
     for (int k = 0; k < p; k++)
         if (a[k] >= divider)
             return false;
     for ( ; p < n  &&  a[p] == divider; p++)
         ;
     for (int k = p; k < n; k++)
         if (a[k] <= divider)
             return false;
     string b[100];
     copy(a, a+n, b);
     sort(b, b+n);
     return equal(b, b+n, c);
 }

 void testone(int n)
 {
     const int N = 6;

     string aa[1+N+1] = {
         "", "alpha", "beta", "gamma", "gamma", "beta", "delta", ""
     };
     string* a = &aa[1];
     string* z = aa;
     a[-1].string::~string();
     a[N].string::~string();
     fill_n(reinterpret_cast<char*>(&a[-1]), sizeof(a[-1]), 0xEF);
     fill_n(reinterpret_cast<char*>(&a[N]), sizeof(a[N]), 0xEF);

     string b[N] = {
         "alpha", "beta", "gamma", "delta", "beta", "delta"
     };

     string d[9] = {
         "alpha", "beta",  "beta", "beta", "alpha",
         "alpha", "delta", "beta", "beta"
     };

     switch (n)
     {
                      case  1: {
         assert(reduplicate(z, -1) == -1 && a[0] == "alpha");
             } break; case  2: {
         assert(reduplicate(z, 0) == 0 && a[0] == "alpha");
             } break; case  3: {
         assert(reduplicate(a, 1) == 1 && a[0] == "alphaalpha" &&
                             a[1] == "beta");
             } break; case  4: {
         a[4] = "";
         assert(reduplicate(a, 6) == 6 && a[0] == "alphaalpha" &&
             a[1] == "betabeta" && a[2] == "gammagamma" &&
             a[3] == "gammagamma" && a[4] == "" &&  a[5] == "deltadelta");
             } break; case  5: {
         assert(locate(z, -1, "alpha") == -1);
             } break; case  6: {
         assert(locate(z, 0, "alpha") == -1);
             } break; case  7: {
         assert(locate(a, 1, "alpha") == 0);
             } break; case  8: {
         assert(locate(a, 6, "delta") == 5);
             } break; case  9: {
         assert(locate(a, 6, "beta") == 1);
             } break; case 10: {
         assert(locate(a, 6, "zeta") == -1);
             } break; case 11: {
         assert(locationOfMax(z, -1) == -1);
             } break; case 12: {
         assert(locationOfMax(z, 0) == -1);
             } break; case 13: {
         assert(locationOfMax(a, 1) == 0);
             } break; case 14: {
         assert(locationOfMax(a, 3) == 2);
             } break; case 15: {
         assert(locationOfMax(a, 6) == 2);
             } break; case 16: {
         assert(locationOfMax(a+3, 3) == 0);
             } break; case 17: {
         a[0] = "";
         a[1] = " ";
         a[2] = "";
         assert(locationOfMax(a, 3) == 1);
             } break; case 18: {
         assert(circleLeft(z, -1, 0) == -1 &&
                 a[0] == "alpha" && a[1] == "beta");
             } break; case 19: {
         assert(circleLeft(a, 6, -1) == -1 &&
             a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
             a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
             } break; case 20: {
         assert(circleLeft(a, 6, 6) == -1 &&
             a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
             a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
             } break; case 21: {
         assert(circleLeft(z, 0, 0) == -1 &&
                 a[0] == "alpha" && a[1] == "beta");
             } break; case 22: {
         assert(circleLeft(a, 1, 0) == 0 &&
                 a[0] == "alpha" && a[1] == "beta");
             } break; case 23: {
         assert(circleLeft(a, 6, 0) == 0 &&
             a[0] == "beta" && a[1] == "gamma" && a[2] == "gamma" &&
             a[3] == "beta" && a[4] == "delta" && a[5] == "alpha");
             } break; case 24: {
         assert(circleLeft(a, 6, 5) == 5 &&
             a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
             a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
             } break; case 25: {
         assert(circleLeft(a, 6, 3) == 3 &&
             a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
             a[3] == "beta" && a[4] == "delta" && a[5] == "gamma");
             } break; case 26: {
         assert(circleLeft(a, 5, 3) == 3 &&
             a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
             a[3] == "beta" && a[4] == "gamma" && a[5] == "delta");
             } break; case 27: {
         assert(enumerateRuns(z, -1) == -1);
             } break; case 28: {
         assert(enumerateRuns(z, 0) == 0);
             } break; case 29: {
         assert(enumerateRuns(a, 1) == 1);
             } break; case 30: {
         assert(enumerateRuns(a, 3) == 3);
             } break; case 31: {
         assert(enumerateRuns(a, 4) == 3);
             } break; case 32: {
         assert(enumerateRuns(a+2, 4) == 3);
             } break; case 33: {
         assert(enumerateRuns(d, 9) == 5);
             } break; case 34: {
         assert(flip(z, -1) == -1 && a[0] == "alpha");
             } break; case 35: {
         assert(flip(z, 0) == 0 && a[0] == "alpha");
             } break; case 36: {
         assert(flip(a, 1) == 1 && a[0] == "alpha" &&
                     a[1] == "beta");
             } break; case 37: {
         assert(flip(a, 2) == 2 && a[0] == "beta" &&
                     a[1] == "alpha" && a[2] == "gamma");
             } break; case 38: {
         assert(flip(a, 5) == 5 && a[0] == "beta" &&
             a[1] == "gamma" && a[2] == "gamma" && a[3] == "beta" &&
             a[4] == "alpha" && a[5] == "delta");
             } break; case 39: {
         a[2] = "zeta";
         assert(flip(a,6) == 6 && a[0] == "delta" && a[1] == "beta" &&
             a[2] == "gamma" && a[3] == "zeta" && a[4] == "beta" &&
             a[5] == "alpha");
             } break; case 40: {
         assert(locateDifference(z, -1, b, 6) == -1);
             } break; case 41: {
         assert(locateDifference(a, 6, z, -1) == -1);
             } break; case 42: {
         assert(locateDifference(z, 0, b, 0) == 0);
             } break; case 43: {
         assert(locateDifference(a, 3, b, 3) == 3);
             } break; case 44: {
         assert(locateDifference(a, 3, b, 2) == 2);
             } break; case 45: {
         assert(locateDifference(a, 2, b, 3) == 2);
             } break; case 46: {
         assert(locateDifference(a, 6, b, 6) == 3);
             } break; case 47: {
         assert(subsequence(z, -1, b, 6) == -1);
             } break; case 48: {
         assert(subsequence(a, 6, z, -1) == -1);
             } break; case 49: {
         assert(subsequence(z, 0, b, 6) == -1);
             } break; case 50: {
         assert(subsequence(a, 6, z, 0) == 0);
             } break; case 51: {
         assert(subsequence(a, 6, b, 1) == 0);
             } break; case 52: {
         assert(subsequence(a, 6, b+4, 2) == 4);
             } break; case 53: {
         assert(subsequence(a, 6, b+3, 1) == 5);
             } break; case 54: {
         assert(subsequence(a, 6, b+3, 2) == -1);
             } break; case 55: {
         assert(subsequence(a, 6, b+2, 2) == -1);
             } break; case 56: {
         assert(subsequence(a, 6, a, 6) == 0);
             } break; case 57: {
         assert(locateAny(a, 6, z, -1) == -1);
             } break; case 58: {
         assert(locateAny(z, -1, b, 6) == -1);
             } break; case 59: {
         assert(locateAny(z, 0, b, 1) == -1);
             } break; case 60: {
         assert(locateAny(a, 6, z, 0) == -1);
             } break; case 61: {
         assert(locateAny(a, 1, b, 1) == 0);
             } break; case 62: {
         assert(locateAny(a, 6, b+3, 3) == 1);
             } break; case 63: {
         assert(locateAny(a, 4, b+3, 3) == 1);
             } break; case 64: {
         assert(locateAny(a, 2, b+2, 2) == -1);
             } break; case 65: {
         assert(divide(z, -1, "beta") == -1 &&
             a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
             a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
             } break; case 66: {
         assert(divide(z, 0, "beta") == 0 &&
             a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
             a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
             } break; case 67: {
         assert(divide(a, 1, "aaa") == 0 &&
             a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
             a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
             } break; case 68: {
         assert(divide(a, 1, "alpha") == 0 &&
             a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
             a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
             } break; case 69: {
         assert(divide(a, 1, "zeta") == 1 &&
             a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
             a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
             } break; case 70: {
         assert(divide(a, 2, "aaa") == 0 &&
             dividecheck(a, 2, 0, "aaa") && a[2] == "gamma" &&
             a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
             } break; case 71: {
         assert(divide(a, 2, "alpha") == 0 &&
             dividecheck(a, 2, 0, "alpha") && a[2] == "gamma" &&
             a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
             } break; case 72: {
         assert(divide(a, 2, "beta") == 1 &&
             dividecheck(a, 2, 1, "beta") && a[2] == "gamma" &&
             a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
             } break; case 73: {
         assert(divide(a, 2, "zeta") == 2 &&
             dividecheck(a, 2, 2, "zeta") && a[2] == "gamma" &&
             a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
             } break; case 74: {
         assert(divide(a, 6, "aaa") == 0 && dividecheck(a, 6, 0, "aaa"));
             } break; case 75: {
         assert(divide(a, 6, "alpha") == 0 &&
             dividecheck(a, 6, 0, "alpha"));
             } break; case 76: {
         assert(divide(a, 6, "beta") == 1 &&
             dividecheck(a, 6, 1, "beta"));
             } break; case 77: {
         assert(divide(a, 6, "delta") == 3 &&
             dividecheck(a, 6, 3, "delta"));
             } break; case 78: {
         assert(divide(a, 6, "gamma") == 4 &&
             dividecheck(a, 6, 4, "gamma"));
             } break; case 79: {
         assert(divide(a, 6, "zeta") == 6 &&
             dividecheck(a, 6, 6, "zeta"));
             } break; case 80: {
         a[2] = "mu";
         c[5] = "mu";
         assert(divide(a, 6, "mu") == 5 && dividecheck(a, 6, 5, "mu"));
             } break; case 81: {
         assert(divide(a, 6, "chi") == 3 && dividecheck(a, 6, 3, "chi"));
             } break; case 82: {
           // To earn the bonus point for circleLeft, this and all other
           // circleLeft tests must pass, and that function must not
           // use any additional arrays.
         const int BIG = 500;
         string h[BIG];
         for (int k = 0; k < BIG; k++)
             h[k] = (k % 2 == 0 ? "alpha" : "beta");
         h[BIG-2] = "gamma";
         h[BIG-1] = "delta";
         circleLeft(h, BIG, 0);
         assert(h[BIG-3] == "gamma"  &&  h[BIG-2] == "delta");
             } break; case 83: {
           // To earn the bonus point for flip, this and all other
           // flip tests must pass, and that function must not
           // use any additional arrays.
         const int BIG = 500;
         string h[BIG];
         for (int k = 0; k < BIG; k++)
             h[k] = (k % 2 == 0 ? "alpha" : "beta");
         h[0] = "gamma";
         h[BIG-1] = "delta";
         flip(h, BIG);
         assert(h[0] == "delta"  &&  h[BIG-1] == "gamma");
             } break; case 84: {
           // To earn the bonus point for divide, this and all other
           // divide tests must pass, and that function must not
           // use any additional arrays.
         const int BIG = 500;
         string h[BIG];
         string i[3] = { "alpha", "beta", "gamma" };
         for (int k = 0; k < BIG; k++)
             h[k] = i[k % 3];
         divide(h, BIG, "beta");
         int m;
         for (m = 0; m < (BIG+2)/3; m++)
             assert(h[m] == "alpha");
         for ( ; m < 2*(BIG+1)/3; m++)
             assert(h[m] == "beta");
         for ( ; m < BIG; m++)
             assert(h[m] == "gamma");
             } break;
     }

     new (&a[-1]) string;
     new (&a[N]) string;
 }

 int main()
 {
     cout << "Enter a test number (1 to 84): ";
     int n;
     cin >> n;
     if (n < 1  ||  n > 84)
     {
     cout << "Bad test number" << endl;
     return 1;
     }
     testone(n);
     cout << "Passed test " << n << endl;
 }*/
