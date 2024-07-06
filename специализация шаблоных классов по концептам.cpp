#include <concepts> 
#include <iostream>  
#include <complex> 
#include <vector> 
#include <cmath> 
#include <string> 
using namespace std;

template <typename T>
class MyVector
{
public:
    friend
        std::ostream& operator << (std::ostream& os, MyVector<T>) { os << "myclass"; return os; }
};
template <>
class MyVector<int>
{
public:
    friend
        std::ostream& operator << (std::ostream& os, MyVector<int>) { os << "full int"; return os; }
};


template <std::integral T>
class MyVector<T>
{
public:
    friend
        std::ostream& operator << (std::ostream& os, MyVector<T>)
    {
        os << "INT"; return os;
    }



};
template<std::floating_point T>
class MyVector<T> {

public:
    friend
        std::ostream& operator << (std::ostream& os, MyVector<T>)
    {
        os << "FLOAT"; return os;
    }
    float func(float arg) {
        return arg * 7;
    }

};
template< typename T>
class MyVector<T*> {

public:
    friend
        std::ostream& operator << (std::ostream& os, MyVector<T>)
    {
        os << "FLOAT"; return os;
    }


};


int main()
{
    MyVector<int> v1;
    cout << v1 << endl;

    MyVector<double> v2;
    cout << v2 << endl;
    cout << v2.func(6.0) << endl;
}