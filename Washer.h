#ifndef WASHER_H
#define WASHER_H
#include "Appliance.h"
#include "AutoRegister.h"

typedef enum _stateWasher { NO_OPERATION_WASHER = 1, GENERAL, BOIL, DRY } stateWasher_t; // ��Ź�� ����1

class Washer : public Appliance {
	int state1; // ��ǰ ���� 1

public:
	Washer(int _type, const string& _machineName, int _powerConsumption, std::shared_ptr<SMSManager> _SMS_Manager);
	static std::shared_ptr<Appliance> creator(int _type, const std::string& _machineName, int _powerConsumption, std::shared_ptr<SMSManager> _SMS_Manager);
	int getState1();
	void setState1(int _state1);
	void display() override;
	void control() override;

	static AutoRegister ar;
};

#endif