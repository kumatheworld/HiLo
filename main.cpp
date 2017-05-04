#include <iostream>
#include <string.h>
#include "hilo.h"

using namespace std;

string strategy(Hilo k) {
	if (k.max == k.h)
		return "(H)";
	if (k.max == k.l)
		return "(L)";
	return "";
}

void are(void) {
	double win[] = {0.8, 1, 1.6, 2, 2.4, 3};
	
	for (int i = 0; i < 6; ++i) {
		double r = win[i];
		cout << "\nwin = " << r << "\nRank\tw/o JK\t\tw/ JK"
		<< "\n-----------------------------------------------\n";
		Hilo res_wojk, res;
		for (int j = 0; j < 13; ++j) {
			res_wojk = exppo_wojk(r, Number(j));
			res = exppo(r, Number(j));
			cout << string_of_number[j] << "\t"
			<< res_wojk.max << "\t"
			<< strategy(res_wojk) << "\t"
			<< res.max << "\t" << strategy(res) << endl;
		}
	}
}

void table_gen(void) {
}

int main(int argc, char *argv[]) {
	are();	
	return 0;
}
