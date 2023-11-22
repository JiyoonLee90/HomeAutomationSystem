#include "Util.h"

/* �ɼ� ����Ʈ�� ���� ���� �Է� ��ȯ
   ���� �Է� ��ȿ�� �˻� ���� */
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
		cout << "������ [SYSTEM] �� �ɼ� �� ���Ͻô� ��ȣ�� �Է��Ͽ� �ּ���. >> ";
		cin >> cmd;
		inputValidity = Util::checkInputValidity(cmd, 1, size); // error handling
	} while (!inputValidity);
	
	return cmd;
}

/* ���� �Է¿� ���� ��ȿ�� �˻� */
bool Util::checkInputValidity() {
	if (cin.fail() || cin.get() != '\n') {
		cerr << "cin validity error" << endl;
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return false;
	}
	return true;
}

/* ���� �Է¿� ���� ��ȿ�� �˻� (���� ��ȿ�� ����) */
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
