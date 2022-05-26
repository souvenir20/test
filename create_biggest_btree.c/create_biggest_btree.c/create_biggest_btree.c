typedef struct node
{
	int val;
	struct node* left;
	struct node* right;
}Btree;   // 树节点的定义

Btree* create_biggest_tree(int array[], int left_start, int right_end)
{
	if (left_start == right_end) //数组左右端点相同，则只剩下该节点，将该结点放进树中；
	{

		Btree* tree_node = create_treenode(array[left_start]);

	}
	if (left_start > right_end) //此时没有截到任何部分数组，即该部分不存在结点，返回NULL；
	{
		return NULL;
	}
	int i = 0;
	int max_node_val, max_pos;
	max_node_val = array[left_start];   // 初始化max_node_val 的值
	max_pos = left_start;
	for (i = left_start; i < right_end; i++)  // 找到分割后数组中最大的元素以及下标；
	{
		if (array[i] > max_node_val)
		{
			max_node_val = array[i];
			max_pos = i;
		}
	}
	Btree* tree_node = create_treenode(max_node_val);
	tree_node->left = create_biggest_tree(array, left_start, max_pos - 1); //在最大值左边的部分数组中递归创建最大二叉树；
	tree_node->right = create_biggest_tree(array, max_pos + 1, right_end);
	return tree_node;  // 此时该tree_node已完成左右的最大二叉树创建
	
}  //   最好情况 ：时间复杂度 ：O（ｎ）　空间复杂度：Ｏ（ｎ）
// 最坏情况 ：　时间复杂度　：O（ｎ²）　空间复杂度　：　O（ｎ）
　