

int flag = 0;  // ����ȫ�ֱ�����������¼�Ƿ��ҵ�x��� 

void find_ancestor(Btree *root,int x)
{
	if(root == NULL)
	{
		return ;
	}
	else
	{
		if(root->val == x)  // �ҵ��ýڵ㣬��ʱ����־��������Ϊ1�� 
		{
			flag = 1; 
			return ;
		}
		if(flag==0)   //Ϊ�ҵ��ýڵ㣬�������²��ң� 
		{
			find_ancestor(root->left,x);
		}
		if(flag==0)
		{
			find_ancestor(root->right,x);
		}
		if(flag==1)  // ��־�����Ѿ�Ϊ1����ʱ ���� ջ���ص㣬����ԭ�����õĺ���ʱ��¼��x�����Ƚڵ㣻 
		{
			printf("%d",root->val);
			return ;
		}
	}
}   // ʱ�临�Ӷ� ��O��n��  �ռ临�Ӷ� ��O��� 
