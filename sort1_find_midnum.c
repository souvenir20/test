#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define maxnum 10000

// 运用快速排序：对原数组进行排序； 会改变原数组的顺序！！ 
int fastsort(int arr[],int left,int right)
{
	if(left>=right)
	{
		return;
	}
	int temp1 = arr[left];
	int i = left;
	int j = right;
	while(i<j)    // 多次交换； 
	{
		while(arr[j]>=arr[left]&&i<j)  // 找到第一个小于arr[left] 的数； 
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

// 函数功能： 对原来的数组进行排序，并返回其中的中位数；（会改变数组的原有顺序！） 
// 时间复杂度 ： O(nlog2n) 


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
    int *milk = (int*)malloc(sizeof(int)*cow_num);  // 创建一个数组； 
    for(i=0;i<cow_num;i++)
    {
    	scanf("%d",&milk[i]);
	}
	fastsort(milk,0,cow_num-1);
	int mid_num = find_midnum(milk,cow_num);
	printf("%d",mid_num);
	return 0;
}
