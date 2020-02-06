#ifndef __UTILS_H_
#define __UTILS_H_

template<typename  T >
T power(T a, int b){
    T buf = (T)1;
    for (int i = 0; i < b; i++) {
        buf *= a;
    }
    return buf;
}

#endif // __UTILS_H_
