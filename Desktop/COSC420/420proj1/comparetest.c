
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
//#include <crypt.h> //- mac doesn't know what this is

// return 1 if true & 0 if not
int compare(char *password, char *crypted) {
  int ret = 0;
  if (strcmp(password, crypted) == 0) {
        printf("Password has been cracked. The password is: \n");
        for (int i = 0; i < strlen(password); i++)
          printf("%c", password[i]);
        printf("\nThe crypted version is: \n");
        for (int i = 0; i < strlen(crypted); i++)
          printf("%c", crypted[i]);
        ret = 1; // set to 0 since its found
      } else {
        printf("Password has not been cracked :(\n");
        ret = 0;
      }
  return ret;
}

// crypt function - returns char* of crypted input word
char* crypting(char *password) {
  //printf("In crypt function -- pasword to be encrypted is %s\n", password);
  char* result = crypt(password, "$1$ab$"); // hardcode the salt - on Mac salt is second!!
  //char* result = crypt("$1$ab$", password); // linux version

  //printf("In crypt function - your encrypted password is: %s\n", result);
  return result;
}

int main () {
  char *word = "aardvark";
  char *testing = "aardvark123";
  char *password = "$1$ab$koTc2TaVJm9d6HbDymlZO"; // aardvark123
  puts("Password in main: ");
  for (int i = 0; i < strlen(password); i++)
          printf("%c", password[i]);
  puts("");

  char *crypted = crypting(testing);
  puts("Crypted in main: ");
  for (int i = 0; i < strlen(crypted); i++)
          printf("%c", crypted[i]);
  puts("");
  
  int result = compare(password, crypted);
  printf("Result: %d\n", result);

  return 0;
}