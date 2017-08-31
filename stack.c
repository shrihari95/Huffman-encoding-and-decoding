#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"

void push(ListNode **head,TreeNode *tn,ListNode **tail)
{
	ListNode *new = malloc(sizeof(ListNode));
	if(*tail==NULL)
	{
		new->ptr = tn;
		new->next = NULL;
		*head = new;
		*tail = *head;
	}
	else
	{
		new->ptr = tn;
		(*tail)->next = new;
		new->next=NULL;
		*tail = new;
	}
}

TreeNode* pop(ListNode **head)
{
	ListNode *curr = *head;
	ListNode *curr1 = *head;
	TreeNode *x;
	if(curr!=NULL)
	{
		x = curr->ptr;
		curr = curr->next;
		free(curr1);
		*head = curr;
	}
	return x;
}

