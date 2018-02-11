#include <iostream>
#include <string>
#include <random>
#include "hilo.h"

using namespace std;

Card atoc(string s) {
	int i, j;
	for (i = 0; i < 4; ++i) {
		if (s[0] == string_of_suit[i][0]) {
			break;
		}
	} for (j = 0; j < 13; ++j) {
		if (s[1] == string_of_number[j][0]) {
			break;
		}
	} if (i < 4 && j < 13) {
		return Card(Suit(i), Number(j));
	}
	return Card(JK, N2);
}

int main(int argc, char *argv[]) {
	bool wojk = true;
	bool exp_assist = true;
	double payout = 1;
	int open = 0;
	Hand h;
	bool suited = true;
	
	// handling options
	for (int i = 1; i < argc; ++i) {
		if (argv[i][0] != '-') {
			cout << "(@@)\n";
			return 0;
		}
		string s = argv[i]+1;
		if (s == "j") {
			wojk = false;
		} else if (s == "n") {
			exp_assist = false;
		} else if (s == "w") {
			if (i == argc-1) {
				cout << "(@@)\n";
				return 0;
			}
			payout = atof(argv[++i]);
		} else if (s == "b") {
			if (i == argc-1) {
				cout << "(@@)\n";
				return 0;
			} for (open = 0; open < 4; ++open) {
				if (i == argc-1) {
					break;
				} if (argv[i+1][0] == '-') {
					break;
				}
				h[open] = atoc(argv[++i]);
				bool invalid = (h[open].s == JK);
				if (open) {
					invalid = invalid || (h[open].n == h[open-1].n);
				} for (int i = 0; i < open-1; ++i) {
					invalid = invalid || (h[open] == h[i]);
				} if (invalid) {
					cout << "(@@)\n";
					return 0;
				} if (h[open].s != h[0].s) {
					suited = false;
				}
			}
		} else {
			cout << "(@@)\n";
			return 0;		
		}
	}

	random_device rnd;
	mt19937 mt(rnd());
	uniform_int_distribution<> rand128(0, 127);
	
	int n = 0;
	int acc = 0;
	int r = rand128(mt);
	if (open == 0) {
		for (int j = 0; j < 13; ++j) {
			acc += init_dist[j];
			if (r >= acc) {
				++n;
			} else
				break;
		} // generating a random number distibuted to init_dist
		h[0] = Card(Suit(rand128(mt)%4), Number(n));
		open = 1;
	}
	
	payout *= 0.5;
	for (int i = 0; i < open; ++i) {
		cout << string_of_card(h[i]) << " ";
		payout *= 2;
	}
	
	int t;
	for (t = open; t < 5; ++t) { // t : turn
		cout << endl;
		if (exp_assist) {
			double hi, lo;
			if (wojk) {
				hi = exppo_wojk_sub(t, payout, h, suited).h;
				lo = exppo_wojk_sub(t, payout, h, suited).l;
			} else {
				hi = exppo_sub(t, payout, h, suited).h;
				lo = exppo_sub(t, payout, h, suited).l;
			}
			cout << "Expected p/o rate : H = " 
			<< hi << ", L = " << lo << endl;
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
			if (wojk) {
				acc += cpds_of_number_wojk[h[t-1].n][j];
			} else {
				acc += cpds_of_number[h[t-1].n][j];
			} if (r >= acc) {
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
				if (t == 4) {
					payout += odds_of_rank[rank_of_hand_wojk(h)];
				} 
			} else {
				payout = 0;
				break;
			}
		}
	} if (payout) {
		if (t == 5) {
			cout << "(" << string_of_rank[rank_of_hand(h)] << ")";
		}
		cout << "\nYOU WIN! (Payout : " << payout << ")\n";
	} else {
		cout << "\nYOU LOSE!\n";
	}
	
	return 0;
}
