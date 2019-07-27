#include <stdio.h>
#include "sort.h"
//O(n) O(n^2) O(n^2) O(1) 稳定
void bubble_sort ( int array[],int length )
{
    printf ( "%s\n",__FUNCTION__ );
    for ( int i = 0; i < length; i++ ) {
        for ( int j = 0; j < ( length - i - 1 ); j++ ) {
            if ( array[j] > array[j+1] ) {
                int temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }


        for ( int i = 0; i < length; i++ ) {
            printf ( "%d  ",array[i] );
        }
        printf ( "\n" );
    }
}

//O(n^2) O(n^2) O(n^2) O(1) 不稳定
void selection_sort ( int array[], int length )
{
    for ( int i = 0; i <length; i++ ) {
        for ( int j = i + 1; j < length; j++ ) {
            if ( array[j] < array[i] ) {
                int temp = array[j];
                array[j] = array[i];
                array[i] = temp;
            }
        }
        for ( int i = 0; i < length; i++ ) {
            printf ( "%d  ",array[i] );
        }
        printf ( "\n" );
    }
}

//O(n) O(n^2) O(n^2) O(1) 稳定
void insert_sort ( int array[], int length )
{
    for ( int i = 0; i < length; i++ ) {
        for ( int j = i - 1; j >= 0; j-- ) {
            if ( array[j + 1] < array[j] ) {
                int temp = array[j + 1];
                array[j + 1] = array[ j ];
                array[ j] =temp;
            }
        }

        for ( int i = 0; i < length; i++ ) {
            printf ( "%d  ",array[i] );
        }
        printf ( "\n" );

    }
}


void quick_sort ( int array[], int left, int right )
{
    if ( left > right ) {
        return;
    }
    int i = left, j = right;
    int key = array[left]; //key中存的就是基准数
    while ( i != j ) { 
        
        //顺序很重要，要先从右边开始找
        while ( array[j] >= key && i < j ) {
            j--;
        }
        
        //再找左边的
        while ( array[i] <= key && i < j ) { 
            i++;
        }
        
        if ( i < j ) { //交换两个数在数组中的位置
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
    //最终将基准数归位
    array[left] = array[i];
    array[i] = key;


    for ( int i = 0; i < 10; i++ ) {
        printf ( "%d  ",array[i] );
    }
    printf ( "\n" );

    quick_sort ( array, left, i-1 ); //继续处理左边的，这里是一个递归的过程
    quick_sort ( array, i+1, right ); //继续处理右边的 ，这里是一个递归的过程
}



void quick_sort2 ( int *a, int left, int right )
{
    if ( left >= right ) { /*如果左边索引大于或者等于右边的索引就代表已经整理完成一个组了*/
        return ;
    }
    
    int i = left;
    int j = right;
    int key = a[left];

    while ( i < j ) {                          /*控制在当组内寻找一遍*/
        while ( i < j && key <= a[j] )
            /*而寻找结束的条件就是，1，找到一个小于或者大于key的数（大于或小于取决于你想升
            序还是降序）2，没有符合条件1的，并且i与j的大小没有反转*/
        {
            j--;/*向前寻找*/
        }

        a[i] = a[j];
        /*找到一个这样的数后就把它赋给前面的被拿走的i的值（如果第一次循环且key是
        a[left]，那么就是给key）*/

        while ( i < j && key >= a[i] )
            /*这是i在当组内向前寻找，同上，不过注意与key的大小关系停止循环和上面相反，
            因为排序思想是把数往两边扔，所以左右两边的数大小与key的关系相反*/
        {
            i++;
        }

        a[j] = a[i];
    }

    a[i] = key;/*当在当组内找完一遍以后就把中间数key回归*/
    quick_sort2 ( a, left, i - 1 ); /*最后用同样的方式对分出来的左边的小组进行同上的做法*/
    quick_sort2 ( a, i + 1, right ); /*用同样的方式对分出来的右边的小组进行同上的做法*/
    /*当然最后可能会出现很多分左右，直到每一组的i = j 为止*/
}
