#include "Module7.h"
#include <exception>
#include <iostream>

using namespace std;

int main()
{
    setlocale(LC_ALL, "");

    try
    {
    IntArray array(10);

    for (int i{ 0 }; i < 10; ++i)
        array[i] = i + 1;
        array.resize(8);
        array.insertBefore(20, 11);
        array.remove(3);
        array.insertAtEnd(30);
        array.insertAtBeginning(40);
        for (int i{ 0 }; i < array.getLength(); ++i)
            std :: cout << array[i] << ' ';
        std :: cout << '\n';
    }
    catch (BadLength& e)
    {
        std :: cout << e.what();
    }
    catch (BadRange& e)
    {
        std :: cout << e.what();
    }
    return 0;
}