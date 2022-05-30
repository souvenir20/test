#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define maxnum 10000

// ���ÿ������򣺶�ԭ����������� ��ı�ԭ�����˳�򣡣� 
int fastsort(int arr[],int left,int right)
{
	if(left>=right)
	{
		return;
	}
	int temp1 = arr[left];
	int i = left;
	int j = right;
	while(i<j)    // ��ν����� 
	{
		while(arr[j]>=arr[left]&&i<j)  // �ҵ���һ��С��arr[left] ������ 
		{
			j--;
		}
	    while(arr[i]<=arr[left]&&i<j)
	    {
	    	i++;
		}
		if(j>i)
		{
			int temp2 = arr[i];
		    arr[i] = arr[j];
		    arr[j] = temp2;   
		}  
	} 
	arr[left] = arr[i];
	arr[i] = temp1;
	fastsort(arr,left,i-1);
	fastsort(arr,i+1,right);
}

int find_midnum(int arr[],int num)
{
	int mid_pos=(num-1)/2;
	return arr[mid_pos];
	
}

void printarr(int *arr,int num)
{
	int i=0;
	for(i=0;i<num;i++)
	{
		printf("%d ",arr[i]);
	}
	printf("\n");
}

// �������ܣ� ��ԭ��������������򣬲��������е���λ��������ı������ԭ��˳�򣡣� 
// ʱ�临�Ӷ� �� O(nlog2n) 


int main()
{
	int i=0;
    int cow_num = 0;
    scanf("%d",&cow_num);
    if(cow_num>=maxnum||cow_num<=0)  
    {
    	printf("the number of cow is too big!");
    	return 0;
	}
    int *milk = (int*)malloc(sizeof(int)*cow_num);  // ����һ�����飻 
    for(i=0;i<cow_num;i++)
    {
    	scanf("%d",&milk[i]);
	}
	fastsort(milk,0,cow_num-1);
	int mid_num = find_midnum(milk,cow_num);
	printf("%d",mid_num);
	return 0;
}
