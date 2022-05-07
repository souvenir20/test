#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int find_sameanc(int i,int j,int num_tree)  // 返回共同祖先的下标位置，接收两个结点的下标位置以及存放完全二叉树的数组； 
{
	int temp1 = i+1;
	int temp2 = j+1;
	if(i<0||j<0||i>=num_tree||j>=num_tree)
	{
	    return -1;
	}
	while(temp1!=temp2)
	{
		if(temp1 > temp2)
		{
			if(temp1%2)  // temp1 为奇数则进入 
			{
				temp1 = (temp1-1)/2; // 利用完全二叉树的性质 
			}
			else
			{
				temp1 = temp1/2;
			}
		}
		else
		{
			if(temp2%2)
			{
				temp2 = (temp2-1)/2;
			}
			else
			{
				temp2 = temp2/2;
			}
		}
	}
    return temp1-1;
}  // 时间复杂度 O（log2n） 空间复杂度：O（1） 
int main()
{
	int num_treeNode = 0;
	int pos_anc = 0;
	int i=0,j=0,k=0;
	printf("how many node of tree?");
	scanf("%d",&num_treeNode);
    int *tree = (int*)malloc(sizeof(int)*num_treeNode);
    for(k=0;k<num_treeNode;k++)
    {
    	scanf("%d",&tree[k]);
	}
	getchar();
	printf("finished");
	printf("the point you want to search: ");
	scanf("%d %d",i,j);
	
	pos_anc = find_sameanc(i,j,num_treeNode);
	
	printf("the anc pos is %d",pos_anc);
	return 0;
 } 
