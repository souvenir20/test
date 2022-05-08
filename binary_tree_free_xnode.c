
void free_this_subtree(Btree *root)  // ����rootΪ���Ľ��������ͷ�ȫ���ռ䣻 ���õݹ飬 
{
	if(root->left)      // �Ƚ��뵽��� 
	{
		free_this_subtree(root->left);
	}
	if(root->right)
	{
		free_this_subtree(root->right);
	}
	free(root);         // �ٿ�ʼ ʹ�� free ������ 
}

Btree* find_x_node(Btree *root,int x)  //ͨ���ݹ�������ҵ�Ԫ��Ϊx�����ڵ㣬���ڷ��ظýڵ�λ�ã��������򷵻�NULL�� 
{
	int temp1 = NULL;
	if(root==NULL)      // �˳�����һ�������� 
	{
		return;            
	}
	if(root->val == x)  // �ҵ�x����ʼ���ظý���ַ�� 
	{
		return root;
	}
	else    //ÿ����㶼���ȱ������������ٱ���������
	{  
	    temp1 = find_x_node(root->left,x);
	    if(temp1 != NULL)     // �����������ҵ�����ֱ��һ·���أ� 
	    {
	    	return temp1;
		}
        temp1 = find_x_node(root->right,x);  // ��ʼ�����������ң� 
        if(temp1 !=NULL)
        {
        	return temp1;
		}
		else
		{
			return NULL;
		}
	}
}

void free_all_x_node_subtree(Btree *root)
{
	Btree *temp=NULL;
	temp = find_X_node(root);   // ��ʼ�ҵ�һ��x ��� 
	while(temp)   // �ҵ������ѭ���� 
	{
		free_this_subtree(temp);    // ���ýڵ������free�� 
		temp = find_x_node(root);   // �� tree  �ٴν��в��ң����ٴ��ҵ����ٽ���ѭ����һֱ��x���ȫ����freeΪֹ�� 
	}
    return;
}
