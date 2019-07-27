#include"find.h"


//二分查找前提是数据是有序的
int binary_serach ( int key , int array[], int n )
{
  int low = 0,high = n;
  while ( low <= high )
    {
      int mid = low + ( high -low ) / 2;
      if ( array[mid] > key )
        {
          high = mid -1;
        }
      else if ( array[mid] == key )
        return mid;
      else
        {
          low = mid + 1;
        }
    };
  return -1;
}

int binary_serach2 ( int key, int array[], int left , int right )
{
  if ( left <= right )
    {
      int mid = left + ( right -left ) / 2;
      if ( array[mid] < key )
        {
          return binary_serach2 ( key, array, mid +1 , right );
        }
      else if ( array[mid] == key )
        return mid;
      else
        {
          return binary_serach2 ( key, array, left, mid -1 );
        }
    }
  return -1;
}

