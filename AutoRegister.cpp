#include "AutoRegister.h"

AutoRegister::AutoRegister(int _type, std::shared_ptr<Appliance>(*f)(int _type, const std::string& _machineName, int _powerConsumption, std::shared_ptr<SMSManager>_SMS_Manager)) {
	Factory& factory = Factory::getFactory();
	factory.registerCreator(_type, f);
}
