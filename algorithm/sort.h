#ifndef __SORT_H__
#define __SORT_H__
#ifdef __cplusplus
extern "C"{
#endif
void bubble_sort ( int array[],int length );
void selection_sort ( int array[], int length );
void insert_sort ( int array[], int length );
void quick_sort ( int array[], int left, int right );
void quick_sort2 ( int *a, int left, int right );
#ifdef __cplusplus
}
#endif

#endif
