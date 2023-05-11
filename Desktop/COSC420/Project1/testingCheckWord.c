
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// takes in the crypted password & the current dictionary word
// going through every prefix & suffix, hash the prefixWord & suffixWord to determine if it matches the password
// (use string compare, == compares pointers)
int checkWord(char *pswd , char *word) {

  int maxLen = 40; // maximum word length
  int buflen = maxLen * sizeof(word) * sizeof(char); // buffer length = max * array length * char size
  char *buf = malloc(buflen); // buffer to hold the dictionary word and the prefix/suffix
  memset(buf, '\0', buflen); // fills with null terminators

  // traverse through the buf by character index to change
  // ex) word[3]++ NOT string word2 = word + 1

  // insert 4 zeros before the word
  for (int i = 0; i < 4; i++) {
    buf[i] = 0;
  }
}

int main () {
  char *password = 
  char *word = "aardvark";

  return 0;
}