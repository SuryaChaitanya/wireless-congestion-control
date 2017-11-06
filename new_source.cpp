#include<iostream>
#include<stdio.h>
#include<bits/stdc++.h>
#include<vector>
#include<unistd.h>
#define N 10
#define buffer_size 50000			//buffer_capacity for each node
#define energy_node 100			//Energy of each node at the initial
#define link_bw 1000				//bandwidth of each link (2Mbps)
#define s_end_time 60			//simulation end time
#define src_nn 2		
#define e_packet_transfer 4.1548		//number of traffic gen sources
using namespace std;
int neighbour_routing_table[N][N];
float energy_table[N];
int buffer_table[N];

struct Node
{
	int ip_val;					//id of the router
	int data;					//data at present transmitted
	float energy;				//energy remaining
	int buffer;					//buffer filled
	//int reduced_rate;			//msg from intermediate node to reduce the rate of flow to control congestion when rerouting is not possible
	int next,prev;
	
}node[10];

void create_nodes(int n)
{	
	usleep(500000);
	cout<<endl<<"Entering node buffer capacity, energy, ip_value::\n";
	for(int i=0;i<n;i++)
	{
		node[i]->ip_val=i;
		node[i]->data=0;
		node[i]->energy=100;
		node[i]->buffer=5000;
		node[i]->next=-1;
		node[i]->prev=-1;
	}

}
void create_routing_table()
{
	int a,b;
	do{
		cout<<"Enter the neighbouring nodes ::"
		cin>>a>>b;
		neighbour_routing_table[a][b]=neighbour_routing_table[b][a]=1;


	}while(a!=-1 && b!=-1);

	neighbour_routing_table[][]={
		{0,1,0,0,0,0,0,0,0},
		{1,0,1,0,0,0,0,1,0},
		{0,1,0,1,0,1,0,1,1},
		{0,0,1,0,1,0,0,1,0},
		{0,0,0,1,0,0,0,0,0},
		{0,0,1,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0},
		{0,1,1,1,0,0,0,0,1},
		{0,0,1,0,0,0,0,0,0}
	}
	for(int i=0;i<9;i++)
	{
		cout<<endl;
		for(int j=0;j<9;j++)
			cout<<neighbour_routing_table[i][j]<<"\t";

	}
}
int main()
{
	int n;
	cout<<"Enter number of sources::";
	cin>>n;
	int src1,src2,dest1, dest2;
	src1=0;
	src2=5;
	dest1=4;
	dest2=8;
	for(int i=0;i<n;i++)
	{
		cout<<"\nEnter souce and destination::";

	}
	
	//Creating routing array vector
	vector<int>route1;
	vector<int>route2;

	route1.push_back(0);
	route1.push_back(1);
	route1.push_back(2);
	route1.push_back(3);
	route1.push_back(4);

	route2.push_back(5);
	route2.push_back(2);
	route2.push_back(8);

	//vector<int>::iterator i;
	//updating predecesor and successor

	for(i=0;i<route1.size();i++)
	{
		int k=*i;
		if(i==route1.size()-1)
			n[k]->next=-1;
		else
			n[k]->next=route1[i+1];
	}

	//updating predecessor and successor
	for(i=0;i<route2.size();i++)
	{
		int k=*i;
		if(i==route2.size()-1)
			n[k]->next=-1;
		else
			n[k]->next=route2[i+1];
	}
	
	int m;
	m=10;
	cout<<"Enter the number of nodes:: "<<m;
	
	create_nodes(m);
	create_routing_table();

	for(int i=0;i<60;i++)
	{
		get_instant();
		for(int i=end;i>=0;i--)
		{
			
		}
	}
}