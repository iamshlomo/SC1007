#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int *M;
/*
Take note not to initialise the matrix within the function.
Doing so will cause the function to repeatedly create 
the M matrix with every recursive run of the top_down_dp function,
leading to "Memory limit exceeded" situation.
*/

int top_down_dp(int n)
{
    //write your code here
    if (n < 0) return 0;

    if (n == 0){
        M[0] = 0;
        return 0;
    }
        
    if (n == 1){
        M[1] = 1;
        return 1;
    }
    
    if (n == 2){
        M[2] = 2;
        return 2;
    }

    if (M[n-1] == -1)   //F(n-1) was not calculated
   	    
        //calculate F(n-1) and store in M
        M[n-1] = top_down_dp(n-1);	
           
   
    if (M[n-2] == -1)   //F(n-2) was not calculated
        
        //calculate F(n-2) and store in M
   	    M[n-2] = top_down_dp(n-2);		

    if (M[n-3] == -1)   //F(n-3 was not calculated)

        //calculate F(n-3) and store in M
        M[n-3] = top_down_dp(n-3);

   M[n] = M[n-1] + 2*(M[n-2]) - 3*(M[n-3]);
   return M[n];
}


 
int main ()
{
    int n;
    //int function;
    int i;

    //allocate the memory array
    M = malloc(sizeof(int) * (n+2));

    //set all memory elements to -1
    for (i=0; i<=n; i++)
        M[i] = -1;
    
    printf("Enter the value of n:\n");
    scanf("%d",&n);
    
    printf("The value of F(%d) is: %d \n", n, top_down_dp(n));
        
}