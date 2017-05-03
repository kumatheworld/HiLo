#include <iostream>
#include "hilo.h"

using namespace std;

int main(int argc, char *argv[]) {

	cout << "Number\tw/o JK\tw/ JK" << endl;
	cout << "-------------------------" << endl;
	Hilo res_wojk, res;
	for (int i = 0; i < 13; ++i) {
		res_wojk = exppo_wojk(1, Number(i));
		res = exppo(1, Number(i));
		cout << string_of_number[i] << "\t"
		<< res_wojk.max << "\t"<< res.max << endl;
	}
	
	return 0;
}
