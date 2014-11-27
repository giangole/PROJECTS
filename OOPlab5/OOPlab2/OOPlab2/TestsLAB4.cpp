    
// LAB4 QUESTION 1
// use of : classname (variable, variable) to inherit the values of parent constructors
/*
											#include <iostream>
												using namespace std;
												class A {
													public:
													A(int n ){
														cout << n;
													}
												};
												class B: public A {
													public:
													B(int n, double d)
													: A(n) {
														cout << d;
													}    
												};
												class C: public B {
													public:
													C(int n, double d, char ch)
													: B(n, d) {
														cout <<ch;
													}
												};
												int main()
												{
													C c(5, 4.3, 'R');
													cin.get();
													return 0;
												}
*/
// LAB QUESTION 2
/*
	    #include <iostream>
    using namespace std;
    class Parent     {
        public:
        Parent (void) 
        {     
            cout << "Parent()\n";
        }
        Parent (int i) 
        { 
            cout << "Parent("<< i << ")\n"; 
        };
        ~Parent (void) 
        { 
            cout << "~Parent()\n";
        }; 
    };
    class Child1 : public Parent { };
    class Child2 : public Parent     {
        public:
        Child2 (void) 
        {
            cout << "Child2()\n";
        }
        Child2 (int i) : Parent (i) 
        {
            cout << "Child2(" << i << ")\n"; 
        }
        ~Child2 (void) 
        {
            cout << "~Child2()\n"; 
        }
    };
    int main (void)     {
        Child1 a;
		cout<<"\n";
        Child2 b(0);
		cout<<"\n";
        Child2 c(42);
		cin.get();
        return 0;
    }
	*/