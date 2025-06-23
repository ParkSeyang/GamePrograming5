#include <iostream>
#include <vector>

/* Tree 자료구조
* 데이터를 어떻게 저장하는 형태인가?
* 노드 형태로 데이터를 저장을 한다. Value, 연결되어 잇는 Node 주소를 저장한다.
*/

/* Tree 순회 방법
* 1. 전위 순회(pre - order)
* - N -> L -> R 순서로 읽는 방식
* 2. 중위 순회(in - order)
*   L -> N -> R 순서로 읽는 방식
* 3. 후위 순회(Post - order)
*   L -> R -> N 순서로 읽는 방식
*/

/*
* BST (Binary search Tree) 이진 탐색 트리
* - 자기 자신과, 왼쪽, 오른쪽을 저장하는 노드를 가지고 있다.
* - Node기준으로 왼쪽과 오른쪽의 값을 비교할 수 있다.
* - 작은 값을 왼쪽으로 큰 값을 오른쪽으로 저장을 하면 규칙성을 갖는다.
* - 특정한 규칙을 갖는 클래스를 만들어서 데이터를 출력해본다.
*/

/*
*  순차 컨테이너 방식의 단점 : 탐색 및 수정이 효율적이지 않다.
*  연관 컨테이너 - "Tree 자료 구조"
*  "BST" - 이진 탐색 알고리즘으로 자료 구조를 표현한것
*  단점 : 트리가 한 쪽으로 편향될 경우 O(n) 시간만큼 걸린다.
*/

/* 트리 자료구조의 용어
* 노드 : (값(value), 왼쪽 노드 주소, 오른쪽 노드 주소) 트리의 기본 요소를 저장하는 데이터 단위
* 부모 노드 : 하위의 노드와 직접 연결된 노드
* 자식 노드 : 부모 노드의 하위에 직접 연결된 노드
* 루트 노드 : 트리의 최상위에 있는 노드. 부모 노드가 없습니다.
* 조상 노드 : 특정 노드에서 루트까지의 경로에 있는 모든 노드들
* 후손 노드 : 특정 노드의 모든 자식들을 포함한 노드들
* 
* - 알고리즘 트리 코드 구현 시 사용되는 용어 -
* 레벨(level) : 루트로 부터의 거리를 뜻합니다. 루트는 0을 반환합니다. (트리의 깊이를 나타내는 용어로, 루트 노드는 레벨 0, 그 다음 레벨은 1, 2, ... 순으로 증가합니다.)
* 높이        : 트리에서 가장 깊은 레벨을 뜻합니다. 높이는 루트 노드에서 가장 깊은 후손 노드까지의 거리로 정의됩니다.
* 서브 트리   : 트리 내부에 후손들로 구성된 또다른 트리입니다.
*/


struct Node
{
	int value;
	Node* leftNode;
	Node* rightNode;

	Node(int val) : value(val), leftNode(nullptr), rightNode(nullptr) {}

};

#pragma region 트리 순회하는 방식

class Tree
{
private:

public:

	
	void preOrder(Node* root)  // 재귀 방식으로 만든다.
	{
		if (root == nullptr)  // 재귀 함수 탈출조건
		{
			return;
		}
		std::cout << root->value << " ";  // 노드를 가리키는 값 N 을 출력
		preOrder(root->leftNode);         // L에 있는 노드에 가서 preOrder를 실행하세요.
		preOrder(root->rightNode);        // R에 있는 노드에 가서 preOrder를 실행하세요.

		// -N-> L -> R
	}
	void inOrder(Node* root) 
	{
		if (root == nullptr)  // 재귀 함수 탈출조건
		{
			return;
		}

		inOrder(root->leftNode);          // L에 있는 노드에 가서 inOrder를 실행하세요.
		std::cout << root->value << " ";  // 노드를 가리키는 값 N 을 출력
		inOrder(root->rightNode);         // R에 있는 노드에 가서 inOrder를 실행하세요.

		// L -> N -> R

	}
	void postOrder(Node* root) 
	{
		if (root == nullptr)  // 재귀 함수 탈출조건
		{
			return;
		}

		postOrder(root->leftNode);        // L에 있는 노드에 가서 postOrder를 실행하세요.
		postOrder(root->rightNode);       // R에 있는 노드에 가서 postOrder를 실행하세요.
		std::cout << root->value << " ";  // 노드를 가리키는 값 N 을 출력

		//  L -> R -> N
	}

};

#pragma endregion

#pragma region 노드 직접 연결

void NodeConnect()
{
	Tree tree;
	Node* root = new Node(4);
	root->leftNode = new Node(2);
	root->leftNode->leftNode = new Node(9);
	root->leftNode->rightNode = new Node(7);
	root->rightNode = new Node(6);
	root->rightNode->leftNode = new Node(1);
	/* └─ 위의 노드 그림 예시
	*          [4]
	*     [2]       [6]
	*  [9]   [7] [1]
	*/

	std::cout << "\n트리를 전위 순회로 출력" << std::endl;
	tree.preOrder(root);
	// 결과 : 4 2 9 7 6 1

	std::cout << "\n트리를 중위 순회로 출력" << std::endl;
	tree.inOrder(root);
	// 결과 : 9 2 7 4 1 6

	std::cout << "\n트리를 후위 순회로 출력" << std::endl;
	tree.postOrder(root);
	// 결과 : 9 7 2 1 6 4
}
#pragma endregion

#pragma region BST (이진 탐색 트리)
/*
* root에서 부터 데이터를 삽입합니다.
* root 보다 insert값이 작으면 왼쪽으로 크면 오른쪽으로 저장합니다.
* 모든 데이터를 저장 후 중위순회 방식으로 데이터를 읽으면 오름차순으로 데이터가 정렬이 됩니다.
*/

class BST
{
private:
	Node* root;

	Node* insert(Node* node, int value)
	{
		// 데이터가 0개 일 때
		if (node == nullptr)
		{
			return new Node(value);
		}

		// node 가 작으면 왼쪽, 크면 오른쪽으로 삽입

		if (node->value > value)
		{
			node->leftNode = insert(node->leftNode, value);
		}
		else if (node->value < value)
		{
			node->rightNode = insert(node->rightNode, value);
		}

		return node;

	}

	Node* findMin(Node* node)
	{
		if (node == nullptr || node->leftNode == nullptr)
		{
			return node;
		}

		return findMin(node->leftNode);
	}

	Node* findMax(Node* node)
	{
		if (node == nullptr || node->rightNode == nullptr)
		{
			return node;
		}

		return findMax(node->rightNode);
	}

	Node* deleteNode(Node* node, int target) // 삭제. 데이터를 찾은 다음에 있으면 지운다.
	{
		if (node == nullptr)
		{
			return nullptr;
		}
		
		if (node->value > target) // 왼쪽 노드로 이동하세요.
		{
			node->leftNode = deleteNode(node->leftNode, target);
		}

		else if (node->value < target) // 오른쪽 노드로 이동하세요.
		{
			node->rightNode = deleteNode(node->rightNode, target);
		}

		else // 지울 데이터를 찾은 경우. 그 노드를 삭제해주세요.
		{
			// 찾았다. 삭제해라

			// if (node->leftNode == nullptr && node->rightNode == nullptr)
			// if (node->leftNode == nullptr)
			// if (node->rightNode == nullptr)

			if (node->leftNode == nullptr || node->rightNode == nullptr)
			{
				Node* temp = node->leftNode != nullptr ? node->leftNode : node->rightNode;  // 왼쪽, 오른쪽 체크

				if (temp == nullptr)  // 자식노드가 없는 경우
				{
					temp = node;      // 지우고 싶은 노드를 임시로 저장 (지워야할 메모리를 가리키고 있다.)
					node = nullptr;   // 지우고 싶은 노드를 null가리키도록 수정.
					delete temp;      // 임시 보관한 주소를 지워라.
				}
				else
				{
					Node* nodeToDelete = node;  // 지울 노드를 잠시 저장할 변수를 선언.
					node = temp;                // 1개만 있는 자식(temp)을 지워야할 노드(node)위치로 이동
					delete nodeToDelete;        // 지워야할 노드(nodeToDelete) - 메모리를 해제한다.
				}

			}
			else  // 자식노드가 둘인 경우
			{
				// 오른쪽에서 가장 작은 값을 찾겠다. findMin();

				Node* temp = findMin(node->rightNode);
				node->value = temp->value;
				node->rightNode = deleteNode(node->rightNode, temp->value);
			}

		}

		return node;

	}

	void inOrder(Node* node)
	{
		if (node == nullptr)
		{
			return;
		}
		inOrder(node->leftNode);
		std::cout << node->value << " ";
		inOrder(node->rightNode);

	}

public:
	BST()
	{
		root = nullptr;
	}

	void insert(int value)
	{
		root = insert(root, value);
	}

	// 중위 순회로 root를 읽는 코드를 만들어보세요.
	void inOrder()
	{
		inOrder(root);
		std::cout << std::endl;
	}

	void DeleteNode(int value)
	{
		root = deleteNode(root, value);
	}

	void ReturnRoot()
	{
		std::cout << ""
	}
};

#pragma endregion


int main()
{
	 NodeConnect();

	 std::cout << "\n이진 탐색 트리 데이터 입력 예시" << std::endl;
	 BST bst;
	 bst.insert(4);
	 bst.insert(2);
	 bst.insert(6);
	 bst.insert(9);
	 bst.insert(7);
	 bst.insert(1);
	 bst.inOrder();

	 std::cout << "\n 6 데이터 삭제후 결과 예시" << std::endl;
	 bst.DeleteNode(6);
	 bst.inOrder();


}

