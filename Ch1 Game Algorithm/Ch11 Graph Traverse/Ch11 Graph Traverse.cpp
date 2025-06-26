#include <iostream>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

/* 1. DFS
* - 그래프가 모두 연결 되어 있는가? connected Graph
* - 핵심 아이디어 : 그래프 (점, 선)
* - 점의 갯수가 고정되어 있다.
* - 만약에 점 사이에 연결된 길이 없다면 순회하면서 만나 점의 갯수를 증가시키는 결과 값, 점의 수가 다르게 나올 것이다.
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
                cout << cVertex << " ";
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

    void BFSIter(int start)
    {
        queue<int> q;
        visited[start] = true;
        q.push(start);   // 그래프의 시작 노드를 삽입


        while (!q.empty())
        {
            int c = q.front();
            q.pop();

            cout << c << " ";

            // c에 연결되어 있는 노드를 접근하는 코드 adj[c]
            for (auto& e : adjacentMatrix[c])
            {
                if (visited[e] == false)
                {
                    visited[e] = true;
                    q.push(e);
                }
            }

        }

    }

    void BFSRecursive(queue<int>& q)
    {
        // 1. 재귀 함수의 탈출 조건을 작성해 보세요 ( q가 empty 일때)
        // BFS 반복 방식의 코드를 여기에 가져와 보세요.
        if (q.empty())
        {
            return;
        }

        int c = q.front();
        q.pop();
        cout << c << " ";

        for (auto& e : adjacentMatrix[c])
        {
            if (!visited[e])
            {
                visited[e] = true;
                q.push(e);
            }
        }

        BFSRecursive(q);

    }

    void BFS(int start)
    {
        queue<int> q;
        q.push(start);
        visited[start] = true;
        BFSRecursive(q);

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

    void BFSIterTraverse(int startV)
    {
        fill(visited.begin(), visited.end(), false);   // 방문 경혐을 초기화 하는 코드

        cout << "BFS Iterative 방식 탐색 결과 (시작 지점 : " << startV << ") ";
        BFSIter(startV);
        cout << endl;
    }

    void BFSTraverse(int startV)
    {

        fill(visited.begin(), visited.end(), false);   // 방문 경혐을 초기화 하는 코드

        cout << "BFS 방식 탐색 결과 (시작 지점 : " << startV << ") ";
        BFS(startV);
        cout << endl;
    }

    // 모든 그래프가 연결되어 있나요?

    void DFSCount(int& count, int startV)
    {
        // DFS - Stack

        visited[startV] = true;

        count++;

        for (int e : adjacentMatrix[startV])
        {
            if (!visited[e])
            {
                visited[e] = true;
                DFSCount(count, e);
            }
        }

    }

    bool IsConnected(int startV)
    {
        fill(visited.begin(), visited.end(), false);

        int count = 0;
        // DFS 순회하면서 출력 대신에 count수를 증가시켜라.

        DFSCount(count, startV);

        return count == Vertex; 

    }


    void CheckGraphIsConnected()
    {
        if (IsConnected(0))
        {
            cout << "모든 그래프가 연결되었습니다." << endl;
        }
        else
        {
            cout << "연결되지 않은 그래프가 존재합니다." << endl;
            cout << "-1";
        }
    }

    // 경로 찾기 (최소의 거리를 찾는 문제)  -BFS, 다익스트라(비용이 있을 때 길을 찾는 방법), 프림
    

    vector<int> refindPath(vector<int>& parent, int start, int end)
    {
        vector<int> path;

        if (parent[end] == -1 && start != end)  // parent -1로 초기화. 접근을 못한다? 길을 못찾았다.
        {
            return path; // 경로가 없는 데이터 반환;
        }

        int current = end;

        while (current != -1)
        {
            path.insert(path.begin(), current);
            current = parent[current];
        }

        return path;

    }


    vector<int> findShortestPath(int start, int end)
    {
        if (start == end)
        {
            return { end };
        }

        fill(visited.begin(), visited.end(), false);

        queue<int> q;

        vector<int> parent(Vertex, -1);  // 목표 지점까지의 배열을 저장한다.
        
        vector<int> distance(Vertex, -1);  // 노드의 거리를 저장하는 배열

        q.push(start);
        visited[start] = true;
        distance[start] = 0;

        while (!q.empty())
        {
            int c = q.front();

            q.pop();

            // while을 강제 종료해야하는 조건. (현재 노드가 목표 지점에 도착 했을 때)
            if (end == c)
            {
                break;
            }
            // 도착을 안했으면?
            for (int e : adjacentMatrix[c])
            {
                if (!visited[e])
                {
                    visited[e] = true;
                    q.push(e);
                    parent[e] = c;
                    distance[e] = distance[c] + 1;
                }
            }
        }

        return refindPath(parent, start, end);
    }

    


};



int main()
{
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(2, 5);
    g.CheckGraphIsConnected();

   vector<int> temp = g.findShortestPath(0, 5);

   cout << "0에서 5로 이동하는 최소 거리" << endl;

   for (auto& e : temp)
   {
       cout << "->" << e;
   }

}

