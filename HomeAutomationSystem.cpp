#include "HomeAutomationSystem.h"

HomeAutomationSystem::HomeAutomationSystem() : totalPowerConsumption(0) {
	/* make SMS Manager*/
	SMS_Manager = make_shared<SMSManager>();
	
	/* make root tree */
	shared_ptr<PopupMenu> root = make_shared<PopupMenu>("ROOT", bind(&HomeAutomationSystem::exitRoutine, this));

	shared_ptr<ActionMenu> am_display = make_shared<ActionMenu>("������ǰ ���� Ȯ��", 1, bind(&HomeAutomationSystem::displayAppliance, this));
	shared_ptr<PopupMenu> pm_control = make_shared<PopupMenu>("������ǰ ����");
	shared_ptr<ActionMenu> am_add = make_shared<ActionMenu>("������ǰ ���", 2, bind(&HomeAutomationSystem::addAppliance, this));
	shared_ptr<ActionMenu> am_delete = make_shared<ActionMenu>("������ǰ ����", 3, bind(&HomeAutomationSystem::deleteAppliance, this));
	root->add(am_display);
	root->add(pm_control);
	root->add(am_add);
	root->add(am_delete);

	/* make pm_control tree */
	shared_ptr<ActionMenu> am_control = make_shared<ActionMenu>("������ǰ ���� ����", 4, bind(&HomeAutomationSystem::controlAppliance, this));
	shared_ptr<ActionMenu> am_pwroff_all = make_shared<ActionMenu>("��ü ������ǰ PWR OFF", 5, bind(&HomeAutomationSystem::poweroff_all, this));
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
		std::cout << "������ [SYSTEM] �ý��ۿ� ��ϵǾ��� ������ǰ�� ������ �ҷ��Խ��ϴ�." << endl;
		std::cout << "������ [SYSTEM] �ƹ� Ű�� �����ø� Home automation system�� ���۵˴ϴ�." << endl;
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
		std::cout << "������ [SYSTEM] ��ϵ� ������ǰ�� �����ϴ�." << endl;
		std::cout << "������ [SYSTEM] ���� �޴��� ������ �ƹ� Ű�� ��������" << endl;
		_getch();
		return;
	}

	for (int i = 0; i < vApp.size(); i++) {
		std::cout << "[" << i + 1 << "��] ������ǰ" << endl;
		vApp[i]->display(); // appliance�� display �Լ� ȣ��
		std::cout << endl;
	}

	std::cout << "������ [SYSTEM] ���� �޴��� ������ �ƹ� Ű�� ��������" << endl;
	_getch();
}

/* contorl appliance action menu */
void HomeAutomationSystem::controlAppliance() {
	/* empty check */
	if (vApp.size() == 0) {
		std::cout << "������ [SYSTEM] ��ϵ� ������ǰ�� �����ϴ�." << endl;
		std::cout << "������ [SYSTEM] ���� �޴��� ������ �ƹ� Ű�� ��������" << endl;
		_getch();
		return;
	}

	/* get number of appliacne to control */
	for (int i = 0; i < vApp.size(); i++) {
		std::cout << "[" << i + 1 << "��] ������ǰ" << endl;
		vApp[i]->display();
		std::cout << endl;
	}

	int cmd = -1; // ������ ������ǰ ��ȣ
	bool inputValidity = true;
	do {
		std::cout << "������ ������ǰ�� ��ȣ�� �Է��Ͽ� �ּ���" << endl;
		cin >> cmd;
		inputValidity = Util::checkInputValidity(cmd, 1, vApp.size()); // error handling
	} while (!inputValidity);

	vApp[cmd - 1]->control();
	std::cout << "������ [SYSTEM] ���� �޴��� ������ �ƹ� Ű�� ��������" << endl;
	_getch();
}

/* add appliance action menu */
void HomeAutomationSystem::addAppliance() {
	/* get appliance type */
	int type = 0; // ������ǰ Ÿ��
	vector<string> vOptions = { "�ó����", "���", "��Ź��", "����" };
	type = Util::getCommand(vOptions);

	/* get name */
	string machineName;
	bool inputValidity = true;
	bool _isIn = false;
	do {
		std::cout << "������ [SYSTEM] ������ǰ�� �̸��� �Է��Ͽ� �ּ��� (���� ����)" << endl;
		cin >> machineName;
		if ( inputValidity = Util::checkInputValidity() ){ // 1�� : validity �˻�
		_isIn = isIn(machineName); // 2�� : �ߺ� �˻�
		}
	} while (_isIn || !inputValidity);

	/* get power consumption */
	int powerConsumption = 0;
	inputValidity = true;
	do {
		std::cout << "������ [SYSTEM] �ð��� �Ҹ����·�(kW)�� �Է��Ͽ� �ּ���." << endl;
		cin >> powerConsumption;
		inputValidity = Util::checkInputValidity(); // error handling
	} while (!inputValidity);

	/* create appliance by factory */
	std::shared_ptr<Appliance> app = Factory::getFactory().createApp(type, machineName, powerConsumption, getSMSManager());
	vApp.push_back(app);

	std::cout << "������ [SYSTEM] ���� �޴��� ������ �ƹ� Ű�� ��������" << endl;
	_getch();
}

/* delete appliance action menu */
void HomeAutomationSystem::deleteAppliance() {
	/* empty check */
	if (vApp.size() == 0) {
		std::cout << "������ [SYSTEM] ��ϵ� ������ǰ�� �����ϴ�." << endl;
		std::cout << "������ [SYSTEM] ���� �޴��� ������ �ƹ� Ű�� ��������" << endl;
		_getch();
		return;
	}

	/* get number to delete appliance */
	for (int i = 0; i < vApp.size(); i++) {
		std::cout << "[" << i + 1 << "��] ������ǰ" << endl;
		vApp[i]->display();
		std::cout << endl;
	}

	int cmd = -1; // ������ ������ǰ ��ȣ
	bool inputValidity = true;
	do {
		std::cout << "������ ������ǰ�� ��ȣ�� �Է��Ͽ� �ּ���" << endl;
		cin >> cmd;
		inputValidity = Util::checkInputValidity(cmd, 1, vApp.size()); // error handling
	} while (!inputValidity);

	/* power off if power on */
	if (vApp[cmd - 1]->getPowerFlag()) vApp[cmd - 1]->powerOff();

	/* save power consumption */
	setTotalPowerConsumption(vApp[cmd - 1]);

	/* erase vector */
	vApp.erase(vApp.begin() + cmd - 1);

	std::cout << "������ [SYSTEM] ������ �Ϸ�Ǿ����ϴ�." << endl;
	std::cout << "������ [SYSTEM] ���� �޴��� ������ �ƹ� Ű�� ��������" << endl;
	_getch();

}

/* power off all appliances action menu */
void HomeAutomationSystem::poweroff_all(){
	/* empty check */
	if (vApp.size() == 0) {
		std::cout << "������ [SYSTEM] ��ϵ� ������ǰ�� �����ϴ�." << endl;
		std::cout << "������ [SYSTEM] ���� �޴��� ������ �ƹ� Ű�� ��������" << endl;
		_getch();
		return;
	}
	
	/* power off all appliances */
	for (int i = 0; i < vApp.size(); i++) {
		if (!(vApp[i]->getPowerFlag())) { // �̹� �����ִ� ���
			std::cout << "������ [SYSTEM] �̹� ������ ���� �ֽ��ϴ�." << " (��ǰ��:" << vApp[i]->getMachineName() << ")" << endl;
		}
		else {
			vApp[i]->powerOff();
			std::cout << "������ [SYSTEM] ������ �����ϴ�." << " (��ǰ��:" << vApp[i]->getMachineName() << ")" << endl;
		}
	}
	
	std::cout << "������ [SYSTEM] ���� �޴��� ������ �ƹ� Ű�� ��������" << endl;
	_getch();
}

/* ���α׷� ���� routine */
void HomeAutomationSystem::exitRoutine() {
	for (auto e : vApp) {
		/* ������ �����ִٸ� ���� OFF */
		if (e->getPowerFlag()) e->powerOff();
		
		/* �Һ����� ��� */
		totalPowerConsumption += (e->getPowerConsumption() * e->getUseHour()) / 3600.0;
	}
	
	std::cout << "������ [SYSTEM] �� �Һ�����(kWh) : " << totalPowerConsumption << endl;

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
		std::cout << "������ [SYSTEM] ������ǰ ������ �����Ͽ����ϴ�." << endl;
	}

	std::cout << "������ [SYSTEM] �����Ͻ÷��� �ƹ� Ű�� ��������" << endl;
	_getch();
}

/* ������ǰ �̸��� ��ϵǾ� �ִ��� �˻� */
bool HomeAutomationSystem::isIn(string _machineName) {
	for (auto e : vApp) {
		if (e->getMachineName() == _machineName) {
			std::cout << "�ߺ��� �̸��� �ֽ��ϴ�." << endl;
			return true;
		}
	}
	return false;
}