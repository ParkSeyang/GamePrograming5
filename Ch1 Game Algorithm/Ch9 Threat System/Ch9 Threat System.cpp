#include <iostream>
#include <queue>    // queue, priority_queue
#include <vector>
#include <utility>  // pair

using namespace std;

/*
* RPG게임 보스 레이드, 5인파티, (전사, 도적, 궁수, 마법사, 성직자)
* 각각의 직업들은 스킬을 사용할 때 마다 보스 어그로가 증가합니다.
* 총 5번의 보스 공격 마다 누구를 우선적으로 공격하는지 찾는 로직을 작성해보세요.
* 이때, 보스가 특정 직업을 공격할 때 마다 그 직업의 어그로는 0으로 초기화됩니다.
*           1턴  2턴  3턴   4턴  5턴
* 전사   :  10    5    8     7    6 ( 강력하거나, 위협적인 스킬일 수록 그 수치가 높다)
* 도적   :
* 궁수   :
* 마법사 :
* 성직자 :
*
* [보스의 스킬을 결정하는 로직]
* 보스 : 파티 안에서 누가 가장 위협적인가?, 누가 가장 덜위협적인가?
*
* (1) n개의 직업 마다 우선순위를 비교 가장 큰 순위를 출력한다.
* (2) Heap 자료구조를 사용해서 k번째 순위를 찾는다.
*
* - 갯수가 적으면 적을수록 1번 방식이 효율적이다.
* - 2번을 사용해야하는 보스가 찾아야할 우선 순위 대상이 많으면 많을수록 2번 방식이 효율적이다.
*/

// 전사, 마법사, 궁수, 도적, 성직자

class Character
{
private:
	string name;
	vector<int> threatLevel;   // threatLevel {10,5,8,7,6}
	int currentTurn;
public:
	Character(string name, vector<int> TL) : name(name), threatLevel(TL), currentTurn(0) {}

	int getCurrentThreat()
	{
		if (threatLevel.size() <= currentTurn)
		{
			throw runtime_error("Out of Range");
			return -1;  // -1을 리턴하면 에러로 인식하세요.
		}
		return threatLevel[currentTurn];
	}

	void NextTurn()
	{
		currentTurn++;
	}

	void PrintStat()
	{
		cout << name << "현재 위협도 : " << getCurrentThreat() << ")" << std::endl;
	}

};

class Boss
{
private:

public:
	string name;
	int currentTurn;
	priority_queue<int> threatQueue;       //priority_queue<std::pair<int, int> vector<int,int>> TQ
	Boss(string name) : currentTurn(0) {}

	void Clear()
	{
		while (!threatQueue.empty())
		{
			threatQueue.pop();
		}
	}

	void UpdateThreatQueue(vector<Character>& party)
	{
		Clear();

		for (auto& charatcter : party )
		{
			int threat = charatcter.getCurrentThreat();
			threatQueue.push(threat);
			charatcter.NextTurn();  // 파티의 모든 캐릭터의 턴을 1 증가시킨다.
		}
		// 위협도가 가장 큰수를 저장.

	}

	int FindMostThreatCharacter(vector<Character>& party)
	{
		Character* target = nullptr;

		int MostThreatValue = threatQueue.top();


		return MostThreatValue;
	}

	void Attack()
	{
		// target = FindTarget();
		// charachter.TakeDamage();
	}
};

// maxHeap, minHeap
// 오늘의 챕터
// 1. 우선순위 큐를 이용해서 힙구조를 작성해봅시다.

bool myLess(int a, int b)
{
	return a < b;
}
bool myGreater(int a, int b)
{
	return a > b;
}

// k번째로 작은 수 구하기, k번째로 큰수 구하기를 우선순위 큐를 사용하면 쉽게 표현할 수 있다.
// logn 시간으로 k 번째 작은 수를 찾을 수 있다. => (k번째 수를 찾는다, 1:1대응 N시간으로 코드를 작성하면 시간이 초과했습니다.)



class minHeap  // 가장 작은 수가 제일 위에 있는 구조.
{

private:
	priority_queue<int, vector<int>, greater<int>> pq;
	priority_queue<int> pq2;
public:
	// push, pop, empty, top = (<=extreactMax)

	minHeap() = default;

	void push(int value) 
	{
		pq.push(value);
	}
	bool empty() const
	{
		return pq.empty();
	}
	const int& top() const         // 저장되어있는 가장 위의 값을 참조한다.
	{
		if (empty())
		{
			throw runtime_error("Priority Queue is Empty!");
		}
		return pq.top();
	}
	int pop() // 복사를 한 후에, 자료구조에서 삭제
	{
		if (empty())
		{
			throw runtime_error("Priority Queue is Empty!");
		}
		int minValue = pq.top();
		pq.pop();
		return minValue;
	}         
	
	
};

class maxHeap  // 가장 큰 수가 제일 위에 있는 구조
{
private:
	priority_queue<int, vector<int>, less<int>> pq3;

public:
	maxHeap() = default;

	void push(int value)
	{
		pq3.push(value);
	}
	bool empty() const
	{
		return pq3.empty();
	}
	const int& top() const
	{
		if (empty())
		{
			throw runtime_error("Priority Queue is Empty!");
		}
		return pq3.top();
	}
	int pop()
	{
		if (empty())
		{
			throw runtime_error("Priority Queue is Empty!");
		}
		int maxValue = pq3.top();
		pq3.pop();
		return maxValue;
	}

};

void FindKthExample()
{
	minHeap myHeap;
	maxHeap stHeap;
	myHeap.push(11);
	myHeap.push(7);
	myHeap.push(5);
	myHeap.push(3);

	stHeap.push(11);
	stHeap.push(7);
	stHeap.push(5);
	stHeap.push(3);


	std::cout << "최소 힙의 가장 값 : " << myHeap.top() << std::endl;
	std::cout << "최대 힙의 가장 값 : " << stHeap.top() << std::endl;
	int k = 3;
	// ??

	// for 반복문을 k로 표현하여 k번째 수를 찾아보세요.

	std::cout << "k번째 작은 수를 출력하세요 : " << std::endl;
}

void ThreatSystem()
{
	// 1. 등장 캐릭터의 위협도를 출력하세요.

	Character a("전사", { 1,2,3,4,5 });
	Character b("도적", { 1,1,1,10,5 });
	Character c("궁수", { 3,4,5,6,7 });
	Character d("마법사", { 0,1,6,6,6 });
	Character e("성직자", { 0,0,10,0,10 });

	std::vector<Character> party;

	party.push_back(a);
	party.push_back(b);
	party.push_back(c);
	party.push_back(d);
	party.push_back(e);

	for (auto& character : party)
	{
		character.PrintStat();
	}
	// 보스가 가장 위협도가 높은 숫자를 찾도록 해보세요.
	Boss boss("킹고블린");
	boss.UpdateThreatQueue(party);     // 첫번째 턴
	int value = boss.FindMostThreatCharacter(party);
	cout << "첫 번째 턴에서 위협도가 가장 큰 수치 : " << value << std::endl;


	boss.UpdateThreatQueue(party);    // 두번째 턴
	value = boss.FindMostThreatCharacter(party);
	cout << "두 번째 턴에서 위협도가 가장 큰 수치 : " << value << std::endl;


	int nextTurnValue = 3;
	// 연습 문제. 전사만 3번째 턴 동안 누적된 위협도를 출력해보세요.
	int currentThreat = 0;
	for (int i = 0; i < nextTurnValue; i++)
	{
		currentThreat += a.getCurrentThreat();
		a.NextTurn();
	}

	cout << "전사의 3턴 후 위협도 : " << currentThreat << std::endl;

	// n번째 턴일 때 각 직업의 위협도를 출력을 하려면 어떻게 해야 될까?
	// 1. 각 턴에 위협도를 현재 위협도에 더해서 추가해보세요.


}

int main()
{
	// FindKthExample();
	ThreatSystem();
}
