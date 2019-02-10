#pragma once
#include "CommandPattern.h"
#include <Windows.h>		//used for console interface


class UI
{
public:
	UI(const Receiver& r);
	~UI();
	void run();
private:
	Receiver res;
	HANDLE consoleHandler = GetStdHandle(STD_OUTPUT_HANDLE);
	enum CursorMode
	{
		CURSOR_ON,
		CURSOR_OFF,
		CURSOR_BIG
	};
	unsigned countLine = 7;

	void setMyCursor(CursorMode cursorMode);
	void setColor(const WORD newColorToSet);
	int whereX();
	int whereY();
	void gotoxy(const int x, const int y);
	void clearArea(int x1, int y1, int x2, int y2);
	void box(int x1, int y1, int x2, int y2);
	void headerLine(const std::string& headString);
	void footerLine(const std::string& footString);
	void rightBottomText(const std::string& headerText, const WORD textColor);
	void blink(const std::string blinkText, const WORD textColor);
	void warning(const std::string& warningText);
	void showTextInBox(const std::string& shownInfo, bool newBeginKey, bool controlKey, int x1, int y1, int x2, int y2);
	void showLeftSide(const std::string& shownInfo, bool newBeginKey = 0);
	void showRightSide(const std::string& shownInfo, bool newBeginKey = 0, bool controlKey = 0);
	void showMore(const std::string&, const std::vector<Med>&);
	void redCross();
	int setup();
	void menu1();		//Add
	void menu2();		//Delete
	void menu3();		//Update
	void menu4();		//Search
	void menu5();		//Short Supply
	void menu6();		//Group by price
};

