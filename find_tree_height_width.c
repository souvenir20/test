

int get_height (Btree *tree)  //函数功能：求二叉树的高度； 
{
	if(root==NULL)
	{
		return 0;
	}
	else
	{
		return max(get_height(tree->left),get_height(tree->right))+1; //max 函数为返回左右子树中 高度较大的值； 
	}
}

int get_fanmaodu(Btree *tree)   //函数功能：得到树的繁茂度， 
{
	int level_num = get_height(tree);
    int *Node_num_of_eachlevel =(int *)malloc(sizeof(int)*level_num); // 创建一个数组，存放各层节点个数 
	Btree *temp;
	queue *q = init_queue(); // 创建队列，并将其初始化为空；
	int i=0;
	int num = 0;
	int width = 0;
	if(tree == NULL)  // 空树，直接退出，繁茂度为0； 
	{
	    return 0;
    }
    Eequeue(q,tree); 
    while(!isempty(q))  // 对队列进行 空 检查，退出条件为 队列为空； 
	{
		num = get_length(q); //得到当前队列q 的长度，并将其放在数组中；
		Node_num_of_eachlevel[i] = num;
		i++;
		for(j=0;j<num;j++)  // 循环num次，将当前队列中所有树节点出队列
		{
			Dequeue(q,temp);  //temp 用来存放当前出队列的结点；
			if(temp->left!=NULL)  // temp 出队后 将其孩子节点入队 
			{
			    Enqueue(q,temp->left);
			} 
			if(temp->right!=NULL)
			{
				Enqueue(q,temp->right);
			}
		} 
	} //完成该循环，即完成了整个树节点的入队出队。此时数组Node_num_of_eachlevel已经是每一层的节点数 
	width = find_max(Node_num_of_eachlevel,level_num);   //找到数组中的最大值，即单曾最大的节点数； 
	return width*level_num;  // 返回高度×宽度的值 
} // 时间复杂度 O（n） 空间复杂度 （log2n） 
