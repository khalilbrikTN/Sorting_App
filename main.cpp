
#include "LL.hpp"
#include <iostream>


int main() {
    // insert code here...
    LinkedList list;
    list.add(5);
    list.add(7);
    list.add(3);
    list.add(9);
    cout<<"Original List"<<endl;
    list.ShowList();
    cout<<"Sorted List "<<endl;
    list.sort();
    list.ShowList();
    
    return 0;
}