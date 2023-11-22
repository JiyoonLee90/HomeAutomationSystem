#include "Washer.h"

Washer::Washer(int _type, const string& _machineName, int _powerConsumption, std::shared_ptr<SMSManager> _SMS_Manager)
	: Appliance(_type, _machineName, _powerConsumption, _SMS_Manager),
	state1(NO_OPERATION_WASHER) {}

std::shared_ptr<Appliance> Washer::creator(int _type, const std::string& _machineName, int _powerConsumption, std::shared_ptr<SMSManager> _SMS_Manager)
{
	std::shared_ptr<Appliance> app = std::make_shared<Washer>(_type, _machineName, _powerConsumption, _SMS_Manager);
	return app;
}

/*************************************** getter ***************************************/
int Washer::getState1() { return state1; }
/**************************************************************************************/

/*************************************** setter ***************************************/
void Washer::setState1(int _state1){
	state1 = _state1;
	switch (_state1)
	{
	case NO_OPERATION_WASHER:
		cout << "������ [SYSTEM] ������ ��带 �����մϴ�." << endl;
		break;
	case GENERAL:
		cout << "������ [SYSTEM] ���� ��带 �����մϴ�." << endl;
		break;
	case BOIL:
		cout << "������ [SYSTEM] ������ ��带 �����մϴ�." << endl;
		break;
	case DRY:
		cout << "������ [SYSTEM] ����� ��带 �����մϴ�." << endl;
		break;
	default:
		break;
	}
}
/**************************************************************************************/

/* ������ǰ ��� */
void Washer::display() {
	cout << "  - �̸� : " << getMachineName() << endl;

	if (getPowerFlag()) cout << "  - ���� : ON" << endl;
	else cout << "  - ���� : OFF" << endl;

	switch (getState1())
	{
	case NO_OPERATION_WASHER:
		cout << "  - ��� : ������" << endl;
		break;
	case GENERAL:
		cout << "  - ��� : �Ϲ� ����" << endl;
		break;
	case BOIL:
		cout << "  - ��� : ���� ����" << endl;
		break;
	case DRY:
		cout << "  - ��� : ������" << endl;
		break;
	default:
		break;
	}
}

/* ������ǰ ���� */
void Washer::control(){
	int cmd = 0;
	vector<string> vOptions = { "����", "���" };
	cmd = Util::getCommand(vOptions);

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
				powerOff(); // ��� �ð� ���� �� ���� OFF
				cout << "������ [SYSTEM] ������ �����ϴ�." << endl;
			}
		}
		break;

	case MODE:
		vOptions = { "������", "�Ϲ� ����", "���� ����", "������" };
		cmd = Util::getCommand(vOptions);
		setState1(cmd);
		break;

	default:
		break;
	}
}
AutoRegister Washer::ar(WASHER, &Washer::creator);
