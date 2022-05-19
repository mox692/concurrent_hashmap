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
        // MEMO: head->key == k を条件に入れてるのは、バケットの先頭のkeyが一致している時も
        //       loop内の処理に入れたいため.
        for (List<V> *prev = nullptr; head->next != nullptr || head->key == k; prev = head, head = head->next)
        {
            if (head->key == k)
            {
                // * 同じkeyによる更新処理の場合
                // Hashmapに同じkeyの要素が追加される場合は、そのkeyのvalueを上書きしてしまえば良いが、
                // thread安全に実装しようとすると注意が必要.
                //
                // [prevが存在する時]
                // prev -> head -> next
                // ↓
                // prev -> head -> next
                //   |               ^
                //   V               |
                //   --> new_head -> |
                //
                // [prevが存在しない(先頭のitemのkeyが一致)した時]
                // inner[h] -> head
                // ↓
                // inner[h] -> next
                //   |
                //   V
                //   --> new_head ->
                //
                // どちらも処理の順番としては、
                // 1. new_headの生成
                // 2. new_head->nextをnextに繋ぐ
                // 3. prev -> nextを headからnew_headにCASでつなぎ変える.
                // 4. headの開放

                List<V> *new_list = new List<V>(k, v);
                new_list->next = head->next;
                if (prev != nullptr)
                {
                    // prevが存在する時
                    prev->next = new_list; // TODO: CASで書き換える
                }
                else
                {
                    // prevが存在しない時
                    this->inner[h] = new_list;
                }
                delete head;
                return 0;
            }
        }
        List<V> *new_list = new List<V>(k, v);
        head->next = new_list;
        return 0;
    }
}
