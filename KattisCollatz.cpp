#include <iostream>
#include <vector>

using namespace std;

vector<int> create_collatz(int num)
{
    vector<int> collatzList;

    collatzList.push_back(num);

    while(num != 1)
    {
        if(num % 2 == 0)
        {
            num = num/2;
        }
        else
        {
            num = (num*3) + 1;
        }

        collatzList.push_back(num);
    }

    return collatzList;
}

int count_collatz(int num, vector<int> list)
{
    for(int i = 0; i<list.size(); ++i)
    {
        if(num == list[i])
            return i;
    }

    return -1;
}

int main()
{
    int num1, num2;

    int step1, step2;

    int i, k;

    vector<int> list1;
    vector<int> list2;

    while(cin >> num1 >> num2 && num1 && num2)
    {

        if(num1 == 0 && num2 == 0)
            exit(0);
        if(num1>1000000 || num2>1000000)
            exit(0);

        list1 = create_collatz(num1);
        list2 = create_collatz(num2);

        for(i = 0; i<list1.size(); ++i)
        {
            k = count_collatz(list1[i], list2);
            if(k != -1)
                break;
        }

        cout << num1 << " needs " << i << " steps, " << num2 << " needs " << k << " steps, they meet at " << list1[i] << '\n';
    }

    return 0;

}