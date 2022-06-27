// returnSize 记录等下返回的数据个数，初始为0，若能找到，则更改为2 ；作用：作为是否找到的标志； 

int* twoSum(int* nums, int numsSize, int target.int* returnSize){
    int* returned = NULL; 
    int pt1 = 0;
    int pt2 = pt1 + 1;
    for(pt1 = 0;pt1 < numsSize-1 ; pt1++)
    {
    // 	if(nums[pt1]>target)   如果nums数组均为非负数，则可以先判断；
        for(pt2 = pt1+1;pt2 < numsSize ; pt2++)
		{
			if(nums[pt1]+nums[pt2] == target)
			{
				returned = (int*)malloc(sizeof(int)*2);
				if(returned==NULL)
				{
					return NULL;
				}
				returned[0] = pt1;
				returned[1] = pt2;
				*returnSize = 2;      // 找到两个对应数字，将其改为2 
				return returned;
			}
		} 
	}
    return returned;   // 若运行到此处，说明 returnSize 为 0 ，代表没找到； 
}
