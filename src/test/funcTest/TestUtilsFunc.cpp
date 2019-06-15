#include <iostream>

#include "../../util/Utils.h"
#include <queue>

using namespace std;

struct Stu {
	string name;
	int age;
	
	Stu(string name, int age) {
		this->name = name;
		this->age = age;
	}

	friend bool operator < (Stu& a, Stu& b) {//����trueʱ��˵��a�����ȼ�����b
		//xֵ�ϴ��Node���ȼ��ͣ�xС��Node���ڶ�ǰ��
		return a.age < b.age;
	}
};

struct cmp {
	bool operator()(Stu* a, Stu* b) {
		return a->age > b->age;
	}
};


int main() {

	priority_queue<Stu*, vector<Stu*>, cmp> q;
	q.push(new Stu("Hello", 12));
	q.push(new Stu("Hello", 15));
	q.push(new Stu("ab", 14));

	cout << q.top()->name << "," << q.top()->age << endl;
	q.pop();

	q.push(new Stu("ac", 11));

	while (!q.empty()) {
		cout << q.top()->name << "," << q.top()->age << endl;
		q.pop();
	}

	system("pause");
	return 0;
}