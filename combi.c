#include<stdio.h>
#define MAX 10
int n,r,o[MAX], visited[MAX];
#if 0
 output =>  1 2 3
 output =>  1 3 2
 output =>  2 1 3
 output =>  2 3 1
 output =>  3 1 2
 output =>  3 2 1
#endif
void find(int ind, int count)
{
	int i,j;
	if(count == n)
	{
		printf(" output => ");
		for(i=0;i<n;i++)
			printf(" %d",o[i]);
		printf("\n");
		return;
	}

	for(i=1;i<=n;i++)
	{
		if (!visited[i])
		{
			visited[i] = 1;
			o[count] = i;
			find(i+1, count+1);
			visited[i] = 0;
		}
	}
}

int main()
{
	int i;
	n = 3;
	r = 3;
	for(i=0;i<=MAX;i++)
	{
		o[i] = 0;
		visited[i]=0;
	}
	find(1, 0);
	return 0;
}
