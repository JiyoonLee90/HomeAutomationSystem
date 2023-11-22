#ifndef RICECOOKER_H
#define RICECOOKER_H
#include "Appliance.h"
#include "AutoRegister.h"

typedef enum _stateRiceCooker { NO_OPERATION = 1, WARM, COOK, HEAT } stateRiceCooker_t; // ╧Д╪э ╩Себ1


class RiceCooker : public Appliance {
	int state1; // а╕г╟ ╩Себ 1

public:
	RiceCooker(int _type, const string& _machineName, int _powerConsumption, std::shared_ptr<SMSManager> _SMS_Manager);
	static std::shared_ptr<Appliance> creator(int _type, const std::string& _machineName, int _powerConsumption, std::shared_ptr<SMSManager> _SMS_Manager);
	int getState1();
	void setState1(int _state1);
	void display() override;
	void control() override;

	static AutoRegister ar;
};
#endif
