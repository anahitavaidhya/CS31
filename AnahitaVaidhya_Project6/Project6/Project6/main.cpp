//
//  main.cpp
//  Project6
//
//  Created by Anahita Vaidhya on 11/23/23.
//

#include <iostream>
using namespace std;
int main()
{
int arr[3] = { 5, 10, 15 };
int* ptr = arr;


*ptr = 10;          // set arr[0] to 10
ptr[1] = 20;      // set arr[1] to 20
ptr += 2;
ptr[0] = 30;        // set arr[2] to 30
        
while (ptr >= arr) {
     cout << *ptr << endl;    // print values
          ptr--;
}
 }





/*const char* findTheChar(const char* str, char chr)
{
    while(*str != 0){
        if(*str == chr){
            return str;
        }
        str++;
    }
    return nullptr;
}


 int main()
    {
     char str[10] = "hi my";
     const char* n =  findTheChar(str, 'h');
     if (n == nullptr){
         cout << "i am null";
     } else {
         cout << n << endl;
     }
    }*/

/*const char* findTheChar(const char str[], char chr)
{
    while(*str != 0){
        if(*str == chr){
            return str;
        }
        str++;
    }
    return nullptr;
}

int main(){
    char str[10] = "hi my";
    const char* n =  findTheChar(str, 'j');
    if (n == nullptr){
        cout << "i am null";
    } else {
        cout << n << endl;
    }
    
}*/

    /*int* maxwell(int* a, int* b)
    {
        if (*a > *b)
            return a;
        else
            return b;
    }


    void swap1(int* a, int* b)
    {
        int* temp = a;
        a = b;
        b = temp;
    }
//it is a copy, you are swapping address of a copy, doesn’t change stuff


    void swap2(int* a, int* b)
    {
        int temp = *a;
        *a = *b;
        *b = temp;
    }
//changing the value of it and is getting reflected in the main, even tho still copy, holds memory


    int main()
{
        int array[6] = { 5, 3, 4, 17, 22, 19 };
        
        int* ptr = maxwell(array, &array[2]);
        //passes in first element of array (5) and third element (4)
        //ptr’s memory location is set to 5 of the array after the function is ran through
        *ptr = -1; //ptr is setting array[0] to -1
        //for (int i = 0; i < 6; i++)
            //cout << "1: " << array[i] << endl;
        ptr += 2; //ptr points to the third element of array now
        ptr[1] = 9; //ptr sets fourth element of array to 9
        //for (int i = 0; i < 6; i++)
           // cout << array[i] << endl;
        *(array+1) = 79; //the value of the second element of array is now 79
        for (int i = 0; i < 6; i++)
            cout << array[i] << endl;
        
        
        cout << &array[5] - ptr << endl; //5 - 4 = 1 so prints out array[1] which is 3
        
        //{-1, 79, 4, 9, 22, 19}
        
        for (int i = 0; i < 6; i++)
            cout << array[i] << endl;
        
        
        swap1(&array[0], &array[1]); //doesn’t switch the 1st and 2nd element’s value
        //stays: {-1, 79, 4, 9, 22, 19}
        
        for (int i = 0; i < 6; i++)
            cout << array[i] << endl;
        
        swap2(array, &array[2]); //switches 1st and 3rd element’s values
        //{4, 79, -1, 9, 22, 19}
        
        for (int i = 0; i < 6; i++)
            cout << array[i] << endl;
        //prints out all the elements of the array {4, 79, -1, 9, 22, 19}
    }

*/
/*const char* findTheChar(const char str[], char chr)
    {
        for (int k = 0; *(str+k) != 0; k++)
            if (*(str+k) == chr)
                return (str+k);


        return nullptr;
    }*/

//Now rewrite the function shown in part b so that it uses neither square brackets nor any integer variables. Your new function must not use any local variables other than the parameters. Do not use any of the <cstring> functions such as strlen, strcpy, etc.
/*const char* findTheChar(const char str[], char chr)
{
    while(str != 0){
        if(*str == chr){
            return str;
        } else if(*(str+1) != 0){
            str++;
        } else {
            break;
        }
    }
    return nullptr;
}

int main(){
    char str[10] = "hi my";
    const char* n =  findTheChar(str, 'm');
    if (n == nullptr){
        cout << "i am null";
    } else {
        cout << n << endl;
    }
    
}
*/



    /*int main()
    {
        double* cat;
        double mouse[5] = {0, 1, 2, 3, 4};
        cat = &mouse[4];
        *cat = 25;
        *(mouse + 3)=17;
        cat -= 3;
        cout << *cat << endl;
        cat[1] = 42;
        *cat = 54;
        bool d = (cat == &mouse[0]);
        cout << "d: " << d << endl;
        bool b = (*cat == *(cat+1));
        cout << "b: " << b << endl;

        
        cout << mouse[0] << endl;
        cout << mouse[1] << endl;
        cout << mouse[2] << endl;
        cout << mouse[3] << endl;
        cout << mouse[4] << endl;
    }


*/


/*Write a function named removeS that accepts one character pointer as a parameter and returns no value. The parameter is a C string. This function must remove all of the upper and lower case 's' letters from the string. The resulting string must be a valid C string.
Your function must declare no more than one local variable in addition to the parameter; that additional variable must be of a pointer type. Your function must not use any square brackets and must not use any of the <cstring> functions such as strlen,strcpy, etc.
    */

/*void removeS(char ch[]){
    char* point = ch;
    while(*point != '\0'){
        if(*point == 'S' || *point == 's'){
            while(*point != '\0'){
                *point = *(point + 1);
                point++;
                
            }
            point = ch;
        }
            point++;
        }
}
               
int main()
{
    //length is hardcoded in function??
    char msg[50] = "She'll blossom like a masssssss princess.";
    removeS(msg);
    cout << msg << endl;  // prints   he'll bloom like a male prince.
}

*/






    /*int* nochange(int* p)
    {
        return p;
    }

    int* getPtrToArray(int& m)
    {
        int anArray[100];
        for (int j = 0; j < 100; j++)
            anArray[j] = 100-j;
        m = 100;
        return nochange(anArray);
    }

    void f()
    {
        int junk[100];
        for (int k = 0; k < 100; k++)
            junk[k] = 123400000 + k;
        junk[50]++;
    }

    int main()
    {
        int n;
        int* ptr = getPtrToArray(n);
        f();
        for (int i = 0; i < 3; i++)
            cout << ptr[i] << ' ';
        for (int i = n-3; i < n; i++)
            cout << ptr[i] << ' ';
        cout << endl;
    }



*/










/*int* maxwell(int* a, int* b)
    {
        if (*a > *b)
            return a;
        else
            return b;
    }

    void swap1(int* a, int* b)
    {
        int* temp = a;
        a = b;
        b = temp;
    }

    void swap2(int* a, int* b)
    {
        int temp = *a;
        *a = *b;
        *b = temp;
    }

    int main()
    {
        int array[6] = { 5, 3, 4, 17, 22, 19 };
        cout << *array << endl;

        int* ptr = maxwell(array, &array[2]);
        cout << " hello1: " << *ptr << endl;
        *ptr = -1;
        cout << " hello2: " << *array << endl;
        ptr += 2;
        cout << " hello3: " << *ptr << endl;
        ptr[1] = 9;
        cout << array[3] << endl;
        *(array+1) = 79;
        cout << array[1] << endl;

        cout << &array[5] - ptr << endl;
        
        for(int i = 0; i < 6; i++){
            cout << "happy: " << array[i] << endl;
        }

        swap1(&array[0], &array[1]); //why isn't this changing anything might have to do with pointer thing like the value isn't being assigned
        
        for(int i = 0; i < 6; i++){
            cout << "sad: " << array[i] << endl;
        }
        
        swap2(array, &array[2]);
        
        for(int i = 0; i < 6; i++){
            cout << "happy: " << array[i] << endl;
        }

        for (int i = 0; i < 6; i++)
            cout << array[i] << endl;
    }*/

/*#include <iostream>
    using namespace std;

    int* nochange(int* p)
    {
        return p;
    }

    int* getPtrToArray(int& m)
    {
        int anArray[100];
        for (int j = 0; j < 100; j++)
            anArray[j] = 100-j;
        m = 100;
        return nochange(anArray);
    }

    void f()
    {
        int junk[100];
        for (int k = 0; k < 100; k++)
            junk[k] = 123400000 + k;
        junk[50]++;
    }

    int main()
    {
        int n;
        int* ptr = getPtrToArray(n);
        f();
        for (int i = 0; i < 3; i++)
            cout << ptr[i] << ' ';
        for (int i = n-3; i < n; i++)
            cout << ptr[i] << ' ';
        cout << endl;
    }
*/


/*bool strequal(const char str1[], const char str2[])
{
    for(int i = 0; str1[i] != '\0' && str2[i] != '\0'; i++){
        if (strcmp(str1, str2) != 0)  // compare corresponding characters
            return false;
    }
    return strlen(str1) == strlen(str2);   // both ended at same time?
}

int main()
{
    char a[15] = "Chen, G.";
    char b[15] = "Chen, G.";

    if (strequal(a,b))
        cout << "They're the same person!\n";
    else {
        cout << "nvm";
    }
}*/


















/*void computeCube(int n, int* ncubed)
    {
        *ncubed = n * n * n;
    }

    int main()
    {
        int n = 0; //creates a memory location to assign to pointer
        int* ptr = &n; //assigned ptr to memory location of n
        //int* ptr; (can't have an uninitialized ptr
        computeCube(5, ptr);
        cout << "Five cubed is " << *ptr << endl;
        cout << "Five cubed is " << n << endl;
    }*/











/*void findMax(int arr[], int n, int* pToMax)
    {
        if (n <= 0)
            return;      // no items, no maximum!
    
        pToMax = arr;


        for (int i = 1; i < n; i++)
        {
            if (arr[i] > *pToMax)
                 pToMax = &arr[i];
        }
    }

int main()
    {
        int nums[4] = { 5, 3, 15, 6 };
        int* ptr = &nums[0];

        findMax(nums, 4, ptr);
    
        cout << "The maximum is at address " << ptr << endl;
        cout << "It's at position " << ptr - nums << endl;
        cout << "Its value is " << *ptr << endl;
    }*/































/*int main() {
    int arr[3] = { 5, 10, 15 };
    int* ptr = arr;
    *ptr = 30;
    ptr++;
    *ptr = 20;
    ptr++;
    *ptr = 10;
    
    ptr -= 2;
    int i = 0;
    
    while (ptr >= &arr[i] && i<=2)
    {
        cout << *ptr << endl; //prt values
        ptr++;
        i++;
        
    }*/
    
    //sets first element of array and ptr to 30
    //*ptr = 30;          // set arr[0] to 30
    //cout << *ptr << endl;
    //Prints out address of 2nd element of array (arr just prints out 1st element)
    //cout << arr + 1 << endl;
    //Prints out address of 2nd element of array (arr just prints out 1st element)
    //cout << &arr[1] << endl;
    
    //can't assign ptr + 1 like we can with arr + 1 (which means address of element in arr)
    //arr[1] = 20;      // set arr[1] to 20
    
    //changes index of where ptr is pointing
    //ptr += 1;
    //cout << *ptr << endl;
    
    //changes the first element to 10
    //ptr[0] = 10;        // set arr[2] to 10
    //cout << ptr[0] << endl;
    
    //*ptr = 20;
    //ptr += 1;
    //*ptr = 10;
    
    //cout << ptr << endl;
    //cout << arr << endl;
    
//}
