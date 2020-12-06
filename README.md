# Operating Systems: Assignment 7
Michael Kulinich
kulinich@chapman.edu

Ayden Best
bbest@chapman.edu

CPSC 380-01



### Compile and Deployment

**Linux**
Run Makefile with 'make'

OR


THEN

run ./vmmpr [PAGE REFERENCES(1,2,3...,n; n<41]


```
// create the object file
gcc main.c -o vmmpr

// run
./vmmpr [PAGE REFERENCES(1,2,3...,n; n<41]
```
Argument 2 is a list of page references. If excluded, program will generate an unseeded random set of page references


### Sample output
```
./vmmpr 1,2,1,3,1,4,1,5,1,2,1,3,1,4,5,6,1,7,8,9,1
1 2 1 3 1 4 1 5 1 2 1 3 1 4 5 6 1 7 8 9 1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1
15 Faults detected with FIFO
13 Faults detected with LRU
12 Faults detected with Optimal
```
