#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

#define max_dis 100000
#define max_line 1000

typedef char vextype[20];
typedef struct {
    int N, E;//N是顶点数，E是边数
    int** matrix;//储存邻接矩阵
    vextype* vertex;//存储节点的名字
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
boolean visit[max_line];  // 定义一个全局标志数组，用来记录图结点访问情况；
boolean flag[max_line] = {0};   // 用来判断 当前结点在 S中还是在 V-S中
int flag2[max_line]; // 用来存储访问到该点前的一个节点； 

 
/**
 * 创建一个节点数为n的图
 * @param n 节点个数
 * @return 返回这个图
 */
Graph createGraph(int n) {
    int i, j;
    Graph g;
    g.N = n;
    g.matrix = (int**)malloc(sizeof(int*) * g.N); //创建二维数组 n*n
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
 * 根据距离d和路径数组path输出路径，这样就不需要路径的节点数也能正确输出路径
 * @param d 路径长度
 * @param diameter_path 储存路径的数组
 * @param g 图
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
 * 判断图是否连通
 * @param g 图
 * @return 连通返回1，否则返回0
 */
int Death_search(Graph g, int v_pos)  //深度遍历函数；传参为 图 以及 访问的结点位置；
{
    int i = 0; 
    visit[v_pos] = 1;   //访问到 v_pos 时，将其 visit 对应的标志 改为 1；
    for (i = 0; i < g.N; i++)
    {
        if (visit[i] == 0 && g.matrix[i][v_pos] != 0 && g.matrix[i][v_pos] != max_dis)  // 循环，若有 未访问结点以及 其为连通 则可以对其进行访问
        {
            Death_search(g, i); // 递归使用，退出条件即为 不进入 if 语句，此时所有能访问的结点均已访问完毕
        }
    }
}


// 函数功能 ：查询图是否为连通图； 
int isConnected(Graph g) {
    int i = 0;
    int flag = 1; // 初始为0，代表全都访问
    Death_search(g, 0);
    for (i = 0; i < g.N; i++)
    {
        if (visit[i] == 0)
        {
            flag = 0;   // flag 为1代表 至少有一个结点没访问到；
        }
    }
    return flag;
}


/**
 * 计算每个点的度
 * @param g 图
 * @param node_degree 将每个点的度写到这个数组中
 */
void nodeDegree(Graph g, int* node_degree) {  // 遍历邻接矩阵
    int i = 0;
    int j = 0;
    int onenode_degree = 0;
    for (i = 0; i < g.N; i++)
    {
        onenode_degree = 0;  // 每次进去 第 i行 记得初始化节点数；
        for (j = 0; j < g.N; j++)  // 扫描第i个结点 有连接的点数 ，并将点数放进数组 node_degree中；
        {
            if (g.matrix[i][j] != 0 && g.matrix[i][j]!= max_dis) // 若邻接矩阵ij元素不为0，代表此时两个结点链接，i结点连接的节点数加1；
            {
                onenode_degree++;
            }
            node_degree[i] = onenode_degree;
        }
    }
}

/**
 * 计算图的聚类系数
 * @param g 图
 * @return 返回聚类系数
 */
double clusteringCoefficient(Graph g) {  
	int i=0;
	int j=0;
	int y=0;
	int z=0;
	int i_array[20]={0}; // 记录与i 结点相连接的那些结点； 
	double clustering_num = 0;
	double i_close_edge_num = 0;
	for(i=0;i<g.N;i++)
	{
		int k = 0;
		double i_connum=0; // 记录与i结点连接的节点个数； 
		double max_connected = 0;  // 用来记录 结点 i 的链接的最大 产生的 连接数 
		i_close_edge_num = 0;
		for(j=0;j<g.N;j++)
		{
			if(g.matrix[i][j]!=0&&g.matrix[i][j]!=max_dis)
			{
				i_connum ++;
				i_array[k] = j; // 将下标存放在数组 i_ array 中； 
				k++;
			}
		}
		for(z=0;z<k;z++)
		{
			for(y=0;y<k;y++)
			{
				if(g.matrix[i_array[z]][i_array[y]]!=0&&g.matrix[i_array[z]][i_array[y]]!=max_dis)    
				{
					i_close_edge_num ++;   // 得到与 i 链接 的 结点的连接边数；（记得除以2） 
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
		else // 特殊情况处理1 ： 结点找不到链接点 
		{
			clustering[i] = 0;
		}
	}
    for(i=0;i<g.N;i++)
    {
    	clustering_num+=clustering[i]; //得到全部聚类系数的和； 
	}
	return clustering_num / (g.N);  // 返回平均值； 
    //TODO
}

/**
 * 使用dijkstra算法计算单源最短路径
 * @param g 图
 * @param start 起点
 * @param end 终点
 * @param path 从start到end的路径, [start,...,end]
 * @return 路径长度
 */
int dijkstra(Graph g, int start, int end, int* path) // g , start代表 dist 数组存储 的相关最短路径 最后返回的是 dist [end]  ， path代表的 
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
	flag[start] = 1;  // 此时将start 放进S集合中，代表此时哪些节点的dist已经可以固定，找到了最小值； 
	for(i=0;i<g.N;i++)
	{
		int temp = max_dis;
		int min_node = start; 
		for(j=0;j<g.N;j++)   // 用来寻找在 V-S集合中 dist 值最小的那个结点 
		{
			if(flag[j]==0 && dist[j]<temp)
			{
				min_node = j;
				temp = dist[j];
			}
		}
//		if(min_node == start)   // 没找到对应的最小距离的结点 
//		{
//			return ;
//		} 
		flag[min_node] = 1;
		for(j=0;j<g.N;j++)
		{
			if(flag[j]== 0 && g.matrix[min_node][j]<max_dis)
			{//！flag[j]表示j在v-s集合中，map[t][j]<INF表示t与j邻接
				if(dist[j]>(dist[min_node]+g.matrix[min_node][j])){//经过t到达j的路径更短
					dist[j]=dist[min_node]+g.matrix[min_node][j];
					flag2[j]=min_node;	//记录j的前驱为t
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
 * 计算图的直径。提示：Floyd算法
 * @param g 图
 * @return 直径的长度
 */
int Diameter(Graph g) {
	int k=0;
	int i=0;
	int j=0;
    int temp = g.matrix[0][0];
	for(k=0;k<g.N;k++)  // 三重循环，将图的矩阵 转变成 任意两个节点的距离 （最短）； 
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
	for(i=0;i<g.N;i++) //找到 floyd 矩阵中的最大值 即为直径； 
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
 * 计算图的半径
 * @param g 图
 * @return 半径长度
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
         			g.matrix[i][j] = g.matrix[i][k] + g.matrix[k][j];  // 得到一个floyd 矩阵，存放的都是 
				}
			}
		 }
	} 
	for(i=0;i<g.N;i++) //找到 floyd 矩阵中的最大值 即为直径； 
	{
		temp = g.matrix[i][0];
		for(j=0;j<g.N;j++)  // 找到这一行的最大值 
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
