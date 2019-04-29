# Harvard CS50 2017/18x Problem Sets 

[Link to edX](https://www.edx.org/course/introduction-computer-science-harvardx-cs50x#!)

## Problem Set 0: Scratch

Link to play the game that I created : 
```javascript
https://scratch.mit.edu/projects/227860033/
```

## Problem Set 1: C
cash.c : a program to calculate the minimum number of coins someone could receive as change.
```javascript
~/workspace/pset1/ (master) $ ./cash
How much change is owed? 1.49
11
```

mario.c : a program that recreates half-pyramid using hashes (#) for blocks.
```javascript
~/workspace/pset1/ (master) $ ./mario
height: 8
       ##
      ###
     ####
    #####
   ######
  #######
 ########
#########
```
greedy.c : a program to count minimum number of coins needed for a change using greedy algorithm
```javascript
~/workspace/pset1/ (master) $ ./mario
Height: -2
Height: -1
Height: foo
Retry: bar
Retry: 1
##
```

## Problem Set 2: Crypto
caesar.c : a program to caesar cipher a text
```javascript
~/workspace/pset2/ (master) $ ./caesar 13
Be sure to drink your Ovaltine!
Or fher gb qevax lbhe Binygvar!
```

vigenere.c : a program to vigenere cipher a text
```javascript
~/workspace/pset2/ (master) $ ./vigenere bacon
Meet me at the park at eleven am
Negh zf av huf pcfx bt gzrwep oz
```

## Problem Set 3: Music
synthesize.c : creates .wav files from text files
```javascript
~/workspace/pset3/music (master) $ ./synthesize jeopardy.wav < songs/jeopardy.txt
open jeopardy.wav
```

## Problem Set 4: Forensics
whodunit.c : a program that intelligently analyses an image (clue.bmp) and removes details to show whodunit (verdict.bmp)
```javascript
~/workspace/pset4/ (master) $ ./whodunit clue.bmp verdict.bmp
```

resize.c : a program that can enlarge an image to n size
```javascript
~/workspace/pset4/ (master) $ ./resize 4 small.bmp large.bmp
```

recover.c : a program that recovers .jpeg images from card.raw
```javascript
~/workspace/pset4/ (master) $ ./recover
```

## Problem Set 5: Spellchecker
```javascript
~/workspace/pset5/ (master) $ ./speller dictionaries/large endi.txt

MISSPELLED WORDS

nme
veri
persan
yo
bro
USConstitution
http
usconstitution
const
html

WORDS MISSPELLED:     10
WORDS IN DICTIONARY:  143091
WORDS IN TEXT:        722
TIME IN load:         0.10
TIME IN check:        0.00
TIME IN size:         0.00
TIME IN unload:       0.06
TIME IN TOTAL:        0.16
```


## Problem Set 6: Python
Requirements & Dependencies:
```javascript
cd ~/workspace/pset6/sentiments/
pip3 install --user -r requirements.txt
```

Convert some of week 1 & 2 .c programs to .py
```javascript
~/workspace/pset6/ (master) $ python mario.py
Height: 5
    ##
   ###
  ####
 #####
######
```

```javascript
~/workspace/pset6/ (master) $ python cash.py
How much change is owed?
0.41
4
```

```javascript
~/workspace/pset6/ (master) $ python caesar.py 13
HELLO
URYYB
```

```javascript
~/workspace/pset6/ (master) $ python vigenere.py bacon
Meet me at the park at eleven am
Negh zf av huf pcfx bt gzrwep oz
```

Similarities creates a website that compares the similarities between 2 text files.
```
./compare --lines FILE1 FILE2
./compare --sentences FILE1 FILE2
./compare --substrings 1 FILE1 FILE2
./compare --substrings 2 FILE1 FILE2
```

## Problem Set 7: Python & SQL

C$50 Finance
Implement a website via which users can "buy" and "sell" stocks.

Requirements & Dependencies:
```javascript
cd ~/workspace/pset7/finance/
pip3 install --user -r requirements.txt
```
Usage: 
```javascript
~/workspace/pset7/finance/ (master) $ flask run
~/workspace/pset7/finance/ (master) $ phpliteadmin finance.db
```

## Week 12-end: Final Project
http://thepantry.xyz/

