#include <iostream>
#include <cstddef>
#include <cstdint>
#include <cstring>
#define Gb sizeof(int)*2*128*1024*1024


void ReadAllocate(size_t numGb, size_t step){
    int *a = (int*)malloc(numGb*step*sizeof(int));
    size_t i = 0;
    char c;
    volatile int r;
    size_t x = 0;
    while (i < numGb){
        x = i*step;
        while (x < (i + 1)*step){
            r = a[x];
            ++x;
        }
        r = a[i];
        ++i;
        std::cout << "Allocated " << step/(Gb) << " Gb\n";
        system("free");
        std::cout << "Continue? y/n\n";
        std::cin >> c;
        if (c != 'y'){
            break;
        }
    }
    free(a);
}

void WriteAllocate(size_t numGb, size_t step){
    int **a = (int**)malloc(step*sizeof(int*));
    size_t i = 0;
    char c;
    while (i < numGb){
        a[i] = (int*)malloc(step);
        memset((void*)a[i], 1, step);
        ++i;
        std::cout << "Allocated " << step/(Gb) << " Gb\n";
        system("free");
        std::cout << "Continue? y/n\n";
        std::cin >> c;
        if (c != 'y'){
            break;
        }
    }
    for (size_t x = 0; x < numGb; ++x){
        free((void*)a[i]);
    }
    free(a);
}

int main(){
    system("echo 1 | sudo tee /proc/sys/vm/overcommit_memory"); //default value = 0
    WriteAllocate(8, Gb); //8Gb will allocate, 1Gb step
    return 0;
}
