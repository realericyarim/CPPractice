#include <iostream>
#include <typeinfo>

using namespace std;

char* convert (int number){

    static char charray[12]; // this array is static, so that the stuff we put in doesnt disappear after function cessation (memory dumps), str = charray

    // a do while loop, so we can manually iterate over the integer in a way

    int number_mod;

    int i = 0;

    do {
        number_mod = number %10;
        char ch = number_mod +'0';
        number /= 10;
        charray[i++] = number_mod + '0'; //this works cause we told the program charray will be full of characters, and this operation makes characters
        cout << ch<< endl;

    } while (number >0);

    charray[i] = '\0'; //kills last values

    return charray; //note arrays decay into pointer to the first element implicity, hence us needing a char*
}

void reverse(char* string){ //so no type or anytthing needs to be declared because this works at the pointer

    char* end = string;
    while (*end) end++;
    end--;

    while (string < end) {
        char temp = *string;
        *string = *end;
        *end = temp;
        string++;
        end--;
    }
}

int main (){

    cout << "enter a number: " << endl;
    int user_integer;
    cin >> user_integer;
    char* result = convert(user_integer);
    reverse(result);

    cout << typeid(result).name() << endl;
    

    return 0;
}