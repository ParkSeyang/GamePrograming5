#include <iostream>
#include <queue>
#include <algorithm>


/* 오늘의 목표
* 0. k번째 문제 찾기 오류수정, delete temp 삭제하는거.
* 1. Heap 특정한 규칙을 갖고 있는 자료구조를 직접 구현해보기
* 2. k번째 존재하는 수를 더 빨리 찾을 수 있다. -> 게임 예제
*/

// k번째 숫자 찾기

// 1. vector, array 숫자를 정렬시킨 후에 가장 크거나 (작은) 수를 찾는다. (정렬 알고리즘 시간)
// 2. 전체 갯수가 n개가 있으면 n - 1번 비교를 해야한다.                 (모든 경우의 수를 탐색, 완전 탐색)
// 3. 시간이 logn이 걸리는 방법이 없을까? -> 데이터의 수가 백만개 이상(처리해야할 데이터가 많으면) 일 때 어덯게 해야 하나?
// 만약에 처리해야할 데이터가 적으면, (10 ~ 1)

// Tree ( 편향적으로 데이터가 저장될 경우 효율적이지 않다.)
// 1. 단점을 해결하기 위한 하나의 방법으로 트리 형태로 균형 잡히게 일단 데이터를 넣어보자. (트리를 차례대로 저장한다, 완전 이진 트리)
// 2. root 방향으로 가장 큰 수 (가장 작은 수)를 저장하도록 규칙을 설정한다.
// 위의 규칙을 갖는 자료구조를 힙(Heap)이라고 부른다. maxHeap, minHeap

// MaxHeap 구현을 보고 MinHeap을 따로 구현해보기 (!! 자습할 때 사용해보세요 !!)


void PriorityQueue()
{
	std::priority_queue<int> pq;

	// Heap 자료 구조로 만들어진 클래스 입니다.
}

class MaxHeap
{
private:
	struct Node
	{
		int value;
		Node* leftNode;
		Node* rightNode;
		Node* parentNode;

		Node(int val) : value(val), leftNode(nullptr), rightNode(nullptr), parentNode(nullptr) {}

	};

	Node* root;
	int size;

	/* 역참조 하는법
	* 1. (*node).value 
	* 2. node->value
	*/

	/*
	* 부모 노드를 기준으로 큰 녀석을 바꾸면 안되나요?
	* heap의 특징은 데이터가 들어올 때 heap의 성질을 만족하고 있다 가정.
	* 새로 들어온 녀석만 규칙에 맞도록 수정하면 된다.
	*/

	void heapifyup(Node* node)  // 새로 추가된 노드 
	{
		// node의 부모 노드를 포인터로 가리키고 있다. node->parentNode -> value  node ->value

		// while (1번조건 && 2번조건)
		// 1. 추가된 노드와 부모 노드의 값을 비교하는 코드를 만들어보세요. 새로 추가된 노드가 더 클때
		// 2. 새로 추가된 노드의 부모 노드가 존재하면 계속 실행하세요.
		
		// node-> parentNode가 없을때

		while (node->parentNode != nullptr && node->value > node->parentNode->value) // 변경을 하기 위한 조건
		{
			// 알고리즘 헤더를 추가해준다음에, 부모 노드와 자기 노드를 스왑해준다. (value를 swap)
			// 스왑후에 노드를 부모노드와 변경해준다. (부모 노드를 가리키고 있는 것을 변경한다.)
			std::swap(node->parentNode->value, node->value);
			node = node->parentNode;
		}

	}

	Node* findLastNode()  // 노드를 삭제할 때 규칙1을 만족시키기 위해서 가장 마지막 노드를 찾는다.
	{
		if (root == nullptr)
		{
			return nullptr;  // 데이터가 1개도 없는 경우 실행하지마세요.
		}
		
		std::queue<Node*> q;

		q.push(root);

		Node* lastNode = nullptr;

		while (!q.empty())
		{
			lastNode = q.front();
			q.pop();
			if (lastNode->leftNode)
			{
				q.push(lastNode->leftNode);
			}
			if (lastNode->rightNode)
			{
				q.push(lastNode->rightNode);
			}

		}

		return lastNode;
	}

	void heapifydown(Node* node)
	{
		// 루트에 올린 마지막 노드를 그 자식 노드(왼쪽, 오른쪽) 중에서 큰 값과 교체한다.
		// 자식의 왼쪽, 오른쪽 노드보다 자기가 더 크거나, 더 이상 자식이 없을 때 까지 반복해라

		while(node)
		{
			Node* largest = node;  // 현재 노드가 제일 크다. (가정)

			// 왼쪽과 오른쪽중에서 큰수로 바뀐다.
			if (node->leftNode && node->leftNode->value > largest->value)
			{
				largest = node->leftNode;
			}
			if (node->rightNode && node->rightNode->value > largest->value)
			{
				largest = node->rightNode;
			}

			if (largest == node) // 만약에 변경이 안됐으면 반복문을 탈출해라
			{
				break;
			}

			std::swap(node->value, largest->value);
			node = largest;
		}

	}

	void deleteNode(Node* node)
	{
		if (!node)
		{
		   return;
		} 
		
		deleteNode(node->leftNode);
		deleteNode(node->rightNode);
		delete node;

	}

public:

	MaxHeap() : root(nullptr), size(0) {}


	void Insert(int value)
	{
		Node* newNode = new Node(value);

		if (!root)  // 데이터가 0개일 경우, 새로 들어온 데이터가 루트가 된다.
		{
			root = newNode;
			size = 1;
			return;
		}

		// 루트가 존재할 경우, 규칙1을 따라서 순서대로 노드가 저장될 수 있게 조건을 작성하세요.
		
		

		std::queue<Node*> q;  // FIFO 구조로 데이터를 저장하기 위한 큐를 사용합니다.
		q.push(root);

		while (!q.empty())  // q가 데이터가 있을 때만 반복하세요.
		{
			Node* currentNode = q.front();

			q.pop();

			if (!currentNode->leftNode)  // 왼쪽에 데이터가 없으면 -> 왼쪽에 데이터 넣기.
			{
				currentNode->leftNode = newNode;     // 현재 노드의 왼쪽 자식에 새로운 데이터를 넣었다.
				newNode->parentNode = currentNode;   // 자식의 부모를 설정해준다.
				break;
			}
			// 왼쪽에 데이터가 있으면?
			if (!currentNode->rightNode) // 오른쪽에도 데이터가 없을 때 -> 오른쪽에 데이터 넣기.
			{
				currentNode->rightNode = newNode;
				newNode->parentNode = currentNode;
				break;
			}
			// root에 더이상 연결된 노드가 없을 때 까지 반복하기 위해서 연결된 노드들을 추가해주는 코드.
			q.push(currentNode->leftNode);
			q.push(currentNode->rightNode);
		}
		
		size++;
		heapifyup(newNode);

		// 현재 들어간 노드와, 그 부모의 노드를 비교해서 큰 수를 위쪽으로 보내라.
		// heapify up 과정

	}

	int extractMax() // 최대값을 제거하라. front, pop
	{
		if (!root)
		{
			return -1;   // -1 을 리턴하면 에러가 있는것이다.
		}

		int maxValue = root->value;

		if (size == 1)
		{
			delete root;
			root = nullptr;
			size = 0;
			return maxValue;

		}

		// 1. 마지막 노드를 찾으세요.
		Node* lastNode = findLastNode();

		if (!lastNode)
		{
			return -2;    // if(-1) 갯수가 0, (-2) 마지막 노드를 찾는 코드가 에러가 있습니다.
		}
		 
		// 2. 마지막 노드를 root 노드로 이동시킨 후 다시 heap의 성질을 갖도록 정의하세요.

		root->value = lastNode->value;  // 제일 밑에 있는 노드를 가리켰는데, 현재 root에는 마지막 값이 들어있다.

		// 지우기 위해서 가리키고 있는 가장 마지막 노드
		if (lastNode->parentNode)
		{
			
			// lastNode의 값은 root로 올라갔으니까 현재 lastNode에 있는 주소를 nullptr로 바꾸기

			if (lastNode->parentNode->leftNode == lastNode)  // 마지막 노드가 부모노드의 왼쪽에 있는 경우
			{
				lastNode->parentNode->leftNode = nullptr;
			}
			else  // 마지막 노드가 부모 노드의 오른쪽에 있는 경우
			{
				lastNode->parentNode->rightNode = nullptr;
			}
		}
		delete lastNode;
		size--;
		heapifydown(root);

		return maxValue;
	}

	std::vector<int> toArray()
	{
		std::vector<int> result;

		// 힙으로 저장한 자료구조를 vector로 변환해보세요.

		// while queue자료형을 사용해서 데이터를 탐색하는 형태의 코드

		if (!root) // root가 nullptr이면?
		{
			return result; // 예외처리
		}

		std::queue<Node*> q;

		q.push(root);  

		while (!q.empty())
		{
			Node* node = q.front();
			q.pop();

			result.push_back(node->value);

			if (node->leftNode)
			{
				q.push(node->leftNode);
			}
			if (node->rightNode)
			{
				q.push(node->rightNode);
			}
			
		}

		return result;
	}
};

int main()
{
	MaxHeap mheap;

	std::cout << "가장 큰 수를 찾는 Heap 데이터 입력" << std::endl;

	mheap.Insert(7);
	mheap.Insert(3);
	mheap.Insert(5);
	mheap.Insert(11);

	std::cout << "Heap 자료구조의 트리 저장 순서대로 출력하는 예제" << std::endl;
	std::vector<int> tempV = mheap.toArray();

	for (auto& data : tempV )
	{
		std::cout << data << " ";
	}

	std::cout << "가장 큰수를 반환하고 다시 Heap 정렬 하는 예제" << std::endl;

	int maxValue = mheap.extractMax(); // 1번째 큰수
	int k = 2;     // 2번째로 큰 수
	int kthValue;

	for (int i = 0; i < k - 1; i++)
	{
		kthValue = mheap.extractMax();  // 2번째로 큰 수를 kthValue에 저장한다.
	}

	// k번째로 큰 수를 찾아라.
	std::cout << "k번째로 큰 수는 : " << kthValue << std::endl;

}
