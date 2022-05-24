
//  graph �ṹ�� ͼ �ṹ���У� Vnode[vex_num]; vex_num ; 
typedef struct arcnode   // �߽��Ķ��� 
{
	int arcvex;
	struct arcnode *nextarc;
}Arcnode;

typedef struct vnode   // �ڽӱ��� �����Ķ��壻  ͼ�д�� Vnode[g.vex_num] 
{ 
	char vexnode_name;
	Arcnode *firstarc;
}Vnode;


// ����ջ ����ɶ�ͼ����ȱ��� 

 
void DFS_nonrecursion(graph g,int pos)
{
	int visit[g.vex_num];  // ��¼����Ƿ���ʹ� 
	int stack[g.vex_num];   //  ջ����ʵ��������ȣ�ÿ�ζ�ջ�����д��� 
	printf("��%d��㿪ʼ������ȱ�����");
	push_stack(pos);   // ��pos��ջ����������з��ʣ� ��visit ��Ϊ1�� 
	printf("%d",pos);
	visit[pos] = 1 ; 
	while(stack_not_empty(stack))   // ջ�ǿգ� 
	{
		temp = get_top(stack);
	    p = g.Vnode[temp].firstarc;  // �ҵ�ջ��Ԫ���ڽӱ�ĵ�һ�����p�� 
	    while(p!=NULL)   // ��һ��ѭ���ҵ�δ���ʣ���visit[p->temp]==0)���Ǹ���㣻 
	    {
	    	while(visit[p->arcvex]==1&&p!=NULL)
	    	{
	    		p = p->nextarc;   
			}
            if(p== NULL)
            {
            	break; 
			}
			printf("->%d",p->arcvex);             // p����ָ����һ����δ���ʵĵ� 
			push_stack(p->arcvex);                // ���Ǹ�����ջ
			visit[p->arcvex] = 1;
			p = g.Vnode[p->arcvex].firstarc; 
		}
		pop_stack(stack);   //�� ջ��Ԫ�������Ҳ���ʱ�����ջ�� 
	} 
	 
} 
