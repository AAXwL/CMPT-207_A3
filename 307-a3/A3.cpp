#include<iostream>
#include<limits.h>
#include<ctime>
using namespace std;
 
int max(int a, int b) { return (a > b) ? a : b; }
/* Returns the best obtainable price for a rod of length n and
   price[] as prices of different pieces */
int cutRod(int price[], int n)
{
    if (n <= 0)
        return 0;
    int max_val = INT_MIN;

    // Recursively cut the rod in different pieces and compare different  
    // configurations 
    for (int i = 0; i < n; i++)
        max_val = max(max_val, price[i] + cutRod(price, n - i - 1));

    return max_val;
}
int MEMOIZED_CUT_ROD_AUX(int p[], int n, int r[]) {
    if (r[n] >= 0) { return r[n]; }
    int q;
    if (n == 0) { q = 0; }
    else {
        q = INT_MIN;
        for (int i = 0; i < n; i++) { // textbook i starts at 1 
            q = max(q, p[i] + MEMOIZED_CUT_ROD_AUX(p, n - i - 1, r));// so here should n - i- 1;
        }
    }
    r[n] = q;
    return q;
}
int MEMOIZED_CUT_ROD(int p[], int n) {
    int* r = new int[n+1];
    for (int i = 0; i < n + 1; i++) {
        r[i] = INT_MIN;
    }
    return MEMOIZED_CUT_ROD_AUX(p, n, r);
}
int BOTTOM_UP_CUT_ROD(int p[], int n) {
    int* r = new int[n + 1];
    int q;
    r[0] = 0;
    for (int j = 1; j <= n; j++)
    {
        q = INT_MIN;
        for (int i = 0; i < j; i++)
        {
            q = max(q, p[i] + r[j - i - 1]);
        }
        r[j] = q;
    }
    return r[n];
}
/* Driver program to test above functions */
int main()
{   
    int get;
    for (int i = 0; i < 6; i++) {
        if (i == 0) {get = 5;}
        else if (i == 1) {get = 10;}
        else if (i == 2) {get = 15;}
        else if (i == 3) {get = 20;}
        else if (i == 4) {get = 25;}
        else if (i == 5) {get = 30;}
        srand((int)time(NULL));
        int const size = get;
        int* arr = new int[size];
        for (int i = 0; i < size; i++) {
            arr[i] = (rand()%(100+1));
        }
        for (int i = 0; i < size -1 ; i++) {
            for (int j = i + 1; j < size; j++) {
                if (arr[i] > arr[j]) {
                    int temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = arr[i];
                }
            }
        }
        cout << "CASE for size = " << size << endl;
        time_t begin, end;
        float ret;
        begin = clock();
        cout << "CUT-ROD Max benefit is : " << cutRod(arr, size) << endl;
        end = clock();
        ret = double(end - begin) / CLOCKS_PER_SEC;
        cout << "CUT-ROD runtime:   " << ret << endl;
        time_t begin2, end2;
        float ret2;
        begin2 = clock();
        cout << "Memoized-Cut-Rod Max benefit is : " << MEMOIZED_CUT_ROD(arr, size) << endl;
        end2 = clock();
        ret2 = double(end2 - begin2) / CLOCKS_PER_SEC;
        cout << "Memoized-Cut-Rod runtime:   " << ret2 << endl;
        time_t begin3, end3;
        float ret3;
        begin3 = clock();
        cout << "BOTTOM_UP_CUT_ROD Max benefit is : " << BOTTOM_UP_CUT_ROD(arr, size) << endl;
        end2 = clock();
        ret2 = double(end2 - begin2) / CLOCKS_PER_SEC;
        cout << "BOTTOM_UP_CUT_ROD runtime:   " << ret2 << endl << endl;
    }
    return 0;
}