/**
 * author: polin and fightinggg
 */

#include <iostream>
#include <cstring>
#include <queue>

/**
 *  global config
 */
//#define ArrayListPopBackByLazy
//#define debug
#define MultiSimple
#define ArrayListIncreaseFactor 2.0
#define ArrayListDecreaseFactor 0.5
#define HashMapIncreaseFactor 2.0
#define HashMapIncreaseThreshold 0.75
#define MemoryPageByteSize ( 4<<10 /* 4kb */ )

namespace IO {
    inline int readInt() {
        static int x;
        scanf("%d", &x);
        return x;
    }

    inline void print(char ch) {
        putchar(ch);
    }

    inline void print(int x) {
        if (x < 0) {
            print('-');
            x = -x;
        }
        static char buf[20];
        static int tot;
        tot = 0;
        do {
            buf[tot++] = (x % 10) + '0';
            x /= 10;
        } while (x);
        for (int i = tot - 1; i >= 0; i--) {
            print(buf[i]);
        }
    }

    inline void print(const char *x) {
        while (*x != 0) {
            print(*(x++));
        }
    }

    class Init {
    public:
        Init() {
            std::ios::sync_with_stdio(false);
            std::cin.tie(nullptr);
            std::cout.tie(nullptr);
        }
    } _;/* NOLINT */
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

namespace Memory {
    namespace CppMemory {
        inline void *getMemory(int size) {

        }

        inline void *deleteMemory(void *ptr) {

        }
    }

    namespace PageMemory {
        inline void *getMemory(int size) {

        }
    }

    namespace BitMapMemoryPool {
        template<int PoolSize>
        struct MemoryPool {
            void *memory;
            void *memoryBitMap;
        };

        template<int size>
        inline void *getMemory() {
        }
    }

    namespace StackMemoryPool {
        template<int MemoryUnitSize, int BucketSize>
        inline void *getMemory() {
            static void ***poolBucket = nullptr;
            static int poolBucketCap = 0;
            static int poolBucketSize = 0;

            static int *stack = nullptr;
            static int stackCap = 0;
            static int stackSize = 0;

            if (stackSize == 0) {



            } else {
                stackSize--;
                int index = stack[stackSize];
                return index < BucketSize ? poolBucket[0][index] : poolBucket[index / BucketSize][index % BucketSize];
            }

        }
    }


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
    T abs(const T &a) { return a > 0 ? a : -a; }

    template<class T>
    T max(const T &a, const T &b) { return a > b ? a : b; }

    template<class T>
    T min(const T &a, const T &b) { return a < b ? a : b; }

    inline int findTheFirstMatch(int l, int r, bool(*check)(int i)) {
        while (l < r) {
            int mid = (l + r) / 2;
            if (check(mid)) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        return l;
    }

    inline int findTheLastMatch(int l, int r, bool(*check)(int i)) {
        while (l < r) {
            int mid = (l + r + 1) / 2;
            if (check(mid)) {
                l = mid;
            } else {
                r = mid - 1;
            }
        }
        return l;
    }
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

        ArrayList(int size) {
            data = Memory::newArrayInit<T>(size);
            this->size = size;
            this->cap = size;
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

        static int hashCode(int t) {
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

    class Graph {
    protected:
        int *head;
        int *to, *nex, *ew;
        int tot;

        int edgeSize, vertexSize;
    public:
        /**
         * @param edgeSize 单向边的个数
         * @param vertexSize 点的个数 vertex: [0,vertexSize-1)
         */
        Graph(int edgeSize, int vertexSize) {
            this->edgeSize = edgeSize;
            this->vertexSize = vertexSize;
            head = Memory::newArrayInit<int>(vertexSize);
            to = Memory::newArrayInit<int>(edgeSize);
            nex = Memory::newArrayInit<int>(edgeSize);
            ew = Memory::newArrayInit<int>(edgeSize);
            tot = 1;
        }

        ~Graph() {
        }

        void addSimpleEdge(int u, int v, int w) { to[++tot] = v, nex[tot] = head[u], ew[tot] = w, head[u] = tot; }
    };


    // 最大流最小割算法
    class MaxFlow : Graph {
        int *lv, *current, src, dst;
        int *cap;//容量等于边权

        bool maxflowbfs() {
            using std::queue;
            queue<int> q;
            lv[src] = 0, q.push(src);
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (int i = head[u]; i; i = nex[i]) {
                    if (cap[i] == 0 || lv[to[i]] >= 0)continue;
                    lv[to[i]] = lv[u] + 1, q.push(to[i]);
                }
            }
            return lv[dst] >= 0;
        }

        int maxflowdfs(int u, int f) {
            if (u == dst)return f;
            for (int &i = current[u]; i; i = nex[i]) {//当前弧优化
                if (cap[i] == 0 || lv[u] >= lv[to[i]])continue;
                int flow = maxflowdfs(to[i], Algorithm::min(f, cap[i]));
                if (flow == 0) continue;
                cap[i] -= flow, cap[i ^ 1] += flow;
                return flow;
            }
            return 0;
        }


    public:
        MaxFlow(int edgeSize, int vertexSize) : Graph(edgeSize, vertexSize) {
            lv = Memory::newArrayInit<int>(vertexSize);
            current = Memory::newArrayInit<int>(vertexSize);
            cap = Memory::newArrayInit<int>(edgeSize);
            src = -1;
            dst = -1;
        }

        void addDoubleEdge(int u, int v, int w) {
            addSimpleEdge(u, v, w);
            addSimpleEdge(v, u, 0);
        }

        long long maxflow(int n, int s, int t) {
            src = s, dst = t;
            long long flow = 0, f = 0;// 计算最大流的过程中不可能爆int 唯独在最后对流量求和对时候可能会比较大 所以只有这里用ll
            Algorithm::copyArray(cap, ew, this->edgeSize);
            while (true) {
                for (int i = 1; i <= n; ++i) current[i] = head[i], lv[i] = -1;
                if (!maxflowbfs())return flow;
                while (f = maxflowdfs(src, 2e9))
                    flow += f;
            }
        }
    };
}

namespace stdadapt {
    template<class T>
    using vector = DataStruct::ArrayList<T>;

    template<class K, class V>
    using map = DataStruct::TreeMap<K, V, DataStruct::AvlTree>;

    template<class K, class V>
    using unorder_map = DataStruct::HashMap<K, V>;

    using std::cout;
    using std::endl;

}

using namespace stdadapt;


// inline 可以对多样例有明显加速
inline void solve(int turn) {
    DataStruct::MaxFlow mf(1e5, 2e5);
    int n = IO::readInt();
    int size = 1;
    int s = size++;
    int t = size++;

    unorder_map<int, int> numbers;
    for (int i = 1; i <= n; i++) {
        numbers.put(i, size++);
        mf.addDoubleEdge(s, numbers.get(i), 1);
    }
    for (int i = 0; i < n; i++) {
        int x = IO::readInt();
        int out = size++;
        mf.addDoubleEdge(out, t, 1);

        while (x) {
            int node = size++;
            mf.addDoubleEdge(numbers.get(x), node, 1);
            mf.addDoubleEdge(node, out, 1);
            x /= 2;
        }
    }

    long long w = mf.maxflow(size, s, t);
    if (w == n) {
        IO::print("YES\n");
    } else {
        IO::print("NO\n");
    }


}

int main() {
#ifdef MultiSimple
    int n = IO::readInt();
    for (int i = 1; i <= n; i++) {
        solve(i);
    }
#else
    solve(1);
#endif
}
