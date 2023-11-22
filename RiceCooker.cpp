#include "RiceCooker.h"

RiceCooker::RiceCooker(int _type, const string& _machineName, int _powerConsumption, std::shared_ptr<SMSManager> _SMS_Manager)
	: Appliance(_type, _machineName, _powerConsumption, _SMS_Manager),
	  state1(NO_OPERATION) {}

std::shared_ptr<Appliance> RiceCooker::creator(int _type, const std::string& _machineName, int _powerConsumption, std::shared_ptr<SMSManager> _SMS_Manager)
{
	std::shared_ptr<Appliance> app = std::make_shared<RiceCooker>(_type, _machineName, _powerConsumption, _SMS_Manager);
	return app;
}

/*************************************** getter ***************************************/
int RiceCooker::getState1() { return state1; }
/**************************************************************************************/

/*************************************** setter ***************************************/
void RiceCooker::setState1(int _state1){
	state1 = _state1;
	switch (_state1)
	{
	case NO_OPERATION:
		cout << "������ [SYSTEM] ������ ��带 �����մϴ�." << endl;
		break;
	case WARM:
		cout << "������ [SYSTEM] ���� ��带 �����մϴ�." << endl;
		break;
	case COOK:
		cout << "������ [SYSTEM] ������ ��带 �����մϴ�." << endl;
		break;
	case HEAT:
		cout << "������ [SYSTEM] ����� ��带 �����մϴ�." << endl;
		break;
	default:
		break;
	}
}
/**************************************************************************************/

/* ������ǰ ��� */
void RiceCooker::display() {
	cout << "  - �̸� : " << getMachineName() << endl;

	if (getPowerFlag()) cout << "  - ���� : ON" << endl;
	else cout << "  - ���� : OFF" << endl;

	switch (getState1())
	{
	case NO_OPERATION:
		cout << "  - ��� : ������" << endl;
		break;
	case WARM:
		cout << "  - ��� : ����" << endl;
		break;
	case COOK:
		cout << "  - ��� : ������" << endl;
		break;
	case HEAT:
		cout << "  - ��� : �����" << endl;
		break;
	default:
		break;
	}
}

/* ������ǰ ���� */
void RiceCooker::control(){
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
		vOptions = { "������", "����", "������", "�����"};
		cmd = Util::getCommand(vOptions);
		setState1(cmd);
		break;

	default:
		break;
	}
}
AutoRegister RiceCooker::ar(RICECOOKER, &RiceCooker::creator);

