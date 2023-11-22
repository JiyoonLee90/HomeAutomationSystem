#include "Menu.h"

/* Menu class member */
Menu::Menu(const string& _title, HANDLER _handler) : title(_title), handler(_handler) {}

string Menu::get_title() { return title; }

HANDLER Menu::getHandler() { return handler; }

Menu::~Menu() {}


/* PopupMenu class member*/
PopupMenu::PopupMenu(const string& _title, HANDLER _handler) : Menu(_title, _handler) {}

void PopupMenu::add(shared_ptr<Menu> menu) { vMenu.push_back(menu); }

/* routine when it is selected */
void PopupMenu::selected() {
	while (1) {
		system("cls");

		/* show menu */
		int size = vMenu.size();
		for (int i = 0; i < size; i++)
		{
			std::cout << i + 1 << ". " << vMenu[i]->get_title() << std::endl;
		}
		std::cout << size + 1 << ". 종료\n";

		/* get user commnad */
		int cmd;
		bool cinValidity = true;
		do {
			cout << "━━━ [SYSTEM] 메뉴를 선택하세요 >> ";
			cin >> cmd;
			cinValidity = Util::checkInputValidity(cmd, 1, vMenu.size() + 1); // error handling
		} while (!cinValidity);

		if (cmd == size + 1){ // 종료 메뉴 선택 시
			if (get_title() == "ROOT") { // root라면
				getHandler()(); // exitRoutine 실행 후 종료
			}
			break;
		}
		
		vMenu[cmd - 1]->selected();
	}
}


/* ActionMenu class member */
ActionMenu::ActionMenu(const string& _title, int _id, HANDLER _handler)
	: Menu(_title, _handler), id(_id) {}

/* operate when menu is selected */
void ActionMenu::selected() {
	if (getHandler() != nullptr) getHandler()();
}

