
// 该函数打印 图g 从start 到 target 结点的所有简单路径，i 表示在当前函数中path的个数，初始为 0 
//  path 用来记录从 start 到 target 的路径 ，只有在找到 目标结点 才会打印； 

void find_path(graph g,int start,int target,int i,int path[])
{
	int visit[max_size] = {0};   // 用来标记哪些结点在此次寻找在已经访问； 
	arcnode *p = NULL;
	visit[start] = 1;            // 对当前结点访问，进path，再判断； 
	path [i++] = start ;
	if(start == target)
	{
		print_path(path,i);
	}
    p = g.Vnode[start].firstarc;
    while(p!=NULL)                   // 该循环用来找从start 点出发能到达的其他结点； 
    {
    	if(visit[p->vexnum]==0)
    	{
    		find_path(g,p->vexnum,target,i,path); // 开始递归，类似DFS 
		}
		p = p->nextacr; // 等到上面函数出栈后则对前一个函数的 p 进行移动； 
	}
	visit[start] = 0;  // 取消标记 ！！否则只能找一条； 
} 




//该函数是在上面的 find_path 的基础上进行修改，因为也先得找到对应的路径才能进行判断； 

int flag = 0;  // 全局变量：0 表示没找到； 1表示找到了 k 长度的路径； 

int calculate_pathlength(int path[],int n)
{
	int i=0;
	int sum = 0;
	int vex1 = path[i];             // 将path 中第一和第二 个结点赋值给 vex1 和 vex2； 
	int vex2 = path[i+1];
	arcnode *p = NULL; 
	for(i=1;i<n;i++)
	{
		p = g.Vnode[vex1].firstarc;
		while(p->vexnum!=vex2)   // 找到 vex1 到 vex2 的边 p
		{
			p = p->nextacr ; 
		}
		sum += p->weight;   // 将该条边的权重累计到 sum 中； 
		vex1 = path[i];     // 找下一条边； 
		vex2 = path[i+1];
	}
	return sum;
}

void find_path(graph g,int start,int target,int i,int path[],int k)
{
	int length;
	int visit[max_size] = {0};   // 用来标记哪些结点在此次寻找在已经访问； 
	arcnode *p = NULL;
	visit[start] = 1;            // 对当前结点访问，进path，再判断； 
	path [i++] = start ;
	if(start == target)
	{
		length = calculate_pathlength(path,i); 
		if(length == k)
		{
			flag = 1;
			print_path(path,i); //打印长度为k的路径； 
		}
	}
    p = g.Vnode[start].firstarc;
    while(p!=NULL)                   // 该循环用来找从start 点出发能到达的其他结点； 
    {
    	if(visit[p->vexnum]==0)
    	{
    		find_path(g,p->vexnum,target,i,path); // 开始递归，类似DFS 
		}
		p = p->nextacr; // 等到上面函数出栈后则对前一个函数的 p 进行移动； 
	}
	visit[start] = 0;  // 取消标记 ！！否则只能找一条； 
} 
