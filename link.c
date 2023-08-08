#include<stdio.h>

int main()
{
	int count,src_router,i,j,k,w,v,min;
	int cost_matrix[100][100],dist[100];
	int flag[100];
	
	//input no of routers
	printf("\nEnter the no of routers ");
	scanf("%d",&count);
	//input the cost matrix
	printf("Enter the cost matrix values:\n");
	
	for(i=1;i<=count;i++)
	{
		for(j=1;j<=count;j++)
		{
			printf("%d->%d:",i,j);
			scanf("%d",&cost_matrix[i][j]);
			// if negative assign max value
			if(cost_matrix[i][j]<0)
				cost_matrix[i][j]=1000;
		}
	}
	//input source router
	printf("\nEnter the source router:");
	scanf("%d",&src_router);
	
	for(v=1;v<=count;v++)
	{
		flag[v]=0;
		// taking distance as value from matrix
		dist[v]=cost_matrix[src_router][v];
	}
	flag[src_router]=1;
	for(i=1;i<=count;i++)
	{
		min=1000;
		for(w=1;w<=count;w++)
		{
			//checking if not a source router
			if(!flag[w])
				//taking minimum distance
				if(dist[w]<min)
				{
					v=w;
					min=dist[w];
				}
		}

		flag[v]=1;
		for(w=1;w<=count;w++)
		{
			if(!flag[w])
				if(min+cost_matrix[v][w]<dist[w])
				{
					dist[w]=min+cost_matrix[v][w];
				}
		}
	}
	for(i=1;i<=count;i++)
	{
		printf("\n%d==>%d",src_router,i);
		printf("\n Shortest path cost:%d",dist[i]);
	}

}
