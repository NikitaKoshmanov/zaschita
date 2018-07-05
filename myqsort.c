#include <stdio.h>
#include <stdlib.h> 
#include <float.h> 
#include <math.h>
#include <string.h>
#define N 10

int cmp_for_char(const void * a, const void * b)
{
	if ( *(char*)a >  *(char*)b) return -1;
	if ( *(char*)a == *(char*)b) return 0;
	if ( *(char*)a <  *(char*)b) return 1;
}

int cmp_for_int(const void * a, const void * b)
{
	if ( *(int*)a >  *(int*)b) return -1;
	if ( *(int*)a == *(int*)b) return 0;
	if ( *(int*)a <  *(int*)b) return 1;
}

int cmp_for_double(const void * a, const void * b)
{
	if ( fabs(*(double*)a - *(double*)b) <= FLT_EPSILON) return 0;
	if ( *(double*)a > *(double*)b) return -1;
	if ( *(double*)a <  *(double*)b) return 1;
}

/*int cmp_struct(const void *elem1, const void *elem2)
{
	return (((struct S*)elem1)->age) - (((struct S*)elem2)->age);
}*/

int cmp_for_string(const void * a, const void * b)
{
	return -strcmp(*(char**)a, *(char**)b);
}

void swap(const void* a, const void* b, int size)
{
    char tmp = 0;
    int i = 0;
    while (size > 0) {
        tmp = *( (char*)a + i );
        *( (char*)a + i ) = *( (char*)b + i );
        *( (char*)b + i ) = tmp;
        ++i;
        --size;
    }
}


void myqsort(void *base, int num, int size, int (*cmp)(const void *, const void *))
{
  if(base != NULL && num > 1 && size > 0)
    {
      int i1=num-1, i2=0;
      for(i1=num-1; i1>=i2; i1--)
            if(cmp((char *)base+(num-1)*size, (char *)base+i1*size) < 0)
              {
                while(i2<i1 && cmp((char *)base+(num-1)*size, (char *)base+i2*size)<0)
                  i2++;
                if(i2<i1)
                  swap((char *)base+i1*size, (char *)base+i2*size, size);
                i2++;
              }
      if(i2<num-1)
        swap((char *)base+(num-1)*size, (char *)base+i2*size, size);
      if(i2>1)
        myqsort(base, i2, size, cmp);
      if(i2<num-2)
        myqsort((i2+1)*size+(char *)base, num-i2-1, size, cmp);
    }
}

int main(void){
	int type;
	char arr_char[N];     //1 
	int arr_int[N];       //2 
	double arr_double[N]; //3  
	char** str;           //4
	char str1[][100] = {"whello", "aworld", "dd"};
//        myqsort(str1, 3, sizeof(char*), cmp_for_string);
	scanf("%d\n", &type);
	switch (type){
	 	case 1: for(int i=0;i<N;i++) 
	 				scanf("%c ", &arr_char[i]);
	 			myqsort(arr_char, N, sizeof(char), cmp_for_char);
	 			for(int i=0;i<N;i++)
	 				printf("%c ", arr_char[i]);
	 			break;
	 	case 2: for(int i=0;i<N;i++)
	 				scanf("%d ", &arr_int[i]);
	 			myqsort(arr_int, N, sizeof(int), cmp_for_int);
	 			for(int i=0;i<N;i++)
	 				printf("%d ", arr_int[i]);
	 			break;
	 	case 3: for(int i=0;i<N;i++)
	 				scanf("%lf ", &arr_double[i]);
	 			myqsort(arr_double, N, sizeof(double), cmp_for_double);
	 			for(int i=0;i<N;i++)
	 				printf("%lf ", arr_double[i]);
	 			break;
	 	case 4: str = malloc(N*sizeof(char*));
	 			for(int i=0;i<N;i++){
	 				str[i]=malloc(N*sizeof(char)); 
	 				scanf("%s ", str[i]);
	 			}
	 			myqsort(str, N, sizeof(char*), cmp_for_string);
	 			for(int i=0;i<N;i++)
	 				printf("%s ", str[i]);
	 			for(int i=0;i<N;i++)
	 				free(str[i]);
	 			free(str);
	 			break;
	 	default: printf("Error\n"); 
	}
	return 0;
}
