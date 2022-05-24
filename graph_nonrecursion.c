
//  graph 结构体 图 结构体中： Vnode[vex_num]; vex_num ; 
typedef struct arcnode   // 边结点的定义 
{
	int arcvex;
	struct arcnode *nextarc;
}Arcnode;

typedef struct vnode   // 邻接表中 主结点的定义；  图中存放 Vnode[g.vex_num] 
{ 
	char vexnode_name;
	Arcnode *firstarc;
}Vnode;


// 利用栈 来完成对图的深度遍历 

 
void DFS_nonrecursion(graph g,int pos)
{
	int visit[g.vex_num];  // 记录结点是否访问过 
	int stack[g.vex_num];   //  栈用来实现深度优先，每次对栈顶进行处理； 
	printf("从%d结点开始进行深度遍历：");
	push_stack(pos);   // 将pos进栈，并对其进行访问， 将visit 改为1； 
	printf("%d",pos);
	visit[pos] = 1 ; 
	while(stack_not_empty(stack))   // 栈非空； 
	{
		temp = get_top(stack);
	    p = g.Vnode[temp].firstarc;  // 找到栈顶元素邻接表的第一个结点p； 
	    while(p!=NULL)   // 用一个循环找到未访问（即visit[p->temp]==0)的那个结点； 
	    {
	    	while(visit[p->arcvex]==1&&p!=NULL)
	    	{
	    		p = p->nextarc;   
			}
            if(p== NULL)
            {
            	break; 
			}
			printf("->%d",p->arcvex);             // p现在指向下一个还未访问的点 
			push_stack(p->arcvex);                // 将那个结点进栈
			visit[p->arcvex] = 1;
			p = g.Vnode[p->arcvex].firstarc; 
		}
		pop_stack(stack);   //当 栈顶元素往下找不到时，则出栈； 
	} 
	 
} 
