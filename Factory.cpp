#include "Factory.h"

void Factory::registerCreator(int _type, CREATOR f) { mCreator[_type] = f; }

std::shared_ptr<Appliance> Factory::createApp(int _type, const std::string& _machineName, int _powerConsumption, std::shared_ptr<SMSManager> _SMS_Manager)
{
	CREATOR f = mCreator[_type];
	std::shared_ptr<Appliance> app;
	if (f != nullptr) app = f(_type, _machineName, _powerConsumption, _SMS_Manager);
	
	return app;
}

Factory& Factory::getFactory()
{
	static Factory factory;
	return factory;
}
