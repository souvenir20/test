
int tree_wpl(Btree *root,int path_len)  // �ݹ鶨�庯��������Ϊ������ַ���Լ���ǰ�����ڵ��·������ 
{
	int treewpl = 0;
	if(root==NULL)   
	{
		return 0;
	}
	if(!root->lchild&&!root->rchild)    // �ж��Ƿ�ΪҶ�ӽڵ㣬���ǣ��򽫸õ�� ·�����ȡ�Ȩ�� ���뵱ǰwpl�У� 
	{
		treewpl = root->weight * path_len;
	}
	// ����ݹ�Ҳ�����ҵ�root ������Ҷ�ӽ�㣻 
	treewpl+=tree_wpl(root->lchild,path_len+1);  // ·�����ȣ�1 ���������ҽڵ㣻 
	treewpl+=tree_wpl(root->rchild,path_len+1);
	return treewpl;
}  // ʱ�临�Ӷȣ� O��n��  �ռ临�Ӷ� �� O��1�� 


