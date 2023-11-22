#include "HomeAutomationSystem.h"

HomeAutomationSystem::HomeAutomationSystem() : totalPowerConsumption(0) {
	/* make SMS Manager*/
	SMS_Manager = make_shared<SMSManager>();
	
	/* make root tree */
	shared_ptr<PopupMenu> root = make_shared<PopupMenu>("ROOT", bind(&HomeAutomationSystem::exitRoutine, this));

	shared_ptr<ActionMenu> am_display = make_shared<ActionMenu>("가전제품 상태 확인", 1, bind(&HomeAutomationSystem::displayAppliance, this));
	shared_ptr<PopupMenu> pm_control = make_shared<PopupMenu>("가전제품 제어");
	shared_ptr<ActionMenu> am_add = make_shared<ActionMenu>("가전제품 등록", 2, bind(&HomeAutomationSystem::addAppliance, this));
	shared_ptr<ActionMenu> am_delete = make_shared<ActionMenu>("가전제품 삭제", 3, bind(&HomeAutomationSystem::deleteAppliance, this));
	root->add(am_display);
	root->add(pm_control);
	root->add(am_add);
	root->add(am_delete);

	/* make pm_control tree */
	shared_ptr<ActionMenu> am_control = make_shared<ActionMenu>("가전제품 개별 제어", 4, bind(&HomeAutomationSystem::controlAppliance, this));
	shared_ptr<ActionMenu> am_pwroff_all = make_shared<ActionMenu>("전체 가전제품 PWR OFF", 5, bind(&HomeAutomationSystem::poweroff_all, this));
	pm_control->add(am_control);
	pm_control->add(am_pwroff_all);

	/* load data of appliances */
	std::ifstream fin("appliance.txt", std::ios::in);
	if (fin.is_open()) {
		int _type; std::string _machineName; int _powerConsumption; int _state1; int _state2;
		while(!fin.eof()){
			fin >> _type;
			if (_type == AIRCONDITIONER) {
				fin >> _machineName >> _powerConsumption >> _state1 >> _state2 >> std::ws;
				shared_ptr<AirConditioner> tmp = make_shared<AirConditioner>(_type, _machineName, _powerConsumption, getSMSManager());
				tmp->setState1(_state1);
				tmp->setState2(_state2);
				vApp.push_back(tmp);
			}
			else if (_type == RICECOOKER) {
				fin >> _machineName >> _powerConsumption >> _state1 >> std::ws;
				shared_ptr<RiceCooker> tmp = make_shared<RiceCooker>(_type, _machineName, _powerConsumption, getSMSManager());
				tmp->setState1(_state1);
				vApp.push_back(tmp);
			}
			else if (_type == WASHER) {
				fin >> _machineName >> _powerConsumption >> _state1 >> std::ws;
				shared_ptr<Washer> tmp = make_shared<Washer>(_type, _machineName, _powerConsumption, getSMSManager());			
				tmp->setState1(_state1);
				vApp.push_back(tmp);
			}
			else { // LIGHT
				fin >> _machineName >> _powerConsumption >> std::ws;
				shared_ptr<Light> tmp = make_shared<Light>(_type, _machineName, _powerConsumption, getSMSManager());
				vApp.push_back(tmp);
			}
		}
		system("cls");
		std::cout << "━━━ [SYSTEM] 시스템에 등록되었던 가전제품의 정보를 불러왔습니다." << endl;
		std::cout << "━━━ [SYSTEM] 아무 키나 누르시면 Home automation system이 시작됩니다." << endl;
		_getch();
	}
	
	/* Home automation system start */
	root->selected();
}

/* calc. total power consumption */
void HomeAutomationSystem::setTotalPowerConsumption(shared_ptr<Appliance> App) {
	totalPowerConsumption += (App->getUseHour() * App->getPowerConsumption()) / 3600.0;
}

std::shared_ptr<SMSManager> HomeAutomationSystem::getSMSManager() { return SMS_Manager; }

/* display appliances action menu */
void HomeAutomationSystem::displayAppliance() {
	/* empty check */
	if (vApp.size() == 0) {
		std::cout << "━━━ [SYSTEM] 등록된 가전제품이 없습니다." << endl;
		std::cout << "━━━ [SYSTEM] 이전 메뉴로 가려면 아무 키나 누르세요" << endl;
		_getch();
		return;
	}

	for (int i = 0; i < vApp.size(); i++) {
		std::cout << "[" << i + 1 << "번] 가전제품" << endl;
		vApp[i]->display(); // appliance별 display 함수 호출
		std::cout << endl;
	}

	std::cout << "━━━ [SYSTEM] 이전 메뉴로 가려면 아무 키나 누르세요" << endl;
	_getch();
}

/* contorl appliance action menu */
void HomeAutomationSystem::controlAppliance() {
	/* empty check */
	if (vApp.size() == 0) {
		std::cout << "━━━ [SYSTEM] 등록된 가전제품이 없습니다." << endl;
		std::cout << "━━━ [SYSTEM] 이전 메뉴로 가려면 아무 키나 누르세요" << endl;
		_getch();
		return;
	}

	/* get number of appliacne to control */
	for (int i = 0; i < vApp.size(); i++) {
		std::cout << "[" << i + 1 << "번] 가전제품" << endl;
		vApp[i]->display();
		std::cout << endl;
	}

	int cmd = -1; // 제어할 가전제품 번호
	bool inputValidity = true;
	do {
		std::cout << "제어할 가전제품의 번호를 입력하여 주세요" << endl;
		cin >> cmd;
		inputValidity = Util::checkInputValidity(cmd, 1, vApp.size()); // error handling
	} while (!inputValidity);

	vApp[cmd - 1]->control();
	std::cout << "━━━ [SYSTEM] 이전 메뉴로 가려면 아무 키나 누르세요" << endl;
	_getch();
}

/* add appliance action menu */
void HomeAutomationSystem::addAppliance() {
	/* get appliance type */
	int type = 0; // 가전제품 타입
	vector<string> vOptions = { "냉난방기", "밥솥", "세탁기", "전등" };
	type = Util::getCommand(vOptions);

	/* get name */
	string machineName;
	bool inputValidity = true;
	bool _isIn = false;
	do {
		std::cout << "━━━ [SYSTEM] 가전제품의 이름을 입력하여 주세요 (띄어쓰기 금지)" << endl;
		cin >> machineName;
		if ( inputValidity = Util::checkInputValidity() ){ // 1차 : validity 검사
		_isIn = isIn(machineName); // 2차 : 중복 검사
		}
	} while (_isIn || !inputValidity);

	/* get power consumption */
	int powerConsumption = 0;
	inputValidity = true;
	do {
		std::cout << "━━━ [SYSTEM] 시간당 소모전력량(kW)을 입력하여 주세요." << endl;
		cin >> powerConsumption;
		inputValidity = Util::checkInputValidity(); // error handling
	} while (!inputValidity);

	/* create appliance by factory */
	std::shared_ptr<Appliance> app = Factory::getFactory().createApp(type, machineName, powerConsumption, getSMSManager());
	vApp.push_back(app);

	std::cout << "━━━ [SYSTEM] 이전 메뉴로 가려면 아무 키나 누르세요" << endl;
	_getch();
}

/* delete appliance action menu */
void HomeAutomationSystem::deleteAppliance() {
	/* empty check */
	if (vApp.size() == 0) {
		std::cout << "━━━ [SYSTEM] 등록된 가전제품이 없습니다." << endl;
		std::cout << "━━━ [SYSTEM] 이전 메뉴로 가려면 아무 키나 누르세요" << endl;
		_getch();
		return;
	}

	/* get number to delete appliance */
	for (int i = 0; i < vApp.size(); i++) {
		std::cout << "[" << i + 1 << "번] 가전제품" << endl;
		vApp[i]->display();
		std::cout << endl;
	}

	int cmd = -1; // 삭제할 가전제품 번호
	bool inputValidity = true;
	do {
		std::cout << "삭제할 가전제품의 번호를 입력하여 주세요" << endl;
		cin >> cmd;
		inputValidity = Util::checkInputValidity(cmd, 1, vApp.size()); // error handling
	} while (!inputValidity);

	/* power off if power on */
	if (vApp[cmd - 1]->getPowerFlag()) vApp[cmd - 1]->powerOff();

	/* save power consumption */
	setTotalPowerConsumption(vApp[cmd - 1]);

	/* erase vector */
	vApp.erase(vApp.begin() + cmd - 1);

	std::cout << "━━━ [SYSTEM] 삭제가 완료되었습니다." << endl;
	std::cout << "━━━ [SYSTEM] 이전 메뉴로 가려면 아무 키나 누르세요" << endl;
	_getch();

}

/* power off all appliances action menu */
void HomeAutomationSystem::poweroff_all(){
	/* empty check */
	if (vApp.size() == 0) {
		std::cout << "━━━ [SYSTEM] 등록된 가전제품이 없습니다." << endl;
		std::cout << "━━━ [SYSTEM] 이전 메뉴로 가려면 아무 키나 누르세요" << endl;
		_getch();
		return;
	}
	
	/* power off all appliances */
	for (int i = 0; i < vApp.size(); i++) {
		if (!(vApp[i]->getPowerFlag())) { // 이미 꺼져있는 경우
			std::cout << "━━━ [SYSTEM] 이미 전원이 꺼져 있습니다." << " (제품명:" << vApp[i]->getMachineName() << ")" << endl;
		}
		else {
			vApp[i]->powerOff();
			std::cout << "━━━ [SYSTEM] 전원을 껐습니다." << " (제품명:" << vApp[i]->getMachineName() << ")" << endl;
		}
	}
	
	std::cout << "━━━ [SYSTEM] 이전 메뉴로 가려면 아무 키나 누르세요" << endl;
	_getch();
}

/* 프로그램 종료 routine */
void HomeAutomationSystem::exitRoutine() {
	for (auto e : vApp) {
		/* 전원이 켜져있다면 전원 OFF */
		if (e->getPowerFlag()) e->powerOff();
		
		/* 소비전력 계산 */
		totalPowerConsumption += (e->getPowerConsumption() * e->getUseHour()) / 3600.0;
	}
	
	std::cout << "━━━ [SYSTEM] 총 소비전력(kWh) : " << totalPowerConsumption << endl;

	/* save data of appliances*/
	if(vApp.size() > 0){
		std::ofstream fout("appliance.txt", std::ios::out | std::ios::trunc);
		if (!fout.is_open()) std::cerr << "file open error" << endl;
	 
		for (auto e : vApp) {
			fout << e->getType() << " "
				<< e->getMachineName() << " "
				<< e->getPowerConsumption();
		
			if (e->getType() == AIRCONDITIONER) { 
				shared_ptr<AirConditioner> tmp_ac = dynamic_pointer_cast<AirConditioner>(e);
				fout << " " << tmp_ac->getState1()
					<< " " << tmp_ac->getState2() << endl;;
			}
			else if (e->getType() == RICECOOKER) {
				shared_ptr<RiceCooker> tmp_rc = dynamic_pointer_cast<RiceCooker>(e);
				fout << " " << tmp_rc->getState1() << endl;;
			}
			else if (e->getType() == WASHER) {
				shared_ptr<Washer> tmp_w = dynamic_pointer_cast<Washer>(e);
				fout << " " << tmp_w->getState1() << endl;;
			}
			else fout << endl;
		}
		fout.close();
		std::cout << "━━━ [SYSTEM] 가전제품 정보를 저장하였습니다." << endl;
	}

	std::cout << "━━━ [SYSTEM] 종료하시려면 아무 키나 누르세요" << endl;
	_getch();
}

/* 가전제품 이름이 등록되어 있는지 검사 */
bool HomeAutomationSystem::isIn(string _machineName) {
	for (auto e : vApp) {
		if (e->getMachineName() == _machineName) {
			std::cout << "중복된 이름이 있습니다." << endl;
			return true;
		}
	}
	return false;
}