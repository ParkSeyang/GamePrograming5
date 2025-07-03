#include <iostream>
#include <Windows.h>

/* 오늘의 배울것
* 콘솔 창 색을 변경하는 기능들
* ANSI ESCAPE 문자의 색을 변경하는 기능을 만들어봅시다.
* 
* 목표 : 숫자로 표기를 하는 것이 아니라, 사람이 알아보기 쉽도록 클래스를 만들자.
* Helper 클래스
* ex) Color::White, Color::BG_White, Color::UnderLine
* 
* 30 ~ 39 글자색, 40 ~ 47 배경색
*/

using namespace std;

class Color
{
public:
	static const string RESET;
	static const string UNDERLINE;

	static const string BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE;
	static const string BG_RED, BG_GREEN, BG_YELLOW, BG_BLUE, BG_MAGENTA, BG_CYAN, BG_WHITE, BG_BLACK;

	static void Print(const string& BG, const string& textColor, const string& message)
	{
		cout << BG << textColor << "==== TITLE ====" << message << Color::RESET;
		cout << endl;
	}
};

const string Color::RESET = "\033[0m";

const string Color::UNDERLINE = "\033[4m";

const string Color::BLACK = "\033[30m";

const string Color::RED = "\033[31m";

const string Color::GREEN = "\033[32m";

const string Color::YELLOW = "\033[33m";

const string Color::BLUE = "\033[34m";

const string Color::MAGENTA = "\033[35m";

const string Color::CYAN = "\033[36m";

const string Color::WHITE = "\033[37m";

const string Color::BG_RED = "\033[41m";

const string Color::BG_GREEN = "\033[42m";

const string Color::BG_YELLOW = "\033[43m";

const string Color::BG_BLUE = "\033[44m";

const string Color::BG_MAGENTA = "\033[45m";

const string Color::BG_CYAN = "\033[46m";

const string Color::BG_WHITE = "\033[47m";

const string Color::BG_BLACK = "";

void PrintMenu()
{
	
	cout << "===== 메뉴 =====" << endl;

	Color::Print(Color::BG_BLACK, Color::GREEN, "1. ");
	cout << "새로운 게임" << endl;
	
	cout <<Color::BG_BLUE << "2. " << "불러오기" << Color::RESET << endl;

	cout << "3. " << "설정" << endl;

	cout << "4. " << "종료" << endl;

}

void PrintProgressBar(int current, int total, int width = 30)
{
	float progress = (float)current / total;
	int filled = (int)(width * progress);

	for (int i = 0; i < filled; i++)
	{
		cout << Color::GREEN << "▣";
	}

	for (int i = filled; i < width; i++)
	{
		cout << Color::WHITE << "▣";
	}

	cout << Color::RESET << (int)(progress * 100) << "%";

}

void LoadingAnimation()
{
	cout << "로딩 진행 현황을 그려준다." << endl;

	for (int i = 0; i < 20; i++)
	{
		PrintProgressBar(i, 20);
		cout << endl;
		cout.flush();
		Sleep(500);

	}

	// vector 자료구조에 진행현황을 그림으로 저장을 했다가 갱신을 하는 방식.

}

void DrawBox()
{
	/* 개인과제
	* - 상자는 위, 중간, 아래 부분으로 구분이 됩니다.
	* 반복문을 이용해서 표현해보세요.
	*/

	// for (size_t i = 0; i < length; i++)
	// {
	// 	for ()
	// 	{
	// 	}
	// }

	cout << Color::BG_CYAN<< "+----------+" << Color::RESET << endl;
	Color::Print(Color::BG_CYAN, Color::WHITE, "|");
	cout << "          ";
	Color::Print(Color::BG_CYAN, Color::WHITE, "|");
	cout << endl;
	cout << "          ";
	Color::Print(Color::BG_CYAN, Color::WHITE, "|");
	cout << "|          |" << endl;
	cout << "|          |" << endl;
	cout << "|          |" << endl;
	cout << Color::BG_CYAN << "+----------+" << Color::RESET << endl;
}


int main()
{
	cout << "\033[46m" << "글자" << Color::RESET << endl;

	cout << "\033[33m" << "글자" << "\033[0m" << endl;

	cout << "\033[4m" << "글자" << "\033[0m" << endl;

	// 노란색 글자에 밑줄이 그어진 문자

	// 예시 2가지)
	cout << Color::BG_BLUE << Color::GREEN << "==== TITLE ====" << Color::RESET << endl;

	Color::Print(Color::BG_BLUE, Color::GREEN, "==== TITLE ====");

	// 로딩바, 메뉴 표시, UI표현

	// 제목 - 게임 시작, UI표현

	PrintMenu();
	// 제목 - Color클래스를 사용해서
	// 1. 게임시작
	// 2. 게임종료

	// LoadingAnimation();
	DrawBox();
	
}
