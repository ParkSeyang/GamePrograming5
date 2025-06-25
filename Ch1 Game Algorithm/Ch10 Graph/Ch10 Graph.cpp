#include <iostream>
#include <vector>
#include <stack>  // DFS - stack 으로 표현한다.  데이터 입출력 방식 LIFO(Last in first out)
#include <queue>  // BFS - queue 으로 표현한다.  데이터 입출력 방식 FIFO(First in first out)
using namespace std;

/*
* 1. 정렬 (데이터 순서 대로 나열)
* 2. 탐색 (데이터의 수정 및 삭제)
* 
* - vector 정렬 시키고 이진 탐색
* - Tree 자료 구조, 이진 검색 트리
* - Heap (우선 순위 큐 priority Queue)
* 
* - Graph 탐색.
* 
* 그래프가 무엇일까?
* - 점 (Vertex)와 간선(edge)으로 표현한 자료구조이다.
* - <기준>
* 1. 방향(Direction) 이 존재하는가 안하는가?
* 2. 순환 (Cycle)이 존재하는가?
* 3. 가중치(weight)가 존재하는가?
* 
* Tree = DAG(방향이 존재하고, ACycle 순환이 없는, Graph 그래프)
* 
* 그래서 그래프를 어떻게 표현할 것인가?
* 1. 2차원 배열 (Matrix방식)
* 2. 각 정점에서 연결된 데이터를 자료구조 표현하는 방식
*/

/* 그래프를 Matrix로 표현했을 때 실제로 어떻게 점과 선이 연결되어있는지 알 수 있다.
*     A    B    C    D
*  A  0    1    1    1
*  B  1    0    1    1
*  C  1    1    0    0 
*  D  1    1    0    0
* 
* (연결된 데이터들)
* A : B - C - D
* B : A - C - D
* C : A - B
* D : A - B
* 
* 프로그래밍으로 그래프를 표현할 수 있게 되었습니다.
* 연결되어 있는 그래프를 탐색을 하는 방법?
* [1] 깊이 우선 탐색 (Depth First Search)
* [2] 너비 우선 탐색 (Breadth First Search)
* 
*/

/* 도전 과제
* 게임 속에서 점과 선으로 연결되어 있는 이미지를 하나 찾아보세요.
* 점과 선을 그래프로 표현하는 것을 아무 주제나 선택해보세요 실행해보세요.
*/



class Graph
{
private:
    int Vertex; // 점의 갯수 (도시, 노드)
    vector<vector<int>> adjacentMatrix; // 각 점에서 인접한 점을 저장하는 2차원 배열

    // 한번 지나간 길은 봤다(들렀다).

    vector<bool> visited;

    void DFS(int v)
    {
        // v방문 visited = true
        visited[v] = true;
        cout << v << " ";

        for (auto& i : adjacentMatrix[v])
        {
            // adj 안에 B, C, D ("B") - > DFS 실행, 재귀방식으로

            if (visited[i] == false)  // 조건 만약에 Vertex에 방문하지 않앗다면 코드를 실행, 방문을했다면 하지마세요.
            {
                DFS(i);   // DFS(B) -> DFS(C) -> DFS(D)
            }
              
        }
    }

    void DFSIter(int v)
    {
        // 방문한 점은 true로 반환합니다.
        

        // 재귀방식을 사용하지 않고 반복문을 사용해서 표현해보세요.

        stack<int> stack;
        stack.push(v);
        
        // 힌트
        // stack.push
        // push - pop;
        // while(empty)
        // top, pop
        // 조건 방문하지 않앗을 때만

        // push() <- 연결되어 있는 자식 데이터를 추가
        while (!stack.empty())
        {
           int cVertex = stack.top();
           
           stack.pop();

           // Stack : 데이터를 삽입 후 가장 마지막에 들어온 데이터를 먼저 실행하라.
           // 반복문. 역순으로 데이터를 실행하게 만들어 준다.

           if (visited[cVertex] == false)
           {
               visited[cVertex] = true;
               cout << v << " ";
           }


           // 이웃 노드
           for (int i = adjacentMatrix[cVertex].size() - 1; i >= 0; i--)
           {
               int neighbor = adjacentMatrix[cVertex][i];
               if (visited[neighbor] == false)
               {
                   stack.push(neighbor);
               }
           }

        }


    }



public:
    // 생성자. 점의 갯수, 2차원 배열 V의 갯수 만큼 모두 0으로 초기화
    Graph(int vertex) : Vertex(vertex)
    {
        adjacentMatrix.resize(Vertex);
        visited.resize(Vertex, false);
    }

    void addEdge(int u, int v)       // 쌍방향, 단방향 연결
    {
        adjacentMatrix[u].push_back(v);  // u가 1  v가 2 1번 점에 연결된 값 : 2
        adjacentMatrix[v].push_back(u);
    }

    void PrintGraph()
    {
        for (int i = 0; i < Vertex; i++)
        {
            cout << "정점 " << i << " 의 인접한 리스트 : ";
            for (auto& elem : adjacentMatrix[i])
            {
                cout << " -> " << elem;
            }
            cout << endl;
        }
    }

    void DFSTraverse(int startV)
    {
        // 방문한 경험을 리셋 시킨다.
        fill(visited.begin(), visited.end(), false);

        cout << "DFS 탐색 결과 (시작 지점 : " << startV << ") ";
        DFS(startV);
        cout << endl;
    }

    void DFSIterTraverse(int startV)
    {
        fill(visited.begin(), visited.end(), false);

        cout << "DFS Iterative 탐색 결과 (시작 지점 : " << startV << ") ";
        DFSIter(startV);
        cout << endl;
    }


};

class GraphMatrix
{
private:
    int V;
    std::vector<vector<int>> adj;
public:
    GraphMatrix(int v) : V(v), adj(v, vector<int>(v, 0)) {}  // v * v 2차원 배열을 0으로 초기화

    void addEdge(int u, int v)
    {
        adj[u][v] = 1;  // 단 방향
        adj[v][u] = 1;
    }

    void PrintGraph()
    {
        cout << "인접 행렬" << endl;
        
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                cout << adj[i][j] << " ";
            }
            cout << endl;
        }

    }

};



int main()
{
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(0, 3);

    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.DFSTraverse(0);
    g.DFSIterTraverse(3);
    g.PrintGraph();

    GraphMatrix gm(4);

    gm.addEdge(0, 1);
    gm.addEdge(0, 2);
    gm.addEdge(0, 3);
    gm.addEdge(1, 2);
    gm.addEdge(1, 3);

    gm.PrintGraph();


}

