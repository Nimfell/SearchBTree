#include <stdio.h>
//========================================================== 
int index = 0; 
int* new_a;
#define empty -1

static int two_to_the_degree(int D) 
{  if (D == 0) return 1;
   else        return (2 * two_to_the_degree(D-1));  }
   
int count_max_level(int D) 
{  
   int count = 1;
   if (D == 1)          
      return 0;
   else        
      count += (count_max_level(D/2) );
      return count;  
}
//---------bubbleSort----------
void Swap(int* A,int* B) 
{ int t = *A; *A = *B; *B = t; }

void bubbleSort(int a[], int n)
{     
   do {
      int nn = 0;
      for (int j = 1; j < n; ++j)
      if (a[j-1] > a[j]) {
         Swap(a+j-1, a+j);
         nn = j; }
      n = nn; }
   while (n);
}
//------------------------------
void sortArray (int* begin, int* end, int index, int size, int common_size)
{      
   int L_Index = 2 * index + 1;  // lift  child index
   int R_Index = 2 * index + 2;  // right child index

   if (begin == end) {           // if child is leaf
      new_a[index] = begin[0];
      if (L_Index < common_size)
         new_a[L_Index] = empty;
      if (R_Index < common_size)
         new_a[R_Index] = empty;
      return; }
   else
      new_a[index] = begin[size/2];

   sortArray (begin, begin+ size/2 - 1, L_Index, size/2, common_size);
   if (begin + size/2 == end) {    // if there no child in the right
      if (R_Index < common_size)
         new_a[R_Index] = empty;   // right child is empty
      return; }
   sortArray (begin + size/2 + 1, end, R_Index, size/2,common_size); 
   return ;
}

int* GenerateBBSTArray(int a[], int size) 
{  		
   int depth = count_max_level(size);
   int new_a_size = (two_to_the_degree(depth + 1) - 1);      
   new_a = new int[new_a_size]; //create new array with correct size

   bubbleSort (a + 0, size); // sort from min to max
   sortArray(a, (a + size - 1), 0, size, new_a_size); // begin , end , size
   return new_a;
}
//======================================================================

void test()
{
   int a[10] = {6,7,3,4,5,2,1,0,9,8};
   int* b = GenerateBBSTArray(a, 10);

   int c[10] = {6,3,4,5,2,1,0};
   b = GenerateBBSTArray(a, 7);

   int d[10] = {3,4,5,2,1,0};
   b = GenerateBBSTArray(a, 6);
}

