#include <stdio.h>

#define MAX_LEN 100
//======================================================================================
class BSTNode
{   
    public:
      int      NodeKey; 
      int      Level; 
      BSTNode* LeftChild; 
      BSTNode* RightChild; 
      BSTNode* Parent; 
	
      BSTNode(int key, BSTNode* parent)
      {
            NodeKey = key;
            LeftChild = NULL;
            RightChild = NULL;
            Parent = parent;
      }
};
//====================================================================================== 
class BalancedBST
{
   public:
	   BSTNode* Root;
      int BSTArray[MAX_LEN]; 
	   int length;
	
	   BalancedBST() 
	   { 
	      Root = NULL;
	   }

      void CreateFromArray(int* a, int a_len) 
      {        
         if (a_len >= MAX_LEN) 
            return;
         for(int i = 0; i < MAX_LEN ; i++)
         {
            if (i < a_len) 
               BSTArray[i] = a[i];            
            else 
               BSTArray[i] = -1;           
         } 
         length = a_len;
      }

      void GenerateTree() 
      {       
         Root = fillTree(NULL, 0, length, 1);
      } 

      bool IsBalanced(BSTNode* root_node) 
      {  
	      int check = CheckLevel(root_node);
         if (check)
            return true; 
         return false;
      }

   private:
      BSTNode* fillTree(BSTNode* parent, int index, int length, int level)
      {  
         BSTNode* Node = new BSTNode(BSTArray[index], parent);
         Node->Level = level;

         if ((2 * index + 1) < length && BSTArray[(2 * index + 1)] != -1)      // if the index is in an array and not empty
            Node->LeftChild = fillTree(Node, 2 * index + 1, length, level+1 ); // left 
         else {
            Node->LeftChild = NULL;
            return Node; }

         if ((2 * index + 2) < length && BSTArray[(2 * index + 2)] != -1)       // if the index is in an array and not empty  
            Node->RightChild = fillTree(Node, 2 * index + 2, length, level+1 ); // right 
         else {
            Node->RightChild = NULL;
            return Node; }
         return Node;
      }

      int CheckLevel(BSTNode* Node)  
      {      
         int x, y;
         if (Node->LeftChild == NULL)   x = Node->Level;
         else                           x = CheckLevel(Node->LeftChild);      

         if (Node->RightChild == NULL)  y = Node->Level;
         else                           y = CheckLevel(Node->RightChild); 
      
         if (x-y > 1 || x-y < -1 || x == 0 || y == 0) // if not balanced      
            return 0;         
      
         if (x > y)       
            return x;
         return y;
      }
};
//====================================================================================== 
#define empty -1
int index = 0; 
int* new_a;
//=================================
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
   int L_Index = 2 * index + 1;
   int R_Index = 2 * index + 2;

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

int get_new_array_size(int size)
{
   int depth = count_max_level(size);
   int new_size = (two_to_the_degree(depth + 1) - 1);
   return new_size;
}

int* GenerateBBSTArray(int a[], int size) 
{ 	
   int new_a_size = get_new_array_size(size);
   new_a = new int[new_a_size]; //create new array with correct size
   bubbleSort (a + 0, size); // sort from min to max
   sortArray(a, (a + size - 1), 0, size, new_a_size); // begin , end , size
   return new_a;
}
//======================================================================================
//--------------------------------------------------------------------------------------
//======================================================================================

int test()
{
   const int length = 10;
   int a[length] = {6,7,3,4,5,2,1,0,9,8};
   int* b = GenerateBBSTArray(a, length);   
   
   BalancedBST tree = BalancedBST();
   int b_size = get_new_array_size(length);
   tree.CreateFromArray(b, b_size); 
   tree.GenerateTree();
   bool test = tree.IsBalanced(tree.Root);
   
   int c[15] = {5,2,8,1,4,7,-1,0,-1,3,-1,6,-1,-1,-1};
   BalancedBST tree2 = BalancedBST();
   tree2.CreateFromArray(c+0, 15);
   tree2.GenerateTree();
   test = tree2.IsBalanced(tree2.Root);
   return 0;
}




