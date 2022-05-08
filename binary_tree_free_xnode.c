
void free_this_subtree(Btree *root)  // 对以root为根的结点的子树释放全部空间； 采用递归， 
{
	if(root->left)      // 先进入到深层 
	{
		free_this_subtree(root->left);
	}
	if(root->right)
	{
		free_this_subtree(root->right);
	}
	free(root);         // 再开始 使用 free 函数； 
}

Btree* find_x_node(Btree *root,int x)  //通过递归遍历，找到元素为x的树节点，存在返回该节点位置，不存在则返回NULL； 
{
	int temp1 = NULL;
	if(root==NULL)      // 退出的另一个条件； 
	{
		return;            
	}
	if(root->val == x)  // 找到x，开始返回该结点地址； 
	{
		return root;
	}
	else    //每个结点都会先遍历左子树，再遍历右子树
	{  
	    temp1 = find_x_node(root->left,x);
	    if(temp1 != NULL)     // 若在左子树找到，则直接一路返回； 
	    {
	    	return temp1;
		}
        temp1 = find_x_node(root->right,x);  // 开始在右子树查找； 
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
	temp = find_X_node(root);   // 开始找第一个x 结点 
	while(temp)   // 找到则进入循环； 
	{
		free_this_subtree(temp);    // 将该节点的子树free； 
		temp = find_x_node(root);   // 对 tree  再次进行查找，若再次找到则再进入循环；一直到x结点全部被free为止； 
	}
    return;
}
