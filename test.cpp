#include<iostream>
#include<stdio.h>
#include<bits/stdc++.h>
#include<unistd.h>


int neighbour_routing_talbe[10][10];

float energy_table[10];

#define buffer_size 10000			//buffer_capacity for each node
#define energy_node 100			//Energy of each node at the initial
#define link_bw 1000				//bandwidth of each link (2Mbps)
#define s_end_time 60			//simulation end time
#define src_nn 2		
#define e_packet_transfer 4.1548
using namespace std;	
struct node
{
	//int x, y;
	int ip_val;
	int data;
	float energy;
	int buffer;
	int reduced_rate;
	struct node *next, *prev;
	
};

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
 
    /* 4. change prev of head node to new node */
    if((*head_ref) !=  NULL)
      (*head_ref)->prev = new_node ;
 
    /* 5. move the head to point to the new node */
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
    /* 1. allocate node */
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
	struct node* head1=NULL;
	append(&head1, 0,750,79.226, 10000);
	append(&head1, 1, 0, 83.3808, 10000);
	append(&head1, 2, 0, 87.5356, 10000);
	append(&head1, 3, 0, 91.6904, 10000);
	append(&head1, 4, 0, 95.8452, 10000);
	
	struct node *it=head1;
	while(it!=NULL)
	{		
		if(it->ip_val==3)
		{
			it=rerouting(it);
			//it=newit;
			//cout<<endl<<newit->ip_val<<" This is it ::"<<newit->next->ip_val<<endl;
		}
		cout<<it->ip_val<<"\t";
		it=it->next;
	}
	return 0;
}
		
