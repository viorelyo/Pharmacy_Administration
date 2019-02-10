#include "stdafx.h"
#include "UI.h"
#include <iomanip>			//used for cout << setw()


UI::UI(const Receiver& r)
{
	this->res = r;
}


UI::~UI()
{
}


void UI::setMyCursor(CursorMode cursorMode) {
	/*
	*	Set cursor mode
	*/

	if (consoleHandler == INVALID_HANDLE_VALUE)
		return;

	CONSOLE_CURSOR_INFO cursorInfo;

	switch (cursorMode)
	{
	case CURSOR_OFF:
		cursorInfo.bVisible = false;
		cursorInfo.dwSize = 10;
		break;
	case CURSOR_ON:
		cursorInfo.bVisible = TRUE;
		cursorInfo.dwSize = 10;
		break;
	case CURSOR_BIG:
		cursorInfo.bVisible = TRUE;
		cursorInfo.dwSize = 100;
		break;
	}

	SetConsoleCursorInfo(consoleHandler, &cursorInfo);
}


void UI::setColor(const WORD newColorToSet) {
	/*
	*	Set Console Display Color to specified one
	*/

	if (consoleHandler == INVALID_HANDLE_VALUE)
		return;

	SetConsoleTextAttribute(consoleHandler, newColorToSet);
}


int UI::whereX() {
	/*
	*	Get current cursor position on X dimension
	*/

	if (consoleHandler == INVALID_HANDLE_VALUE)
		return 0;

	CONSOLE_SCREEN_BUFFER_INFO screenInfo;
	GetConsoleScreenBufferInfo(consoleHandler, &screenInfo);

	return screenInfo.dwCursorPosition.X + 1;
}


int UI::whereY() {
	/*
	*	Get current cursor position on Y dimension
	*/

	if (consoleHandler == INVALID_HANDLE_VALUE)
		return 0;

	CONSOLE_SCREEN_BUFFER_INFO screenInfo;
	GetConsoleScreenBufferInfo(consoleHandler, &screenInfo);

	return screenInfo.dwCursorPosition.Y + 1;
}


void UI::gotoxy(const int x, const int y) {
	/*
	*	Set cursor to given position
	*/

	if (consoleHandler == INVALID_HANDLE_VALUE)
		return;

	COORD coords = { short(x - 1), short(y - 1) };
	SetConsoleCursorPosition(consoleHandler, coords);
}


void UI::clearArea(int x1, int y1, int x2, int y2) {
	int i, j;
	int x = whereX();
	int y = whereY();
	gotoxy(x1, y1);

	setMyCursor(CURSOR_OFF);
	for (j = y1; j <= y2; j++)
		for (i = x1; i <= x2; i++) {
			gotoxy(i, j);
			std::cout << " ";
		}

	setMyCursor(CURSOR_ON);
	//gotoxy(x, y);
}


void UI::box(int x1, int y1, int x2, int y2) {
	/*
	*	Create box with given Coordinates
	*/

  	unsigned char topLeft = 201;
	unsigned char horizontalLines = 205;
	unsigned char topRight = 187;
	unsigned char verticalLines = 186;
	unsigned char bottomLeft = 200;
	unsigned char bottomRight = 188;

	int i;
	int xBegin = whereX();
	int yBegin = whereY();

	setMyCursor(CURSOR_OFF);

	gotoxy(x1, y1);			//left top corner
	std::cout << topLeft;
	for (i = x1 + 1; i < x2; i++)
		std::cout << horizontalLines;
	gotoxy(x2, y1); 		//right top corner
	std::cout << topRight;
	for (i = y1 + 1; i < y2; i++) {
		// Vertical lines
		gotoxy(x1, i);			//left vLine
		std::cout << verticalLines;
		gotoxy(x2, i);			//right vLine
		std::cout << verticalLines;
	}
	gotoxy(x1, y2);
	std::cout << bottomLeft; 	//left bottom corner
	for (i = x1 + 1; i < x2; i++)
		std::cout << horizontalLines;		//bottom line
	gotoxy(x2, y2);
	std::cout << bottomRight;			//right bottom corner

	gotoxy(xBegin, yBegin);
	setMyCursor(CURSOR_ON);
}


void UI::headerLine(const std::string& headString) {
	/*
	*	Set title (headline)
	*/

	setMyCursor(CURSOR_OFF);

	int xBegin = whereX();
	int yBegin = whereY();
	int strLength = headString.length();

	clearArea(6, 3, 76, 3);
	box(5, 2, 78, 4);			//top box

	strLength /= 2;
	gotoxy((40 - strLength), 3);
	std::cout << headString;

	gotoxy(xBegin, yBegin);
}


void UI::footerLine(const std::string& footString) {
	/*
	*	Set the text at the bottom
	*/

	int strLength = footString.length();
	clearArea(6, 24, 77, 24);
	box(5, 23, 78, 25); 		//bottom box

	strLength /= 2;
	gotoxy(8, 24);
	std::cout << footString;

	setMyCursor(CURSOR_ON);
}


void UI::rightBottomText(const std::string& headerText, const WORD textColor) {
	/*
	*	Display text at right bottom box
	*/

	setMyCursor(CURSOR_OFF);

	int xBegin = whereX();
	int yBegin = whereY();
	setColor(textColor);

	std::string ptrLetter = headerText;
	int ctr = 0;
	int xAxes = 77;

	while (ctr != ptrLetter.length()) {
		ctr++;
		gotoxy(xBegin, yBegin);
	}

	int i = ptrLetter.length();
	for (; ctr != -1; ctr--) {
		gotoxy(xAxes, 24);
		std::cout << ptrLetter[i];
		i--;
		xAxes--;
	}
	gotoxy(70, 24);			//75
	setColor(textColor);
	gotoxy(xBegin, yBegin);
}


void UI::blink(const std::string blinkText, const WORD textColor) {
	/*
	*	Blink Error text at right bottom box
	*/

	CONSOLE_SCREEN_BUFFER_INFO screenInfo;
	GetConsoleScreenBufferInfo(consoleHandler, &screenInfo);
	setMyCursor(CURSOR_OFF);

	int xBegin = whereX();
	int yBegin = whereY();

	Sleep(500);
	for (int i = 0; i < 1; i++) {			//Blink 2 times
		setColor(textColor);
		rightBottomText(blinkText, textColor);
		Sleep(500);
		clearArea(6, 24, 77, 24);
		Sleep(500);
		setColor(textColor);
		rightBottomText(blinkText, textColor);
	}
	Sleep(2000);
	clearArea(6, 24, 77, 24);
	gotoxy(xBegin, yBegin);
	setColor(screenInfo.wAttributes);
}


void UI::warning(const std::string& warningText) {
	/*
	*	Blink red Message at the bottom in case of error
	*/

	blink(warningText, FOREGROUND_RED | FOREGROUND_INTENSITY);
}


void UI::showTextInBox(const std::string& shownInfo, bool newBeginKey, bool controlKey, int x1, int y1, int x2, int y2) {
	/*
	*	Show given info on the screen in specified box
	*/

	setMyCursor(CURSOR_OFF);
	box(x1, y1, x2, y2);
	x1++;
	x2--;
	y2--;
	int xBegin = whereX();
	int yBegin = whereY();

	if (newBeginKey == 1) {
		clearArea(x1 + 1, y1 + 1, x2 - 1, y2 - 1);
		countLine = y1 + 1;
	}
	countLine++;

	gotoxy(x1 + 1, countLine);

	unsigned placeHolder = 0;
	unsigned letterCounterBegin = 0;
	unsigned letterCounterEnd = 0;
	unsigned xPixel;
	unsigned yPixel;
	bool equalityKey = false;
	bool lastLine = false;
	char letter;
	while (letterCounterBegin < shownInfo.length())
	{
		letter = shownInfo[letterCounterBegin];
		if (letter != ' ')
		{
			placeHolder = letterCounterBegin;
			while (letter != ' ' && letterCounterBegin < shownInfo.length())
			{
				letterCounterBegin++;
				letter = shownInfo[letterCounterBegin];
			};
		};

		xPixel = whereX();
		yPixel = whereY();

		if (countLine == y2 - 1 && controlKey == 0 && ((letterCounterBegin - placeHolder) >= (x2 - xPixel)))
		{
			countLine = y1 + 1;
			clearArea(x1 + 1, y1 + 1, x2 - 1, y2 - 1);
			gotoxy(x1 + 1, countLine);
		}
		if (countLine == y2 - 1 && controlKey == 1 && ((letterCounterBegin - placeHolder) >= (x2 - xPixel)))
		{
			countLine = y1 + 1;
			setColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
			getchar();
			clearArea(x1 + 1, y1 + 1, x2 - 1, y2 - 1);
			setColor(FOREGROUND_GREEN);
			clearArea(1, 24, 80, 24);
			gotoxy(x1 + 2, countLine + 1);
		}
		if ((letterCounterBegin - placeHolder) < (x2 - xPixel))
		{
			for (;placeHolder < letterCounterBegin; placeHolder++)
				std::cout << shownInfo[placeHolder];
		}

		else if ((letterCounterBegin - placeHolder) < x2 - x1)
		{
			countLine++;
			gotoxy(x1 + 1, countLine);
			for (;placeHolder < letterCounterBegin; placeHolder++)
				std::cout << shownInfo[placeHolder];
		}
		else
		{
			for (;placeHolder < letterCounterBegin; placeHolder++)
			{
				int xPixel2 = whereX();
				if (xPixel2 == x2) {
					countLine++;
					gotoxy(x1 + 1, countLine);
				}
				std::cout << shownInfo[placeHolder];
			}

		}
		letterCounterBegin++;
		if (whereX() != x2 - 1)
			std::cout << (" ");
	}
}


void UI::showLeftSide(const std::string& shownInfo, bool newBeginKey) {
	/*
	*	Show given items as menu on the left side
	*/

	CONSOLE_SCREEN_BUFFER_INFO screenInfo;
	GetConsoleScreenBufferInfo(consoleHandler, &screenInfo);
	setColor(BACKGROUND_GREEN);
	showTextInBox(shownInfo, newBeginKey, 1, 7, 6, 30, 21);			//left - menu box
	setColor(screenInfo.wAttributes);
}


void UI::showRightSide(const std::string& shownInfo, bool newBeginKey, bool controlKey) {
	showTextInBox(shownInfo, newBeginKey, 1, 32, 6, 76, 21);
}


void UI::showMore(const std::string& menuTitle, const std::vector<Med>& foundMedicines) {
	/*
	*	Creates new dynamic box (depending on number of objects in vector) 
	*	Shows all objects
	*/

	if (foundMedicines.size() != 0) {
		//Create large center BOX for displaying elements
		clearArea(5, 6, 78, 25);		//delete previous
		box(5, 5, 78, 6 + foundMedicines.size() + 5);			//reserve box space for showing elements
		gotoxy(35, 7);
		std::cout << menuTitle;			//title of menu parameter 
		gotoxy(35, 8);
		for (unsigned i = 0; i < menuTitle.length(); i++)				//show dotted Line under menu title
			std::cout << "-";
		gotoxy(10, 9);
		std::cout << std::setw(15) << "Name" << std::setw(18) << "Concentration" << std::setw(13) << "Quantity" << std::setw(10) << "Price";			//setw() aligns the fields

		setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		int cursorY = 10;					//used for change cursor to new LINE (OY)
		for (unsigned i = 0; i < foundMedicines.size(); i++) {
			gotoxy(10, cursorY++);
			std::cout << std::setw(15) << foundMedicines[i].getName() << std::setw(18) << foundMedicines[i].getConcentration() << std::setw(13) << foundMedicines[i].getQuantity() << std::setw(10) << foundMedicines[i].getPrice();
		}

		setMyCursor(CURSOR_OFF);
		std::cin.get();					//wait for user to press any key to get back to main menu
	}
	else {
		warning("Error: No match!");
	}
}


void UI::redCross() {
	/*
	*	Display Red Cross (Medicine)
	*/

	setMyCursor(CURSOR_OFF);
	setColor(FOREGROUND_RED | FOREGROUND_INTENSITY);

	gotoxy(54, 12);
	unsigned char point = 219;
	std::cout << point << point;
	gotoxy(52, 13);
	std::cout << point << point << point << point << point << point;
	gotoxy(54, 14);
	std::cout << point << point;

	setColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	setMyCursor(CURSOR_ON);
}


int UI::setup() {
	/*
	*	Display initial menu
	*	Wait for option
	*/

	setColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	clearArea(5, 2, 78, 30);	//prepare for next iteration (should be changed depending on previous size)
	box(5, 2, 78, 4);			//top box
	box(5, 5, 78, 22); 			//center - out box      
	box(7, 6, 30, 21); 			//left - menu box     
	box(32, 6, 76, 21); 		//right - screen box
	box(5, 23, 78, 25); 		//bottom box

	headerLine("Smiles Pharmacy");

	showLeftSide("    MENU   ", 1);
	showLeftSide("    ----   ");
	showLeftSide(" 0 EXIT");
	showLeftSide(" 1 Add Medicine");
	showLeftSide(" 2 Delete Medicine");
	showLeftSide(" 3 Update Medicine");
	showLeftSide(" 4 Search Medicine");
	showLeftSide(" 5 Short supply");
	showLeftSide(" 6 Group by price");
	showLeftSide(" 7 Undo");
	showLeftSide(" 8 Redo");
	redCross();

	footerLine("Enter your choice [1-6]: ");

	int option = 0;
	std::cin >> option;
	while (option < 0 || option > 8)					//should be changed in case of adding new menus
	{
		option = 0;
		warning("Error: No such option!");
		footerLine("Enter your choice [1-6]: ");
		std::cin >> option;
	}

	return option;
}


void UI::menu1()
{
	/*
	*	Menu for Adding Medicine
	*/

	std::string name;
	double concentration;
	double quantity;
	double price;
	std::string auxiliaryString;

	showRightSide("        ADD MEDICINE", 1);
	showRightSide(" ----------------------------------------");				//40 dashes
	showRightSide("");
	showRightSide("Complete the information about a new product. Every product is identified by it's name and concentration");	
	showRightSide(" ----------------------------------------");				//40 dashes

	footerLine("Name : ");
	std::cin >> name;
	footerLine("Concentration : ");
	std::cin >> concentration;
	footerLine("Quantity : ");
	std::cin >> quantity;
	while (quantity <= 0) {
		warning("Quantity should be > 0!");
		footerLine("Quantity : ");
		std::cin >> quantity;
	}

	footerLine("Price : ");
	std::cin >> price;
	while (price <= 0) {
		warning("Price should be > 0!");
		footerLine("Price : ");
		std::cin >> price;
	}
	std::cin.ignore();
	
	res.Add(name, concentration, quantity, price);
	
	std::string concentration_str = std::to_string(concentration);
	auxiliaryString = name + " " + concentration_str + "\b\b\b\b" + " successfully added!";
	showRightSide(auxiliaryString);
	Sleep(2000);
}


void UI::menu2()
{
	/*
	*	Menu for Deleting
	*/

	std::string name;
	double concentration;
	double quantityToDelete;
	std::string auxiliaryString;

	showRightSide("       DELETE MEDICINE", 1);
	showRightSide(" ----------------------------------------");
	showRightSide("");
	showRightSide("Specify the quantity of a product you want to delete.");
	showRightSide(" ----------------------------------------");

	footerLine("Name : ");
	std::cin >> name;
	std::cin.ignore();
	footerLine("Concentration : ");
	std::cin >> concentration;
	std::cin.ignore();
	footerLine("Quantity to delete : ");
	std::cin >> quantityToDelete;
	std::cin.ignore();

	if (res.Delete(name, concentration, quantityToDelete) == -1) {
		std::string concentration_str = std::to_string(concentration);

		auxiliaryString = "Error: " + name + " " + concentration_str.substr(0, 6) + " not found!";				//substr() used for setting precision
		warning(auxiliaryString);
	}
	else {
		std::string concentration_str = std::to_string(concentration);
		auxiliaryString = name + " " + concentration_str + "\b\b\b\b" + " successfully deleted!";
		showRightSide(auxiliaryString);
		Sleep(2000);
	}
}


void UI::menu3()
{
	/*
	*	Menu for Updating
	*/

	std::string name;
	double concentration;
	double newPrice;
	std::string auxiliaryString;

	showRightSide("       UPDATE MEDICINE", 1);
	showRightSide(" ----------------------------------------");
	showRightSide("");
	showRightSide("Specify the new price for the product you want to update.");
	showRightSide(" ----------------------------------------");

	footerLine("Name : ");
	std::cin >> name;
	std::cin.ignore();
	footerLine("Concentration : ");
	std::cin >> concentration;
	std::cin.ignore();
	footerLine("New Price : ");
	std::cin >> newPrice;
	while (newPrice <= 0) {
		warning("New Price should be > 0!");
		footerLine("New Price : ");
		std::cin >> newPrice;
	}
	std::cin.ignore();

	if (res.Update(name, concentration, newPrice) == -1) {
		std::string concentration_str = std::to_string(concentration);

		auxiliaryString = "Error: " + name + " " + concentration_str.substr(0, 6) + " not found!";				//substr() used for setting precision
		warning(auxiliaryString);
	}
	else {
		std::string concentration_str = std::to_string(concentration);
		auxiliaryString = name + " " + concentration_str + "\b\b\b\b" + " successfully updated!";
		showRightSide(auxiliaryString);
		Sleep(2000);
	}
}


void UI::menu4()
{
	/*
	*	Display menu of Search substring
	*	If the whole name of medication is introduced, the image of product is displayed in browser
	*/
	
	std::vector<Med> foundMedicines;
	std::string search;
	std::string auxiliaryString;

	showRightSide("       SEARCH MEDICINE", 1);
	showRightSide(" ----------------------------------------");			//40 dashes
	showRightSide("");
	showRightSide("Search a product by it's name.");
	showRightSide(" ----------------------------------------");

	footerLine("Search medicine : ");

	std::cin.ignore();			//delete input buffer : get ready for getline
	getline(std::cin, search);		//used to verify if string is empty

	foundMedicines = res.getCtrl().searchName(search);
	
	showMore("Found Items", foundMedicines);

	//If the search string is full equal to a Medicine name
	//Search the image of the product on google
	std::vector<Med> googleItALL = res.getCtrl().getRepo().getMedicines();
	bool gotcha = false;

	for (unsigned i = 0; i < googleItALL.size(); i++)
		if (googleItALL[i].getName() == search) {
			gotcha = true;
			break;
		}

	if (gotcha) {
		std::string url = "https://www.google.com/search?tbm=isch&q=";
		url = url + search;
		ShellExecuteA(NULL, NULL, "chrome.exe", url.c_str(), NULL, SW_SHOWMAXIMIZED);
	}
}


void UI::menu5()
{
	/*
	*	Display menu of Short Supply
	*/

	std::vector<Med> foundMedicines;
	double items;
	
	showRightSide("       SHORT SUPPLY", 1);
	showRightSide(" ----------------------------------------");			//40 dashes
	showRightSide("");
	showRightSide("Introduce a quantity value and see which products are in short supply.");
	showRightSide(" ----------------------------------------");

	footerLine("Quantity : ");
	std::cin >> items;
	std::cin.ignore();

	foundMedicines = res.getCtrl().shortSupply(items);

	showMore("Found Items", foundMedicines);
}


void UI::menu6()
{
	/*
	*	Display menu for group by price
	*/


	std::vector<std::vector<Med>> group = res.getCtrl().groupPrice();
	unsigned elements = res.getCtrl().getRepo().getMedicines().size();

	showRightSide("       GROUP BY PRICE", 1);
	showRightSide(" ----------------------------------------");			//40 dashes
	showRightSide("");
	showRightSide("Show all available products grupped in price categories.");
	showRightSide(" ----------------------------------------");
	
	footerLine("Press ENTER to view...");
	std::cin.ignore();
	std::cin.get();

	if (group.size() != 0) {
		//Create large center BOX for displaying elements
		clearArea(5, 6, 78, 25);			//delete previous (Main menu)			
		box(5, 5, 78, 6 + 5 + group.size() * 3 + elements);				//reserve box space for showing elements
		gotoxy(35, 7);
		std::cout << "GROUP BY PRICE";				//title of menu parameter 
		gotoxy(35, 8);
		std::cout << "--------------";

		int cursorY = 10;					//used for change cursor to new line (oy)
		for (unsigned i = 0; i < group.size(); i++) {
			gotoxy(10, cursorY++);
			std::cout << "Category : " << group[i][0].getPrice();
			gotoxy(10, cursorY++);
			std::cout << "--------------------------------------------------------";
			gotoxy(10, cursorY++);
			std::cout << std::setw(15) << "Name" << std::setw(18) << "Concentration" << std::setw(13) << "Quantity" << std::setw(10) << "Price";			//setw() aligns the fields
			setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			for (unsigned j = 0; j < group[i].size(); j++) {
				gotoxy(10, cursorY++);
				std::cout << std::setw(15) << group[i][j].getName() << std::setw(18) << group[i][j].getConcentration() << std::setw(13) << group[i][j].getQuantity() << std::setw(10) << group[i][j].getPrice();
			}
			setColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}

		setMyCursor(CURSOR_OFF);
		std::cin.get();					//wait for user to press any key to get back to main menu
	}
	else {
		warning("Error: No match!");
	}
	
}


void UI::run()
{
	/*
	*	Run the GUI
	*	Interact with user
	*/

	while (true)
	{
		switch (setup())			//setup() returns the option of the user
		{
		case 0:						//Exit condition
			setMyCursor(CURSOR_OFF);
			showRightSide(" Bye!  ", 1);
			Sleep(600);
			std::cout << "Press any key to exit ...";
			redCross();
			gotoxy(77, 24);
			std::cin.ignore();
			std::cin.get();
			return;
		case 1: 
			menu1();
			break;
		case 2:
			menu2();
			break;
		case 3:
			menu3();
			break;
		case 4:
			menu4();
			break;
		case 5:
			menu5();
			break;
		case 6:
			menu6();
			break;
		case 7:
			if (res.Undo() == -1)
				warning("History is empty");
			break;
		case 8:
			if (res.Redo() == -1)
				warning("History is empty");
			break;
		}
	}
	//gotoxy(5, 28);			//Cursor at the end
	return;
}

