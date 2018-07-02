# zaschita
#include<stdio.h>
#include<stdlib.h>
#include<float.h>
#define N 10


int cmp_for_char(const void * a, const void * b)
{
        if (*(char*)a >  *(char*)b) return 1;
        if (*(char*)a == *(char*)b) return 0;
        if (*(char*)a <  *(char*)b) return -1;
}

int cmp_for_int(const void * a, const void * b)
{
        if(*(int*)a >  *(int*)b) return 1;
        if(*(int*)a == *(int*)b) return 0;
        if(*(int*)a <  *(int*)b) return -1;
}

int cmp_for_double(const void * a, const void * b)
{
        if(*fabs((double*)a - *(double*)b) <= FLT_EPSILON) return 0;
        if(*(double*)a > *(double*)b) return 1;
        if(*(double*)a < *(double*)b) return -1;
}

void Swap(void *p1, void * p2, int size)
{
        int i = 0;
        for (i = 0; i< size; i++)
        {
                char tmp = *((char *)p1 + i);
                *((char *)p1 + i) = *((char *)p2 + i);
                *((char *)p2 + i) = tmp;
        }
}
void MyQsort(void* base,size_t count,size_t size,int(*comp)(void*,void*))
{
        int i = 0, j = 0;
        for (i; i < count; i++)
        {
                for (j = i + 1; j < count; j++)
                {
                        if (comp((char*)base + i * size, (char*)base + j * size)>0)
                        {
                                 Swap((char*)base + i * size, (char*)base + j * size,size);
                        }
                }
        }
}
    char arr_char[N];     //1
        int arr_int[N];       //2
        double arr_double[N]; //3
        scanf("%d\n", &type);
        switch (type){
                case 1:
                        for(int i=0;i<N;i++)
                                scanf("%c ", &arr_char[i]);
                        MyQsort(arr_char, N, sizeof(char), cmp_for_char);
                        for(int i=0;i<N;i++)
                                printf("%c ", arr_char[i]);
                        break;
                case 2:
                        for(int i=0;i<N;i++)
                                scanf("%d ", &arr_int[i]);
                        MyQsort(arr_int, N, sizeof(int), cmp_for_int);
                        for(int i=0;i<N;i++)
                                printf("%d ", arr_int[i]);
                        break;
                case 3:
                        for(int i=0;i<N;i++)
                                scanf("%lf ", &arr_double[i]);
                        MyQsort(arr_double, N, sizeof(double), cmp_for_double);
                        for(int i=0;i<N;i++)
                                printf("%lf ", arr_double[i]);
                        break;
                default:
                        printf("Error\n");
                        return 0;

        }
}

