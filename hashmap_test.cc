#include <stdio.h>
#include "hashmap.hpp"
#include <cctest/cctest.h>
#include <thread>
#include <chrono>
#include <vector>

using namespace hashmap;

int main()
{
    // TODO: TEST LIBを直す.
    CC_TEST_START;
    {
        HashMap<int> *h = new HashMap<int>;
        std::string s("aaa");
        int aa = 3;
        h->set(s, aa);
        int res = h->get(s);
        if (aa != res)
        {
            printf("expect %d, got %d\n", aa, res);
            return -1;
        }
    }
    CC_TEST_END;
}
