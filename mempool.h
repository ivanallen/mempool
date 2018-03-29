#include <stdio.h>
#define OBJECT_NUM 3 

template<int OBJECT_SIZE>
class Mempool {
    struct MemNode {
        MemNode *next;
        char data[OBJECT_SIZE];
    };
    struct MemBlock {
        MemBlock *next;
        MemNode data[OBJECT_NUM];
    };
public:
    Mempool() : memBlockHeader(nullptr), freeNodeHeader(nullptr) {
    }
    ~Mempool() {
        MemBlock *nextBlock;
        while(memBlockHeader) {
            printf("free block: %p\n", memBlockHeader);
            nextBlock = memBlockHeader->next;
            delete(memBlockHeader);
            memBlockHeader = nextBlock;
        }
    }
    void *alloc() {
        if (freeNodeHeader == nullptr) {
            MemBlock *newBlock = new MemBlock;
            printf("malloc block: %p\n", newBlock);
            newBlock->data[0].next = nullptr;
            for (int i = 1; i < OBJECT_NUM; ++i) {
                newBlock->data[i].next = &newBlock->data[i - 1];
            }
            freeNodeHeader = &newBlock->data[OBJECT_NUM - 1];
            newBlock->next = memBlockHeader;
            memBlockHeader = newBlock;
        }
        void *freeNode = freeNodeHeader; 
        freeNodeHeader = freeNodeHeader->next;
        return freeNode;
    }
    void free(void *p) {
        MemNode *freeNode = (MemNode*)p;
        freeNode->next = freeNodeHeader;
        freeNodeHeader = freeNode;
    }
private:
    MemBlock *memBlockHeader;
    MemNode *freeNodeHeader;
};
