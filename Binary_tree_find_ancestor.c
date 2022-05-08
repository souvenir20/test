

int flag = 0;  // 设置全局变量，用来记录是否找到x结点 

void find_ancestor(Btree *root,int x)
{
	if(root == NULL)
	{
		return ;
	}
	else
	{
		if(root->val == x)  // 找到该节点，此时将标志变量设置为1； 
		{
			flag = 1; 
			return ;
		}
		if(flag==0)   //为找到该节点，继续往下查找； 
		{
			find_ancestor(root->left,x);
		}
		if(flag==0)
		{
			find_ancestor(root->right,x);
		}
		if(flag==1)  // 标志变量已经为1，此时 利用 栈的特点，返回原来调用的函数时记录着x的祖先节点； 
		{
			printf("%d",root->val);
			return ;
		}
	}
}   // 时间复杂度 ：O（n）  空间复杂度 ：O（ｎ） 
