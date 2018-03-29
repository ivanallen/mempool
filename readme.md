# 一个用于学习的内存池

## 结构

```
memBlockHeader  -> |   next   | ---------->  |   next   |
                .->|  memNode | -> null      |  memNode |  <-  下面这些 memNode 都被申请了
                `--|  memNode | <-.          |  memNode |
                .->|  memNode | --'          |  memNode |
                `--|  memNode | <-.          |  memNode |
                .->|  memNode | --'          |  memNode |
                | 
                |
freeNodeHeader -'  <- 这个链表里的 memNode 都是可以用的
```


```
memNode 

|   next  |
|   data  |
```


## 说明


每次分配的时候，把 freeNodeHeader 返回给用户。即：

```
p = freeNodeHeader;
freeNodeHeader = freeNodeHeader->next;
```

如果 freeNodeHeader 为空，说明 memBlock 不够用了，需要新申请一块 memBlock；申请资源使用头插法。

释放资源也使用头插法：

```
free(p) {
    p->next = freeNodeHeader;
    freeNodeHeader = p;
}
```
