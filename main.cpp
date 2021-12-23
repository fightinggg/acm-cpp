/**
 * author: polin and fightinggg
 */

#include <iostream>

//#define debug

/**
 *  global config
 */
const double ArrayListIncreaseFactor = 2.0;
const double ArrayListDecreaseFactor = 0.5;


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
}

namespace DataStruct {

    template<class T>
    class ArrayList {
        T *data; // array data
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
    };

    template<class T>
    using vector = ArrayList<T>;



    template<class K, class V>
    struct HashMap {

    };

}


int main() {
    DataStruct::ArrayList<int> a;
    std::cout << a[1] << std::endl;
}


