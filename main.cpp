/**
 * author: polin and fightinggg
 */

#include <iostream>

#define debug

struct fastio {
    static int readInt() {
        int x;
        scanf("%d", &x);
        return x;
    }
};


int main() {
    std::cout << fastio::readInt() << std::endl;
}


