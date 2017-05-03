#ifndef HILO_H
#define HILO_H

using namespace std;

enum Suit {
	C, // Club
	D, // Diamond
	H, // Heart
	S, // Spade
	JK // Joker
};

extern const string string_of_suit[];

enum Number {
	N2, // 2
	N3, // 3
	N4, // 4
	N5, // 5
	N6, // 6
	N7, // 7
	N8, // 8
	N9, // 9
	 T, // 10
	 J, // Jack
	 Q, // Queen
	 K, // King
	 A  // Ace
};

extern const string string_of_number[];

class Card {
public:
	Suit s;
	Number n;
public:
	Card();
	Card(Suit s_, Number n_);
};

bool operator==(const Card c1, const Card c2);

bool operator<(const Card c1, const Card c2);

string string_of_card(Card c);

using Hand = Card[5];

void sort_hand(Hand h, Hand sh);

bool valid_hand(Hand h);

void print_hand(Hand h);

enum Rank {
	ROYAL_FLUSH,
	STRAIGHT_FLUSH,
	FOUR_OF_A_KIND, // an imaginary guy
	FULL_HOUSE,
	FLUSH,
	STRAIGHT,
	THREE_OF_A_KIND,
	TWO_PAIR,
	JACKS_OR_BETTER,
	NO_HAND,
	INVALID
};

extern const string string_of_rank[];

extern const int odds_of_rank[];

Rank rank_of_hand_wojk(Hand h);

Rank rank_of_hand(Hand h);

void rank_test_wojk(void);

extern const int init_dist[];

extern const int cpds_of_number_wojk[][13];

extern const int cpds_of_number[][13];

class Hilo {
public:
	double h;
	double l;
	double max;
public:
	Hilo();
	Hilo(double h_, double l_);
};

Hilo exppo_wojk_naive_sub(int open, double score, Hand h, int pile[13]);

Hilo exppo_wojk_naive(double win, Card c);

Hilo exppo_wojk_sub(int open, double score, Hand h, bool suited);

Hilo exppo_wojk(double win, Number n);

Hilo exppo_sub(int open, double score, Hand h, bool suited);

Hilo exppo(double win, Number n);

#endif
