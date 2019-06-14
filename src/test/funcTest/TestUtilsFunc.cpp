#include <iostream>

#include "../../util/Utils.h"

using namespace std;

int main() {

	string s = "THEN EnemyDistance, distance(127.12, 35.33), speed(a, b), hand";

	vector<string> v = Utils::split(s, ",", "(", ")");
	for (string s : v) {
		cout << s << endl;
	}

	system("pause");
	return 0;
}