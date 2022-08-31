//Jabari Crenshaw
//Control Structure Programs: Pangram
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int main(){

   //Integer a holds the flags for each letter of the alphabet
   int a = 25;
   char r;
   char ch;
   int i;
   //Array for letters of the alphabet
   bool flag[a];
   //Char ch[] holds the values of the input charachters
   bool success = true;
   
   //Initializes all the flags to false
   for(i = 0; i <= a; i++){
      flag[i] = false;
   }
   
   //Asks the user for input
   printf("Enter a string to check if it's a Pangram!:\n");
   while(ch != '\n'){
      ch = getchar();
      //Switch case sets the values in the flag[] to true if a letter of the alphabet exits in the string
      switch(ch){
         case 'A' ... 'Z':
            if(ch > 64 && ch < 91){
               flag[ch-65] = true;
            }
            break;
         case 'a' ... 'z':
            if(ch > 96 && ch < 123){
               flag[ch-97] = true;
            }
            break;
      }
   }
   
   //If any value in the flag array remains false the string is not a pangram
   for(i = 0; i <= a; i++){
      if(!flag[i]){
         success = false;
      }
   }
   if(success){
      printf("Entered string is a pangram.\n");
   }else if(!success){
      printf("Entered string is not a pangram.\n");
   }
   
   //Prompt to ask the user if they would like to enter another string
   printf("\nWould you like to see if another string is a Pangram? (Y/N): ");
   while(r != 'Y' || r != 'y' || r != 'n' || r != 'N'){
      r = getchar();
      if(r == 'y' || r == 'Y'){
         while ((getchar()) != '\n');
         printf("\n");
         main();
      }else if(r == 'n' || r == 'N'){
         printf("Bye!");
         exit(1);
      }
   }
   
   //printf(flag[i] ? "true" : "false");
}