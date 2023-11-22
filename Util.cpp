#include "Util.h"

/* 옵션 리스트에 대해 유저 입력 반환
   유저 입력 유효성 검사 포함 */
int Util::getCommand(vector<string>& vOptions)
{
	int size = vOptions.size();
	int idx = 1;
	for (auto e : vOptions) {
		cout << idx << ". " << e << endl;
		idx++;
	}

	int cmd;
	bool inputValidity = true;
	do {
		cout << "━━━ [SYSTEM] 위 옵션 중 원하시는 번호를 입력하여 주세요. >> ";
		cin >> cmd;
		inputValidity = Util::checkInputValidity(cmd, 1, size); // error handling
	} while (!inputValidity);
	
	return cmd;
}

/* 유저 입력에 대한 유효성 검사 */
bool Util::checkInputValidity() {
	if (cin.fail() || cin.get() != '\n') {
		cerr << "cin validity error" << endl;
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return false;
	}
	return true;
}

/* 유저 입력에 대한 유효성 검사 (범위 유효성 포함) */
bool Util::checkInputValidity(int _target, int _min, int _max){
	if (cin.fail() || cin.get() != '\n') {
		cerr << "cin validity error" << endl;
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return false;
	}
	if (_target < _min || _target > _max) {
		cerr << "cin validity error" << endl;
		return false;
	}
	
	return true;
}
