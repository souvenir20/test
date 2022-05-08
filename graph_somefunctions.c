#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_dis 0
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


typedef int boolean;
boolean visit[max_line];  // 定义一个全局标志数组，用来记录图结点访问情况；

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
        if (visit[i] == 0 && g.matrix[i][v_pos] != 0)  // 循环，若有 未访问结点以及 其为连通 则可以对其进行访问
        {
            Death_search(g, i); // 递归使用，退出条件即为 不进入 if 语句，此时所有能访问的结点均已访问完毕
        }
    }
}



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
            if (g.matrix[i][j] != 0) // 若邻接矩阵ij元素不为0，代表此时两个结点链接，i结点连接的节点数加1；
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
int dijkstra(Graph g, int start, int end, int* path)
{
    //TODO
}

/**
 * 计算图的直径。提示：Floyd算法
 * @param g 图
 * @return 直径的长度
 */
int Diameter(Graph g) {
    //TODO
}


/**
 * 计算图的半径
 * @param g 图
 * @return 半径长度
 */
int Radius(Graph g) {
    //TODO
}


int main() {
    int node_num;
    int edge_num;
    scanf("%d %d\n", &node_num, &edge_num);
    int start_idx, end_idx, weight;
    Graph g = createGraph(node_num);
    for (int i = 0; i < node_num; i++) {
        sprintf(g.vertex[i], "%d", i);
    }
    for (int i = 0; i < edge_num; i++) {
        scanf("%d %d %d", &start_idx, &end_idx, &weight);
        g.matrix[start_idx][end_idx] = weight;
        g.matrix[end_idx][start_idx] = weight;
    }

    printf("connected: %d\n", isConnected(g));

    int* degree = (int*)malloc(sizeof(int) * g.N);
    nodeDegree(g, degree);
    printf("degree distribution:\n");
    for (int i = 0; i < g.N; i++)
    {
        printf("node%s:%d ", g.vertex[i], degree[i]);
    }
    free(degree);
    return 0;
}
