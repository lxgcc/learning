/* 生成0至n-1之间k个不同的随机顺序的随机整数 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <stdexcept>
#include <string.h>
#include <cstdio>

using namespace std;


/* 生成[0, 0x3FFFFFFF]之间的随机整数
 * RAND_MAX = 32767(Ox7FFF)
 */
int bigrand()
{
    int temp = RAND_MAX*rand() + rand() + rand();
    if(temp < 0)
    {
        /*
         * std::cout << "temp is less 0" << endl;
         * exit(1);
         */
        return -temp;
    }
    return temp;
}

int randint(int a, int b)
{
    if(b < a)
        throw domain_error("Argument to randint is out of range!");
    return a + bigrand() % (b - a + 1);
}

/* 生成0-arrSize之间num个不同的随机顺序的随机整数
 * arrSize 数组大小 num 范围
 */
void set_randarray(int arr[], const int arrSize, const int num)
{
    if(arrSize < 1 || num < 0 || num > arrSize)
        throw domain_error("Argument to SetArrAand is out of range!");

    srand((unsigned) time(NULL));
    for(int i=0; i<arrSize; ++i)
        arr[i] = i;

    for(int i=0; i<num; ++i)
    {
        int temp = arr[i];
        int p = randint(i, num-1);
        arr[i] = arr[p];
        arr[p] = temp;
        
        //std::swap(arr[i], arr[randint(i, arrSize-1)]);
    }
    return;
}

int main()
{
    const int N = 1000000;
    const int K = 1000000;

    int a[N] = {0};
    int index = 0;
    set_randarray(a, N, K);
    // outfile
    ofstream ofile;
    ofile.open("myfile1.txt",std::ofstream::out | std::ofstream::binary | std::ofstream::app);
    for(int i=0; i<K; ++i)
        ofile.write(reinterpret_cast<const char*>(&a[i]), sizeof(int));
    ofile.close();

    memset(a, 0, sizeof(a));

    /* 开始时间*/ 
    clock_t start_time = clock();
    ifstream ifile;
    ifile.open("myfile.txt", std::ifstream::in | std::ifstream::binary);
    for(int i=0; i<K; ++i)
    {
        ifile.read(reinterpret_cast<char*>(&a[i]), sizeof(int));
        index++;
    }
    ifile.close();

    clock_t end_time = clock();
    float cost_time = (float)(end_time - start_time)/CLOCKS_PER_SEC;
    std::cout << "the number of int in file is: " << index << endl; 
    std::cout << "the time is: " << setprecision(2) << cost_time << endl;
    std::cout << "the time is: " << cost_time << endl;
    printf("the time is %.2f\n", cost_time);
    return 0;
}




