# 一个用于学习的内存池

## 结构

```
memBlockHeader -> |   next   | -----> |   next   | ----------> null
                  |  memNode |     .->|  memNode | -> null
                  |  memNode |     `--|  memNode | <-.
                  |  memNode |     .->|  memNode | --'
                  |  memNode |     `--|  memNode | <-.
                  |  memNode |     .->|  memNode | --'
                                 / 
                                |
freeNodeHeader -----------------'
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

释放资源：

```
free(p) {
    p->next = freeNodeHeader;
    freeNodeHeader = p;
}
```
