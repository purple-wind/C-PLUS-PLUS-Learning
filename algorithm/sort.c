#include <stdio.h>
#include "sort.h"
//排序稳定性是指:待排序数据中有相同的数时，排序之后相同的数的位置与排序前的位置关系不变
//



////////////////////////////////////////////////////////////////////
//交换排序
////////////////////////////////////////////////////////////////////

//1.冒泡
//O(n) O(n^2) O(n^2) 稳定 O(1)
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

//2.快速排序
//基本思想:找到一个基数,通过一趟排序将记录分割成独立的两部分，其中一部分记录比基数小,另一部分比基数大。
//然后分别对两部分进行此操作,直到基数左右两边的序列个数为1停止
//O(nlogn) O(nlogn) O(n^2) 不稳定
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


//O(nlogn) O(nlogn) O(n^2) 不稳定
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
    /*当然最后可能会出现很多份左右，直到每一组的i = j 为止*/
}


////////////////////////////////////////////////////////////////////
//选择排序
////////////////////////////////////////////////////////////////////

//1.普通选择排序
//O(n^2) O(n^2) O(n^2) 不稳定
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

//2.堆排序
//基本思想:初始时把要排序的n个数的序列看作是一棵顺序存储的二叉树（一维数组存储二叉树），调整它们的存储序，使之成为一个堆。
//将堆顶元素输出，得到n个元素中最小(或最大)的元素，这时堆的根节点的数最小（或者最大）。然后对前面(n-1)个元素重新调整使之成为堆，
//输出堆顶元素，得到n个元素中次小(或次大)的元素。依此类推，直到只有两个节点的堆，并对它们作交换，最后得到有n个节点的有序序列。
//称这个过程为堆排序
//O(nlogn) O(nlogn) O(nlogn) 不稳定




////////////////////////////////////////////////////////////////////
//插入排序
////////////////////////////////////////////////////////////////////

//1.普通插入排序
//基本思想:把一个记录插入到已经排序好的有序序列中，从而得到一个新的有序序列
//如果在插入过程中在已排序好的序列中遇到一个和待插入元素相同的元素,则待插入元素会放在相同元素后面,所以插入排序是稳定的
//O(n) O(n^2) O(n^2) 稳定
void insert_sort ( int array[], int length )
{
    for ( int i = 0; i < length; i++ ) {
        printf("step %d-->", i);
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

//2.希尔排序
//基本思想:把整个序列分成n组，分别对这n组中的数据进行插入排序，然后再把整个序列分成n-1组，再对这n-1组分别进行插入排序
//依次循环，直到0组即结束
//O(n) O(nlogn) O(n^2) 不稳定
void shell_sort()
{

}

////////////////////////////////////////////////////////////////////
//归并排序
////////////////////////////////////////////////////////////////////
void merge_sort()
{

}

////////////////////////////////////////////////////////////////////
//基数排序
////////////////////////////////////////////////////////////////////
void radix_sort()
{

}


