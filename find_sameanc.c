#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int find_sameanc(int i,int j,int num_tree)  // ���ع�ͬ���ȵ��±�λ�ã��������������±�λ���Լ������ȫ�����������飻 
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
			if(temp1%2)  // temp1 Ϊ��������� 
			{
				temp1 = (temp1-1)/2; // ������ȫ������������ 
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
}  // ʱ�临�Ӷ� O��log2n�� �ռ临�Ӷȣ�O��1�� 
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
