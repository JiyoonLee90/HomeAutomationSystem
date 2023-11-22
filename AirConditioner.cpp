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
		cout << "━━━ [SYSTEM] 송풍 모드를 가동합니다." << endl;
		break;
	case COOLER:
		cout << "━━━ [SYSTEM] 냉방 모드를 가동합니다." << endl;
		break;
	case HEATER:
		cout << "━━━ [SYSTEM] 난방 모드를 가동합니다." << endl;
		break;
	default:
		break;
	}
}

void AirConditioner::setState2(int _state2) { 
	state2 = _state2;
	cout << "━━━ [SYSTEM] " << _state2 << "도로 설정되었습니다." << endl;
}
/**************************************************************************************/

/* 가전제품 정보 출력 */
void AirConditioner::display() {
	cout << "  - 이름 : " << getMachineName() << endl;
	
	if (getPowerFlag()) cout << "  - 전원 : ON" << endl;
	else cout << "  - 전원 : OFF" << endl;

	switch (getState1())
	{
	case SENDAIR:
		cout << "  - 모드 : 송풍" << endl;
		break;
	case COOLER:
		cout << "  - 모드 : 냉방" << endl;
		break;
	case HEATER:
		cout << "  - 모드 : 난방" << endl;
		break;
	default:
		break;
	}

	cout << "  - 설정 온도 : " << getState2() << endl;
}

/* 가전제품 제어 */
void AirConditioner::control() {
	int cmd = 0;
	vector<string> vOptions = {"전원", "모드", "온도"};
	cmd = Util::getCommand(vOptions); // 유저 입력 획득 (유효성 검사 포함)

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
				powerOff(); // 사용 시간 설정 및 전원 OFF, SMS Manager call back
				cout << "━━━ [SYSTEM] 전원을 껐습니다." << endl;
			}
		}
		break;

	case MODE:
		vOptions = { "송풍", "냉방", "난방"};
		cmd = Util::getCommand(vOptions);
		setState1(cmd);		
		break;

	case TEMP:
		int temp;		
		bool inputValidity;
		do {
			cout << "━━━ [SYSTEM] 원하는 온도를 정수로 입력하여 주세요 (18~40도)" << endl;
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

