#include "Light.h"

Light::Light(int _type, const string& _machineName, int _powerConsumption, std::shared_ptr<SMSManager> _SMS_Manager)
	: Appliance(_type, _machineName, _powerConsumption, _SMS_Manager) {}

std::shared_ptr<Appliance> Light::creator(int _type, const std::string& _machineName, int _powerConsumption, std::shared_ptr<SMSManager> _SMS_Manager)
{
	std::shared_ptr<Appliance> app = std::make_shared<Light>(_type, _machineName, _powerConsumption, _SMS_Manager);
	return app;
}

/* 가전제품 출력 */
void Light::display() {
	cout << "  - 이름 : " << getMachineName() << endl;

	if (getPowerFlag()) cout << "  - 전원 : ON" << endl;
	else cout << "  - 전원 : OFF" << endl;
}

/* 가전제품 제어 */
void Light::control(){
	int cmd = 0;
	vector<string> vOptions = { "전원 ON", "전원 OFF" };
	cmd = Util::getCommand(vOptions);

	if (cmd == POWER_ON) {
		if (getPowerFlag()) { // 이미 커져있는 경우
			cout << "━━━ [SYSTEM] 이미 전원이 켜져 있습니다." << endl;
		}
		else {
			setStartHour_PWR_ON(); // 시작 시간 설정
			setPowerFlag(true); // 전원 ON
			cout << "━━━ [SYSTEM] 전원을 켰습니다." << endl;

			/* SMS Manager call back */
			std::string msg = getMachineName() + "을 켰습니다.";
			getSMSManager()->send_sms("POWER_ON", msg);
		}
	}
	else {
		if (!getPowerFlag()) { // 이미 꺼져있는 경우
			cout << "━━━ [SYSTEM] 이미 전원이 꺼져 있습니다." << endl;
		}
		else {
			powerOff(); // 사용 시간 설정 및 전원 OFF
			cout << "━━━ [SYSTEM] 전원을 껐습니다." << endl;
		}
	}
}
AutoRegister Light::ar(LIGHT, &Light::creator);