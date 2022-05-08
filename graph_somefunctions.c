#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_dis 0
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


typedef int boolean;
boolean visit[max_line];  // ����һ��ȫ�ֱ�־���飬������¼ͼ�����������

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
        if (visit[i] == 0 && g.matrix[i][v_pos] != 0)  // ѭ�������� δ���ʽ���Լ� ��Ϊ��ͨ ����Զ�����з���
        {
            Death_search(g, i); // �ݹ�ʹ�ã��˳�������Ϊ ������ if ��䣬��ʱ�����ܷ��ʵĽ����ѷ������
        }
    }
}



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
            if (g.matrix[i][j] != 0) // ���ڽӾ���ijԪ�ز�Ϊ0�������ʱ����������ӣ�i������ӵĽڵ�����1��
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
int dijkstra(Graph g, int start, int end, int* path)
{
    //TODO
}

/**
 * ����ͼ��ֱ������ʾ��Floyd�㷨
 * @param g ͼ
 * @return ֱ���ĳ���
 */
int Diameter(Graph g) {
    //TODO
}


/**
 * ����ͼ�İ뾶
 * @param g ͼ
 * @return �뾶����
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
