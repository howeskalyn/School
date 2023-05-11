// Kalyn Howes
// 3.25.21
// Lab 7 - Hash Functions: clearly demonstrates the correctness of each of the methods, displaying strings and their hashes

#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iomanip>
using namespace std;

size_t hashin(size_t); 
size_t strTo128(char*);
void convert(size_t);
size_t hashin2(char*);
size_t hashin3(char* str);

int main(int argc, char** argv) {

    //take a string argument to hash
    char* str = argv[1];
    cout << "\nString: " << str << endl;

    // given function:
    cout << "\n-- Multiplciation Method --" << endl;
    size_t str128 = strTo128(str);
    cout << "String in base-128: " << str128 << endl;
    size_t hashed = hashin(str128);
    cout << "Hashed string (multiplcation method): " << hashed << endl;
    convert(hashed); // shows in hexidecimal form

    // my hash function call #1:
    cout << "\n-- My Hash Function #1 --" << endl;
    size_t hashed2 = hashin2(str);
    convert(hashed2); // shows in hexidecimal form
    
    // my hash function call #2:
    cout << "\n-- My Hash Function #2 --" << endl;
    size_t hashed3 = hashin3(str);
    convert(hashed3); // shows in hexidecimal form

    return 0;
}

// performs a hash of a given integer argument
// uses the “multiplication method” to compute the hash
size_t hashin(size_t k) {
    size_t ret = 0; // holds return

    // maintain three hard-coded internal variables:
    size_t w = 32;
    size_t p = 7; // can change this to differ the hashing process
    double A = ( sqrt(5) - 1 ) / 2; // number given from class

    size_t one = 1; // get 1 as a size_t
    size_t s = A * size_t(one << w);
    size_t prod = k * s;

    // restrict k to be only w least sig, same as "masking" k with 1111..1
    // i.e. w 1's in a row which is 2^w - 1
    size_t mask = (one << w) - one;

    // all non-zeros after w least sig will now be 0.
    size_t masked_k = prod & mask;

    // get rid of the rightmost (w - p)
    ret = masked_k >> (w - p);

   return ret;
}

// takes each character as an ASCII value & interprets the string as a number in base-128
// (because ASCII characters have numerical value 0-127)
size_t strTo128(char* str) {
    size_t sum = 0; // return value

    int n = strlen(str);
    for(int i = 0; i < n; i++){
        // str[i] * 128^(n-1) = str[i] * 2^(7*(n-1)) = str[i] << 7*(n-1)
        // make sure we convert to avoid prematurely overflowing
        sum += size_t(str[i]) << 7 * (n - i - 1);
    }

    return sum;
}

// converts a size_t to hexidecimal characters to be displayed in a more efficient way
// (you can use the std::hex object from the iomanip library)
void convert(size_t T) {
    cout << T << " in hexidecimal form: " << hex << T << endl;
}

// takes the given string, makes it backwards, and uses the mutliplication method on it
size_t hashin2(char* str) {
    size_t ret = 0;
    char* newstr = new char[50];

    // if the string is over 50 char long, take the first 50
    if (strlen(str) >= 50) {
        cout << "Chopping string by first 50 elements." << endl;
        for (int i = 0; i <= 50; i++) {
            newstr[i] = str[i];
        }

        // set str to newstr
        for (int i = 0; i <= 50; i++) {
            str[i] = newstr[i];
        }
    }

    char* backwards = new char[strlen(str)];
    for (int i = 0; i < strlen(str) + 1; i++) {
        backwards[i] = str[strlen(str) - i];
    }

    /* print testing:
    cout << " Backwards String: " << endl;
    for (int i = 0; i <= strlen(newstr); i++) {
        cout << backwards[i] << " ";
    }*/

    size_t str128 = strTo128(str);
    cout << "String in base-128: " << str128 << endl;
    ret = hashin(str128);
    cout << "Hashed string: " << ret << endl;

    return ret;
}

// separates the odd and even indices of the string & puts all of the evens first (in order of index),
// then shifts the contents down (bit-wise) by 2^127
// this is not case-sensitive - when the new string is made the case is not kept...
size_t hashin3(char* str) {
    size_t ret = 0;
    char* newstr = new char[50];
    char* even = new char[strlen(str) / 2];
    char* odd = new char[strlen(str) / 2];
    char* totalstr = new char[strlen(str)];

    // if the string is over 50 char long, take the first 50
    if (strlen(str) >= 50) {
        cout << "Chopping string by first 50 elements." << endl;
        for (int i = 0; i <= 50; i++) {
            newstr[i] = str[i];
        }

        // set str to newstr
        for (int i = 0; i <= 50; i++) {
            str[i] = newstr[i];
        }
    }

    // set evens
    int j = 0;
    for (int i = 0; i < strlen(str) + 1; i++) {
        even[i] = str[j];
        j = j + 2;
    }

    // set odds
    j = 1;
    for (int i = 1; i < strlen(str); i++) {
        odd[i] = str[j];
        j = j + 2;
    }

    /* even & odd printing testing
    cout << " \nEVEN String: " << endl;
    for (int i = 0; i <= strlen(str) / 2; i++) {
        cout << even[i] << " ";
    }
    cout << " \nODD String: " << endl;
    for (int i = 1; i <= strlen(str) / 2; i++) {
        cout << odd[i] << " ";
    }*/

    // combine
    for (int i = 0; i < strlen(str) / 2; i++) {
        totalstr[i] = even[i];
    } 
    j = 0;
    for (int i = (strlen(str) / 2); i < strlen(str) + 1; i++) {
        totalstr[i] = odd[j];
        j++;
    }

    /* printing testing
    cout << " \nNew String: " << endl;
    for (int i = 0; i <= strlen(str); i++) {
        cout << newstr[i] << " ";
    }*/

    // convert to int
    size_t str128 = strTo128(str);
    cout << "String in base-128: " << str128 << endl;
    size_t n = pow(2, 197); // value to be shifted by
    size_t m = 11; // value to be shifted by
    ret = str128 << (n - m);
    cout << "Hashed string: " << ret << endl;

    return ret;
}

/* BONUS:
    // Look up and use the memcpy function to create a templated hash function that first converts any
    // arbitrary type to a pure byte string (e.g. char*) and then hashes it
    // take a string argument to hash
template<typename T>
size_t templateHash (T s) {
    size_t ret = 0;
    char *bytes = new char[];

    // mempcy function: memcpy(*destination, *source, size_t num) 
    //  copies the values of num bytes from the location pointed to by source directly to the memory block pointed to by destination
    //  (copies num bytes from source to destination)

    // converts any type to a byte string (a sequence of bytes)
    mempcy(bytes, s, s.length());

    return ret;
}*/