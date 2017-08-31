#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include "huffman.h"

void write_freq(long *asciiCount, char *filename, FILE *fptr1, FILE *outfptr){
	FILE *fptr;
	char buffer[ASCII_SIZE];
	int index = 0;
	ListNode *head = NULL;
	ListNode *tail = NULL;
	TreeNode *tn1 = NULL;
	TreeNode *tn2 = NULL;
	TreeNode *final = NULL;
	int sum = 0;
   fptr = fopen(filename, "w");
   		for(int i = 0;i<ASCII_SIZE;i++){   		
   			if(asciiCount[i]==0)
   				sum++;
   		}
   		int ind = 0;
 	sum--;
   	while(sum < ASCII_SIZE-1){
   		long min = INT_MAX;
		for(int i = 0;i<ASCII_SIZE;i++){
				if(asciiCount[i]<min && asciiCount[i] !=0)
				{
					min = asciiCount[i];
					ind = i;
				}
		}
		fprintf(fptr, "%c:%ld\n", ind,asciiCount[ind]);
		TreeNode *x = malloc(sizeof(TreeNode));
		x->label = ind;
  		x->count = asciiCount[ind];
  		x->left = NULL;
   		x->right = NULL;
		push(&head,x,&tail);
		asciiCount[ind] = 0;
		sum++;
	}
	while(head->next!=NULL)
	{
		tn1 = pop(&head);
		tn2 = pop(&head);
		final = Tree_merge(tn1,tn2);
		int x = comp(final,head);
		printf("%d\n",x);
		//push(&head,final,&tail);
		insert(&head,x,final);
		//push
		//return;
	}

	//return;
	unsigned char whichbit = 0;
	unsigned char curbyte = 0;
	print_huffman(head->ptr,index,buffer,fptr1);
	
	printheader(head->ptr, outfptr, & whichbit, & curbyte);
  // add one more 0 to end the header
  	writeBit(outfptr, 0, & whichbit, & curbyte);
  	padZero(outfptr, & whichbit, & curbyte);
  // add '\n' at the end of the header
  	freeTree(head->ptr);
	free(head);
    fclose(fptr);
	printf("hello");
}

//void 
TreeNode * Tree_merge(TreeNode *tn1 , TreeNode *tn2)
{
  TreeNode *tn = malloc(sizeof(TreeNode));
  tn -> left = tn1;
  tn -> right = tn2;
  tn -> label = 0; 
  tn -> count = tn1 -> count + tn2 -> count;
  return tn;
}
int comp(TreeNode *tn, ListNode *head)
{
	bool x;
	bool y;
	ListNode *curr = head;
	int index = 0;
	
	while(curr!=NULL){
		x = tn->count < curr->ptr->count;
		switch (x)
		{
		case true: return index;
					break;
		case false: 
			{
				y = tn->count == curr->ptr->count;
				switch(y)
				{
					case true:
					{
						if(tn->label !=0) 
						{
							bool z = (curr->ptr->label==0);
							switch(z)
							{
								case true:	return index;
											break;
								case false: 
								{
									bool w = tn->label < curr->ptr->label;
									switch(w){
										case true: return index;
													break;
										default: break;
									}
								}
								break;
								default: break;
							}
						}	
					}
					break;
					default: break;
				}
			}
			break;
		default: break;
		}	
		curr = curr->next;
		index++;
	}
	return index;
}

void printheader(TreeNode *tn,FILE * outfptr,unsigned char * whichbit, unsigned char * curbyte){

	//printf("%s\n", );
	if(tn==NULL){
		return;
	}
	if(ifLeaf(tn)){
		  writeBit(outfptr, 1, whichbit, curbyte);
		  char2bits(outfptr, tn -> label, whichbit, curbyte);
		return;
	}
	writeBit(outfptr, 0, whichbit, curbyte);
	printheader(tn->left, outfptr, whichbit, curbyte);
	printheader(tn->right, outfptr, whichbit, curbyte);
}

// Taken from PA09 - linkedlist.c
void insert(ListNode** head, int index, TreeNode* tn)
{
	  ListNode* obj_add = malloc(sizeof(*obj_add));

  if (*head == NULL)
  {
  	 obj_add->ptr = tn;
  obj_add->next = NULL;
  *head = obj_add;
    return;
  }

  // allocate memory for node we wish to insert
  //ListNode* obj_add = malloc(sizeof(*obj_add));
  if (obj_add == NULL)
  {

    return;
  }
  obj_add->ptr = tn;
  obj_add->next = NULL;

  // if the head node doesn't exist our new node
  // is the head. this is why we wanted a reference
  // to the head, so we can modify it if we need to.
  if (*head == NULL)
  {
    *head = obj_add;
  }

  // special case of having to insert myself at the beginning
  // so the head will need to be modified
  if (index == 0)
  {
    ListNode * old_head = *head;
    *head = obj_add;
    (*head)->next = old_head;
  }

  // otherwise we need to iterate through the list to find
  // where I need to insert this node at the index specified
  ListNode *prev = *head;
  ListNode *cur = (*head)->next;
  int i;
  for (i = 1; (i < index) && (cur != NULL); i++) 
  {
    prev = prev->next;
    cur = cur->next;
  }
 
  // if we didn't reach the index that means the list
  // isn't long enough and we don't want to add at an
  // index that can't exist
  if (i != index)
  {
    free(obj_add);
    return;
  }

  prev->next = obj_add;
  obj_add->next = cur;
}
void print_huffman(TreeNode *tn,int index,char buffer[], FILE *fptr)
{
	
	if(tn==NULL){
		//fclose(fptr);
		return;
	}
	if(tn->left==NULL && tn->right == NULL)
	{
		 //fputc (tn->label,fptr);
		fprintf(fptr, "%c:",tn->label);
		for(int i=0;i<index;i++)
		{
			 fputc (buffer[i],fptr);
			//fprintf(fptr, "%c", buffer[i]);
		}
		fprintf(fptr, "\n");
		return;
	}
	if(tn->left)
	{
		buffer[index] = '0';
		print_huffman(tn->left,index+1,buffer, fptr);
	}
	if(tn->right)
	{
		buffer[index] = '1';
		print_huffman(tn->right,index+1,buffer, fptr);
	}
}
void freeTreeNode(TreeNode * t) {
	free(t);
}

void freeTree(TreeNode * t) {
	if (t == NULL) return;
	freeTree(t->left);
	freeTree(t->right);
	freeTreeNode(t);
}
bool ifLeaf(TreeNode *tn){
	if(tn->right == NULL && tn->left==NULL)
		return true;
	else
		return false;
}
// Taken from Prof. Lu's book - Intermediate C programming
int padZero(FILE * fptr, unsigned char * whichbit, 
	    unsigned char * curbyte)
{
  int rtv;
  while ((* whichbit) != 0)
    {
      rtv = writeBit(fptr, 0, whichbit, curbyte);
      if (rtv == -1)
	{
	  return -1;
	}
    }
  return rtv;
}
// write one bit to a file
//
// whichbit indicates which bit this is written to 
// (0 means leftmost, 7 means rightmost)
//
// curbyte is the current byte
//
// if whichbit is zero, curbyte is reset and bit is put 
// to the leftmost bit
// 
// when whichbit reaches 7, this byte is written to the 
// file and whichbit is reset
// 
// the function returns 1 if a byte is written to the file
//              returns 0 if no byte is written
//                     -1 if it tries to write and fails
int writeBit(FILE * fptr, unsigned char bit, 
	     unsigned char * whichbit, 
	     unsigned char * curbyte)
{
  if ((* whichbit) == 0)
    {
      // reset
      * curbyte = 0;
    }
  // shift the bit to the correct location
  unsigned char temp = bit << (7 - (* whichbit));
  * curbyte |= temp; // store the data
  int value = 0;
  if ((* whichbit) == 7)
    {
      int ret;
      ret = fwrite(curbyte, sizeof(unsigned char), 1, fptr);
      // printByte(* curbyte); // for debugging
      if (ret == 1)
	{
	  value = 1;
	}
      else
	{
	  value = -1;
	}
    }
  * whichbit = ((* whichbit) + 1) % 8;
  return value;
}
void char2bits(FILE * outfptr, int ch, 
		      unsigned char * whichbit,
		      unsigned char * curbyte)
{
  unsigned char mask = 0x80; // only 7 bits
  while (mask > 0)
    {
      writeBit(outfptr, (ch & mask)==mask,
	       whichbit, curbyte);
      mask >>= 1;
    }
}