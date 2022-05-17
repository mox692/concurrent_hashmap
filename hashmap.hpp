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
        List(std::string key, V elm) : elm(elm), key(key){};
        std::string key;
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
        V *get(std::string);
        int set(std::string, V);

    private:
        size_t hash_arr_size;
        std::vector<List<V> *> inner;
        size_t hash(std::string s)
        {
            return std::hash<std::string>{}(s) % this->hash_arr_size;
        }
    };

    template <typename V>
    V *HashMap<V>::get(std::string k)
    {
        size_t h = this->hash(k);
        if (this->inner[h] != nullptr)
        {
            List<V> *head = this->inner[h];
            for (List<V> *head = this->inner[h];; head = head->next)
            {
                if (head->key == k)
                {
                    return &head->elm;
                }
                if (head->next == nullptr)
                {
                    return nullptr;
                }
            }
        }
        return nullptr;
    }

    template <typename V>
    int HashMap<V>::set(std::string k, V v)
    {
        size_t h = this->hash(k);

        if (this->inner[h] == nullptr)
        {
            this->inner[h] = new List<V>(k, v);
            return 0;
        }
        List<V> *head = this->inner[h];
        for (; head->next != nullptr; head = head->next)
        {
            if (head->key == k)
            {
                List<V> new_list = List<V>(k, v);
                new_list.next = head->next;
                *head = new_list;
                return 0;
            }
        }
        List<V> *new_list = new List<V>(k, v);
        head->next = new_list;
        return 0;
    }
}
