#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int **m;

int max(int num1, int num2)
{
    return (num1 > num2 ) ? num1 : num2;
}

int bottom_up_dp(int n, int *s, int *v, int C)
{
    //write your code here
    int i, j;
    for(i=1; i<=n; i++)
    {
        for(j=1; j<=C; j++)
        {
            if(s[i] <= j) //test if (j-s[i]) is positive value
            m[i][j] = max( m[i-1][j] , m[i-1][j-s[i]] + v[i]);
            else m[i][j] = m[i-1][j];
        }
    }
    return m[n][C];
}
 
int main ()
{
    int n,C;
    int function;
    int *s;
    int *v;
    int i,j;
    printf("Enter the number of items n:\n");
    scanf("%d",&n);
    printf("Enter the capacity C:\n");
    scanf("%d",&C);

    // initialise global matrix m
    m = (int **) malloc((n+1) * sizeof(int *));

	for(i=0; i<=n; i++)
		m[i] = malloc((C+1) * sizeof(int));
    
    // for the first row (items = 0), 
    // all values will be 0 for all the different capacities.
    // this is because there will be no item at all. 


    // for the first column (capacity = 0),
    // all values will be 0 for all the different item count.
    // this is because no item will fit into bag capacity = 0.

    // we want to start with every node in matrix == 0 as well.
    for(i=0; i<=n; i++)
    {
        for(j=0; j<=C; j++)
        {
            m[i][j] = 0;
        }
    }

    s = (int *) malloc(sizeof(int) * (n+1));
    v = (int *) malloc(sizeof(int) * (n+1));
    
    printf("Enter the sizes of items (as a list, separate by spacing:\n");
    for (i=1;i<=n;i++)
        scanf("%d",&s[i]);
        
    printf("Enter the values of items (as a list, separate by spacing:\n");
    for (i=1;i<=n;i++)
        scanf("%d",&v[i]);
    
    printf("The maximum value is: %d \n", bottom_up_dp(n,s,v,C));
        
}