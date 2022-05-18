#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100000

/* 函数声明 */
void OrderList(int List[MAX], int n);
void AntitoneList(int List[MAX], int n);
void DisorderList(int List[MAX], int n);
void BubbleSort (int List[MAX], int n);
void QuickSortTime(int List[MAX], int n);
void QuickSort(int List[MAX], int first, int last);
int FindPivot(int List[MAX], int first, int last);
int Partition(int List[MAX], int first, int last, int pivot);

int main()
{
    int op1, op2;
    int n;
    int List[MAX];
    while(1)
    {
        printf("请选择一种排序方法：\n");
        printf("1.冒泡排序\n");
        printf("2.快速排序\n");
        printf("0.退出\n");
        scanf("%d", &op1);
        printf("请选择一种数据分布方式：\n");
        printf("1.正序\n");
        printf("2.反序\n");
        printf("3.乱序\n");
        scanf("%d", &op2);
        switch(op1)
        {
        case 0:
            exit(0);
        case 1:
            printf("请输入排序规模（待排序元素个数）：\n");
            scanf("%d", &n);
            switch(op2)
            {
            case 1:
                OrderList(List, n);
                BubbleSort(List, n);
                break;
            case 2:
                AntitoneList(List, n);
                BubbleSort(List, n);
                break;
            case 3:
                DisorderList(List, n);
                BubbleSort(List, n);
                break;
            }
            break;
        case 2:
            printf("请输入排序规模（待排序元素个数）：\n");
            scanf("%d", &n);
            switch(op2)
            {
            case 1:
                OrderList(List, n);
                QuickSortTime(List, n);
                break;
            case 2:
                AntitoneList(List, n);
                QuickSortTime(List, n);
                break;
            case 3:
                DisorderList(List, n);
                QuickSortTime(List, n);
                break;
            }
            break;
        default:
            printf("请输入正确的选项！\n");
            break;
        }
    }
    return 0;
}

/* 建立不同分布的列表 */
void OrderList(int List[MAX], int n)
{
    int i;
    for(i = 0; i < n; i++)
        List[i] = 2 * i + 1;
}

void AntitoneList(int List[MAX], int n)
{
    int i;
    for(i = 0; i < n; i++)
        List[i] = 2 * (n - 1 - i) + 1;
}
void DisorderList(int List[MAX], int n)
{
    int i;
    int index;
    int temp;
    for(i = 0; i < n; i++)
    {
        List[i] = 2 * i + 1;
    }
    srand((unsigned)time(NULL));
    for(i = 0; i < n - 1; i++)
    {
        index = rand() % (n - 1);
        temp = List[index];
        List[index] = List[n - 1];
        List[n - 1] = temp;
    }
}

/* 冒泡排序 */
void BubbleSort (int List[MAX], int n)
{
    int i, j;
    int temp;
    int flag;
    clock_t t1, t2;
    t1 = clock();
    for(i = 0; i < n; i++)
    {
        flag = 0;
        for(j = n - 1; j > i; j--)
        {
        if(List[j] < List[j - 1])
            {
                temp = List[j];
                List[j] = List[j - 1];
                List[j - 1] = temp;
                flag = 1;
            }
        }
        if(!flag) /* 若未发生交换，说明已经有序 */
            break;
    }
    t2 = clock();
    printf("排序时间为： %ld\n", t2 - t1);
}

/* 快速排序 */
void QuickSortTime(int List[MAX], int n)
{
    //int i;
    clock_t t1, t2;
    t1 = clock();
    QuickSort(List, 0, n-1);
    t2 = clock();
    printf("排序时间为： %ld\n", t2 - t1);
}

void QuickSort(int List[MAX], int first, int last)
{
    int pivot;
    int k;
    int pivotindex;
    pivotindex = FindPivot(List, first, last);
    if(pivotindex >= 0)
    {
        pivot = List[pivotindex];
        k = Partition(List, pivotindex, last, pivot); /* pivot找的是first或first的下一个元素，若为后者，则first和pivot两元素有序，分半从pivot开始，而不必从first开始 */
        QuickSort(List, first, k - 1);
        QuickSort(List, k + 1, last);
    }
}

int FindPivot(int List[MAX], int first, int last)
{
    int i;
    for(i = first + 1; i <= last; i++)
    {
        if(List[i] > List[first])
            return i;
        if(List[i] < List[first])
            return first;
    }
    return -1;
}

int Partition(int List[MAX], int first, int last, int pivot)
{
    int l = first, r = last;
    while(l < r)
    {
        while(l < r && List[r] >= pivot)
            r--;
        List[l] = List[r];
        while(l < r && List[l] <= pivot)
            l++;
        List[r] = List[l]; /* 分半，这里的first就是基准元素的下标，它无需在列表中占据位置，先用右侧较小元素占据它的位置，再用左侧的较大元素占据该右侧元素的位置，最后将基准元素插入到中间位置即可 */
    }
    List[l] = pivot;
    return l;
}
