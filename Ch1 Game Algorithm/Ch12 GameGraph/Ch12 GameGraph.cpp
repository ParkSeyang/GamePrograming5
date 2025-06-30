#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

/* 이게임에 필요한 것
* 1. 그래프
* 2. 위치를 표현하는 코드. (x,y) (x,y,z) + 노드 정보(이름, 아이디)
*/


class Spire  // spire 라는 게임을 만들어 보고싶다.
{

private:

	struct Node
	{
		int x, y, id;

		string name;
		// 시작, 일반, 엘리트, 보스, 상점, 휴식, 이벤트

		Node(string name, int id, int x, int y) : name(name), id(id), x(x), y(y) {}
	};

	

	// 가변 배열(vector) 노드를 저장하는 컨테이너를 선언해보세요.
	
	vector<Node> nodes;
	vector<vector<int>> adj;   // 인접 행렬 (각 점이 어디에 연결되어 있는지 저장하는 컨테이너)
	vector<bool> visited;
	int nodeCount;

	const int CONSOLEHEIGHT = 40;
	const int CONSOLEWIDTH = 80;


public:
	Spire() : nodeCount(0) {}

	void addNode(string name, int x = 0, int y = 0)  // id와 nodeCount 가 일치하게 만듭니다.
	{
		nodes.emplace_back(name, nodeCount, x, y);   // nodes 컨테이너 데이터를 추가합니다.
		adj.push_back(vector<int>());                // 노드를 추가할 때 인접행렬의 공간을 생성
		visited.push_back(false);                    // 방문체크 공간을 생성해주세요.
		nodeCount++;                                 // 노드의 숫자를 증가시킨다.
	}
	void addEdge(int start, int end)
	{
		adj[start].push_back(end);  // 방향이 있는 그래프이기 때문에 역순으로 연결은 하지 않는다.
	}

	void printGraph()
	{
		for (int i = 0; i < nodeCount; i++)
		{
			cout << "노드 :" << i << "(" << nodes[i].name << ")" << endl;
			cout << "연결된 노드 : ";

			if (adj[i].size())
			{
				cout << "없음";
			}

			else
			{
				for (int j = 0; j < adj[i].size(); j++)
				{
					cout << adj[i][j] << "(" << nodes[adj[i][j]].name << ")" << endl;

					if (j < adj[i].size() - 1)
					{
						cout << ", ";
					}
				}
			}
			
			cout << endl;
		}
	}

	vector<int> refindPath(vector<int>& parent, int start, int end)
	{
		vector<int> path;

		if (parent[end] == -1 && start != end)  // parent -1로 초기화. 접근을 못한다? 길을 못찾았다.
		{
			return path; // 경로가 없는 데이터를 반환.
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
		if (start == end) return { start };

		fill(visited.begin(), visited.end(), false);

		vector<int> parent(nodeCount, -1);   // 목표 지점까지의 배열을 저장한다.
		vector<int> distance(nodeCount, -1); // 노드의 거리를 저장하는 배열
		queue<int> q;
		q.push(start);
		visited[start] = true;
		distance[start] = 0;

		while (!q.empty())
		{
			int c = q.front();
			q.pop();

			// while 강제 종료해야하는 조건. (현재 노드가 목표 지점에 도착했을 때)
			if (end == c) break;

			// 도착을 안햇으면?
			for (int e : adj[c])
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

	// 그래프를 그래픽으로 표현하는 코드
private:
	
	void calculateNodePos()  // 추가해준 노드들을 레벨별로 좌표를 설정하는 코드
	{
		if (nodeCount == 0)  
		{
			return;
		}

		vector<vector<int>> levels;  // 던전의 층을 저장하는 컨테이너
		vector<bool> processed(nodeCount, false);  // 방문한 노드를 기록

		levels.push_back({ 0 });  // 시작지점 : 0층은 항상 0이다.

		processed[0] = true;     // 시작지점은 방문했습니다.

		int currentLevel = 0;

		while (currentLevel < levels.size())  // 각 층의 방의 갯수를 측정하는 코드
		{
			vector<int> nextLevel;

			for (int node : levels[currentLevel])
			{
				for (int neighbor : adj[node])
				{
					if (!processed[neighbor])
					{
						nextLevel.push_back(neighbor);
						processed[neighbor] = true;
					}
					
				}
				if (!nextLevel.empty())
				{
					levels.push_back(nextLevel);
				}

				currentLevel++; // 다음 층을 계산하세요.
			}

			
		}

		// 모든 층의 레벨을 계산을 했으면, 각 노드가 몇 층에 있고, 몇 번째에 있는지 기록이 됩니다.
		
		for (int level = 0; level < levels.size(); level++) // 0층 ~ 마지막 층 까지 반복
		{
			int nodeLevel = levels[level].size();   // 각 층의 방의 갯수
			int spacing = CONSOLEWIDTH / (nodeLevel + 1);     // const ConsoleWIDTH = 80

			for (int i = 0; i < nodeLevel; i++)
			{
				int nodeID = levels[level][i];     // n층 n번째 노드 = id
				nodes[nodeID].x = spacing * (i + 1);  // i가 0부터 시작하기 때문에 1을 더한다.
				nodes[nodeID].y = level * 2 + 2;     // 각 층의 여백 크기를 설정한다.
			}

		}

	}
	void DrawCircle(vector<vector<char>>& screen, int x, int y)
	{
		screen[y][x] = '0';
	}

	void DrawEdge(vector<vector<char>>& screen)
	{
		for (int i = 0; i < nodeCount; i++)
		{
			for (int neighbor : adj[i])
			{
				DrawLine(screen, nodes[i].x, nodes[i].y, nodes[neighbor].x, nodes[neighbor].y);
			}
		}
	}

	void DrawLine(vector<vector<char>>& screen, int x1, int y1, int x2, int y2)  // 정수 사이의 픽셀 선을 그리는 알고리즘 Bresenham
	{
		int dx = abs(x2 - x1);
		int	dy = abs(y2 - y1);

		int sx = (x1 < x2) ? 1 : -1;
		int sy = (y1 < y2) ? 1 : -1;


		int err = dx - dy;

		int x = x1;
		int y = y1;

		while (true)
		{
			if (x >= 0 && x < CONSOLEWIDTH && y >= 0 && y < CONSOLEHEIGHT)
			{
				if (screen[y][x] == ' ')
				{
					screen[y][x] = '-';
				}


				if (x == x2 && y == y2)  // x,y 좌표가 목표지점에 도달했으면 반복을 그만둔다.
				{
					break;
				}

				int e2 = 2 * err;

				if (e2 > -dy)
				{
					err -= dy;
					x += sx;
				}

				if (e2 < dx)
				{
					err += dx;
					y += sy;
				}
			}
		}

	}

	void DrawNode(vector<vector<char>>& screen)
	{
		for (int i = 0; i < nodeCount; i++)
		{
			DrawCircle(screen, nodes[i].x, nodes[i].y);
		}
	}

	void printfScreen(vector<vector<char>>& screen)
	{
		cout << endl;
		for (int y = 0; y < CONSOLEHEIGHT; y++)
		{
			for (int x = 0; x < CONSOLEWIDTH; x++)
			{
				cout << screen[y][x];
			}
			cout << endl;
		}
		cout << endl;

	}

public:

	void drawGraph()
	{
		vector<vector<char>> screen(CONSOLEHEIGHT, vector<char>(CONSOLEWIDTH, ' '));

		calculateNodePos();
		// DrawEdge();         // 선을 먼저 그리고
		DrawNode(screen);         // 선 위에 점을 그린다.
		printfScreen(screen);
	}


};





int main()
{
	Spire spire;

	cout << "슬레이더 스파이어의 맵 노드 구현" << endl;


	spire.addNode("시작");         // 0
	spire.addNode("1층 전투방");    // 1
	spire.addNode("1층 전투방");    // 2
	spire.addNode("1층 전투방");    // 3
	spire.addNode("1층 전투방");    // 4
	spire.addNode("1층 전투방");    // 5

	spire.addNode("2층 엘리트방");   // 6
	spire.addNode("2층 전투방");     // 7
	spire.addNode("2층 전투방");     // 8
	spire.addNode("2층 이벤트방");   // 9
	spire.addNode("2층 휴식방");     // 10

	spire.addNode("3층 휴식방");     // 11
	spire.addNode("3층 이벤트방");   // 12
	spire.addNode("3층 상점방");    // 13
	spire.addNode("3층 엘리트방");   // 14

	spire.addNode("4층 휴식방");   // 15
	
	spire.addNode("5층 보스방");   // 16

	// 노드들의 선을 정의해주세요.

	// 0 ~ 1 층
	spire.addEdge(0, 1); spire.addEdge(1, 6); spire.addEdge(6, 11); spire.addEdge(11, 15); spire.addEdge(15, 16);

	spire.addEdge(0, 2); spire.addEdge(2, 7); spire.addEdge(7, 12); spire.addEdge(12, 15); 

	spire.addEdge(0, 3); spire.addEdge(3, 8); spire.addEdge(8, 13); spire.addEdge(13, 15); 

	spire.addEdge(0, 4); spire.addEdge(4, 10); spire.addEdge(10, 12); spire.addEdge(12, 15); 

	spire.addEdge(0, 5); spire.addEdge(5, 9); spire.addEdge(9, 14), spire.addEdge(14, 15); 


	// 1 ~ 2층

	spire.printGraph();
	spire.drawGraph();

	vector<int> temp = spire.findShortestPath(0, 16);

	for (auto& e : temp)
	{
		cout << e << " -> ";
	}

}
