#include <iostream>

using namespace std;

class MyClass
{
    int a;
    int b;
    string c;

    int sum(int a, int b)
    {
        cout<<"Sum of "<<a<<"and "<<b<<"is ";
        return (a+b);
    }

};

int main()
{

    MyClass mc = new MyClass();
    mc.a = 5;
    mc.b = 8;
    mc.c = "Parth";

    cout<<mc.sum(mc.a, mc.b)<<endl;

    cout<<"My Name is "<<mc.c<<endl;

    return 0;
}