#include <stdio.h>
#include "huffman.h"

TreeNode * TreeNode_create(char val, int freq)
{
  TreeNode * tn = malloc(sizeof(TreeNode));
  tn -> left = NULL;
  tn -> right = NULL;
  tn -> value = val;
  tn -> freq = freq;
  return tn;
}