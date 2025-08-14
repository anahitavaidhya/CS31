//
//  main.cpp
//  trial
//
//  Created by Anahita Vaidhya on 10/18/23.
//

#include <iostream>
using namespace std;
int main() {
        int side;
        int j;

        cout << "Enter a number: ";
        cin >> side;

        for (int i = 0; i < side; i++)
        {
            j = i;
            while (j >= 0){
                cout << "#";
                j--;
            }
            cout << "\n";
        }
}


