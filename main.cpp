#include <iostream>
#include <cstddef>
#include <cstdint>
#include <cstring>
#define Gb sizeof(int)*2*128*1024*1024

void Write(){

}

void Read(){

}

void Allocate(size_t numGb, size_t step){
    int **a = new int*[numGb];
    size_t i = 0;
    char c;
    while (i < numGb){
        a[i] = static_cast<int*>(malloc(step));
        //Write();
        //Read();
        memset((void*)a[i], 1, step);
        ++i;
        std::cout << "Allocated " << (int)step/Gb << " Gb\n";
        system("free");
        std::cout << "Continue? y/n\n";
        std::cin >> c;
        if (c != 'y'){
            break;
        }
    }
    for (size_t x = 0; x < numGb; ++x){
        free(a[i]);
    }
    delete[] a;
}

int main(){
    // Read();
    // Write();
    Allocate(8, Gb); //8Gb will allocate, 1Gb step
    return 0;
}
