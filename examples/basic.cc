#include <stdio.h>
#include <iostream>
#include <hashmap/hashmap.hpp>

using namespace hashmap;
int main()
{
    HashMap<int> *h = new HashMap<int>;
    std::string str("str");
    h->set(str, 42);
    std::cout << h->get(str) << std::endl;
}
