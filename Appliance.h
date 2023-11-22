#ifndef APPLIANCE_H
#define APPLIANCE_H
#include <string>
#include <iostream>
#include <conio.h> // _getch()
#include "SMSManager.h"
#include "Util.h"

typedef enum _applianceType { AIRCONDITIONER = 1, RICECOOKER, WASHER, LIGHT } applianceType_t; // 가전제품 타입
typedef enum _controlOpt { POWER = 1, MODE, TEMP } controlMenu_t; // 제어 옵션
typedef enum _controlOpt_PWR { POWER_ON = 1, POWER_OFF } controlMenu_PWR_t; // 제어 옵션 파워부
using namespace std;

class Appliance {
	int type; // 가전 제품 종류 { 1:"냉난방기", 2:"밥솥", 3:"세탁기", 4:"전등" };
	string machineName; // 가전 제품명(ID역할)
	int powerConsumption; // 시간당 전력 소모량
	bool powerFlag; // 전원 ON:TURE, 전원 OFF:FALSE
	time_t startHour; // 제품 사용 시작시간 (단위:Sec.)
	time_t useHour; // 누적 사용 시간 (단위:Sec.)
	std::shared_ptr<SMSManager> SMS_Manager;

public:
	Appliance(int _type, const string& _machineName, int _powerConsumption, std::shared_ptr<SMSManager> _SMS_Manager);
	int getType();
	string getMachineName();
	int getPowerConsumption();
	bool getPowerFlag();
	time_t getStartHour();
	time_t getUseHour();
	std::shared_ptr<SMSManager> getSMSManager();

	void setType(const int& _type);
	void setMachineName(const std::string& _machineName);
	void setPowerConsumption(const int& _powerConsumption);
	void setPowerFlag(bool _powerFlag);
	void setStartHour(const time_t& _startHour);
	void setUseHour(const time_t& _useHour);
	void setSMSManager(std::shared_ptr<SMSManager> _SMS_Manager);
	void setStartHour_PWR_ON();
	void powerOff(); // 사용 시간 설정 및 전원 OFF, SMS Manager call back

	virtual void display() = 0;
	virtual void control() = 0;
};

#endif