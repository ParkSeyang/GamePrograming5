#include <iostream>
#include <Windows.h>
#include <InventoryDP.h>
#include <queue>
#include <string>

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
		cout << BG << textColor << message << Color::RESET;
		
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
		cout << Color::GREEN << "■";
	}

	for (int i = filled; i < width; i++)
	{
		cout << Color::WHITE << "□";
	}

	cout << Color::RESET << (int)(progress * 100) << "%";

}

void LoadingAnimation()
{
	const int total = 20;
	const int width = 30;

	cout << "로딩 진행 현황을 그려준다." << endl;

	for (int i = 0; i <= total; i++)
	{
		system("cls");
		PrintProgressBar(i, total, width);
		cout << endl;
		cout.flush();
		Sleep(100);

	}

	// vector 자료구조에 진행현황을 그림으로 저장을 했다가 갱신을 하는 방식.

}

void DrawBox(int width, int height)  // 매개변수로 가로, 세로의 크기를 받는다
{
	/* 개인과제
	* - 상자는 위, 중간, 아래 부분으로 구분이 됩니다.
	* 반복문을 이용해서 표현해보세요.
	*/


	cout << Color::BG_CYAN << "+";
	// "----------"
	for (int i = 0; i < width; i++)
	{
		cout << "-";
	}
	cout <<	"+" << Color::RESET << endl;

	
	for (int y = 0; y < height; y++)
	{
		// 왼쪽 기둥
		Color::Print(Color::BG_CYAN, Color::WHITE, "|");

		// 공백
		for (int i = 0; i < width; i++)
		{
			cout << " ";
		}

		// 오른쪽 벽
		Color::Print(Color::BG_CYAN, Color::WHITE, "|");
		cout << endl;
	}

	// 바닥
	cout << Color::BG_CYAN << "+";

	// "----------"
	for (int i = 0; i < width; i++)
	{
		cout << "-";
	}


	cout << "+" << Color::RESET << endl;


}

void GotoXY(int x, int y)
{
	COORD pos{ x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

/*
* DrawBox를 내가 원하는 좌표에 그릴 수 있도록 아래 함수를 수정해보세요.
* GotoXY를 이용하세요. 탑, 몸통, 바닥
* 도형 그리기 + 위치 이동 => 주어진 자료를 원하는 위치에 상타 형태로 출력하는 UI 만들기.
*/

void DrawBox(int px, int py, int width, int height, const ItemW& item)  // 매개변수로 가로, 세로의 크기를 받는다
{
	/* 개인과제
	* - 상자는 위, 중간, 아래 부분으로 구분이 됩니다.
	* 반복문을 이용해서 표현해보세요.
	*/


	// 머리

	GotoXY(px, py);
	cout << Color::BG_CYAN << "+";

	// "----------"
	for (int i = 0; i < width; i++)
	{
		cout << "-";
	}
	cout << "+" << Color::RESET << endl;


	
	for (int y = 0; y < height; y++)
	{
		GotoXY(px, py + y + 1);
		// 왼쪽 벽
		Color::Print(Color::BG_CYAN, Color::WHITE, "|");

		// item의 정보를 출력

		string content = "";

		if (y == 1)
		{
			content = "이름 : " + item.GetName();
		}

		else if (y == 2)
		{
			content = "무게 : " + to_string(item.GetWeight());
		}

		else if (y == 3)
		{
			content = "가치 : " + to_string(item.GetValue());
		}

		if (!content.empty())
		{
			cout << Color::CYAN << content;

			for (int i = content.length(); i < width; i++)
			{
				cout << " ";
			}
		}

		else
		{
			// 공백
			for (int i = 0; i < width; i++)
			{
				cout << " ";
			}
		}

		// 오른쪽 벽
		Color::Print(Color::BG_CYAN, Color::WHITE, "|");
		cout << endl;

	}



	// 바닥
	GotoXY(px, py + height + 1);
	cout << Color::BG_CYAN << "+";

	// "----------"
	for (int i = 0; i < width; i++)
	{
		cout << "-";
	}


	cout << "+" << Color::RESET << endl;


}

void TestI(const ItemW& item)
{
	cout << item.GetName() << endl;
}

void ProcedualDrawBox(int startX, int startY, std::vector<ItemW>& items)
{
	queue<ItemW> itemQueue;


	for (auto& item : items)
	{
		itemQueue.push(item);
	}

	// ctrl + r + r 이름바꾸기 단축기
	int currentRow = 0;  // 현재 그려야할 도형의 X좌표
	int currentCol = 0;  // 현재 그려야할 도형의 Y좌표

	const int Box_Width = 20;
	const int Box_Height = 10;
	const int Box_RowSpacing = 5;
	const int Box_ColSpacing = 5;


	while (!itemQueue.empty())
	{
		ItemW currentItem = itemQueue.front();
		itemQueue.pop();
		TestI(currentItem);

		// ItemW 타입을 사용하는 함수를 만들어보세요.

		int boxX = startX + (currentRow * (Box_RowSpacing + Box_Width));
		int boxY = startY + (currentCol * (Box_ColSpacing + Box_Height));

		// 좌표를 수정해주는 코드를 작성해주세요. 3x3 의 박스로 아이템이 그려지도록 코드를 만들어보세요.

		DrawBox(boxX, boxY, Box_Width, Box_Height, currentItem);

		currentRow++;  // 0,1,2

		if (currentRow >= 3)
		{
			currentRow = 0;
			currentCol++;
		}

		Sleep(100);
	}
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

	LoadingAnimation();
	system("cls");
	
	// ItemW item("롱소드", 10, 10);
	// 
	// for (int i = 0; i < 4; i++)
	// {
	// 	DrawBox(5 + 25 * i, 5, 20, 10, item);
	// }

	// 어떤 좌표에 작성해야 겹치지 않고 그릴 수 있는지
	// 가로 길이 + 여백

	// DrawBox(35, 5, 20, 10);


	InventoryW inventory(7);

	ItemW A("A", 6, 13);
	ItemW B("B", 4, 8);
	ItemW C("C", 3, 6);
	ItemW D("D", 5, 12);

	std::vector<ItemW> selectableTable{ A,B,C,D };

	std::pair<int, std::vector<ItemW>>Bestitems = inventory.findOptionalItemCombination(7, selectableTable);

	std::cout << "주어진 아이템의 최대 가치 : " << Bestitems.first << std::endl;

	std::vector<ItemW> ItemC = Bestitems.second;

	ProcedualDrawBox(5,5, ItemC);

}
