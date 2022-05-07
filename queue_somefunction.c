#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define Maxsize 128

typedef struct TreeNode {
    int val;  // 存储数据的地方
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode, *TreeNodePtr;

typedef TreeNodePtr Datatype;

typedef struct
{
	int front;
	int rear;
	TreeNodePtr data[Maxsize];   // 最好是采用循环数组 的方式，不会浪费空间；
}Queue;

TreeNodePtr createTreeNode(int val, TreeNodePtr left, TreeNodePtr right) {  // 创建树节点；
    TreeNodePtr curr = (TreeNodePtr) (malloc(sizeof(TreeNode)));
    curr->val = val;
    curr->left = left;
    curr->right = right;
    return curr;
}

int Isempty(Queue *p)
{
	if(p->front == -1&& p->rear == -1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

TreeNodePtr gethead(Queue *p)
{
	if(!Isempty(p))
	{
		return p->data[p->front];
	}
	else
	{
		printf("empty queue!");
		return NULL;
	}
}
void Printqueue(Queue *p)
{
	int i=0;
	if(Isempty(p))
	{
		printf("this queue is empty!");
	}
	else
	{
		printf("the queue: ");
		for(i=p->front;i<=p->rear;i++)
		{
			printf("%d ",p->data[i]);
		}
		putchar('\n');
	}
}

Queue *Init_queue()
{
	Queue *new_queue = (Queue*) malloc (sizeof(Queue));
	new_queue -> front = -1;
	new_queue -> rear = -1;
	return new_queue;
}


int Isfull(Queue *p)
{
	if(p->rear == Maxsize-1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int Dequeue(Queue *p)
{
	if(Isempty(p))
	{
		return 0; // 表删除 失败，返回0 值
	}
	else if(p->front == p->rear)
	{
		p->front = -1;
		p->rear = -1;
	}
	else
	{
		p->front++;
		return 1;
	}
}

int Enqueue(Queue *p,Datatype e)
{
	if((p->rear+1)%(Maxsize)==p->front)     // 要对应修改Isfull 的判断条件
	{
		return 0;
	}
	else if(Isempty(p))
	{
		p->front = 0;
		p->rear = 0;
	}
	else
	{
		p->rear = (p->rear+1)%(Maxsize) ;// 循环队列？
	}
	p->data[p->rear] = e;
	return 1;
}

void getDigits(char *buff, int *data) {

    int len = strlen(buff);
    int i=0;
    int index = 0;
    for (i = 0; i < len; i++) {
        int num = 0;
        if (buff[i] == '#') {
            num = -1;
            i++;
        } else {
            while (buff[i] != ' ' && buff[i] != '\0') {
                num = num * 10 + (buff[i++] - '0');
            }
        }
        data[index++] = num;
    }
}

TreeNodePtr createTreeWithLevelOrder(int *data, int size) {
    TreeNodePtr T,BT;
    Queue *Q=Init_queue();
    int i=0;
    if(data[0]!=-1)
    {
        BT=(TreeNodePtr)malloc(sizeof(TreeNode));
        BT->val=data[0];
        BT->left=BT->right=NULL;
        Enqueue(Q,BT);
    }
    else return NULL;
    while(i<size&&!Isempty(Q))
    {
        T=gethead(Q);
        Dequeue(Q);
        i++;
        if(i>=size)
        {
            break;
        }
            T->left=(TreeNodePtr)malloc(sizeof(TreeNode));
            T->left->val=data[i];
            T->left->left=T->left->right=NULL;
            Enqueue(Q,T->left);
        i++;
        if(i>=size)
        {
            break;
        }
            T->right=(TreeNodePtr)malloc(sizeof(TreeNode));
            T->right->val=data[i];
            T->right->left=T->right->right=NULL;
            Enqueue(Q,T->right);
    }
    return BT;
}

void preOrderTraverse(TreeNodePtr root) {
   if(root == NULL|| root->val== -1)
    {
    	return;
	}
	printf("%d ",root->val);
    preOrderTraverse(root->left);
    preOrderTraverse(root->right);
}

void inOrderTraverse(TreeNodePtr root) {
    if(root == NULL|| root->val== -1)
    {
    	return;
	}
    inOrderTraverse(root->left);
	printf("%d ",root->val);
    inOrderTraverse(root->right);
}

void postOrderTraverse(TreeNodePtr root) {
    if(root == NULL|| root->val== -1)
    {
    	return;
	}
	postOrderTraverse(root->left);
	postOrderTraverse(root->right);
	printf("%d ",root->val);
}

void destoryTree(TreeNodePtr root) {   // 清理root所指的树 
    if (!root) return;
    if (root->left) {
        destoryTree(root->left);
        root->left = NULL;
    }
    if (root->right) {
        destoryTree(root->right);
        root->right = NULL;
    }
    free(root);
}
int maxPathSum(TreeNodePtr root)  // 找到最大路径  函数 
{
	if(!root||root->val == -1)
	{
		return 0;
	}
	if(root->left&&root->val!= -1)
	{
		if(!root->left->left||root->left->left->val == -1)
		{
			if(!root->left->right||root->left->right->val == -1)
			{
				return root->left->val + maxPathSum(root->right);
			}
	    }
	}
	else
	{
		return maxPathSum(root->left) +  maxPathSum(root->right);
	}
}

TreeNodePtr invertTree(TreeNodePtr root)  // 反转链表 函数 
{
	if(root==NULL||root->val==-1)
	{
		return NULL;
    }
	invertTree(root->left);
	invertTree(root->right);
	TreeNodePtr temp = root->left;
	root->left = root->right;
	root->right = temp;
	return root;
}
int main() {
    int SIZE = 128;
    int MAX_NUM = 10;
    char buff[SIZE];
    int num;
     

    while (scanf("%d\n", &num) == 1) {
        fgets(buff, SIZE, stdin);
        char *pos = strchr(buff, '\n');
        if (pos)
            *pos = '\0';
        
        // Mac/Linux 替换\r
        pos = strchr(buff, '\r');
        if (pos)
            *pos = '\0';

        int size = num;
        int data[size];
        getDigits(buff, data);

        TreeNodePtr tree_root = createTreeWithLevelOrder(data, size);
//        inOrderTraverse(tree_root);
        int max_path_sum = maxPathSum(tree_root);
        printf("%d", max_path_sum);

        destoryTree(tree_root);
        tree_root = NULL;
        
//        TreeNodePtr invert_tree_root = invertTree(tree_root);
//        inOrderTraverse(invert_tree_root);
//        if(!tree_root){
//        	printf("\n");
//        }
//
//        destoryTree(tree_root);
//        tree_root = invert_tree_root = NULL;
    }
    return 0;
}
