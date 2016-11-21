// --------------------------
// projects/collatz/Collatz.h
// Copyright (C) 2016
// Glenn P. Downing
// --------------------------

#ifndef Collatz_h
#define Collatz_h

// --------
// includes
// --------

#include <iostream> // istream, ostream
#include <string>   // string
#include <utility>  // pair

using namespace std;

// ------------
// collatz_read
// ------------

/**
 * read two ints from r into i an j
 * @param r an istream
 * @param i an int
 * @param j an int
 * @return true if the read is successful, otherwise false
 */
bool collatz_read (istream& r, int& i, int& j);

// ------------
// collatz_eval
// ------------

/**
 * @param i the beginning of the range, inclusive
 * @param j the end       of the range, inclusive
 * @return the max cycle length of the range [i, j]
 */
int collatz_eval (int i, int j);

// -------------
// collatz_print
// -------------

/**
 * print three ints to w
 * @param w an ostream
 * @param i the beginning of the range, inclusive
 * @param j the end       of the range, inclusive
 * @param v the max cycle length
 */
void collatz_print (ostream& w, int i, int j, int v);

// -------------
// collatz_solve
// -------------

/**
 * @param r an istream
 * @param w an ostream
 */
void collatz_solve (istream& r, ostream& w);

#endif // Collatz_h
// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2016
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream


#define OPTIMIZATION_ON //using feature tag for optimization of cache

using namespace std;

// ------------
// collatz_read
// ------------

bool collatz_read (istream& r, int& i, int& j) {
    if (!(r >> i))
        return false;
    r >> j;
    return true;}

// ------------
// collatz_eval
// ------------

int cache[1000000] = {0}; //use a cache implementation for optimization
int optimized_eval(int i, int j)
{
    bool cacheHit;      //detect hit flags
    int maxCycle = 0;
    int currentNum;
    int tempNum;        //use to test if i>j
    int ct;             //counter for cycles

    if (i > j)          //check if i>j! UVA will usually not trick but public tests
    {
        tempNum = i;
        i = j;
        j = tempNum;
    }
        
    for (i; i <= j; i++) //cycle through the entire range with for loop
    {
        currentNum = i; //use holder
        ct = 1;

        if (cache[i] == 0)  //if there's nothing in that cache slot
        {
            cacheHit = false;
        }

        else
        {
            cacheHit = true;
        }

        if (!cacheHit)      //if nothing in slot, then perform collatz calc
        {
            while (currentNum > 1) //base exit case
            {
                if ((currentNum % 2) == 0) //if even, then divide
                {
                    currentNum = currentNum/2;
                }
                else 
                {
                    currentNum = (currentNum/2) + currentNum + 1; //instead 3n+1 then n/2, shortcut in algorithm and skip to the step after n/2 and add an extra ct++ for compensating the skipped cycle to optimize
                    ct++;
                }

                ct++;
            }

            cache[i] = ct; //put the cycle in that cache slot
            
            if (ct > maxCycle) //check for max 
            {
                maxCycle = ct; //if higher than max, new max
            }
        }

        else 
        {
            if (cache[i] > maxCycle) //if already cached
            {
                maxCycle = cache[i]; //check for higher max
            }

            cacheHit = false; //reset flag to restart for loop
        }

    }

    return maxCycle;
}

int unoptimized_eval(int i, int j)
{
    int maxCycle = 0;
    int currentNum;
    int tempNum;
    int ct;
    
    for (i; i<=j; i++)
    {
        currentNum = i;
        ct = 1;
        
        while(currentNum>1)
        {
            if((currentNum%2) == 0)
            {
                currentNum = currentNum/2;
            }
            else
            {
                currentNum = currentNum*3 + 1;
            }
            ct++;
        }
        
        if (ct>maxCycle)
        {
            maxCycle = ct;
        }
    }
    
    return maxCycle;
}

int collatz_eval (int i, int j) 
{
    #ifdef OPTIMIZATION_ON
       return optimized_eval(i, j);
    #else
       return unoptimized_eval(i,j);
    #endif
}

// -------------
// collatz_print
// -------------

void collatz_print (ostream& w, int i, int j, int v) {
    w << i << " " << j << " " << v << endl;}

// -------------
// collatz_solve
// -------------

void collatz_solve (istream& r, ostream& w) {
    int i;
    int j;
    while (collatz_read(r, i, j)) {
        const int v = collatz_eval(i, j);
        collatz_print(w, i, j, v);}}
// -------------------------------
// projects/collatz/RunCollatz.c++
// Copyright (C) 2016
// Glenn P. Downing
// -------------------------------

// --------
// includes
// --------

#include <iostream> // cin, cout


// ----
// main
// ----

int main () {
    using namespace std;
    collatz_solve(cin, cout);
    return 0;}
