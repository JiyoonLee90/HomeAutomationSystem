#ifndef UTIL_H
#define UTIL_H
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Util {
public:
	static int getCommand(vector<string>& vOptions);
	static bool checkInputValidity();
	static bool checkInputValidity(int _target, int _min, int _max);
};
#endif