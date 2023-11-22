#pragma once
#include <memory>
#include <map>
#include <string>
#include "Appliance.h"
#include "SMSManager.h"

class Factory
{
	using CREATOR = std::shared_ptr<Appliance> (*)(int _type, const std::string& _machineName, int _powerConsumption, std::shared_ptr<SMSManager> _SMS_Manager);
	std::map<int, CREATOR> mCreator;

public:
	void registerCreator(int _type, CREATOR f);
	std::shared_ptr<Appliance> createApp(int _type, const std::string& _machineName, int _powerConsumption, std::shared_ptr<SMSManager> _SMS_Manager);
	static Factory& getFactory();
};

