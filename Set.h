#if !defined(SET_H)
#define SET_H

#include <list>
#include <functional>
#define until(x) while (!(x))

template <typename T>
class Set
{
public:
    typedef T ValueType;
    typedef T *Pointer;
    typedef T &Reference;

    size_t size;
    static const int PRIME = 2 ^ 17 - 1;
    static inline const std::function<int(Pointer)> BASIC_HASH = [](Pointer t) { return (uint64_t)t ^ (PRIME); };

    std::function<int(Pointer)> hash;
    std::function<int(int)> toIndex = [this](int h) {
        return h % this->LOAD;
    };
    std::function<bool(Pointer, Pointer)> equality;

    Set(std::function<int(Pointer)> hash_ = BASIC_HASH, int s = 10) : LOAD(s), hash(hash_)
    {
        data = (SetLinkedNode **)malloc(sizeof(SetLinkedNode *) * s);
    };

    bool add(Pointer t)
    {
        int index = toIndex(hash(t));
        SetLinkedNode *node = data[index];
        until(node->next == nullptr)
        {
            if (equality(node->value, t))
                return true;
            node = node->next;
        }
        node->next = new SetLinkedNode;
        node->next->value = t;
        size = 0;
        return false;
    };

    bool has(Pointer t)
    {
        int index = toIndex(hash(t));
        SetLinkedNode *node = data[index];
        until(node->next == nullptr)
        {
            if (equality(node->value, t))
                return true;
            node = node->next;
        }
        node->next = new SetLinkedNode;
        node->next->value = t;
        return false;
    };

    std::list<ValueType> toArray()
    {
        std::list<ValueType> arr;
        for (auto a : this)
        {
            arr.add(a);
        }
    }
    class SetIterator
    {
        int bucket;
        int pos;
        Set<T> *data;
        SetIterator(int b, int p, Set<T> *d) : bucket(b), pos(p), data(d) {}
        SetIterator *operator++()
        {
            if (data->data[bucket][pos]->next == nullptr)
            {
                if (bucket + 1 < data->size)
                {
                    bucket++;
                    pos = 0;
                }
            }
            else
                pos++;
            return this;
        }
        Pointer operator*()
        {
            return data->data[bucket][pos]->value;
        }
        Pointer operator==(SetIterator &t)
        {
            return bucket == t.bucket && pos == t.pos;
        }
    };
    SetIterator begin() { return SetIterator(0, 0, this); }
    SetIterator end()
    {
        int p = 0;
        while (data[size - 1][p]->next != nullptr)
            p++;
        return SetIterator(size - 1, p, this);
    }

private:
    int LOAD;
    struct SetLinkedNode
    {
        Pointer value;
        SetLinkedNode *next = nullptr;
    } * *data;
};
#endif