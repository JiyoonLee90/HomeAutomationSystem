#include "Appliance.h"

Appliance::Appliance(int _type, const string& _machineName, int _powerConsumption, std::shared_ptr<SMSManager> _SMS_Manager)
	: type(_type), machineName(_machineName), powerConsumption(_powerConsumption), SMS_Manager(_SMS_Manager),
	powerFlag(false), startHour(0), useHour(0) {}

/*************************************** getter ***************************************/
int Appliance::getType() { return type; }
string Appliance::getMachineName() { return machineName; }
int Appliance::getPowerConsumption() { return powerConsumption; }
bool Appliance::getPowerFlag() { return powerFlag; }
time_t Appliance::getStartHour() { return startHour; }
time_t Appliance::getUseHour() { return useHour; }
std::shared_ptr<SMSManager> Appliance::getSMSManager() { return SMS_Manager; }
/**************************************************************************************/

/*************************************** setter ***************************************/
void Appliance::setType(const int& _type) { type = _type; }
void Appliance::setMachineName(const std::string& _machineName) { machineName = _machineName; }
void Appliance::setPowerConsumption(const int& _powerConsumption) {	powerConsumption = _powerConsumption; }
void Appliance::setPowerFlag(bool _powerFlag) { powerFlag = _powerFlag; }
void Appliance::setStartHour(const time_t& _startHour) { startHour = _startHour; }
void Appliance::setUseHour(const time_t& _useHour) { useHour = _useHour; }
void Appliance::setSMSManager(std::shared_ptr<SMSManager> _SMS_Manager) { SMS_Manager = _SMS_Manager; }
/**************************************************************************************/

/* set startHour when appliance is turned on */
void Appliance::setStartHour_PWR_ON(){ time(&startHour); }

/* appliance power off Seq.*/
void Appliance::powerOff(){
	time_t endHour;
	time(&endHour);
	useHour += endHour - startHour;

	powerFlag = false;

	/* call back func (SMS Manager) */
	std::string msg = getMachineName() + "À» ²°½À´Ï´Ù.";
	getSMSManager()->send_sms("POWER_OFF", msg);
}
