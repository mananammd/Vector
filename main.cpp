#include "MyVector.h"
#include <iostream>

using namespace std;
//template<class T>
int main() {
MyVector<int> test = MyVector<int>(3, 5, ResizeStrategy::Additive, 6);
for (int i = 0; i < test.size(); i++) {
    cout << test[i] << " ";
}
cout << endl;
cout << test.size() << endl;
MyVector<int> test1 = MyVector<int>(2, 1, ResizeStrategy::Additive, 3);
for (int i = 0; i < test1.size(); i++) {
    cout << test1[i] << " ";
}
cout << endl;
cout << test1.size() << endl;
test.insert(1, test1);
for (int i = 0; i < test.size(); i++) {
    cout << test[i] << " ";
}
cout << endl;
test.insert(3, 4);
test.insert(5, 7);
test.insert(2, 3);
for (int i = 0; i < test.size(); i++) {
    cout << test[i] << " ";
}
cout << endl;
test.erase(4, 2);
test.pushFront(9);
for (int i = 0; i < test.size(); i++) {
    cout << test[i] << " ";
}
cout << endl;


}