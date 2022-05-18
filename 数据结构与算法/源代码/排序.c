#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100000

/* �������� */
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
        printf("��ѡ��һ�����򷽷���\n");
        printf("1.ð������\n");
        printf("2.��������\n");
        printf("0.�˳�\n");
        scanf("%d", &op1);
        printf("��ѡ��һ�����ݷֲ���ʽ��\n");
        printf("1.����\n");
        printf("2.����\n");
        printf("3.����\n");
        scanf("%d", &op2);
        switch(op1)
        {
        case 0:
            exit(0);
        case 1:
            printf("�����������ģ��������Ԫ�ظ�������\n");
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
            printf("�����������ģ��������Ԫ�ظ�������\n");
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
            printf("��������ȷ��ѡ�\n");
            break;
        }
    }
    return 0;
}

/* ������ͬ�ֲ����б� */
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

/* ð������ */
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
        if(!flag) /* ��δ����������˵���Ѿ����� */
            break;
    }
    t2 = clock();
    printf("����ʱ��Ϊ�� %ld\n", t2 - t1);
}

/* �������� */
void QuickSortTime(int List[MAX], int n)
{
    //int i;
    clock_t t1, t2;
    t1 = clock();
    QuickSort(List, 0, n-1);
    t2 = clock();
    printf("����ʱ��Ϊ�� %ld\n", t2 - t1);
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
        k = Partition(List, pivotindex, last, pivot); /* pivot�ҵ���first��first����һ��Ԫ�أ���Ϊ���ߣ���first��pivot��Ԫ�����򣬷ְ��pivot��ʼ�������ش�first��ʼ */
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
        List[r] = List[l]; /* �ְ룬�����first���ǻ�׼Ԫ�ص��±꣬���������б���ռ��λ�ã������Ҳ��СԪ��ռ������λ�ã��������Ľϴ�Ԫ��ռ�ݸ��Ҳ�Ԫ�ص�λ�ã���󽫻�׼Ԫ�ز��뵽�м�λ�ü��� */
    }
    List[l] = pivot;
    return l;
}
