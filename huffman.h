#include <stdbool.h> 	
#ifndef PA15_H
#define PA15_H	


#define ASCII_SIZE 256


typedef struct TreeNode {
   int label;
   long count;
   struct TreeNode *left;
   struct TreeNode *right;
} TreeNode;

typedef struct ListNode {
   TreeNode *ptr;
   struct ListNode *next;
} ListNode;

void write_freq(long *asciiCount, char *filename, FILE *fptr1, FILE *fptr2);

void push(ListNode **head,TreeNode *, ListNode **tail);

TreeNode* pop(ListNode **head);

TreeNode * Tree_merge(TreeNode * tn1, TreeNode * tn2);

int comp(TreeNode *tn, ListNode *head);

void insert(ListNode** head, int index, TreeNode* tn);

void print_huffman(TreeNode *tn,int index,char buffer[], FILE *fptr);

void printheader(TreeNode *tn,FILE * outfptr,unsigned char * whichbit, unsigned char * curbyte);

void char2bits(FILE * outfptr, int ch, unsigned char * whichbit, unsigned char * curbyte);

int padZero(FILE * fptr, unsigned char * whichbit, 
	    unsigned char * curbyte);

int writeBit(FILE * fptr, unsigned char bit, 
	     unsigned char * whichbit, 
	     unsigned char * curbyte);

bool ifLeaf(TreeNode *tn);

void freeTreeNode(TreeNode * t);

void freeTree(TreeNode * t);

#endif
