#ifndef HOMEAUTOMATIONSYSTEM_H
#define HOMEAUTOMATIONSYSTEM_H
#include <vector>
#include <memory>
#include <fstream>
#include "Menu.h"
#include "AirConditioner.h"
#include "RiceCooker.h"
#include "Washer.h"
#include "Light.h"
#include "SMSManager.h"
#include "Factory.h"
#include "Util.h"

class HomeAutomationSystem
{
	std::shared_ptr<SMSManager> SMS_Manager;
	std::vector<std::shared_ptr<Appliance>> vApp;
	double totalPowerConsumption;

public:
	HomeAutomationSystem();

	void setTotalPowerConsumption(shared_ptr<Appliance> App);
	std::shared_ptr<SMSManager> getSMSManager();
	void displayAppliance();
	void controlAppliance();
	void addAppliance();
	void deleteAppliance();
	void poweroff_all();
	void exitRoutine();
	bool isIn(string _machineName);
};
#endif 
