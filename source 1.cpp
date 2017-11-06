#include<iostream>
#include<stdio.h>
#include<bits/stdc++.h>
#include<unistd.h>

#define buffer_size 10000			//buffer_capacity for each node
#define energy_node 100			//Energy of each node at the initial
#define link_bw 1000				//bandwidth of each link (2Mbps)
#define s_end_time 60			//simulation end time
#define src_nn 2		
#define e_packet_transfer 4.1548		//number of traffic gen sources
using namespace std;
int neighbour_routing_talbe[10][10];
int energy_table[10];
		/*int routing_path[src_nn][10];
	routing_path[0][]={0,1,2,3,4,-1,0,0,0,0};//global to the particular routing path
	routing_path[1][]={5,6,2,7,-1,0,0,0,0,0};
*/
struct node
{
	//int x, y;
	int ip_val;
	int data;
	float energy;
	int buffer;
	int reduced_rate;			//msg from intermediate node to reduce the rate of flow to control congestion when rerouting is not possible
	//int token[5];				//src, dest, sending, receiving, buffer capacity
	
	
}n[10];
	

/*
	Struct node operations 
	*/

void push(struct node** head_ref, int ip_val, int new_data, int buffer, float energy)
{
    /* 1. allocate node */
    struct node* new_node = (struct node*) malloc(sizeof(struct node));
 
    /* 2. put in the data  */
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
struct node*reroute(struct node *head)
{
	head->ip_val=7;
	head->energy=100;
	return head;
}
void append(struct node** head_ref, int ip_val, int new_data, float energy,int buffer)
{
     struct node* new_node = (struct node*) malloc(sizeof(struct node));
    struct node *last = *head_ref;  /* used in step 5*/
 
    /* 2. put in the data  */
    new_node->data  = new_data;
    new_node->ip_val=ip_val;
    new_node->energy=energy;
    new_node->buffer=buffer;
    new_node->reduced_rate=-1;
 
    /* 3. This new node is going to be the last node, so
          make next of it as NULL*/
    new_node->next = NULL;
 
    /* 4. If the Linked List is empty, then make the new
          node as head */
    if (*head_ref == NULL)
    {
        new_node->prev = NULL;
        *head_ref = new_node;
        return;
    }
 
    /* 5. Else traverse till the last node */
    while (last->next != NULL)
        last = last->next;
 
    /* 6. Change the next of last node */
    last->next = new_node;
 
    /* 7. Make last node as previous of new node */
    new_node->prev = last;
 
    return;
}

void fill_neighbour()
{
	int a,b;
	cout<<"Enter nodes that are neighbour to eachother :: ";
	cin>>a>>b;
	while(a!=-1 || b!=-1)
		{
			neighbour_routing_talbe[a][b]=neighbour_routing_talbe[b][a]=5000;
			fill_neighbour();
		}
}

void traffic_gen()
{
	cout<<"Enter number of source ::";
	int src_n;
	cin>>src_n;
	int count=0;
	//int routing_path[src_n][10];
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
	//Need to implement AODV here....for demo assuming that the algorithm selects the below said nodes as the routing path
	cout<<"\nCalcucating optimal routing path.....";
	cout<<"\n cbr1: 0-1-2-3-4\n cbr2: 5-6-2-8";

	
}


/*struct node* rerouting(struct node* head)
{
	//struct node *head=pp;
	//int ip=head->ip_val;
	int ip=head->ip_val;
	for(int i=0;i<9;i++)
	{struct node*head1=new node;
		if(i!=ip)
		{
			if(neighbour_routing_talbe[ip][i]!=0)
			{
					
					append(&head1, i,0,100,neighbour_routing_talbe[ip][i]);
					//node->ip_val=i;
					//node->buffer=neighbour_routing_talbe[ip][i]
			}
		}
	}
	
	
	struct node *prev=head1->prev;
	prev->next=head1;
	head1->next=head1->next;
	return head1;
}*/


int main()
{
	int nn; //number_of_wireless_nodes
	cin>>nn;
	//int buffer_size=50;
	for(int i=0;i<nn;i++)
	{
		for(int j=0;j<nn;j++)
		{
			neighbour_routing_talbe[i][j]=0;
		}
	}

	//neighbour_routing_talbe[i][j]=0;
		
	int null=5;
	cout<<"\n Enter the details \n";
	traffic_gen();
	int i=0;
	int nodes=0;
	//create the routing path
	struct node* head1=NULL;
	append(&head1, 0,750,79.226, 10000);
	append(&head1, 1, 0, 83.3808, 10000);
	append(&head1, 2, 0, 87.5356, 10000);
	append(&head1, 3, 0, 91.6904, 10000);
	append(&head1, 4, 0, 95.8452, 10000);
	for(i=4;i<s_end_time;i++)
	{
		
		usleep(1000000);
		cout<<"\n Time::"<<i<<endl;

		struct node *node=head1;
		int flag=0;
		//cout<<"\n value";
		while(nodes!=null)
		{

			node->energy=node->energy-e_packet_transfer;
			//int data=node->data;
			usleep(500000);
			cout<<"\nNode("<<node->ip_val<<") Buffer:: "<<node->buffer<<" Data:: "<<node->data<<" Energy::"<<node->energy;
			
			if(i>8)
			{
				if(node->ip_val==2)
					node->buffer+=500;
			}	
																										nodes++;
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
						node=reroute(node);	
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
			cout<<"\n "<<i;
			node->next->data=node->data;
			if(node->ip_val!=4)
			node=node->next;
		}
		cout<<"\n outside while loop";
	}

return 0;
}
                