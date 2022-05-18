#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

#define max_dis 100000
#define max_line 1000

typedef char vextype[20];
typedef struct {
    int N, E;//N�Ƕ�������E�Ǳ���
    int** matrix;//�����ڽӾ���
    vextype* vertex;//�洢�ڵ������
} Graph;




Graph createGraph(int n);
int isConnected(Graph g);
void nodeDegree(Graph g, int* node_degree);
double clusteringCoefficient(Graph g);
int Diameter(Graph g);
int Radius(Graph g);
int dijkstra(Graph g, int start, int end, int* path);
void printPath(int d, int* diameter_path, Graph g);


double clustering[20];

typedef int boolean;
boolean visit[max_line];  // ����һ��ȫ�ֱ�־���飬������¼ͼ�����������
boolean flag[max_line] = {0};   // �����ж� ��ǰ����� S�л����� V-S��
int flag2[max_line]; // �����洢���ʵ��õ�ǰ��һ���ڵ㣻 

 
/**
 * ����һ���ڵ���Ϊn��ͼ
 * @param n �ڵ����
 * @return �������ͼ
 */
Graph createGraph(int n) {
    int i, j;
    Graph g;
    g.N = n;
    g.matrix = (int**)malloc(sizeof(int*) * g.N); //������ά���� n*n
    for (i = 0; i < n; i++) {
        g.matrix[i] = (int*)malloc(sizeof(int) * g.N);
    }
    for (i = 0; i < g.N; i++) {
        for (j = 0; j < g.N; j++) {
            g.matrix[i][j] = max_dis;
        }
    }
    for (i = 0; i < g.N; i++) {
        g.matrix[i][i] = 0;
    }
    g.vertex = (vextype*)malloc(sizeof(vextype) * g.N);
    return g;
}

/**
 * ���ݾ���d��·������path���·���������Ͳ���Ҫ·���Ľڵ���Ҳ����ȷ���·��
 * @param d ·������
 * @param diameter_path ����·��������
 * @param g ͼ
 */
void printPath(int d, int* diameter_path, Graph g)
{
    int k = 0;
    int path_length = 0;
    printf("Path: ");
    do {
        printf("%s ", g.vertex[diameter_path[k]]);
        path_length += g.matrix[diameter_path[k]][diameter_path[k + 1]];
        k++;
    } while (path_length < d);
    printf("%s\n", g.vertex[diameter_path[k]]);
}

/**
 * �ж�ͼ�Ƿ���ͨ
 * @param g ͼ
 * @return ��ͨ����1�����򷵻�0
 */
int Death_search(Graph g, int v_pos)  //��ȱ�������������Ϊ ͼ �Լ� ���ʵĽ��λ�ã�
{
    int i = 0; 
    visit[v_pos] = 1;   //���ʵ� v_pos ʱ������ visit ��Ӧ�ı�־ ��Ϊ 1��
    for (i = 0; i < g.N; i++)
    {
        if (visit[i] == 0 && g.matrix[i][v_pos] != 0 && g.matrix[i][v_pos] != max_dis)  // ѭ�������� δ���ʽ���Լ� ��Ϊ��ͨ ����Զ�����з���
        {
            Death_search(g, i); // �ݹ�ʹ�ã��˳�������Ϊ ������ if ��䣬��ʱ�����ܷ��ʵĽ����ѷ������
        }
    }
}


// �������� ����ѯͼ�Ƿ�Ϊ��ͨͼ�� 
int isConnected(Graph g) {
    int i = 0;
    int flag = 1; // ��ʼΪ0������ȫ������
    Death_search(g, 0);
    for (i = 0; i < g.N; i++)
    {
        if (visit[i] == 0)
        {
            flag = 0;   // flag Ϊ1���� ������һ�����û���ʵ���
        }
    }
    return flag;
}


/**
 * ����ÿ����Ķ�
 * @param g ͼ
 * @param node_degree ��ÿ����Ķ�д�����������
 */
void nodeDegree(Graph g, int* node_degree) {  // �����ڽӾ���
    int i = 0;
    int j = 0;
    int onenode_degree = 0;
    for (i = 0; i < g.N; i++)
    {
        onenode_degree = 0;  // ÿ�ν�ȥ �� i�� �ǵó�ʼ���ڵ�����
        for (j = 0; j < g.N; j++)  // ɨ���i����� �����ӵĵ��� �����������Ž����� node_degree�У�
        {
            if (g.matrix[i][j] != 0 && g.matrix[i][j]!= max_dis) // ���ڽӾ���ijԪ�ز�Ϊ0�������ʱ����������ӣ�i������ӵĽڵ�����1��
            {
                onenode_degree++;
            }
            node_degree[i] = onenode_degree;
        }
    }
}

/**
 * ����ͼ�ľ���ϵ��
 * @param g ͼ
 * @return ���ؾ���ϵ��
 */
double clusteringCoefficient(Graph g) {  
	int i=0;
	int j=0;
	int y=0;
	int z=0;
	int i_array[20]={0}; // ��¼��i ��������ӵ���Щ��㣻 
	double clustering_num = 0;
	double i_close_edge_num = 0;
	for(i=0;i<g.N;i++)
	{
		int k = 0;
		double i_connum=0; // ��¼��i������ӵĽڵ������ 
		double max_connected = 0;  // ������¼ ��� i �����ӵ���� ������ ������ 
		i_close_edge_num = 0;
		for(j=0;j<g.N;j++)
		{
			if(g.matrix[i][j]!=0&&g.matrix[i][j]!=max_dis)
			{
				i_connum ++;
				i_array[k] = j; // ���±��������� i_ array �У� 
				k++;
			}
		}
		for(z=0;z<k;z++)
		{
			for(y=0;y<k;y++)
			{
				if(g.matrix[i_array[z]][i_array[y]]!=0&&g.matrix[i_array[z]][i_array[y]]!=max_dis)    
				{
					i_close_edge_num ++;   // �õ��� i ���� �� �������ӱ��������ǵó���2�� 
				}
			}
		}
		if(i_connum!=0)    
		{
			if(i_close_edge_num!=0)
			{
				max_connected = (i_connum)*(i_connum-1)/2;
			    clustering[i] = (i_close_edge_num/2) / max_connected;
			} 
			else
			{
				clustering[i]= 0;
			}
		}
		else // �����������1 �� ����Ҳ������ӵ� 
		{
			clustering[i] = 0;
		}
	}
    for(i=0;i<g.N;i++)
    {
    	clustering_num+=clustering[i]; //�õ�ȫ������ϵ���ĺͣ� 
	}
	return clustering_num / (g.N);  // ����ƽ��ֵ�� 
    //TODO
}

/**
 * ʹ��dijkstra�㷨���㵥Դ���·��
 * @param g ͼ
 * @param start ���
 * @param end �յ�
 * @param path ��start��end��·��, [start,...,end]
 * @return ·������
 */
int dijkstra(Graph g, int start, int end, int* path) // g , start���� dist ����洢 ��������·�� ��󷵻ص��� dist [end]  �� path����� 
{
	int j=0;
	int i=0;
	int k=0; 
	int temp;
	int dist[max_line];
	int oppo_path[max_line];
	for(i=0;i<g.N;i++)
	{
		dist[i] = g.matrix[start][i] ;
		flag[i] = 0 ;
		if(g.matrix[start][i]!=max_dis&&g.matrix[start][i]!=0)
		{
			flag2[i] = start;
		}
		else
		{
			flag2[i] = -1;
		}
	}
	flag[start] = 1;  // ��ʱ��start �Ž�S�����У������ʱ��Щ�ڵ��dist�Ѿ����Թ̶����ҵ�����Сֵ�� 
	for(i=0;i<g.N;i++)
	{
		int temp = max_dis;
		int min_node = start; 
		for(j=0;j<g.N;j++)   // ����Ѱ���� V-S������ dist ֵ��С���Ǹ���� 
		{
			if(flag[j]==0 && dist[j]<temp)
			{
				min_node = j;
				temp = dist[j];
			}
		}
//		if(min_node == start)   // û�ҵ���Ӧ����С����Ľ�� 
//		{
//			return ;
//		} 
		flag[min_node] = 1;
		for(j=0;j<g.N;j++)
		{
			if(flag[j]== 0 && g.matrix[min_node][j]<max_dis)
			{//��flag[j]��ʾj��v-s�����У�map[t][j]<INF��ʾt��j�ڽ�
				if(dist[j]>(dist[min_node]+g.matrix[min_node][j])){//����t����j��·������
					dist[j]=dist[min_node]+g.matrix[min_node][j];
					flag2[j]=min_node;	//��¼j��ǰ��Ϊt
				}  
			}
	    }
	}
	    k=0;
		temp = flag2[end];
		i=0;
		while(temp != -1)
		{
			oppo_path[i++] = temp;
		    temp = flag2[temp];
		}
		for(i=i-1;i>=0;i--)
		{
			path[k++] = oppo_path[i];
		}
		path[k] = end;
	return dist[end];
    //TODO
}


/**
 * ����ͼ��ֱ������ʾ��Floyd�㷨
 * @param g ͼ
 * @return ֱ���ĳ���
 */
int Diameter(Graph g) {
	int k=0;
	int i=0;
	int j=0;
    int temp = g.matrix[0][0];
	for(k=0;k<g.N;k++)  // ����ѭ������ͼ�ľ��� ת��� ���������ڵ�ľ��� ����̣��� 
	{
        for(i=0;i<g.N;i++)
         {
         	for(j=0;j<g.N;j++)
         	{
         		if(g.matrix[i][j]>g.matrix[i][k]+g.matrix[k][j])
         		{
         			g.matrix[i][j] = g.matrix[i][k] + g.matrix[k][j];
				}
			}
		 }
	} 
	for(i=0;i<g.N;i++) //�ҵ� floyd �����е����ֵ ��Ϊֱ���� 
	{
		for(j=0;j<g.N;j++)
		{
			if(temp<g.matrix[i][j])
			{
				temp = g.matrix[i][j];
			}
		}
	}
	return temp;
    //TODO
}



/**
 * ����ͼ�İ뾶
 * @param g ͼ
 * @return �뾶����
 */
int Radius(Graph g) {
	int k=0;
	int i=0;
	int j=0;
	int radius = 0;
	int *eccentricity = (int*)malloc(sizeof(int)*g.N);
    int temp = g.matrix[0][0];
	for(k=0;k<g.N;k++)
	{
        for(i=0;i<g.N;i++)
         {
         	for(j=0;j<g.N;j++)
         	{
         		if(g.matrix[i][j]>g.matrix[i][k]+g.matrix[k][j])
         		{
         			g.matrix[i][j] = g.matrix[i][k] + g.matrix[k][j];  // �õ�һ��floyd ���󣬴�ŵĶ��� 
				}
			}
		 }
	} 
	for(i=0;i<g.N;i++) //�ҵ� floyd �����е����ֵ ��Ϊֱ���� 
	{
		temp = g.matrix[i][0];
		for(j=0;j<g.N;j++)  // �ҵ���һ�е����ֵ 
		{
			if(temp<g.matrix[i][j])
			{
				temp = g.matrix[i][j];
			}
		}
		eccentricity[i] = temp ;
	}
	radius = eccentricity[0];
	for(i=0;i<g.N;i++)
	{
		if(radius>eccentricity[i])
		{
			radius = eccentricity[i];
		}
	}
	free(eccentricity);
	return radius;
    //TODO
}


int main() {
    int node_num;
    int edge_num;
    int i = 0; 
    scanf("%d %d\n", &node_num, &edge_num);
    int start_idx, end_idx, weight;
    Graph g = createGraph(node_num);
    for (i = 0; i < node_num; i++) {
        sprintf(g.vertex[i], "%d", i);
    }
    for (i = 0; i < edge_num; i++) {
        scanf("%d %d %d", &start_idx, &end_idx, &weight);
        g.matrix[start_idx][end_idx] = weight;
        g.matrix[end_idx][start_idx] = weight;
    }
    printf("connected: %d\n", isConnected(g));
    
//	if(isConnected(g))
//    {
//        int d = Diameter(g);
//        printf("diameter:%d\n", d);
//
//        int r = Radius(g);
//        printf("radius:%d", r);
//    }
//    return 0;
	
		
    if(isConnected(g))
    {
        int *short_path = (int *)malloc(sizeof(int) * g.N);
        int dis = dijkstra(g, 1, 3, short_path);
        printf("the shortest path between 1 and 3: %d\n", dis);
        printPath(dis, short_path, g);
        free(short_path);
    }
    return 0;


//    double c = clusteringCoefficient(g);
//    printf("clustering coefficient:%f", c);
//    printf("connected: %d\n", isConnected(g));
//    int* degree = (int*)malloc(sizeof(int) * g.N);
//    nodeDegree(g, degree);
//    printf("degree distribution:\n");
//    for (i = 0; i < g.N; i++)
//    {
//        printf("node%s:%d ", g.vertex[i], degree[i]);
//    }
//    free(degree);
//    return 0;
}
