#include "Light.h"

Light::Light(int _type, const string& _machineName, int _powerConsumption, std::shared_ptr<SMSManager> _SMS_Manager)
	: Appliance(_type, _machineName, _powerConsumption, _SMS_Manager) {}

std::shared_ptr<Appliance> Light::creator(int _type, const std::string& _machineName, int _powerConsumption, std::shared_ptr<SMSManager> _SMS_Manager)
{
	std::shared_ptr<Appliance> app = std::make_shared<Light>(_type, _machineName, _powerConsumption, _SMS_Manager);
	return app;
}

/* ������ǰ ��� */
void Light::display() {
	cout << "  - �̸� : " << getMachineName() << endl;

	if (getPowerFlag()) cout << "  - ���� : ON" << endl;
	else cout << "  - ���� : OFF" << endl;
}

/* ������ǰ ���� */
void Light::control(){
	int cmd = 0;
	vector<string> vOptions = { "���� ON", "���� OFF" };
	cmd = Util::getCommand(vOptions);

	if (cmd == POWER_ON) {
		if (getPowerFlag()) { // �̹� Ŀ���ִ� ���
			cout << "������ [SYSTEM] �̹� ������ ���� �ֽ��ϴ�." << endl;
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
		}
		else {
			powerOff(); // ��� �ð� ���� �� ���� OFF
			cout << "������ [SYSTEM] ������ �����ϴ�." << endl;
		}
	}
}
AutoRegister Light::ar(LIGHT, &Light::creator);