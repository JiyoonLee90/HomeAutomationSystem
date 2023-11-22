#include "AirConditioner.h"

AirConditioner::AirConditioner(int _type, const std::string& _machineName, int _powerConsumption, std::shared_ptr<SMSManager> _SMS_Manager)
	: Appliance(_type, _machineName, _powerConsumption, _SMS_Manager),
	  state1(SENDAIR), state2(25) {}

std::shared_ptr<Appliance> AirConditioner::creator(int _type, const std::string& _machineName, int _powerConsumption, std::shared_ptr<SMSManager> _SMS_Manager) {
	std::shared_ptr<Appliance> app = std::make_shared<AirConditioner>(_type, _machineName, _powerConsumption, _SMS_Manager);
	return app;
}

/*************************************** getter ***************************************/
int AirConditioner::getState1() { return state1; }
int AirConditioner::getState2() { return state2; }
/**************************************************************************************/

/*************************************** setter ***************************************/
void AirConditioner::setState1(int _state1) {
	state1 = _state1;
	switch (_state1)
	{
	case SENDAIR:
		cout << "������ [SYSTEM] ��ǳ ��带 �����մϴ�." << endl;
		break;
	case COOLER:
		cout << "������ [SYSTEM] �ù� ��带 �����մϴ�." << endl;
		break;
	case HEATER:
		cout << "������ [SYSTEM] ���� ��带 �����մϴ�." << endl;
		break;
	default:
		break;
	}
}

void AirConditioner::setState2(int _state2) { 
	state2 = _state2;
	cout << "������ [SYSTEM] " << _state2 << "���� �����Ǿ����ϴ�." << endl;
}
/**************************************************************************************/

/* ������ǰ ���� ��� */
void AirConditioner::display() {
	cout << "  - �̸� : " << getMachineName() << endl;
	
	if (getPowerFlag()) cout << "  - ���� : ON" << endl;
	else cout << "  - ���� : OFF" << endl;

	switch (getState1())
	{
	case SENDAIR:
		cout << "  - ��� : ��ǳ" << endl;
		break;
	case COOLER:
		cout << "  - ��� : �ù�" << endl;
		break;
	case HEATER:
		cout << "  - ��� : ����" << endl;
		break;
	default:
		break;
	}

	cout << "  - ���� �µ� : " << getState2() << endl;
}

/* ������ǰ ���� */
void AirConditioner::control() {
	int cmd = 0;
	vector<string> vOptions = {"����", "���", "�µ�"};
	cmd = Util::getCommand(vOptions); // ���� �Է� ȹ�� (��ȿ�� �˻� ����)

	switch (cmd) 
	{
	case POWER:
		vOptions = { "���� ON", "���� OFF" };
		cmd = Util::getCommand(vOptions);
		if (cmd == POWER_ON) {
			if (getPowerFlag()) { // �̹� Ŀ���ִ� ���
				cout << "������ [SYSTEM] �̹� ������ ���� �ֽ��ϴ�." << endl;
				break;
			}
			else {
				setStartHour_PWR_ON(); // ���� �ð� ����
				setPowerFlag(true); // ���� ON
				cout << "������ [SYSTEM] ������ �׽��ϴ�." << endl;

				/* SMS Manager call back */
				std::string msg = getMachineName() + "�� �׽��ϴ�.";
				getSMSManager()->send_sms("POWER_ON", msg);
			}
		}
		else {
			if (!getPowerFlag()) { // �̹� �����ִ� ���
				cout << "������ [SYSTEM] �̹� ������ ���� �ֽ��ϴ�." << endl;
				break;
			}
			else { 
				powerOff(); // ��� �ð� ���� �� ���� OFF, SMS Manager call back
				cout << "������ [SYSTEM] ������ �����ϴ�." << endl;
			}
		}
		break;

	case MODE:
		vOptions = { "��ǳ", "�ù�", "����"};
		cmd = Util::getCommand(vOptions);
		setState1(cmd);		
		break;

	case TEMP:
		int temp;		
		bool inputValidity;
		do {
			cout << "������ [SYSTEM] ���ϴ� �µ��� ������ �Է��Ͽ� �ּ��� (18~40��)" << endl;
			cin >> temp;
			inputValidity = Util::checkInputValidity(temp, 18, 40); // error handling
		} while (!inputValidity);

		setState2(temp);
		break;

	default:
		break;
	}
}
AutoRegister AirConditioner::ar(AIRCONDITIONER, &AirConditioner::creator);

