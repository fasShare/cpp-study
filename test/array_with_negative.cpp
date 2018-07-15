/*************************************************************************
    > File Name: array_with_negative.cpp
    > Author: fas
    > Created Time: 2018年07月15日 星期日 10时52分29秒
 ************************************************************************/

#include <iostream>
#include <assert.h>

// redis 字符串对象分为sdshdr5， sdshdr8，sdshdr16，sdshdr32，sdshdr64
// 最终sdshdrX被分配之后转成char* sds，赋值给redisObject->ptr，但是ptr并不指向sds的首地址，ptr = sds+1
// sds[0]用于存储一个类型类区别sdshdr5， sdshdr8，sdshdr16，sdshdr32，sdshdr64
// 所以通过ptr[-1]便能拿到sds的具体类型，然后在进一步处理。
//
// 下面是对上面的原理行测试

int main(int argc, char** atgv) {
    int *arr = new int[20]();
    int *neg = arr + 1;
    
    assert(neg - 1 == arr);
    assert(&(neg[-1]) == arr);

    std::cout << "arr:" << arr << std::endl;
    std::cout << "neg:" << neg << std::endl;
    std::cout << "&neg[-1]:" << &neg[-1] << std::endl;

    return 0;
}
