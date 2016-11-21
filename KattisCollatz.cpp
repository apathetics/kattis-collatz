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
#include <vector>

using namespace std;

int step1 = 0;
int step2 = 0;

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
 * @param i the first number
 * @param j the second number
 * @return the number where they first meet
 */
int collatz_eval (int i, int j);

// -------------
// collatz_print
// -------------

/**
 * print three ints to w
 * @param w an ostream
 * @param i the first number
 * @param j the second number
 * @param v the number where they meet
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

int count_cycles(int i, vector<int>& list)
{
    int currentNum;
    int ct;

        currentNum = i;
        ct = 1;
        
        list.push_back(currentNum);

        while(currentNum>1)
        {
            if((currentNum%2) == 0)
            {
                currentNum = currentNum/2;
                list.push_back(currentNum);
            }
            else
            {
                currentNum = currentNum*3 + 1;
                list.push_back(currentNum);
            }
            ct++;
        }
    
    return ct;
}

int collatz_eval (int i, int j) 
{
    vector<int> list1; //initialize list
    vector<int> list2;

    int count1 = count_cycles(i, list1); //inserts into list
    int count2 = count_cycles(j, list2);

    vector<int> smallerV;
    vector<int> biggerV;

    // cout << "Print out of List 1:" << endl;
    // for(int k = 0; k<list1.size(); ++k)
    // {
    //     cout << "Input at " << k << " is: " << list1[k] << endl;
    // }

    // cout << "Print out of List 2:" << endl;
    // for(int k = 0; k<list2.size(); ++k)
    // {
    //     cout << "Input at " << k << " is: " << list2[k] << endl;
    // }

    if(list1.size()<list2.size())
    {
        vector<int> smallerV = list1;
        vector<int> biggerV = list2;

        for(int it = 0; it < smallerV.size(); ++it)
        {
            for(int itt = 0; itt < biggerV.size(); ++itt)
            {
                if(smallerV[it] == biggerV[itt])
                {
                    if(smallerV[0] == list1[0])
                    {
                        step1 = itt;
                        step2 = it;
                    }
                    else
                    {
                        step1 = it;
                        step2 = itt;
                    }
                    return smallerV[it];
                }
            }
        }
    }
    else
    {
        vector<int> smallerV = list2;
        vector<int> biggerV = list1;

        for(int it = 0; it < smallerV.size(); ++it)
        {
            for(int itt = 0; itt <biggerV.size(); ++itt)
            {
                if(smallerV[it] == biggerV[itt])
                {
                    if(smallerV[0] == list1[0])
                    {
                        step1 = itt;
                        step2 = it;
                    }
                    else
                    {
                        step1 = it;
                        step2 = itt;
                    }

                    return smallerV[it];
                }
            }
        }
    }


    return 0;
}

// -------------
// collatz_print
// -------------

void collatz_print (ostream& w, int i, int j, int v) {
    if(i == 0 && j == 0)
        return;

    w << i << " needs " << step2 << " steps, " << j << " needs " << step1 << " steps, they meet at " << v << endl;}

// -------------
// collatz_solve
// -------------

void collatz_solve (istream& r, ostream& w) {
    int i;
    int j;
    while (collatz_read(r, i, j)) 
    {
        const int v = collatz_eval(i, j);
        collatz_print(w, i, j, v);
    }
    }
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
    return 0;
}
