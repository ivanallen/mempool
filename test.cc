#include "mempool.h"
#include <stdio.h>


/*
class Foo {
public:
    Foo() {
        printf("Foo()\n");
    }
    ~Foo() {
        printf("~Foo()\n");
    }

    void* operator new(size_t size);
    void operator delete(void* p);
private:
    int a;
};

Mempool<sizeof(Foo)> mp;

void* Foo::operator new(size_t size) {
    return mp.alloc();
}

void Foo::operator delete(void* p) {
    mp.free(p);
}
*/

int main() {
    /*
    Foo *p1 = new Foo;
    printf("%p\n", p1);
    Foo *p2 = new Foo;
    printf("%p\n", p2);
    Foo *p3 = new Foo;
    printf("%p\n", p3);
    Foo *p4 = new Foo;
    printf("%p\n", p4);
    Foo *p5 = new Foo;
    printf("%p\n", p5);
    */

    Mempool<4> m;
    int *p[5] = { 0 };
    for (int i = 0; i < 5; ++i) {
        p[i] = (int*)m.alloc();
        printf("p%d = %p, *p%d = %08x\n", i, p[i], i, *p[i]);
    }

    for (int i = 0; i < 5; ++i) {
        m.free(p[i]);
    }

    puts("----------------------------");

    for (int i = 0; i < 5; ++i) {
        p[i] = (int*)m.alloc();
        printf("p%d = %p, *p%d = %08x\n", i, p[i], i, *p[i]);
    }
    return 0;
}
