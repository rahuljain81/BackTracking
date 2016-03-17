#include <stdio.h>
#define MAX 20
#define DBG 6
int mat[MAX][3];
int min=999999;
int soldiers[3];
int count;
int path[ DBG * MAX];
void do_process (int node, int index, int cost);
int main()
{
	int t, i, T, x, y;
	scanf ("%d", &T);
	for (t=1; t<=T; t++)
	{
		scanf ("%d", &count);
		for (i=0; i < count; i++)
		{
			scanf ("%d %d", &mat[i][0], &mat[i][1]);
			mat[i][2] = mat[i][1] * 2;
		}
#ifdef DBG
		for (i=0; i < count; i++)
		{
			printf ("%d: %d %d %d\n", i, mat[i][0], mat[i][1], mat[i][2]);
		}
#endif
		soldiers[0] = soldiers[1] = soldiers[2] = 0;
		do_process(0, 0, 0);
		soldiers[0] = soldiers[1] = soldiers[2] = 0;
		do_process(0, 1, 0);
		soldiers[0] = soldiers[1] = soldiers[2] = 0;
		do_process(0, 2, 0);
		printf ("Case %d# %d\n", t, min);
		min = 999999;
		soldiers[0] = soldiers[1] = soldiers[2] = 0;
	}
	return 0;
}

void do_process (int node, int index, int cost)
{
	path[node*DBG] = node;
	path[node*DBG+1] = index;
	path[node*DBG+2] = cost;
	path[node*DBG+3] = soldiers[0];
	path[node*DBG+4] = soldiers[1];
	path[node*DBG+5] = soldiers[2];
	if (node > count)
	{
		//Reached The last node
		if (cost < min)
		{
			int i;
#ifdef DBG
			for (i=0; i < count; i++)
				printf ("([%d %d], %d, %d %d %d)", path[DBG*i], path[DBG*i+1],
						path[DBG*i+2], path[DBG*i+3], path[DBG*i+4], path[DBG*i+5]);
			printf (" cost = %d\n", cost);
#endif
			min = cost;
		}
		return;
	}
	switch (index)
	{
		case 0: //Fighting soldiers
			{
				int cnt = soldiers[0] + soldiers[1] + soldiers[2];
				int temp[3], rem;
				if (cnt >= mat[node][0])
				{
					temp[0] = soldiers[0];
					temp[1] = soldiers[1];
					temp[2] = soldiers[2];
					
					if (temp[0] > mat[node][0])
					{
						//life 1 is more soldiers

						soldiers[0] = soldiers[1];
						soldiers[1] = soldiers[2];
						soldiers[2] = 0;
					}
					else
					{
						//life 1 have all died
						//now check for life 2

						rem = mat[node][0] - temp[0];
						if (temp[1] > rem)
						{
							//life 2 has more soldiers

							soldiers[0] = soldiers[1]-rem;
							soldiers[1] = soldiers[2];
							soldiers[2] = 0;
						}
						else
						{
							// life 1 & life 2 have all died

							rem = rem - temp[1];
							soldiers[1] = soldiers[2] - rem;
							soldiers[0] = soldiers[2] = 0;
						}
					}
				}
				else
					return;
				do_process (node+1, 0, cost);
				do_process (node+1, 1, cost);
				do_process (node+1, 2, cost);
				soldiers[0] = temp[0];
				soldiers[1] = temp[1];
				soldiers[2] = temp[2];
				return;
			}
			break;
		case 1://Buying toll
			{
				do_process (node+1, 0, cost+mat[node][1]);
				do_process (node+1, 1, cost+mat[node][1]);
				do_process (node+1, 2, cost+mat[node][1]);
				return;
			}
			break;
		case 2: //Buying soldiers
			{
				int temp = soldiers[2];
				soldiers[2]+= mat[node][0];
				do_process (node+1, 0, cost+mat[node][2]);
				do_process (node+1, 1, cost+mat[node][2]);
				do_process (node+1, 2, cost+mat[node][2]);
				soldiers[2] = temp;
				return;
			}
			break;
		default: printf ("YOU SHOULD NOT REACH HERE\n");
			break;
	}
}
