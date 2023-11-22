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
		cout << "━━━ [SYSTEM] 무동작 모드를 가동합니다." << endl;
		break;
	case GENERAL:
		cout << "━━━ [SYSTEM] 보온 모드를 가동합니다." << endl;
		break;
	case BOIL:
		cout << "━━━ [SYSTEM] 밥짓기 모드를 가동합니다." << endl;
		break;
	case DRY:
		cout << "━━━ [SYSTEM] 데우기 모드를 가동합니다." << endl;
		break;
	default:
		break;
	}
}
/**************************************************************************************/

/* 가전제품 출력 */
void Washer::display() {
	cout << "  - 이름 : " << getMachineName() << endl;

	if (getPowerFlag()) cout << "  - 전원 : ON" << endl;
	else cout << "  - 전원 : OFF" << endl;

	switch (getState1())
	{
	case NO_OPERATION_WASHER:
		cout << "  - 모드 : 무동작" << endl;
		break;
	case GENERAL:
		cout << "  - 모드 : 일반 빨래" << endl;
		break;
	case BOIL:
		cout << "  - 모드 : 삶은 빨래" << endl;
		break;
	case DRY:
		cout << "  - 모드 : 건조기" << endl;
		break;
	default:
		break;
	}
}

/* 가전제품 제어 */
void Washer::control(){
	int cmd = 0;
	vector<string> vOptions = { "전원", "모드" };
	cmd = Util::getCommand(vOptions);

	switch (cmd)
	{
	case POWER:
		vOptions = { "전원 ON", "전원 OFF" };
		cmd = Util::getCommand(vOptions);
		if (cmd == POWER_ON) {
			if (getPowerFlag()) { // 이미 커져있는 경우
				cout << "━━━ [SYSTEM] 이미 전원이 켜져 있습니다." << endl;
				break;
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
				break;
			}
			else {
				powerOff(); // 사용 시간 설정 및 전원 OFF
				cout << "━━━ [SYSTEM] 전원을 껐습니다." << endl;
			}
		}
		break;

	case MODE:
		vOptions = { "무동작", "일반 빨래", "삶은 빨래", "건조기" };
		cmd = Util::getCommand(vOptions);
		setState1(cmd);
		break;

	default:
		break;
	}
}
AutoRegister Washer::ar(WASHER, &Washer::creator);
