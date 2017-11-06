#include <stdio.h>
#include <string.h>
int main()
{
int count,src_router,i,j,k,w,v,min;
int cost_matrix[100][100],dist[100],last[100];
int flag[100];
 printf("\n Enter the no of routers");
scanf("%d",&count); 
printf("\n Enter the cost matrix values:");


int x,y;
//scanf("%d %d",&x,&y);
do
{
	scanf("%d %d",&x,&y);
	cost_matrix[i][j]=1;
	cost_matrix[i][j]=1;
}while(x!=-1 || y!=-1);

 printf("\n Enter the source router:");
scanf("%d",&src_router);
for(v=0;v<count;v++)
{
flag[v]=0;
last[v]=src_router;
dist[v]=cost_matrix[src_router][v];
}
flag[src_router]=1;
for(i=0;i<count;i++)
{
min=1000;
for(w=0;w<count;w++)
{
if(!flag[w])
if(dist[w]<min)
{
v=w;
min=dist[w];
}
}
flag[v]=1;
for(w=0;w<count;w++)
{
if(!flag[w])
if(min+cost_matrix[v][w]<dist[w])
{
dist[w]=min+cost_matrix[v][w];
last[w]=v;
}
}
}
for(i=0;i<count;i++)
{
 printf("\n%d==>%d:Path taken:%d",src_router,i,i);
w=i;
while(w!=src_router)
{
 printf("\n<--%d",last[w]);w=last[w];
}
 printf("\n Shortest path cost:%d",dist[i]);
}
}