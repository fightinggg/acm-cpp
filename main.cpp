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
const double HashMapIncreaseThreshold = 0.75;
//#define ArrayListPopBackByLazy
#define debug

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
    inline void error(const char *msg) {
#ifdef debug
        std::cout << msg << std::endl;
#endif
    }

    inline void info(const char *msg) {
#ifdef debug
        std::cout << msg << std::endl;
#endif
    }

}

/**
 * memory
 */
namespace Memory {
    int newCount = 0;
    int deleteCount = 0;

    template<class T>
    inline T *newArrayInit(int size) {
#ifdef debug
        newCount++;
#endif
        T *t = new T[size];
        memset(t, 0, size * sizeof(T));
        return t;
    }

    template<class T>
    inline void deleteArray(T *point) {
#ifdef debug
        deleteCount++;
#endif
        delete[] point;
    }

#ifdef debug

    class Init {
    public:
        Init() {
            Log::info("memory init...");
        }

        ~Init() {
            Log::info((std::string("new ") + std::to_string(newCount) + std::string(" count")).data());
            Log::info((std::string("delete ") + std::to_string(deleteCount) + std::string(" count")).data());
        }
    } init;

#endif
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
            data = Memory::newArrayInit<T>(1);
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
            data = Memory::newArrayInit<T>(arrayList.size);
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
                T *newData = Memory::newArrayInit<T>(cap);
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

#ifdef debug


    class HashMapInit {
    public:
        int hashMapFindCount;
        int hashMapSizeCount;

        HashMapInit() {
            Log::info("HashMap init ...");
        }

        ~HashMapInit() {
            Log::info((std::string("HashMap  = ") + std::to_string(1.0 * hashMapFindCount / hashMapSizeCount)).data());
        }
    } init;

#endif

    template<class K, class V>
    class HashMap {
        int size;
        int cap;
        bool *hasElement;
        K *keys;
        V *values;

        int msk;

        inline static void
        put(bool *hasElement, K *keys, V *values, int cap, int msk, int &size, const K &k, const V &v) {
            int place = Algorithm::abs(HashCodeAble::hashCode(k)) & msk;
            while (hasElement[place] && keys[place] != k) {
                place = (place + 1) % cap;
#ifdef debug
                init.hashMapFindCount++;
#endif
            }
#ifdef debug
            init.hashMapFindCount++;
            init.hashMapSizeCount++;
#endif
            size += hasElement[place] ? 0 : 1;
            hasElement[place] = true;
            keys[place] = k;
            values[place] = v;
        }

    public:

        HashMap() {
            size = 0;
            cap = 2;
            msk = cap - 1;
            hasElement = Memory::newArrayInit<bool>(cap);
            keys = Memory::newArrayInit<K>(cap);
            values = Memory::newArrayInit<V>(cap);
        }

        ~HashMap() {
            Memory::deleteArray(hasElement);
            Memory::deleteArray(keys);
            Memory::deleteArray(values);
        }

        void expansionAndRehash() {
            int newCap = cap * HashMapIncreaseFactor;
            int newMsk = newCap - 1;
            bool *newHasElement = Memory::newArrayInit<bool>(newCap);
            K *newKeys = Memory::newArrayInit<K>(newCap);
            V *newValues = Memory::newArrayInit<V>(newCap);
            for (int i = 0; i < cap; i++) {
                int _;
                put(newHasElement, newKeys, newValues, newCap, newMsk, _, keys[i], values[i]);
            }
            Memory::deleteArray(hasElement);
            Memory::deleteArray(keys);
            Memory::deleteArray(values);
            cap = newCap;
            msk = newMsk;
            hasElement = newHasElement;
            keys = newKeys;
            values = newValues;
        }


        void put(const K &k, const V &v) {
            put(hasElement, keys, values, cap, msk, size, k, v);
            if (size > HashMapIncreaseThreshold * cap) {
                expansionAndRehash();
            }
        }

        const V &get(const K &k) {
            int place = Algorithm::abs(HashCodeAble::hashCode(k)) & msk;
            while (hasElement[place] && keys[place] != k) {
                place = (place + 1) % cap;
            }
            return values[place];
        }

        void erase(const K &k) {
            int hashCode = HashCodeAble::hashCode(k);
            int place = Algorithm::abs(hashCode) & msk;
            while (hasElement[place] && keys[place] != k) {
                place = (place + 1) % cap;
            }
            hasElement[place] = false;
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

    for (int i = 1; i < 100; i++) {
        int x = rand();
        int y = rand();
        mp.put(x, y);
    }

    mp.put(1, 1);
    mp.put(2, 2);
    mp.put(3, 3);
    mp.put(4, 4);
    cout << mp.get(1) << endl;
    mp.put(1, 2);
    cout << mp.get(1) << endl;
    cout << mp.get(2) << endl;
    cout << mp.get(4) << endl;

}


