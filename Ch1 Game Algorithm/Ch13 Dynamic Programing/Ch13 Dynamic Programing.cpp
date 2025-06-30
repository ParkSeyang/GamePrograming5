#include <iostream>
#include <vector>
#include <unordered_map>

/* Ch 13 DP( Dynamic Programing )
* [자료형, 클래스(함수), 포인터, 자료구조]
* 알고리즘 시험 : 코드를 작성하는 능력을 평가하기 위한 시험
* - 프로그래밍 사고력을 잘 가지고 있는가? (기초 실력)
* 
* 알고리즘 기출 문제
* - 정렬, 탐색, 트리 순회, 그래프 순회, 탐색(DFS, BFS)
* - 동적계획법, 그리디 알고리즘, 완전 탐색...
* 문제를 푸는 해결 아이디어를 개념으로 정의한것
* 
* DP의 개념
* - 절차적으로 계획을 세운다.
* - 중복되는 문제를 한 번만 사용해서 해결하고 싶다.
* - 메모리에 기억을 해서 사용하겠다.
*/

// DP의 예시 예제
// 1. 피보나치의 수 구현

int Fibonacci(int n)
{
	if (n == 1)
	{
		return 1;
	}
	if (n == 2)
	{
		return 1;
	}
	

	// 피보나치의 수를 만드는방법 두가지.
	// 반복문, 재귀함수

	return Fibonacci(n - 1) + Fibonacci(n - 2);

}
/* 왜 재귀 방식의 피보나치의 수 구현 시간이 오래 걸릴까?
* n의 숫자가 커지면 커질수록 Fibonacci 함수가 계속 실행이 된다.
* 재귀 함수를 사용하면 n이 커지면 커질수록 스택에 메모리가 쌓이겠구나 -> 스택 오버 플로우가 발생할수도있다.
* 중복이 발생하는 문제를 해결하기 위해서 메모리 공간을 확보해서 저장을 해두었다가 사용하겠다. (메모리제이션)
*/

/* 동적 계획법의 구현 방식에는 
* Top - down 방식 : 재귀 방식, 컨테이너로 구현
* bottom - up 방식 : 반복문, 컨테이너로 구현
* 
*/


int FiboDP(int n)  // bottom - up (반복문, 컨테이너)
{
	// 데이터를 저장할 컨테이너를 만들어주세요.

	std::vector<int> dp(n + 1, 0);  // n개의 빈 공간이 있는 배열을 만들어서 생성한다.
	if (n <= 1)
	{
		return n;
	}

	// bottom - up 목적은 dp[n]까지 도달하기 위해서 dp[0] ~ dp[n] 까지 채워 나가는 것이다.
	dp[0] = 0;
	dp[1] = 1;

	for (int i = 2; i <= n; i++)
	{
		dp[i] = dp[i - 1] + dp[i - 2];
	}
	
	return dp[n];

}

class FiboRecursive
{
private:
	std::vector<int> dp;

public:
	FiboRecursive(int n)
	{
		dp.resize(n + 1, -1);
		dp[0] = 0;
		dp[1] = 1;
	}

	int FiboRecur(int n)
	{
		// dp에 값이 이미 존재한다면? -1이 아니면
		// 재귀 함수 return을 실행, 아래에 자기 자신 함수를 실행한다.
		if (dp[n] != -1)
		{
			return dp[n];
		}
			dp[n] = FiboRecur(n - 1) + FiboRecur(n - 2);
		return dp[n];
	}
};

/* 계단 오르기 문제
* 
* ex) 계단을 오르는데, 1계단만 오르거나 2계단을 한번에 오르거나. 두가지 방식으로 계단을 오를 수 있습니다.
* 계단에는 오르기 위한 값이 존재하는데,
* 예를들어, 2번째 계단을 올라가기 위해서는 두가지 방식이 존재합니다. (1+1) = (2)
* 이때 가장 최소한의 비용으로 n의 계단을 오르는 방법을 구현해보세요.
* 핵심 아이디어 : n번째 계단을 최소한으로 올라야 한다. 1칸씩 오를 때 vs 2칸씩 오를 때를 비교할 수 있어야 한다.
*/

/*
* 계단을 오르는 경우의 수를 구해보세요.
* 2번째 계단을 올라가기 위한 방법 : (1,1), (2) = 2
* CountStep(1) = 1;
* CountStep(2) = 2;
*/

/* 
* cache : 캐시(임시로 저장된 데이터 더미) 삭제
* 중복되는 사항이 있을 때 데이터를 저장해서 사용하면 빠르게 사용할 수 있다.
* - 메모리 공간을 사용을 해야한다. "캐싱" : 최적화 방법 중 하나이다. (시간을 확보할 수 있는)
*/

/* 시험 문제로 나올 시 주의 사항
* - 시험 문제로 나오면, 이문제를 DP로 풀어주세요 라고 말을 하지 않습니다.
* 계단 문제를 읽은 다음에 다음 문제가 DP로 풀어야 겠구나 라고 사고를 해야 합니다.
* (1) 각 개념 마다 키워드들이 존재한다.
* - "최소", "저렴하게" -> 시간 초과를 발생하는 함정키워드
* (2) 기출문제 가 존재합니다. 
* - 경험으로 문제를 풀어보는 것.
*/


class GameCache
{
private:

	struct UserData
	{
		int level; 
		int exps;
		int damage;
	};

	std::unordered_map<int, int> exps;  // 해시를 이용한 자료구조. 탐색에서 매우 빠르다. 순서가 없이 저장되는 컨테이너다.
	std::unordered_map<int, int> damage;

	// std::unordered_map<int, int> exps;
	// std::unordered_map<int, int> damage;

public: 

	int CalculateDamage(int level)
	{
		// 아래의 코드를 참고해서 만들어보세요.

		// 이미 데이터가 존재하면 해당 데이터를 가져와서 사용하세요.

		// 그게 아니면 계산식을 이용해서 데이터를 저장하고 출력하세요.

		// int damage = ?? ;


		if (exps.find(level) != exps.end())
		{
			std::cout << "캐시에서 데이터를 가져옴" << " 레벨 : " << level << std::endl;
			return exps[level];
		}

		UserData userdata;

		userdata.damage = 15;
		userdata.exps = 0;

		
		if (userdata.exps == 125)
		{
			userdata.level += 1;
		}




	}

	int CalculateExp(int level)
	{
		// 5레벨 까지 필요한 경험치 1 -> 2, 2 -> 3, 3 -> 4, 4 -> 5

		if (exps.find(level) != exps.end())
		{
			std::cout << "캐시에서 데이터를 가져옴" << "[레벨 " << level << " : " << exps[level] << "]" << std::endl;
			return exps[level];
		}

		// 게임에서 레벨 당 필요한 경험치를 구하는 공식.
		// y = x^2 + 2x + 1

		int exp = level * (level + 100); // 101, 204;

		exps[level] = exp;

		return exp;

	}
};



int CountStep(int n)
{
	// DP를 한번 더 스스로 작성해보세요.
	std::vector<int> step(n + 1, -1);  // n + 1하는 이유 : dp[6]은 인덱스0부터 시작 했을 때 7번째 데이터를 사용해야한다.

	if (n == 0 || n == 1)
	{
		return n;
	}

	for (int i = 2; i <= n; i++)
	{
		step[i] = step[i - 1] + step[i - 2];
	}

	return step[n];

}

int main()
{
	std::cout << "=====[피보나치 의 수 재귀함수로 구현]=====" << std::endl;

	std::cout << "결과 값 : " << Fibonacci(6) << std::endl;

	std::cout << "피보나치의 n번째 숫자를 출력해보세요 :" << Fibonacci(6) << std::endl;
	// 재귀 방식으로 구현하면 시간 초과가 발생합니다.
	

	std::cout << "=====[피보나치 의 수 DP Bottom - up 방식 구현]=====" << std::endl;

	std::cout << "결과 값 : " << FiboDP(6) << std::endl;

	std::cout << "=====[피보나치 의 수 DP Top-down 구현]=====" << std::endl;

	FiboRecursive fibo(6);
	std::cout << "결과 값 : " << fibo.FiboRecur(6) << std::endl;

	std::cout << "계단 오르기 경우의 수 출력" << std::endl;

	std::cout << "n번째 계단을 오르기 위해서 필요한 경우의 수 : " << CountStep(5) << std::endl;


	std::cout << "게임 캐싱 데이터 예제" << std::endl;

	GameCache gameCache;

	for (int i = 1; i < 6; i++)
	{
		std::cout << i << "레벨 경험치 : " << gameCache.CalculateExp(i) << std::endl;
	}


}

