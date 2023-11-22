#define _CRTDBG_MAP_ALLOC // memory leak check
#include <memory>
#include "HomeAutomationSystem.h"

int main(){
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // memory leak check
	shared_ptr<HomeAutomationSystem> homeAutomationSystem = make_shared<HomeAutomationSystem>();
}

