#include <iostream>
#include <algorithm>
#include <string>
#include "hilo.h"

using namespace std;

const string string_of_suit[] = {
	"C",
	"D",
	"H",
	"S",
	"JK"
};

const string string_of_number[] = {
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"T",
	"J",
	"Q",
	"K",
	"A"
};

Card::Card() {}

Card::Card(Suit s_, Number n_) {
	s = s_;
	n = n_;
}

bool operator==(const Card c1, const Card c2) {
	if (c1.s == JK && c2.s == JK)
		return true;
	else if (c1.s == c2.s && c1.n == c2.n)
		return true;
	return false;
}

bool operator<(const Card c1, const Card c2) {
	if (c1.s == JK)
		return false;
	if (c2.s == JK || c1.n < c2.n)
		return true;
	return false;
}

string string_of_card(Card c) {
	if (c.s == JK)
		return string_of_suit[c.s];
	else
		return string_of_suit[c.s] + string_of_number[c.n];
}

void sort_hand(Hand h, Hand sh) {
	for (int i = 0; i < 5; ++i)
		sh[i] = h[i];
	sort(sh, sh+5);
}

bool valid_hand(Hand h) {
	Hand sh;
	sort_hand(h, sh);
	if (sh[3].s == JK)
		return false;
	else if (sh[0] == sh[1] || sh[1] == sh[2]
	|| sh[2] == sh[3] || sh[3] == sh[4])
		return false;
	return true;
}

void print_hand(Hand h) {
	for (int i = 0; i < 5; ++i) {
		cout << string_of_card(h[i]) << " ";
	}
	cout << endl;
}

const string string_of_rank[] = {
	"ROYAL FLUSH",
	"STRAIGHT FLUSH",
	"FOUR OF A KIND",
	"FULL HOUSE",
	"FLUSH",
	"STRAIGHT",
	"THREE OF A KIND",	
	"TWO PAIR",
	"JACKS OR BETTER",
	"NO HAND",
	"INVALID"
};

const int odds_of_rank[] = {
	1000,
	500,
	-1, // never happens
	100,
	70,
	50,
	30,
	20,
	10,
	0,
	0
};

Rank rank_of_hand_wojk(Hand h) {
// hand ranking without Joker
	if (!valid_hand(h))
		return INVALID;
	Hand sh;
	sort_hand(h, sh);
	if (sh[0].s == sh[1].s && sh[1].s == sh[2].s
	 && sh[2].s == sh[3].s && sh[3].s == sh[4].s) {
		if (sh[4].n == A) {
			if (sh[0].n == T)
				return ROYAL_FLUSH;
			if (sh[0].n == N2 && sh[3].n == N5)
				return STRAIGHT_FLUSH;
		} if (sh[0].n + 4 == sh[4].n)
			return STRAIGHT_FLUSH;
		return FLUSH;
	} if (sh[0].n == sh[1].n) {
		if (sh[1].n == sh[2].n) {
			if (sh[2].n == sh[3].n)
				return FOUR_OF_A_KIND;
			if (sh[3].n == sh[4].n)
				return FULL_HOUSE;
			return THREE_OF_A_KIND;
		} if (sh[2].n == sh[3].n) {
			if (sh[3].n == sh[4].n)
				return FULL_HOUSE;
			return TWO_PAIR;
		} if (sh[3].n == sh[4].n)
			return TWO_PAIR;
		if (sh[0].n >= J)
			return JACKS_OR_BETTER;
	} else if (sh[1].n == sh[2].n) {
		if (sh[2].n == sh[3].n) {
			if (sh[3].n == sh[4].n)
				return FOUR_OF_A_KIND;
			return THREE_OF_A_KIND;
		} if (sh[3].n == sh[4].n)
			return TWO_PAIR;
		if (sh[1].n >= J)
			return JACKS_OR_BETTER;
	} else if (sh[2].n == sh[3].n) {
		if (sh[3].n == sh[4].n)
			return THREE_OF_A_KIND;
		if (sh[2].n >= J)
			return JACKS_OR_BETTER;
	} else if (sh[3].n == sh[4].n) {
		if (sh[3].n >= J)
			return JACKS_OR_BETTER;
	} else if (sh[0].n + 4 == sh[4].n
	|| (sh[0].n == N2 && sh[3].n == N5 && sh[4].n == A))
		return STRAIGHT;
	return NO_HAND;
}

Rank rank_of_hand(Hand h) {
	Hand sh;
	sort_hand(h, sh);
	if (sh[3].s == JK)
		return INVALID;
	if (sh[4].s == JK) {
		Rank r_min = INVALID;
		for (int i = 0; i < 4; ++i) {
			sh[4].s = Suit(i);
			for (int j = 0; j < 13; ++j) {
				sh[4].n = Number(j);
				Rank r = rank_of_hand_wojk(sh);
				if (r_min > r)
					r_min = r;
			}
		}
		return r_min;
	}
	return rank_of_hand_wojk(h);
}

void rank_test_wojk(void) {
	Hand h;
	int times[INVALID+1] = {};
	
	for (int i = 0; i < 48; ++i) {
		h[0] = Card(Suit(i%4), Number(i%13));
		for (int j = i + 1; j < 49; ++j) {
			h[1] = Card(Suit(j%4), Number(j%13));
			for (int k = j + 1; k < 50; ++k) {
				h[2] = Card(Suit(k%4), Number(k%13));
				for (int l = k + 1; l < 51; ++l) {
					h[3] = Card(Suit(l%4), Number(l%13));
					for (int m = l + 1; m < 52; ++m) {
						h[4] = Card(Suit(m%4), Number(m%13));
						++times[rank_of_hand_wojk(h)];
					}
				}
			}
		}
	}
	
	cout << "TOTAL : " << 2598960 << endl
	<< "--------------------------------" << endl;
	for (int i = 0; i <= INVALID; ++i) {
		cout << string_of_rank[i] << " : " << times[i] << endl;
	}
}

const int init_dist[] = {
	  2,  4,  6,  8, 14, 20, 20, 20, 14,  8,  6,  4,  2
};

const int cpds_of_number_wojk[][13] = {
	{66,  2,  3,  4,  6, 10, 10, 10,  6,  4,  3,  2,  2}, // 2
	{62,  4,  3,  4,  7, 10, 10, 10,  7,  4,  3,  2,  2}, // 3
	{31, 31,  4,  4,  9, 10, 10, 10,  8,  4,  3,  2,  2}, // 4
	{20, 21, 21,  4, 10, 10, 11, 10, 10,  4,  3,  2,  2}, // 5
	{15, 15, 16, 16,  4, 11, 11, 10, 10, 10,  6,  2,  2}, // 6
	{12, 12, 12, 13, 13,  4, 11, 11, 10, 10, 10,  8,  2}, // 7
	{10, 10, 10, 10, 11, 11,  4, 11, 11, 10, 10, 10, 10}, // 8
	{ 2,  8, 10, 10, 10, 11, 11,  4, 13, 13, 12, 12, 12}, // 9
	{ 2,  2,  6, 10, 10, 10, 11, 11,  4, 16, 16, 15, 15}, // T
	{ 2,  2,  3,  4, 10, 10, 11, 10, 10,  4, 21, 21, 20}, // J
	{ 2,  2,  3,  4,  8, 10, 10, 10,  9,  4,  4, 31, 31}, // Q
	{ 2,  2,  3,  4,  7, 10, 10, 10,  7,  4,  3,  4, 62}, // K
	{ 2,  2,  3,  4,  6, 10, 10, 10,  6,  4,  3,  2, 66}  // A
};

const int cpds_of_number[][13] = {
	{66,  2,  3,  4,  6,  9, 10,  9,  6,  4,  3,  2,  2}, // 2
	{60,  6,  3,  4,  6, 10, 10, 10,  6,  4,  3,  2,  2}, // 3
	{29, 31,  6,  4,  7, 10, 10, 10,  8,  4,  3,  2,  2}, // 4
	{18, 21, 21,  6,  8, 10, 11, 10,  9,  5,  3,  2,  2}, // 5
	{13, 15, 16, 16,  6, 11, 11, 10, 10, 10,  4,  2,  2}, // 6
	{10, 12, 12, 13, 13,  6, 11, 11, 10, 10, 10,  6,  2}, // 7
	{ 8, 10, 10, 10, 11, 11,  6, 11, 11, 10, 10, 10,  8}, // 8
	{ 2,  6, 10, 10, 10, 11, 11,  6, 13, 13, 12, 12, 10}, // 9
	{ 2,  2,  4, 10, 10, 10, 11, 11,  6, 16, 16, 15, 13}, // T
	{ 2,  2,  3,  5,  9, 10, 11, 10,  8,  6, 21, 21, 18}, // J
	{ 2,  2,  3,  4,  8, 10, 10, 10,  7,  4,  6, 31, 29}, // Q
	{ 2,  2,  3,  4,  6, 10, 10, 10,  6,  4,  3,  6, 60}, // K
	{ 2,  2,  3,  4,  6,  9, 10,  9,  6,  4,  3,  2, 66}  // A
};

Hilo::Hilo() {}

Hilo::Hilo(double h_, double l_) {
	h = h_;
	l = l_;
	max = h > l ? h : l;
	max = max > 1 ? max : 1;
}

Hilo exppo_wojk_naive_sub(int open, double score, Hand h, int pile[13]) {
// open stands for the number of cards which are currently open. (1 ~ 4)
// score stands for the current score. (win*2^(open-1))
// h stands for the current hand. (h[open-1], ..., h[4] are indefinite)
// pile[j] stands for the number of cards in the remaining pile. (2 ~ 4)
// pile can be calculated by open, score.

	double exp_hi = 0, exp_lo = 0;
	// the expected magnification w.r.t. score
	int i = h[open-1].n;
	// the number written in the rightmost open card

	for (int j = (i + 1) % 13; j != i; j = (j + 1) % 13) {
		// exclude j == i
		for (int k = 0; k < 4; ++k) {
			h[open] = Card(Suit(k), Number(j));
			bool valid = true;
			for (int l = 0; l < open-1; ++l) {
				valid = valid && !(h[l]==h[open]);
			} if (valid) {
				if (open < 4) {
					--pile[j];
					if (j > i) {
						exp_hi +=
						cpds_of_number_wojk[i][j]/64.0/(pile[j]+1)
						*exppo_wojk_naive_sub(open+1, score*2, h, pile).max;
					} else {
						exp_lo +=
						cpds_of_number_wojk[i][j]/64.0/(pile[j]+1)
						*exppo_wojk_naive_sub(open+1, score*2, h, pile).max;
					}
					++pile[j];
				} else {
					if (j > i) {
						exp_hi +=
						(2 + (double)odds_of_rank[rank_of_hand_wojk(h)]/score)
						*cpds_of_number_wojk[i][j]/128/pile[j];
					} else {
						exp_lo +=
						(2 + (double)odds_of_rank[rank_of_hand_wojk(h)]/score)
						*cpds_of_number_wojk[i][j]/128/pile[j];
					}
				}
			}
		}
	}
	
	Hilo result = Hilo(exp_hi, exp_lo);
	return result;
}

Hilo exppo_wojk_naive(double win, Card c) {
	Hand h;
	int pile[13] = {4,4,4,4,4,4,4,4,4,4,4,4,4};

	h[0] = c;
	--pile[c.n];
	return exppo_wojk_naive_sub(1, win, h, pile);
}

Hilo exppo_wojk_sub(int open, double score, Hand h, bool suited) {
// suited iff h[0].s = ... = h[open-1].s.
// it can be also calculated by open, hand.

	double exp_hi = 0, exp_lo = 0;
	int i = h[open-1].n;

	for (int j = (i + 1) % 13; j != i; j = (j + 1) % 13) {
		if (suited) {
			h[open] = Card(h[0].s, Number(j));
			bool valid = true;
			for (int l = 0; l < open-1; ++l) {
				valid = valid && !(h[l].n==h[open].n);
			} if (valid) {
				if (open < 4) {
					if (j > i) {
						exp_hi +=
						cpds_of_number_wojk[i][j]/256.0
						*exppo_wojk_sub(open+1, score*2, h, true).max;
					} else {
						exp_lo +=
						cpds_of_number_wojk[i][j]/256.0
						*exppo_wojk_sub(open+1, score*2, h, true).max;
					}
				} else {
					if (j > i) {
						exp_hi +=
						(2 + (double)odds_of_rank[rank_of_hand_wojk(h)]/score)
						*cpds_of_number_wojk[i][j]/512;
					} else {
						exp_lo +=
						(2 + (double)odds_of_rank[rank_of_hand_wojk(h)]/score)
						*cpds_of_number_wojk[i][j]/512;
					}
				}
			}
			
			h[open] = Card(Suit((h[0].s+1)%4), Number(j));
			int rem = 3;
			for (int l = 0; l < open-1; ++l) {
				rem += (h[l].n==h[open].n);
			} if (open < 4) {
				if (j > i) {
					exp_hi +=
					rem*cpds_of_number_wojk[i][j]/256.0
					*exppo_wojk_sub(open+1, score*2, h, false).max;
				} else {
					exp_lo +=
					rem*cpds_of_number_wojk[i][j]/256.0
					*exppo_wojk_sub(open+1, score*2, h, false).max;
				}
			} else {
				if (j > i) {
					exp_hi +=
					rem*(2 + (double)odds_of_rank[rank_of_hand_wojk(h)]/score)
					*cpds_of_number_wojk[i][j]/512;
				} else {
					exp_lo +=
					rem*(2 + (double)odds_of_rank[rank_of_hand_wojk(h)]/score)
					*cpds_of_number_wojk[i][j]/512;
				}
			}
		} else {
			for (int k = 0; k < 4; ++k) {
				h[open] = Card(Suit(k), Number(j));
				bool valid = true;
				for (int l = 0; l < open-1; ++l) {
					valid = valid && !(h[l]==h[open]);
				} if (valid)
					break;
			} if (open < 4) {
				if (j > i) {
					exp_hi +=
					cpds_of_number_wojk[i][j]/64.0
					*exppo_wojk_sub(open+1, score*2, h, false).max;
				} else {
					exp_lo +=
					cpds_of_number_wojk[i][j]/64.0
					*exppo_wojk_sub(open+1, score*2, h, false).max;
				}
			} else {
				if (j > i) {
					exp_hi +=
					(2 + (double)odds_of_rank[rank_of_hand_wojk(h)]/score)
					*cpds_of_number_wojk[i][j]/128;
				} else {
					exp_lo +=
					(2 + (double)odds_of_rank[rank_of_hand_wojk(h)]/score)
					*cpds_of_number_wojk[i][j]/128;
				}
			}
		}
	}
	
	Hilo result = Hilo(exp_hi, exp_lo);
	return result;
}

Hilo exppo_wojk(double win, Number n) {
	Hand h;

	h[0] = Card(Suit(0), n);
	return exppo_wojk_sub(1, win, h, true);
};

Hilo exppo_sub(int open, double score, Hand h, bool suited) {
	double exp_hi = 0, exp_lo = 0;
	int i = h[open-1].n;

	for (int j = (i + 1) % 13; j != i; j = (j + 1) % 13) {
		if (suited) {
			h[open] = Card(h[0].s, Number(j));
			bool valid = true;
			for (int l = 0; l < open-1; ++l) {
				valid = valid && !(h[l].n==h[open].n);
			} if (valid) {
				if (open < 4) {
					if (j > i) {
						exp_hi +=
						cpds_of_number[i][j]/256.0
						*exppo_sub(open+1, score*2, h, true).max;
					} else {
						exp_lo +=
						cpds_of_number[i][j]/256.0
						*exppo_sub(open+1, score*2, h, true).max;
					}
				} else {
					if (j > i) {
						exp_hi +=
						(2 + (double)odds_of_rank[rank_of_hand_wojk(h)]/score)
						*cpds_of_number[i][j]/512;
					} else {
						exp_lo +=
						(2 + (double)odds_of_rank[rank_of_hand_wojk(h)]/score)
						*cpds_of_number[i][j]/512;
					}
				}
			}
			
			h[open] = Card(Suit((h[0].s+1)%4), Number(j));
			int rem = 3;
			for (int l = 0; l < open-1; ++l) {
				rem += (h[l].n==h[open].n);
			} if (open < 4) {
				if (j > i) {
					exp_hi +=
					rem*cpds_of_number[i][j]/256.0
					*exppo_sub(open+1, score*2, h, false).max;
				} else {
					exp_lo +=
					rem*cpds_of_number[i][j]/256.0
					*exppo_sub(open+1, score*2, h, false).max;
				}
			} else {
				if (j > i) {
					exp_hi +=
					rem*(2 + (double)odds_of_rank[rank_of_hand_wojk(h)]/score)
					*cpds_of_number[i][j]/512;
				} else {
					exp_lo +=
					rem*(2 + (double)odds_of_rank[rank_of_hand_wojk(h)]/score)
					*cpds_of_number[i][j]/512;
				}
			}
		} else {
			for (int k = 0; k < 4; ++k) {
				h[open] = Card(Suit(k), Number(j));
				bool valid = true;
				for (int l = 0; l < open-1; ++l) {
					valid = valid && !(h[l]==h[open]);
				} if (valid)
					break;
			} if (open < 4) {
				if (j > i) {
					exp_hi +=
					cpds_of_number[i][j]/64.0
					*exppo_sub(open+1, score*2, h, false).max;
				} else {
					exp_lo +=
					cpds_of_number[i][j]/64.0
					*exppo_sub(open+1, score*2, h, false).max;
				}
			} else {
				if (j > i) {
					exp_hi +=
					(2 + (double)odds_of_rank[rank_of_hand_wojk(h)]/score)
					*cpds_of_number[i][j]/128;
				} else {
					exp_lo +=
					(2 + (double)odds_of_rank[rank_of_hand_wojk(h)]/score)
					*cpds_of_number[i][j]/128;
				}
			}
		}
	}

	exp_hi += 0.03125;
	exp_lo += 0.03125;
	if (open == 4) {
		h[4] = Card(JK, Number(0));
		double bonus = (double)odds_of_rank[rank_of_hand(h)]/score/64;
		exp_hi += bonus;
		exp_lo += bonus;
	}
	
	Hilo result = Hilo(exp_hi, exp_lo);
	return result;
}

Hilo exppo(double win, Number n) {
	Hand h;

	h[0] = Card(Suit(0), n);
	return exppo_sub(1, win, h, true);
}
