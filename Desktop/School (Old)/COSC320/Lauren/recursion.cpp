#include <iostream>

using namespace std;

void printStars(int);
void printLine(int);

int main () {

    printStars(5);

    return 0;
}

void printStars(int N) {
    if (N < 1) {
        return;
    } else if (N == 1) {
        printLine(N);
    } else {
        printLine(N);
        printStars(N - 1);
        printLine(N);
    }
}

void printLine(int len) {
    while (len > 0) {
        cout << "*";
        len--;
    }
    cout << endl;
}