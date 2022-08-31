//Jabari Crenshaw
//Control Structure programs: Password Check
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int main(){
   
   //Integer a holds the flags for password requirements
   int a = 3;
   int i;
   char ch;
   char r;
   //Array for password requirements
   bool req[a];
   //Boolean to check all charchters are present after input
   bool success = true;
   
   //Initializes all the flags to false
   for(i = i; i <= a; i++){
      req[i] = false;
   }
   
   //Asks the user for input
   printf("Type in your new password:\n");
   while(ch != '\n'){
      ch = getchar();
      //Switch case sets the values of pass[] (requirements) to true if the requirement exits in the input
      switch(ch){
         case 'A' ... 'Z':
            if(ch > 64 && ch < 91){
               req[0] = true;
            }
            break;
         
         case 'a' ... 'z':
            if(ch > 96 && ch < 123){
               req[1] = true;
            }
            break;
         case '%':
         case '+':
         case '#':
            if(ch == 37 || ch == 43 || ch == 35){
               req[2] = true;
            }
            break;
         case '0' ... '9':
            req[3] = true;
            break;
      }
   }
   
   //Checks if all password requirements are met
   for(i = 0; i <= a; i++){
      if(!req[i]){
         success = false;
      }
   }
   
   //If any value of the password requirements is not met the program will restart
   if(!success){
      printf("\nWeak Password (Requirements: One Number, One Uppercase, One Lowercase, One Special Charachter.)");
      printf("\nPlease try again.\n");
      main();
   }else if(success){
      printf("\nStrong Password!\nExiting...");
   }
}
