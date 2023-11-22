#pragma once
#include <memory>
#include "Appliance.h"
#include "Factory.h"


class AutoRegister {
public:
	AutoRegister(int _type, std::shared_ptr<Appliance>(*f)(int _type, const std::string& _machineName, int _powerConsumption, std::shared_ptr<SMSManager> _SMS_Manager));
};

