
#include "stdafx.h"
//======================================================================
#include <stdio.h>

class aBST
{
    public: 
      int* Tree; // array of positive keys
      int tree_size;
	
    aBST(int depth)
    {      
      tree_size = two_to_the_degree(depth + 1) - 1; // calculation 
      Tree = new int[ tree_size ];
      for(int i=0; i<tree_size; i++) Tree[i] = -1;
    }
	
    int FindKeyIndex(int key)
    {
      int index = findKey(0, key); // finding key index in the array 
      return index; 
    }

    int FindFreeCell(int key)
    {
      int index = findEmptyCell(0 , key); // finding empty cell for new key       
      return index; 
    }
	
    int AddKey(int key)
    {
      if (FindKeyIndex(key) == -1)
      {
         int index = FindFreeCell(key); 
         if(index == -1)         
            return -1;           // no empty place
         else
         {
            Tree[index] = key;   // adding new key
            return index;
         }
      }
      else
         return -1;              // key is found      
    }

 private:
   int findKey(int index, int key)   
   {  
      if (key == Tree[index])
         return index;              // key is found
      if (Tree[index] == -1)
         return -1;                 // array end 
      if (index >= tree_size)  
         return -1;                 // array size exceeded
      else 
         if (key < Tree[index] )
            return findKey(2 * index + 1, key); // to left child
         else
            return findKey(2 * index + 2, key); // to right child    
      return -1;                           // no empty place
   }

   int findEmptyCell(int index, int key)   
   {  
      if (Tree[index] == -1)
         return index;              // empty cell 
      if (index >= tree_size)  
         return -1;                 // array size exceeded
      else 
         if (key < Tree[index] )
            return findEmptyCell(2 * index + 1, key); // to left child
         else
            return findEmptyCell(2 * index + 2, key); // to right child    
      return -1;                           // no empty place
   }

   int lengthCount(int N) // dimension calculation of the array
   {
      if (N == 0) 
         return 1;
      else 
         return (two_to_the_degree(N) + lengthCount(N-1));  
   }

   int two_to_the_degree(int D) 
   {
     if (D == 0) 
       return 1;
     else   
       return (2 * two_to_the_degree(D-1));
   }	
};
//======================================================================


int main()
{
	aBST tree = aBST(3);
   tree.AddKey(50);
   tree.AddKey(75);
   tree.AddKey(25);
   tree.AddKey(37);
   tree.AddKey(84);
   tree.AddKey(62);
   tree.AddKey(92);
   tree.AddKey(55);
   tree.AddKey(43);
   tree.AddKey(31);

   tree.AddKey(45);
   tree.AddKey(40);


   return 0;
}

