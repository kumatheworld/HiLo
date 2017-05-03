#include <iostream>
#include <random>
#include "hilo.h"

using namespace std;

int main(int argc, char *argv[]) {
	if (argc < 2) {
		cout << "(@@)" << endl;
		return 1;
	}
	random_device rnd;
	mt19937 mt(rnd());
	uniform_int_distribution<> rand128(0, 127);
	Hand h;
	double payout = atof(argv[1]);
	bool exp_assist = true;
	
	int n = 0;
	int acc = 0;
	int r = rand128(mt);
	for (int j = 0; j < 13; ++j) {
		acc += init_dist[j];
		if (r >= acc) {
			++n;
		} else
			break;
	} // generate a random number distibuted to init_dist
	h[0] = Card(Suit(rand128(mt)%4), Number(n));
	cout << string_of_card(h[0]);
	
	int t;
	bool suited = true;
	for (t = 1; t < 5; ++t) { // t : turn
		cout << endl;
		if (exp_assist) {
			cout << "Expected p/o rate : H = "
			<< exppo_sub(t, payout, h, suited).h << ", L = "
			<< exppo_sub(t, payout, h, suited).l << endl;
		}
		string s;
		do {
			cout << "CHOOSE [H/C/L] ";
			cin >> s;
		} while (s != "H" && s != "C" && s!= "L");
		if (s == "C")
			break;
		cout << endl;
		
		n = 0;
		acc = 0;
		r = rand128(mt);
		for (int j = 0; j < 13; ++j) {
			acc += cpds_of_number[h[t-1].n][j];
			if (r >= acc) {
				++n;
			} else
				break;
		} if (n == 13) { // JK
			h[t] = Card(JK, Number(0));
			for (int k = 0; k <= t; k++) {
				cout << string_of_card(h[k]) << " ";
			}
			payout *= 2;
			if (t == 4) {
				payout += odds_of_rank[rank_of_hand(h)];
			} break;
		} else {
			bool used[4] = {false,false,false,false};
			for (int k = 0; k < t; ++k) {
				if (h[k].n == n) {
					used[h[k].s] = true;
				}
			}
			int st;
			do {
				st = rand128(mt)%4;
			} while (used[st]);
			if (st != h[0].s) {
				suited = false;
			}
			h[t] = Card(Suit(st), Number(n));
			for (int k = 0; k <= t; k++) {
				cout << string_of_card(h[k]) << " ";
			} if ((s == "H" && h[t-1].n < n)
			|| (s == "L" && h[t-1].n > n)) {
				payout *= 2;
			} else {
				payout = 0;
				break;
			}
		}
	} if (payout) {
		if (t == 5) {
			cout << "(" << string_of_rank[rank_of_hand(h)] << ")";
		}
		cout << endl << "YOU WIN! (Payout : " << payout << ")" << endl;
	} else {
		cout << endl << "YOU LOSE!" << endl;
	}
	
	return 0;
}
