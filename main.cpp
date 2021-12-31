/**
 * author: polin and fightinggg
 */

#include <iostream>


/**
 *  global config
 */
const double ArrayListIncreaseFactor = 2.0;
const double ArrayListDecreaseFactor = 0.5;
const double HashMapIncreaseFactor = 2.0;
//#define ArrayListPopBackByLazy
//#define debug

/**
 * IO
 */
namespace IO {
    inline int readInt() {
        static int x;
        scanf("%d", &x);
        return x;
    }
}

namespace Log {
    inline void error(char *msg) {
#ifdef debug
        std::cout << msg << std::endl;
#endif
    }
}

/**
 * memory
 */
namespace Memory {
    template<class T>
    inline T *newArray(int size) {
        return new T[size];
    }

    template<class T>
    inline void deleteArray(T *point) {
        delete[] point;
    }
}

namespace Algorithm {
    template<class T>
    void copyArray(T *target, T *from, int size) {
        for (int i = 0; i < size; i++) {
            target[i] = from[i];
        }
    }

    template<class T>
    int abs(T a) { return a > 0 ? a : -a; }
}

namespace TemplateProgramLanguage {
    template<class T>
    struct IsIntsType {
        const static bool value = false;
    };

    template<>
    struct IsIntsType<int> {
        const static bool value = true;
    };

    template<>
    struct IsIntsType<long long> {
        const static bool value = true;
    };
};

namespace DataStruct {

    template<class T>
    class ArrayList {
        T *data; // array values
        int cap;
        int size;

    public:
        ArrayList() {
            data = Memory::newArray<T>(1);
            size = 0;
            cap = 1;
        }

        ~ArrayList() {
            Memory::deleteArray(data);
        }

        ArrayList &operator=(const ArrayList &arrayList) {
            if (this == arrayList) {
                return *this;
            }
            Memory::deleteArray(data);
            data = Memory::newArray<T>(arrayList.size);
            Algorithm::copyArray(data, arrayList.data, arrayList.size);
        }

        T &operator[](const int x) {
#ifdef debug
            if (x < 0 || x >= size) {
                Log::error("array bound");
                exit(-1);
            }
#endif
            return data[x];
        }

        inline void add(const T &value) {
            if (size == cap) {
                cap *= ArrayListIncreaseFactor;
                T *newData = Memory::newArray<T>(cap);
                Algorithm::copyArray(newData, data, size);
                Memory::deleteArray(data);
                data = newData;
            }
            data[size++] = 1;
        }

        inline void push_back(const T &value) { add(value); }

        inline void pop_back() {
#ifdef ArrayListPopBackByLazy
            --size;
#else
            data[--size].~T();
#endif
        }
    };

    struct HashCodeAble {
        template<class T>
        static int hashCode(T t) {
            return t.hashCode();
        }

        template<>
        int hashCode(int t) {
            return t;
        }
    };


    template<class K, class V>
    struct HashMap {
        int size;
        int cap;
        bool *vis;
        K *keys;
        V *values;

        int msk;

        HashMap() {
            size = 0;
            cap = 2;
            msk = 1;
            keys = Memory::newArray<K>(cap);
            values = Memory::newArray<V>(cap);
        }

        ~HashMap() {
            Memory::deleteArray(values);
        }

        void expansionAndRehash() {

        }


        void put(const K &k, const V &v) {
            int hashCode = HashCodeAble::hashCode(k);
            int place = Algorithm::abs(hashCode) & msk;
            while (vis[place]) {
                place = (place + 1) % cap;
            }
            vis[place] = true;
            keys[place] = k;
            values[place] = v;
            expansionAndRehash();
        }

        const V &get(const K &k) {
            int hashCode = HashCodeAble::hashCode(k);
            int place = Algorithm::abs(hashCode) & msk;
            while (vis[place] && keys[place] != k) {
                place = (place + 1) % cap;
            }
            return values[place];
        }

        void erase(const K &k) {
            int hashCode = HashCodeAble::hashCode(k);
            int place = Algorithm::abs(hashCode) & msk;
            while (vis[place] && keys[place] != k) {
                place = (place + 1) % cap;
            }
            vis[place] = false;
            values[place];
        }

        HashMap &operator=(const HashMap &rhs) {
            exit(-1);
        }
    };

    template<class K, class V, class Tree>
    struct TreeMap {
        TreeMap() {}

        ~TreeMap() {

        }
    };

    struct AvlTree {
    };
}

template<class T>
using vector = DataStruct::ArrayList<T>;

template<class K, class V>
using map = DataStruct::TreeMap<K, V, DataStruct::AvlTree>;

template<class K, class V>
using unorder_map = DataStruct::HashMap<K, V>;

using std::cout;
using std::endl;

int main() {
//    vector<int> a;
//    a.push_back(1);
//    cout << a[0] << endl;
//    a.pop_back();


    unorder_map<int, int> mp;
    mp.put(1, 1);
    cout << mp.get(1) << endl;
}


