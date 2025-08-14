//
//  fine.cpp
//  Project2
//
//  Created by Anahita Vaidhya on 10/13/23.
//

#include <iostream>
using namespace std;

int main() {
    //Input Variables
    string identification = "";
    double overstated = 0;
    string location = "";
    
    //Output Variables
    double fine = 0;
    
    //Output and Input for Identification
    cout << "Identification: ";
    getline(cin, identification);
    
    //Empty String for Identification
    if (identification == ""){
        cout << "---" << endl;
        cout << "You must enter a property identification." << endl;
        return 1;
    }
    
    //Output and Input for Overstated
    cout << "Overstated amount (in millions): ";
    cin >> overstated;
    cin.ignore(10000, '\n');
    
    //Overstated is Negative
    if (overstated <= 0){
        cout << "---" << endl;
        cout << "The overstated amount must be positive." << endl;
        return 1;
    }

    //Output and Input for Location
    cout << "Location: ";
    getline(cin, location);
    
    //Empty String for Location (check if this is allowed)
    if (location == ""){
        cout << "---" << endl;
        cout << "You must enter a location." << endl;
    }
    
    //If Statements for Calculations of Fine
    if (overstated <= 60){
        fine = overstated * 0.1111;
    }
    if (overstated > 60 && overstated <= 150){
        fine = 60 * 0.1111;
        if (location == "new york" || location == "florida"){
            fine = fine + ((overstated - 60) * 0.18);
        } else {
            fine = fine + ((overstated - 60) * 0.153);
        }
    }
    if (overstated > 150){
        fine = 60 * 0.1111;
        
        if (location == "new york" || location == "florida")
            fine = fine + (90 * 0.18);
        else
            fine = fine + (90 * 0.153);
        
        fine = fine + ((overstated - 150) * 0.21);
    }
    
    //Output
    cout.setf(ios::fixed);
    cout.precision(3);
    cout << "---" << endl;
    cout << "The fine for " << identification << " is $" << fine << " million." << endl;
}


//Solution
/*// Financial fraud fine computation
 
 #include <iostream>
 #include <string>
 using namespace std;

 int main()
 {
       // Get and validate identification

     cout << "Identification: ";
     string identification;
     getline(cin, identification);
     if (identification == "")
     {
         cout << "---\nYou must enter a property identification." << endl;
         return 1;
     }

       // Get and validate overstated amount

     cout << "Overstated amount (in millions): ";
     double overstatedAmount;
     cin >> overstatedAmount;
     cin.ignore(10000, '\n');
     if (overstatedAmount <= 0)
     {
         cout << "---\nThe overstated amount must be positive." << endl;
         return 1;
     }

       // Get and validate location

     cout << "Location: ";
     string location;
     getline(cin, location);
     if (location == "")
     {
         cout << "---\nYou must enter a location." << endl;
         return 1;
     }

       // Overstated amount tier thresholds and fine rates

     const double TIER2_THRESHOLD    = 60;
     const double TIER3_THRESHOLD    = 150;
     const double TIER1_RATE         = 0.1111;
     const double TIER2_RATE_USUAL   = 0.153;
     const double TIER2_RATE_SPECIAL = 0.18;
     const double TIER3_RATE         = 0.21;

       // Compute fine

     double fine;

     if (overstatedAmount <= TIER2_THRESHOLD)
         fine = overstatedAmount * TIER1_RATE;
     else
     {
           // Compute fine for the portion of overstatedAmount in first tier

         fine = TIER2_THRESHOLD * TIER1_RATE;

           // Determine rate for second tier

         double rate_2 = TIER2_RATE_USUAL;
         if (location == "florida"  ||  location == "new york")
             rate_2 = TIER2_RATE_SPECIAL;

         if (overstatedAmount <= TIER3_THRESHOLD)
         {
               // Add fine for remainder of overstatedAmount (in 2nd tier)

             fine += (overstatedAmount - TIER2_THRESHOLD) * rate_2;
         }
         else
         {
               // Add fine for the portion of overstatedAmount in 2nd tier
               // and the remainder of overstatedAmount (in 3rd tier)

             fine += (TIER3_THRESHOLD - TIER2_THRESHOLD) * rate_2 +
                           (overstatedAmount - TIER3_THRESHOLD) * TIER3_RATE;
         }
     }

       // Print fine

     cout.setf(ios::fixed);
     cout.precision(3);
     cout << "---\n" << "The fine for " << identification << " is $" << fine
          << " million." << endl;
 }*/
