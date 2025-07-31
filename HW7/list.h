#ifndef LIST_H
#define LIST_H

#include <iostream>

using std::cout;

#include <new>
#include "listnode.h"  // ListNode class definition

template< class NODETYPE >
class List {
public:
   List();      // constructor
   List(const NODETYPE &); // copy constructor
   ~List();     // destructor
   List& operator=(const NODETYPE & );  // assignment operator
   void insertAtFront( const NODETYPE & );
   void insertMiddle( const NODETYPE & , unsigned int); // insert at middle
   void insertAtBack( const NODETYPE & );
   bool removeFromFront( NODETYPE & );
   bool removeMiddle( NODETYPE & ,unsigned int ); // remove from middle
   bool removeFromBack( NODETYPE & );
   bool isEmpty() const;
   void print() const;

private:
   ListNode< NODETYPE > *firstPtr;  // pointer to first node
   ListNode< NODETYPE > *lastPtr;   // pointer to last node
   // utility function to allocate new node
   ListNode< NODETYPE > *getNewNode( const NODETYPE & );
   int listSize() const;
   void clear();

}; // end class List

// default constructor
template< class NODETYPE >
List< NODETYPE >::List() 
   : firstPtr( 0 ), 
     lastPtr( 0 ) 
{ 
   // empty body

} // end List constructor

template< class NODETYPE >
List< NODETYPE >::List(const NODETYPE &l)
{
   if(l->firstPtr == 0) //  if the list being copied is empty, empty current list
   {
      ~List();
      firstPtr = lastPtr = 0;
   }
   else
   {
      ListNode< NODETYPE > *tempPtr = l->firstPtr; 
      while(tempPtr != 0) // deep copy of other list
      {
         ListNode< NODETYPE > *newPtr = getNewNode(tempPtr); 
         if(firstPtr == 0)
         {
            firstPtr = newPtr;
            lastPtr = newPtr;
         }
         else
         {
            lastPtr -> nextPtr = newPtr;
            lastPtr = newPtr;
         }
         tempPtr = tempPtr -> nextPtr;
      }
   }
}

// destructor
template< class NODETYPE >
List< NODETYPE >::~List()
{
   if ( !isEmpty() ) {    // List is not empty
//      cout << "Destroying nodes ...\n";

      ListNode< NODETYPE > *currentPtr = firstPtr;
      ListNode< NODETYPE > *tempPtr;

      while ( currentPtr != 0 )         // delete remaining nodes
      {  
         tempPtr = currentPtr;

// commented out the output -- no need to print what we are deallocating
//         cout << tempPtr->data << '\n';  

         currentPtr = currentPtr->nextPtr;
         delete tempPtr;

      }

   }

//   cout << "All nodes destroyed\n\n";

} // end List destructor

template < class NODETYPE >
List< NODETYPE >& List< NODETYPE >::operator=(const NODETYPE &l)
{
   if(firstPtr == 0)
   {
      ~List();
      firstPtr = lastPtr = 0;
      return *this;
   }

   ListNode< NODETYPE > *tempPtr = l->firstPtr; 
   while(tempPtr != 0) // deep copy of other list
   {
      ListNode< NODETYPE > *newPtr = getNewNode(tempPtr); 
      if(firstPtr == 0)
      {
         firstPtr = newPtr;
         lastPtr = newPtr;
      }
      else
      {
         lastPtr -> nextPtr = newPtr;
         lastPtr = newPtr;
      }
      tempPtr = tempPtr -> nextPtr;
   }
   return *this;
}

// insert node at front of list
template< class NODETYPE >
void List< NODETYPE >::insertAtFront( const NODETYPE &value )
{
   ListNode< NODETYPE > *newPtr = getNewNode( value );

   if ( isEmpty() )  // List is empty
      firstPtr = lastPtr = newPtr;

   else {  // List is not empty
      newPtr->nextPtr = firstPtr;
      firstPtr = newPtr;

   } // end else

} // end function insertAtFront

template< class NODETYPE >
void List< NODETYPE >::insertMiddle(const NODETYPE & v, unsigned int p)
{
   ListNode< NODETYPE > *newPtr = getNewNode( v );
   ListNode< NODETYPE > *currentNode = firstPtr;
   ListNode< NODETYPE > *tempPtr = firstPtr;
   int c = listSize();
   // make tempptr for original nextptr, switch nextptr for the node at index to the parameter node, then assign nextptr for parameter node to tempptr
   if(isEmpty())
      insertAtFront(v);
   
   else
   {
      if(c < p) // if index is greater than the size of the list, insert at back
         insertAtBack(v);
      else if (p <= 0)
         insertAtFront(v);
      else
      {
         //while ()
         for(int i = 1; i < p-1; i++)
         {
            currentNode = currentNode -> nextPtr;
            //cout<<currentNode->getData()<<endl;
         }
         //cout<<"next to temp"<<endl;
         tempPtr = currentNode -> nextPtr;
         //cout<<"new to next"<<endl;
         currentNode -> nextPtr = newPtr;
         //cout<<"temp to newnext"<<endl;
         newPtr -> nextPtr = tempPtr;
      }
   }
}

// insert node at back of list
template< class NODETYPE >
void List< NODETYPE >::insertAtBack( const NODETYPE &value )
{
   ListNode< NODETYPE > *newPtr = getNewNode( value );

   if ( isEmpty() )  // List is empty
      firstPtr = lastPtr = newPtr;

   else {  // List is not empty
      lastPtr->nextPtr = newPtr;
      lastPtr = newPtr;

   } // end else

} // end function insertAtBack

// delete node from front of list
template< class NODETYPE >
bool List< NODETYPE >::removeFromFront( NODETYPE &value )
{
   if ( isEmpty() )  // List is empty
      return false;  // delete unsuccessful

   else {  
      ListNode< NODETYPE > *tempPtr = firstPtr;

      if ( firstPtr == lastPtr )
         firstPtr = lastPtr = 0;
      else
         firstPtr = firstPtr->nextPtr;

      value = tempPtr->data;  // data being removed
      delete tempPtr;

      return true;  // delete successful

   } // end else

} // end function removeFromFront

template< class NODETYPE >
bool List< NODETYPE >::removeMiddle( NODETYPE & value , unsigned int p)
{
   // 1 2 3 4
   // 2
   // point next1 to 3, delete 2
   int p1 = p, p2 = p;
   int c = listSize();
   if(isEmpty())
      return false;  
   if(c < p || p <= 0)
      return false;
   if(p == 1 || firstPtr -> nextPtr == 0)
   {
      removeFromFront(value);
      return true;
   }
   
   ListNode< NODETYPE > *afterPtr = firstPtr;
   for(int i = 0; i < p; i++) // find node after the one to be deleted
      afterPtr = afterPtr -> nextPtr;

   ListNode< NODETYPE > *tempPtr = firstPtr;
   for(int i = 1; i < p; i++) // find node to be deleted
      tempPtr = tempPtr -> nextPtr;
   value = tempPtr->data;
   delete tempPtr;


   ListNode< NODETYPE > *currentPtr = firstPtr;
   for(int i = 1; i < p - 1; i++) // find node before the deleted one and point its next pointer to the before node
   {
      currentPtr = currentPtr -> nextPtr;
   }
   cout<<currentPtr -> getData()<<endl;
   currentPtr -> nextPtr = afterPtr;
   return true;
}

// delete node from back of list
template< class NODETYPE >
bool List< NODETYPE >::removeFromBack( NODETYPE &value )
{
   if ( isEmpty() )
      return false;  // delete unsuccessful

   else {
      ListNode< NODETYPE > *tempPtr = lastPtr;

      if ( firstPtr == lastPtr )
         firstPtr = lastPtr = 0;
      else {
         ListNode< NODETYPE > *currentPtr = firstPtr;

         // locate second-to-last element
         while ( currentPtr->nextPtr != lastPtr )
            currentPtr = currentPtr->nextPtr;

         lastPtr = currentPtr;
         currentPtr->nextPtr = 0;

      } // end else

      value = tempPtr->data;
      delete tempPtr;

      return true;  // delete successful

   } // end else

} // end function removeFromBack

// is List empty?
template< class NODETYPE > 
bool List< NODETYPE >::isEmpty() const 
{ 
   return firstPtr == 0; 
   
} // end function isEmpty

// return pointer to newly allocated node
template< class NODETYPE >
ListNode< NODETYPE > *List< NODETYPE >::getNewNode( 
   const NODETYPE &value )
{
   return new ListNode< NODETYPE >( value );

} // end function getNewNode

// display contents of List
template< class NODETYPE >
void List< NODETYPE >::print() const
{
   if ( isEmpty() ) {
      cout << "The list is empty\n\n";
      return;

   } // end if

   ListNode< NODETYPE > *currentPtr = firstPtr;

   cout << "The list is: ";

   while ( currentPtr != 0 ) {
      cout << currentPtr->data << ' ';
      currentPtr = currentPtr->nextPtr;

   } // end while

   cout << "\n\n";

} // end function print

template< class NODETYPE >
int List< NODETYPE >::listSize() const // helper function to get size of list
{
   ListNode< NODETYPE > *currentPtr = firstPtr;
   int c = 0;
   while(currentPtr != 0)
   {
      currentPtr = currentPtr -> nextPtr;
      c++;
   }
   return c;
}

template< class NODETYPE >
void List< NODETYPE >::clear()
{
   NODETYPE &value;
   if(!isEmpty())
   {
      int s = listSize();
      for(int i = 0; i < s; i++)
         removeFromFront(value);
   }
}

#endif