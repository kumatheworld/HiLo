# hilo
High&amp;Low Double Down Simulation and Expected Payout Calculator

## Simulator Usage
We mustn't need any detailed explanations; just note that it is always assumed bet = 1. (and win = 1 if "-win" is omitted)
#### Name
sim - the hilo simulator
#### SYNOPSIS
sim [OPTION]...
#### DESCRIPTION
###### -wojk
run sim without Joker
###### --no-assist
do not display the best strategy
###### -win [num]
begin with win = num;
###### -bw [cards]
begin with designated cards;
see the below examples

#### EXAMPLES
$> sim
<br>
Just run sim with win = 1.

$> sim -bw S3 HT -wojk
<br>
Run sim beginning with 3 of Spades and 10 of Heart
in this order(without Joker).

$> sim --no-assist -win 2.4
<br>
Run sim without displaying the best strategy and begin with win = 2.4.
