

#include "Utils.h"
#include <iostream>
using namespace std;
namespace seneca {

    void read(int& i, int min, int max, const char* error)
    {
        bool valid = false;
        char newline;
        do
        {
            cin >> i;
            newline = cin.get();
            if (cin.fail() || newline != '\n')
            {
                valid = false;
                cin.clear();
                cin.ignore(1000, '\n');
            }
            else
            {
                if (i <= max && i >= min)
                    valid = true;
            }
        } while (!valid && cout << error);
    }
}