# hilo --- High&amp;Low Double Down Simulation and Expected Payout Calculation
Hi there! This is a tiny set of programs that analyzes a poker-like card game **High&amp;Low**. Here we go!

## Brief Description of the Game
The game is a kind of high-low split game preceded by a classic video poker game. (If you are not familiar with these terms, go find a machine in some amusement arcade!) Suppose we have gained a score after playing a video poker round. Now we are ready to play another game **High&amp;Low**, expecting raising our score!<br>
**High&amp;Low** is a sort of double down game. First we are dealt 5 face-down cards and open the leftmost card. We have 3 options here before opening the next card.
* guess **High**
* **Collect** the bonus
* guess **Low**

If we choose **Collect**, we gain the current score and the game is over. If we choose **High**/**Low** on the other hand, we open the next card and we double/lose the current score if the guess is correct/incorrect. For example, suppose the face-up card is a **K** and we guess **Low**. We double our score if the next card is something between **2** and **Q**, and lose our score if it is a **K** or an **A**. The game continues if our guess is correct. At each stage of the game, we are supposed to guess whether the leftmost face-down card is **High**/**Low** compared to the rightmost face-up card, and the game may go on until we reach the 5th (i.e. the rightmost) card. Note that if we encounter the joker, our guess is deemed to be correct whichever we chose, and there the game is over.<br>
The most distinctive aspect of this **High&amp;Low** game compared to a mere high-low split game is that, we can get an extra bonus if we finally predict  **High**/**Low** correctly to each of the 4 stages and the set of 5 open cards there makes some winning hand!

## A little bit of Terminology
We need to know some terminology to play with our program, though it would be tedious...(@@)
#### Expressing a card with 2 letters --- What does "S2" stand for?
We express each of 53 cards (including the joker) with 2 letters. The joker is simply **JK** and an ordinary card is made of a letter representing a suit (**C** **D** **H** **S**, meaning Club, Diamond, Heart, Spade respectively) followed by a letter representing a number (**2**, **3**, **4**, **5**, **6**, **7**, **8**, **9**, **T**, **J**, **Q**, **K**, **A**). For example, **S2**,  **HT**  respectively stand for the 2 of Spades and the 10 of Hearts.

#### bet, win, extra bonus, and payout --- How much can we score?
There are 3 factors that determine the final score (what we call **payout** here), namely **bet**, **win**, and **extra bonus**. As we know, we are supposed to win a video poker game before starting the **High&amp;Low** challenge. **bet**/**win** respectively stand for how much you bet/gained on the preceding poker game.<br>
Suppose we won the High&Low game in the middle, choosing **Collect** or encountering **JK**. Then the ***payout*** is simply<br>
***payout = 2^(i-1) &ast; win***<br>
where **i** is the number of face-up cards.<br>
What if we successfully guess all **High**/**Low**s until the end? Well, we can get an extra score depending on the hand. The precise formula and the table of **extra bonus** are as follows.<br>
***payout = 16 &ast; win + bet &ast; extra_bonus***.

| Hand      | Extra Bonus |
|:---------:|:-----------:|
| ROYAL FLASH       | 1000  |
| STRAIGHT FLASH    | 500   |
| FOUR OF A KIND    | N/A   |
| FULL HOUSE        | 100   |
| FLUSH             | 70    |
| STRAIGHT          | 50    |
| THREE OF A KIND   | 30    |
| TWO PAIR          | 20    |
| JACKS OR BETTER   | 10    |
| NO HAND           | 0     |

Since it is the proportion of **win** to **bet** that really matters, ***we always assume bet = 1***.

## Simulator Usage
#### Build
Compile sim.cpp together with hilo.cpp. (You may need C++11.)
```
$ g++ -o sim sim.cpp hilo.cpp -std=c++11
```
#### Run
Run ./sim in your terminal and you'd start to play an interactive game as if you were right before a video poker machine! All you have to do is input either of "**H**", "**C**", "**L**" (meaning **High**, **Collect**, **Low** respectively) every time. Here is an example.
```
$ ./sim
CT
Expected p/o rate : H = 1.36901, L = 1.15436
CHOOSE [H/C/L] H

CT SQ
Expected p/o rate : H = 1.25534, L = 1.31835
CHOOSE [H/C/L] L

CT SQ S6
Expected p/o rate : H = 1.14551, L = 0.96875
CHOOSE [H/C/L] C

YOU WIN! (Payout : 4)
```
Amazingly, the program calculates the expectation of **payout** for each choice **H** and **L**, which provides the best strategy we should take! (The expectation here assumes we always make the best decisions thereafter.)

#### Options
The simulator equips 4 UNIX command-like options that bring you joy. Have fun!
###### -j
run sim using a deck containing the joker
###### -n
do not display the best strategy
###### -w [num]
begin with win = num
###### -b [cards]
begin with designated cards; see the below examples<by>

(By default, we use a joker-free deck, display the best strategy as we can see above, assume **win** = 1 and begin with nothing.)
##### EXAMPLES
```
$ ./sim -b D3 CQ -j
```
Run the simulator beginning with 3 of Diamonds and Queen of Clubs in this order (you may encounter the joker in the middle).

```
$ ./sim -n -w 2.4
```
Run the simulator without displaying the best strategy and begin with win = 2.4.

## What does main.cpp do then?
You may notice that this repository has another file that wasn't mentioned until now --- namely main.cpp. Of course you can build it (together with hilo.cpp).
```
g++ main.cpp hilo.cpp
```
If you run ./a.out, you'll see some tables generated in the standard output. It displays the best strategies at the first stage with the expected **payout** rate.

## Some Excuses
You'll find incorrect terminology or minor English mistakes since I'm neither an expert in this area nor a native English speaker. I was just asked to analyze the game by my friend who loves such kind of games really badly.
So please, let me know if there are any mistakes! (@@)
