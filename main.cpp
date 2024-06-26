#include <iostream>
#include <cstddef>
#include <cstdint>
#include <cstring>

namespace{
    size_t Gb = 1 << 30; //(in bytes)
}; //namespace 

void ReadAllocate(size_t numGb, double stepGb){
    int *a = (int*)malloc(numGb*Gb*4);
    volatile int r;
    size_t step = stepGb*Gb;
    size_t num = numGb*Gb;
    size_t i = 0;
    char c;
    size_t x = 0;
    while (i < num){
        i += step;
        while (x < i){
            r = a[x];
            x += 10000;
        }
        std::cout << "Allocated " << stepGb << " Gb\n";
        system("free");
        std::cout << "Continue? y/n\n";
        std::cin >> c;
        if (c != 'y'){
            break;
        }
    }
    free(a);
}

void WriteAllocate(size_t numGb, double stepGb){
    int **a = (int**)malloc(stepGb*sizeof(int*));
    size_t step = stepGb*Gb;
    size_t i = 0;
    char c;
    while (i < numGb){
        a[i] = (int*)malloc(step);
        memset((void*)a[i], 1, step);
        ++i;
        std::cout << "Allocated " << stepGb << " Gb\n";
        system("free");
        std::cout << "Continue? y/n\n";
        std::cin >> c;
        if (c != 'y'){
            break;
        }
    }
    for (size_t x = 0; x < (size_t)(numGb/stepGb); ++x){
        free((void*)a[i]);
    }
    free(a);
}

int main(){
    system("echo 1 | sudo tee /proc/sys/vm/overcommit_memory"); //default value = 0
    ReadAllocate(8, 1); //8Gb will be allocated, 1Gb step
    return 0;
}
