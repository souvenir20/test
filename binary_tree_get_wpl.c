
int tree_wpl(Btree *root,int path_len)  // 递归定义函数，传参为树结点地址，以及当前到根节点的路径长度 
{
	int treewpl = 0;
	if(root==NULL)   
	{
		return 0;
	}
	if(!root->lchild&&!root->rchild)    // 判断是否为叶子节点，若是，则将该点的 路径长度×权重 进入当前wpl中； 
	{
		treewpl = root->weight * path_len;
	}
	// 这个递归也是在找到root 的所有叶子结点； 
	treewpl+=tree_wpl(root->lchild,path_len+1);  // 路径长度＋1 ，传入左右节点； 
	treewpl+=tree_wpl(root->rchild,path_len+1);
	return treewpl;
}  // 时间复杂度： O（n）  空间复杂度 ： O（1） 


