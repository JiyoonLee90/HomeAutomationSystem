#ifndef AIRCONDITIONER_H
#define AIRCONDITIONER_H

#include "Appliance.h"
#include "AutoRegister.h"

typedef enum _stateAirConditioner { SENDAIR = 1, COOLER, HEATER } stateAirConditioner_t; // 에어컨 상태1

class AirConditioner : public Appliance {
	int state1; // 제품 상태 1
	int state2; // 제품 상태 2  
public:
	AirConditioner(int _type, const std::string& _machineName, int _powerConsumption, std::shared_ptr<SMSManager> _SMS_Manager);
	static std::shared_ptr<Appliance> creator(int _type, const std::string& _machineName, int _powerConsumption, std::shared_ptr<SMSManager> _SMS_Manager);
	int getState1();
	int getState2();
	void setState1(int _state1);
	void setState2(int _state2);
	void display() override;
	void control() override;
	
	static AutoRegister ar;
};

#endif 