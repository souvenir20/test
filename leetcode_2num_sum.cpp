// returnSize ��¼���·��ص����ݸ�������ʼΪ0�������ҵ��������Ϊ2 �����ã���Ϊ�Ƿ��ҵ��ı�־�� 

int* twoSum(int* nums, int numsSize, int target.int* returnSize){
    int* returned = NULL; 
    int pt1 = 0;
    int pt2 = pt1 + 1;
    for(pt1 = 0;pt1 < numsSize-1 ; pt1++)
    {
    // 	if(nums[pt1]>target)   ���nums�����Ϊ�Ǹ�������������жϣ�
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
				*returnSize = 2;      // �ҵ�������Ӧ���֣������Ϊ2 
				return returned;
			}
		} 
	}
    return returned;   // �����е��˴���˵�� returnSize Ϊ 0 ������û�ҵ��� 
}
