#ifndef APPLIANCE_H
#define APPLIANCE_H
#include <string>
#include <iostream>
#include <conio.h> // _getch()
#include "SMSManager.h"
#include "Util.h"

typedef enum _applianceType { AIRCONDITIONER = 1, RICECOOKER, WASHER, LIGHT } applianceType_t; // ������ǰ Ÿ��
typedef enum _controlOpt { POWER = 1, MODE, TEMP } controlMenu_t; // ���� �ɼ�
typedef enum _controlOpt_PWR { POWER_ON = 1, POWER_OFF } controlMenu_PWR_t; // ���� �ɼ� �Ŀ���
using namespace std;

class Appliance {
	int type; // ���� ��ǰ ���� { 1:"�ó����", 2:"���", 3:"��Ź��", 4:"����" };
	string machineName; // ���� ��ǰ��(ID����)
	int powerConsumption; // �ð��� ���� �Ҹ�
	bool powerFlag; // ���� ON:TURE, ���� OFF:FALSE
	time_t startHour; // ��ǰ ��� ���۽ð� (����:Sec.)
	time_t useHour; // ���� ��� �ð� (����:Sec.)
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
	void powerOff(); // ��� �ð� ���� �� ���� OFF, SMS Manager call back

	virtual void display() = 0;
	virtual void control() = 0;
};

#endif