#include <stdio.h>
#define MAX 10
int n;
int pos[MAX];
int count[MAX];
int o[2*MAX];


void find(int ind)
{
	int i,j,k;
	if(ind >= 2*n+1)
	{
		printf(" output -> \n");
		for(i=1;i<=2*n;i++)
		{
			printf(" %d",o[i]);
		}
		printf("\n");
		return;
	}

	for(i=1;i<=n;i++)
	{
		if(count[i] == 2)
			continue;
		if(count[i] == 1)
		{
			if(pos[i] + i + 1 == ind)
			{
				o[ind] = i;
				count[i] = 2;
				find(ind+1);
				count[i] = 1;
			}
		}

		if(count[i] == 0)
		{
		//	if(ind + i <= 2*n)
			{
				o[ind] = i;
				pos[i] = ind;
				count[i] = 1;
				find(ind+1);
				count[i] = 0;
			}
		}
	}
}


int main()
{
	int i,j,k;
	n = 4;
	for(i=0;i<=n;i++)
	{
		pos[i] = 0;
		count[i] = 0;
		o[i] = 0;
	}
	for(i=n+1;i<=2*n;i++)
	{
		o[i] = 0;
	}
	find(1);
	return 0;
}
