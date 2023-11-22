#ifndef LIGHT_H
#define LIGHT_H
#include "Appliance.h"
#include "AutoRegister.h"

class Light : public Appliance {

public:
	Light(int _type, const string& _machineName, int _powerConsumption, std::shared_ptr<SMSManager> _SMS_Manager);
	static std::shared_ptr<Appliance> creator(int _type, const std::string& _machineName, int _powerConsumption, std::shared_ptr<SMSManager> _SMS_Manager);
	void display() override;
	void control() override;

	static AutoRegister ar;
};
#endif