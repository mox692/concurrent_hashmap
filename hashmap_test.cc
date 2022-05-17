#include <stdio.h>
#include "hashmap.hpp"
#include <cctest/cctest.h>
#include <thread>
#include <chrono>
#include <vector>

using namespace hashmap;

int main()
{
    CC_TEST_START;
    {
        // 基本的なset,getが実現できるか
        HashMap<int> *h = new HashMap<int>;
        std::string s("aaa");
        int aa = 3;
        h->set(s, aa);
        int *res = h->get(s);
        if (aa != *res)
        {
            printf("expect %d, got %d\n", aa, *res);
            return -1;
        }
    }
    {
        // hash値がconflictした時に、適切にlistがextendされるか
        HashMap<int> *h = new HashMap<int>(1); // あえて配列のサイズを1に.
        std::string k1("a");
        std::string k2("b");
        std::string k3("c");
        int v1 = 1;
        int v2 = 2;
        int v3 = 3;
        h->set(k1, v1);
        h->set(k2, v2);
        h->set(k3, v3);

        if (v1 != *h->get(k1))
        {
            printf("expect %d, got %d\n", v1, *h->get(k1));
            return -1;
        }
        if (v2 != *h->get(k2))
        {
            printf("expect %d, got %d\n", v2, *h->get(k2));
            return -1;
        }
        if (v3 != *h->get(k3))
        {
            printf("expect %d, got %d\n", v2, *h->get(k3));
            return -1;
        }
    }
    {
        // 指定したkeyが存在しない時に、nullptrが返るか
        HashMap<int> *h = new HashMap<int>();
        std::string k1("a");
        std::string k2("b");
        int v1 = 1;
        h->set(k1, v1);

        if (h->get(k2) != nullptr)
        {
            printf("expect nullptr, got %p\n", h->get(k2));
            return -1;
        }
    }
    CC_TEST_END;
}
