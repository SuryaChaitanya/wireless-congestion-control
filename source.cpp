/* 
	



#include<iostream>
#include<stdio.h>
#include<bits/stdc++.h>
#include<unistd.h>
#define N 10
#define buffer_size 10000			//buffer_capacity for each node
#define energy_node 100			//Energy of each node at the initial
#define link_bw 1000				//bandwidth of each link (2Mbps)
#define s_end_time 60			//simulation end time
#define src_nn 2		
#define e_packet_transfer 4.1548		//number of traffic gen sources
using namespace std;
int neighbour_routing_talbe[10][10];
float energy_table[10];
int buffer_table[10];
	/*int routing_path[src_nn][10];
	routing_path[0][]={0,1,2,3,4,-1,0,0,0,0};//global to the particular routing path
	routing_path[1][]={5,6,2,7,-1,0,0,0,0,0};
*/
struct node
{
	int ip_val;
	int data;
	float energy;
	int buffer;
	int reduced_rate;			//msg from intermediate node to reduce the rate of flow to control congestion when rerouting is not possible
	//int token[5];				//src, dest, sending, receiving, buffer capacity
	struct node *next, *prev;
	
};
void initial_()
{
		for(int i=0;i<10;i++)
			{
				energy_table[i]=energy_node;
				buffer_table[i]=buffer_size;
			}
		for(int i=0;i<10;i++)
			for(int j=0;j<10;j++)
				neighbour_routing_talbe[i][j]=0;
}
void push(struct node** head_ref, int ip_val, int new_data, int buffer, float energy)
{
    struct node* new_node = (struct node*) malloc(sizeof(struct node));
    new_node->data  = new_data;
    new_node->ip_val=ip_val;
    new_node->energy=energy;
    new_node->buffer=buffer;
    new_node->reduced_rate=-1;
    new_node->next = (*head_ref);
    new_node->prev = NULL;
    if((*head_ref) !=  NULL)
      (*head_ref)->prev = new_node ;
    (*head_ref)    = new_node;
}


struct node* create_node(int ip_val, int new_data, float energy,int buffer)
{
	struct node *n=new node;
	n->data  = new_data;
    n->ip_val=ip_val;
    n->energy=energy;
    n->buffer=buffer;
    n->reduced_rate=-1;
    n->next=NULL;
    n->prev=NULL;
    
    return (n);
}
void append(struct node** head_ref, int ip_val, int new_data, float energy,int buffer)
{
    struct node* new_node = (struct node*) malloc(sizeof(struct node));
    struct node *last = *head_ref;  /* used in step 5*/
    new_node->data  = new_data;
    new_node->ip_val=ip_val;
    new_node->energy=energy;
    new_node->buffer=buffer;
    new_node->reduced_rate=-1;
 
    new_node->next = NULL;
 
    if (*head_ref == NULL)
    {
        new_node->prev = NULL;
        *head_ref = new_node;
        return;
    }
    while (last->next != NULL)
        last = last->next;
 
    last->next = new_node;
    new_node->prev = last;
    return;
}

void update(struct node *n)
{
	int ip=n->ip_val;
	energy_table[ip]=n->energy;
	buffer_table[ip]=n->buffer;
}
void fill_neighbour()
{
	int a,b;
	cout<<"Enter nodes that are neighbour to eachother :: ";
	cin>>a>>b;
	if(a!=-1 && b!=-1)
	{
			neighbour_routing_talbe[a][b]=1;
			neighbour_routing_talbe[b][a]=1;
			fill_neighbour();
	}
}

void traffic_gen()
{
	cout<<"Enter number of source ::";
	int src_n;
	cin>>src_n;
	int count=0;
	while(count<src_n)
	{
		count++;
		int size, rate, src, dest;
		cout<<"\n Enter time of traffic_gen :: ";
		int s_time;
		cin>>s_time;
		cout<<"\n Enter src, dest, size, rate :: ";
		cin>>src>>dest>>size>>rate;
	}
	cout<<"\nCalcucating optimal routing path.....";
	cout<<"\n cbr1: 0-1-2-3-4\n cbr2: 5-6-2-8";
	
}


struct node* rerouting(struct node* head)
{
	neighbour_routing_talbe[3][7]=500;
	energy_table[7]=44.0;
	//struct node *head=pp;
	//int ip=head->ip_val;
	int ip=head->ip_val;
	struct node *sub=NULL;
	for(int i=0;i<9;i++)
	{
		if(i!=ip)
		{
			if(neighbour_routing_talbe[ip][i]!=0)
			{
					sub=create_node(i, 0, energy_table[i], neighbour_routing_talbe[ip][i]);
			}
		}
	}
	
	struct node *prev=head->prev;
	
	prev->next=sub;
	prev->energy-=e_packet_transfer;
	sub->next=head->next;
	head->next->prev=sub;
	sub->prev=prev;
	sub->energy-=(2*e_packet_transfer);
	head->energy-=e_packet_transfer;
	head->prev=NULL;
	head->next=NULL;	
	return sub;
}


int main()
{
	initial_();
	int nn; //number_of_wireless_nodes
	cin>>nn;
	
	
	for(int i=0;i<nn;i++)
	{
		for(int j=0;j<nn;j++)
		{
			neighbour_routing_talbe[i][j]=0;
		}
	}
	fill_neighbour();
	

	int null=5;
	cout<<"\n Enter the details \n";
	
	traffic_gen();
	
	int i=0;
	
	//create the routing path
	struct node* head1=NULL;
	append(&head1, 0,750,79.226, 10000);
	append(&head1, 1, 0, 83.3808, 10000);
	append(&head1, 2, 0, 87.5356, 10000);
	append(&head1, 3, 0, 91.6904, 10000);
	append(&head1, 4, 0, 95.8452, 10000);
	

	cout<<"\nRouting table:: \n";
	for(int i=0;i<N;i++)
		{
			cout<<endl;
			for(int j=0;j<N;j++)
			{
				cout<<neighbour_routing_talbe[i][j]<<"\t";
			}
		}
	

	for(i=4;i<s_end_time;i++)
	{
		
		usleep(1000000);
		cout<<"\n Time::"<<i<<endl;

		struct node *node=head1;
		int flag=0;
		//cout<<"\n value";
		while(node!=NULL)
		{

			node->energy=node->energy-e_packet_transfer;
			update(node);
			usleep(500000);
			cout<<"\nNode("<<node->ip_val<<") Buffer:: "<<node->buffer<<" Data:: "<<node->data<<" Energy::"<<node->energy;
			
			if(i>8)
			{
				if(node->ip_val==2)
					node->buffer+=500;
			}	
			
			if(i>8){
				if(node->data>link_bw)
				{
					//int buffer=node->buffer;
					node->buffer+=node->data-link_bw;

					if(node->buffer>(0.75*buffer_size))
					{
						cout<<"\n Congestion might occur...";
						cout<<"\n \n rerouting......";
						usleep(1000000);
						cout<<"\nrerouting......";
						flag=1;
						node=rerouting(node);	
					}
				}
				else
				{
					int diff=link_bw-node->data;
					if(node->buffer>diff)
						node->buffer-=diff;
					else
						node->buffer=0;
				}
			}
			

			cout<<"---> "<<i<<endl;
			
			node->next->data=node->data;
			
			
			update(node);
				node=node->next;
		}
		cout<<"\n outside while loop";
	}

return 0;
}
                
