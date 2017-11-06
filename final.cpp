#include<iostream>
#include<stdio.h>
#include<bits/stdc++.h>
#include<vector>
#include<unistd.h>
#define N 10
#define buffer_size 50000			//buffer_capacity for each node
#define energy_node 100				//Energy of each node at the initial
#define link_bw 1000				//bandwidth of each link (2Mbps)
#define s_end_time 60				//simulation end time
#define src_nn 2		
#define e_packet_transfer 4.1548	//number of traffic gen sources
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
	int buffer_remain;
	//int reduced_rate;			//msg from intermediate node to reduce the rate of flow to control congestion when rerouting is not possible
	int next,prev;
	
}node[10];


void create_nodes(int n)
{	
	usleep(500000);
	cout<<endl<<"Entering node buffer capacity, energy, ip_value::\n";
	for(int i=0;i<n;i++)
	{
		node[i].ip_val=i;
		node[i].data=0;
		node[i].energy=100;
		node[i].buffer=5000;
		node[i].buffer_remain=0;
		node[i].next=-1;
		node[i].prev=-1;
	}

}
void create_routing_table()
{
	int a,b;
	do{
		cout<<"Enter the neighbouring nodes ::";
		cin>>a>>b;
		neighbour_routing_table[a][b]=neighbour_routing_table[b][a]=1;


	}while(a!=-1 && b!=-1);


	for(int i=0;i<9;i++)
	{
		cout<<endl;
		for(int j=0;j<9;j++)
			cout<<neighbour_routing_table[i][j]<<"\t";

	}
}

void display_attributes(int k)
{
	cout<<"\n ID: "<<node[k].ip_val<<" buffer_remain ::"<<node[k].buffer_remain<<" Data:: "<<node[k].data<<" Energy :: "<<node[k].energy;
}

void congestion_control(int k, vector<int> route)
{

	int z=-1;
	//Find the node k in the route1
	for(int i=0;i<route.size();i++)
	{
		if(route[i]==k)
			z=i;
	}	
	int pre=node[route[z-1]].ip_val;
	int nxt=node[route[z+1]].ip_val;
	for(int i=0;i<9;i++)
	{
		if(neighbour_routing_table[k][i]==1)
		{
			if(i!=pre && i!=nxt)
			{
				cout<<"\n-----Getting data of buffer space and energy level-----\n";
				if(node[i].buffer_remain<(0.25*node[k].buffer) && node[i].energy>(0.5*energy_node))
				{
					usleep(1000000);
					cout<<"\n -------REROUTING-------\n";
					route[z]=node[i].ip_val;
				}
			}
		}
	}	
}

void some_function(vector<int>);
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
	usleep(500000);
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

	for(int i=0;i<route1.size();i++)
	{
		
		if(i==route1.size()-1)
			node[route1[i]].next=-1;
		else
			node[route1[i]].next=route1[i+1];
	}
	usleep(500000);
	

	//updating predecessor and successor
	for(int i=0;i<route2.size();i++)
	{
		
		if(i==route2.size()-1)
			node[route2[i]].next=-1;
		else
			node[route2[i]].next=route2[i+1];
	}
	
	int m;
	m=10;
	usleep(500000);
	cout<<"Enter the number of nodes:: "<<m;
	
	create_nodes(m);
	create_routing_table();
	usleep(500000);
	cout<<"\nGenerating traffic ";


	for(int i=0;i<20;i++)
	{
		if(i>=1)
		{
			usleep(500000);
			if(i==1)cout<<"\n\n Starting traffic by src1 ::\n";
			int k=route1[0];
			node[k].data=750;
			display_attributes(k);
		}
		//start injecting packets to source nodes after 8 seconds
		if(i>=8)
		{
			usleep(500000);
			if(i==8)cout<<"\n\n Starting traffic by src2 ::\n"	;
			int k=route2[0];
			node[k].data=750;
			display_attributes(k);
		}


		if(i>1)
			some_function(route1);

			
		//display_attributes(0);
		if(i>8)
		{
			some_function(route2);	
		
		}

	
	}
	return 0;
}

void some_function(vector<int> route1)
{
	for(int j=route1.size()-1;j>0;j--)
	{

			int k=route1[j];

			if(j==route1.size()-1)
				node[k].data=0;

			/* Since if I get the data from the previous node, node 8 is getting congested.
				To prevent it, i am adding the data rate directly to every node isntead of f
				forwarding data to from the previous node to the present node */

			//node[k].data+=node[route1[i-1]].data;
			
			node[k].data+=750;

			node[route1[j-1]].data-=750;
			//if node has data greater than bandwidth-buffer gets filled
			if(node[k].data>link_bw)
			{
				
				node[k].buffer_remain+=node[k].data-link_bw;
				node[k].data=link_bw;

			}
			//if buffer exist
			else if(node[k].buffer_remain>0)
			{
				if(node[k].data+node[k].buffer_remain<link_bw)
					node[k].data+=node[k].buffer_remain;
				else
					node[k].data=link_bw,node[k].buffer_remain-=(link_bw-node[k].data);
			}

			//calculate buffer space and initiate congestion control function
			

			if(node[k].buffer_remain>(node[k].buffer*0.75) && node[k].buffer_remain<node[k].buffer)
			{
				cout<<"\n\n -----CONGESTION AVOIDANCE-------\n";
				congestion_control(k,route1);
			}
			else if(node[k].buffer_remain>node[k].buffer)
			{
				cout<<"\n------PACKET DROP------\n";
				node[k].buffer_remain=node[k].buffer;
			}
	}
}