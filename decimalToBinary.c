//Jabari Crenshaw
//Control Structure programs: Decimal to Binary
#include <stdio.h>
#include <stdlib.h>

int main(){
   
   int n;
   int i = 8;
   int a[i];
   char ch;
   
   //Ask the user to enter a number
   printf("Enter a whole number to convert to binary. (Range: 0-255): ");
   
   scanf("%d", &n);
   
   //Checks if the user has entered a number inside of the specified range
   if(n > 255){
      printf("Number is out of range! (Range: 0-255).\n\n");
      main();
   }else{
      for(i=0; n>0 ;i++){
         a[i] = n%2;
         n = n/2;
      }
   
      printf("Binary conversion = ");
      for(i = i-1; i>=0; i--){
         printf("%d", a[i]);
      }
   }
   
   //Program restarts if the user would like to convert another number
   printf("\n\nWould you like to convert another number? (Y/N): ");
   
   while(ch != 'Y' || ch != 'y' || ch != 'n' || ch != 'N'){
      ch = getchar();
      if(ch == 'y' || ch == 'Y'){
         printf("\n");
         main();
      }else if(ch == 'n' || ch == 'N'){
         printf("Bye!");
         exit(1);
      }
   }
}