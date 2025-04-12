#include<stdio.h>
int main(){
	int i,j,k,n,m[20][20];
	printf("Enter no. of routers: ");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		printf("Router %d: ",i);
		for(j=0;j<n;j++)
		{
			scanf("%d",&m[i][j]);
		}
	}
	printf("\nInitial routing table!!\n\t");
	for(i=0;i<n;i++)
	{
		printf("%d\t",i);
	}
	printf("\n");
	for(i=0;i<n;i++){
		printf("---------");
	}
	printf("\n");
	for(i=0;i<n;i++)
	{
		printf("%d\t",i);
		for(j=0;j<n;j++)
		{
			printf("%d\t",m[i][j]);
		}
		printf("\n");
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			for(k=0;k<n;k++)
			{
				if(m[i][j]>m[i][k]+m[k][j]){
					m[i][j]=m[i][k]+m[k][j];
				}
			}
		}
	}
	printf("\nFinal routing table!!\n\t");
        for(i=0;i<n;i++)
        {
                printf("%d\t",i);
        }
        printf("\n");
        for(i=0;i<n;i++){
                printf("---------");
        }
        printf("\n");
        for(i=0;i<n;i++)
        {
                printf("%d\t",i);
                for(j=0;j<n;j++)
                {
                        printf("%d\t",m[i][j]);
                }
                printf("\n");
        }

}
