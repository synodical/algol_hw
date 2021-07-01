#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>

#define MAX 1000000
using namespace std;

double merge_s_time[3];
double quick_s_time[3];
double merge_r_time[3][3];
double quick_r_time[3][3];

void merge_(long long arr[], long long low, long long mid, long long high)
{
    long long * U = new long long[high + 1]; // 합병에 필요한 지역 배열 U
    long long i,j,k;
    for (i = low; i <= high; i++) {
        U[i] = arr[i];
    }
    i = low; j = mid + 1; k = low;
    while (i <= mid && j <= high) {
        if (U[i] <= U[j]) arr[k] = U[i++];
        else arr[k] = U[j++];
        k++;
    }
    if (i > mid)
        while (j <= high) {
            arr[k++] = U[j++];
        }
    else
        while (i <= mid) {
            arr[k++]=U[i++]; // 아싸
        }
    delete[] U;
}

void merge_sort(long long * arr, long long l, long long r) {
    long long m;
    if (l < r) {
        m = (l+r) / 2;
        merge_sort(arr, l, m);
        merge_sort(arr, m+1, r);
        merge_(arr, l, m, r);
    }
}
void _partition(long long * arr, long long l, long long r, int *pivot) {
    long long i, j;
    long long x = arr[l];
    j = l;
    for (i = l + 1; i <= r; i++) {
        if(arr[i] < x) {
            j++;
            long long temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    *pivot = j;
    long long temp = arr[l];
    arr[l] = arr[j];
    arr[j] = temp;
}
void quick_sort(long long arr[], long long l, long long r) {
    int p;
    if(l < r) {
        _partition(arr, l, r, &p);
        quick_sort(arr, l, p - 1);
        quick_sort(arr, p + 1, r);
    }
}

int main() {
    int inputn[3]; // 1번 N 값 저장
    int inputn2[3]; // 2번
    double avg_merge[3];
    double avg_quick[3];
    
    ifstream fin("input.txt");
    for (int i = 0; i < 3; i++) {
        int sortN;
        fin >> sortN;
        inputn[i] = sortN;
        
        long long * m_sort = new long long[sortN + 1];
        long long * q_sort = new long long[sortN + 1];

        for (int j = 0; j < sortN; j++) {
            m_sort[j] = j;
            q_sort[j] = j;
        }

        clock_t startTime = clock();
        merge_sort(m_sort, 0, sortN - 1);
        clock_t endTime = clock();
        clock_t elapsed = endTime - startTime;
        double ms_d_time = (double)(elapsed) / CLOCKS_PER_SEC;
        
        startTime = clock();
        quick_sort(q_sort, 0, sortN - 1);
        endTime = clock();
        elapsed = endTime - startTime;
        double qs_d_time = (double)(elapsed) / CLOCKS_PER_SEC;
        
        delete[] m_sort;
        delete[] q_sort;
        
        merge_s_time[i] = ms_d_time;
        quick_s_time[i] = qs_d_time;
        
    }
    printf("sorted        N=%-8d  N=%-8d\t  N=%-8d\n", inputn[0], inputn[1], inputn[2]);
    printf("Merge Sort    %-8lf\t  %-8lf\t %-8lf\n", merge_s_time[0], merge_s_time[1], merge_s_time[2]);
    printf("Quick Sort    %-8lf\t  %-8lf\t %-8lf\n", quick_s_time[0], quick_s_time[1], quick_s_time[2]);
    printf("\n");
    
    srand((unsigned int)time(NULL)); //
    
    for (int i = 0; i < 3; i++) {
        int randN;
        fin >> randN;
        inputn2[i] = randN;
        long long * m_rand = new long long[randN + 1];
        long long * q_rand = new long long[randN + 1];
        for (int j = 0; j < 3; j++) { // data 실행 횟수
            
            for (int k = 0; k < randN; k++) {
                int a = rand() % RAND_MAX;
                m_rand[k] = q_rand[k] = a;
            }
            clock_t startTime = clock();
            merge_sort(m_rand, 0, randN - 1);
            clock_t endTime = clock();
            clock_t elapsed = endTime - startTime;
            double ms_r_time = (double)(elapsed) / CLOCKS_PER_SEC;
            
            startTime = clock();
            quick_sort(q_rand, 0, randN - 1);
            endTime = clock();
            elapsed = endTime - startTime;
            double qs_r_time = (double)(elapsed) / CLOCKS_PER_SEC;
            
            merge_r_time[i][j] = ms_r_time;
            quick_r_time[i][j] = qs_r_time;
            
            
        }
        delete[] m_rand;
        delete[] q_rand;
        avg_merge[i] = (merge_r_time[i][0] + merge_r_time[i][1] + merge_r_time[i][2]) / 3;
        avg_quick[i] = (quick_r_time[i][0] + quick_r_time[i][1] + quick_r_time[i][2]) / 3;
        
    }
    printf("random                    N=%-8d\t N=%-8d\t  N=%-8d\n", inputn2[0], inputn2[1], inputn2[2]);
    printf("Merge Sort       data1    %-8lf\t %-8lf\t %-8lf\n", merge_r_time[0][0], merge_r_time[1][0], merge_r_time[2][0]);
    printf("                 data2    %-8lf\t %-8lf\t %-8lf\n", merge_r_time[0][1], merge_r_time[1][1], merge_r_time[2][1]);
    printf("                 data3    %-8lf\t %-8lf\t %-8lf\n", merge_r_time[0][2], merge_r_time[1][2], merge_r_time[2][2]);
    printf("               average    %-8lf\t %-8lf\t %-8lf\n", avg_merge[0], avg_merge[1], avg_merge[2]);
    printf("Quick Sort       data1    %-8lf\t %-8lf\t %-8lf\n", quick_r_time[0][0], quick_r_time[1][0], quick_r_time[2][0]);
    printf("                 data2    %-8lf\t %-8lf\t %-8lf\n", quick_r_time[0][1], quick_r_time[1][1], quick_r_time[2][1]);
    printf("                 data3    %-8lf\t %-8lf\t %-8lf\n", quick_r_time[0][2], quick_r_time[1][2], quick_r_time[2][2]);
    printf("               average    %-8lf\t %-8lf\t %-8lf\n", avg_quick[0], avg_quick[1], avg_quick[2]);
    return 0;
}

