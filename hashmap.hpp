#include <string>
#include <functional>
#include <vector>

namespace hashmap
{
    static const size_t DEFAULT_HASH_ARR_SIZE = 10000;

    template <typename V>
    class List
    {
    public:
        List(V elm) : elm(elm){};
        V elm;
        List *next;

    private:
    };

    template <typename V>
    class HashMap
    {
    public:
        HashMap() : hash_arr_size(DEFAULT_HASH_ARR_SIZE), inner(DEFAULT_HASH_ARR_SIZE){};
        HashMap(size_t size) : hash_arr_size(size), inner(size){};
        ~HashMap(){};
        V get(std::string);
        int set(std::string, V);

    private:
        size_t hash_arr_size;
        std::vector<V> inner;
        size_t hash(std::string s)
        {
            return std::hash<std::string>{}(s) % this->hash_arr_size;
        }
    };

    template <typename V>
    V HashMap<V>::get(std::string k)
    {
        size_t h = this->hash(k);
        return this->inner[h];
    }

    template <typename V>
    int HashMap<V>::set(std::string k, V v)
    {
        size_t h = this->hash(k);
        this->inner[h] = v;
        return 0;
    }
}
