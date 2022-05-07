

int get_height (Btree *tree)  //�������ܣ���������ĸ߶ȣ� 
{
	if(root==NULL)
	{
		return 0;
	}
	else
	{
		return max(get_height(tree->left),get_height(tree->right))+1; //max ����Ϊ�������������� �߶Ƚϴ��ֵ�� 
	}
}

int get_fanmaodu(Btree *tree)   //�������ܣ��õ����ķ�ï�ȣ� 
{
	int level_num = get_height(tree);
    int *Node_num_of_eachlevel =(int *)malloc(sizeof(int)*level_num); // ����һ�����飬��Ÿ���ڵ���� 
	Btree *temp;
	queue *q = init_queue(); // �������У��������ʼ��Ϊ�գ�
	int i=0;
	int num = 0;
	int width = 0;
	if(tree == NULL)  // ������ֱ���˳�����ï��Ϊ0�� 
	{
	    return 0;
    }
    Eequeue(q,tree); 
    while(!isempty(q))  // �Զ��н��� �� ��飬�˳�����Ϊ ����Ϊ�գ� 
	{
		num = get_length(q); //�õ���ǰ����q �ĳ��ȣ���������������У�
		Node_num_of_eachlevel[i] = num;
		i++;
		for(j=0;j<num;j++)  // ѭ��num�Σ�����ǰ�������������ڵ������
		{
			Dequeue(q,temp);  //temp ������ŵ�ǰ�����еĽ�㣻
			if(temp->left!=NULL)  // temp ���Ӻ� ���亢�ӽڵ���� 
			{
			    Enqueue(q,temp->left);
			} 
			if(temp->right!=NULL)
			{
				Enqueue(q,temp->right);
			}
		} 
	} //��ɸ�ѭ������������������ڵ����ӳ��ӡ���ʱ����Node_num_of_eachlevel�Ѿ���ÿһ��Ľڵ��� 
	width = find_max(Node_num_of_eachlevel,level_num);   //�ҵ������е����ֵ�����������Ľڵ����� 
	return width*level_num;  // ���ظ߶ȡ���ȵ�ֵ 
} // ʱ�临�Ӷ� O��n�� �ռ临�Ӷ� ��log2n�� 
