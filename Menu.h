#ifndef MENU_H
#define MENU_H
#include <vector>
#include <string>
#include <conio.h> // _getch()
#include <functional>
#include "Appliance.h"
#include <memory>
#include <iostream>



using namespace std;
using namespace std::placeholders;
using HANDLER = function<void()>;

typedef enum _mainMenu { DISPLAY = 1, CONTROL, ADD, DELETE, EXIT } mainMenu_;

class Menu {
	string title;
	HANDLER handler;

public:
	Menu(const string& _title, HANDLER _handler = nullptr);
	string get_title();
	HANDLER getHandler();

	virtual ~Menu();
	virtual void selected() = 0;
};



class PopupMenu : public Menu {
	vector<shared_ptr<Menu>> vMenu;

public:
	PopupMenu(const string& _title, HANDLER _handler = nullptr);
	void add(shared_ptr<Menu> menu);

	void selected() override;
};



class ActionMenu : public Menu {
	int id;
	

public:
	ActionMenu(const string& _title, int _id, HANDLER _handler = nullptr);
	void selected() override; 
};

#endif