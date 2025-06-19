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
}

