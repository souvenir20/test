
// �ú�����ӡ ͼg ��start �� target �������м�·����i ��ʾ�ڵ�ǰ������path�ĸ�������ʼΪ 0 
//  path ������¼�� start �� target ��·�� ��ֻ�����ҵ� Ŀ���� �Ż��ӡ�� 

void find_path(graph g,int start,int target,int i,int path[])
{
	int visit[max_size] = {0};   // ���������Щ����ڴ˴�Ѱ�����Ѿ����ʣ� 
	arcnode *p = NULL;
	visit[start] = 1;            // �Ե�ǰ�����ʣ���path�����жϣ� 
	path [i++] = start ;
	if(start == target)
	{
		print_path(path,i);
	}
    p = g.Vnode[start].firstarc;
    while(p!=NULL)                   // ��ѭ�������Ҵ�start ������ܵ����������㣻 
    {
    	if(visit[p->vexnum]==0)
    	{
    		find_path(g,p->vexnum,target,i,path); // ��ʼ�ݹ飬����DFS 
		}
		p = p->nextacr; // �ȵ����溯����ջ�����ǰһ�������� p �����ƶ��� 
	}
	visit[start] = 0;  // ȡ����� ��������ֻ����һ���� 
} 




//�ú������������ find_path �Ļ����Ͻ����޸ģ���ΪҲ�ȵ��ҵ���Ӧ��·�����ܽ����жϣ� 

int flag = 0;  // ȫ�ֱ�����0 ��ʾû�ҵ��� 1��ʾ�ҵ��� k ���ȵ�·���� 

int calculate_pathlength(int path[],int n)
{
	int i=0;
	int sum = 0;
	int vex1 = path[i];             // ��path �е�һ�͵ڶ� ����㸳ֵ�� vex1 �� vex2�� 
	int vex2 = path[i+1];
	arcnode *p = NULL; 
	for(i=1;i<n;i++)
	{
		p = g.Vnode[vex1].firstarc;
		while(p->vexnum!=vex2)   // �ҵ� vex1 �� vex2 �ı� p
		{
			p = p->nextacr ; 
		}
		sum += p->weight;   // �������ߵ�Ȩ���ۼƵ� sum �У� 
		vex1 = path[i];     // ����һ���ߣ� 
		vex2 = path[i+1];
	}
	return sum;
}

void find_path(graph g,int start,int target,int i,int path[],int k)
{
	int length;
	int visit[max_size] = {0};   // ���������Щ����ڴ˴�Ѱ�����Ѿ����ʣ� 
	arcnode *p = NULL;
	visit[start] = 1;            // �Ե�ǰ�����ʣ���path�����жϣ� 
	path [i++] = start ;
	if(start == target)
	{
		length = calculate_pathlength(path,i); 
		if(length == k)
		{
			flag = 1;
			print_path(path,i); //��ӡ����Ϊk��·���� 
		}
	}
    p = g.Vnode[start].firstarc;
    while(p!=NULL)                   // ��ѭ�������Ҵ�start ������ܵ����������㣻 
    {
    	if(visit[p->vexnum]==0)
    	{
    		find_path(g,p->vexnum,target,i,path); // ��ʼ�ݹ飬����DFS 
		}
		p = p->nextacr; // �ȵ����溯����ջ�����ǰһ�������� p �����ƶ��� 
	}
	visit[start] = 0;  // ȡ����� ��������ֻ����һ���� 
} 
