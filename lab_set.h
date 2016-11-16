/**
    122COM - Introduction to Algorithms
    lab_set.h
    Purpose: C++ Implementation of Set ADT using arrays.
        
    Author : Rithin Chalumuri
    Version: 1.5 
    Date   : 15/07/16 
*/


#include <exception>
#include <memory>
#include <iostream>
#include <string>

using namespace std;

class Set
{
private:
    const int maxSize;
    unique_ptr<char[]> setElements; 
    int pos;

public:
    class Full: public exception
    {
    public:
        virtual const char* what() const throw()
          {
            return "The Set is full";
          }
    };

    class Empty: public exception
    {
    public:
        virtual const char* what() const throw()
          {
            return "The Set is empty";
          }
    };
  

    /** Initialise the set, maxSize is the maximum number of
        values that can be stored in the set at any time 
    */
    Set( const int _maxSize ) : maxSize(_maxSize), setElements( new char[maxSize] )
    {
        pos = 0;
    }    

    ~Set()
    {
    }
  
    /** Another Initialisation constructor for class Set, which allows you to create a new set
        by copying data of another set. Used for Intersection, Union and Difference operations.
    */
    Set( const Set &otherSet ) : maxSize(otherSet.maxSize), setElements( new char[otherSet.maxSize] )
    {
        pos=0;
      
        for (int i=0; i<otherSet.maxSize; ++i)
        {
            addElement(otherSet.setElements[i]);
        } 
    }
    
    /** Function that returns the number of values currently stored in the 
        set.
    */
    int num_elements()
    {
        return pos;
    }
  
    /** 
      Function to check if a particular value is in the set. 
  
       Parameters: 
          value(char); the value being searched for in the set. 
       Returns:
          A boolean value. True if the value is found in the set, otherwise false.
    
    */  
    bool checkIfInSet(char value)
    {
      for (int i=0 ; i<pos; i++)
      {
        if ( setElements[i] == value)
        {
          return true;
        }
      } 
      return false;
    }
    
    /** Function that Prints out all the elements present in the set (in a nice manner). 
    */  
    void printSet()
    {
      cout << "{";
      for (int i=0 ; i<pos; i++)
      {
        if (i == pos - 1)                // if it is last element it will not print ',' after it.
        {
          cout << setElements[i] ;
        }
        else
        {
          cout << setElements[i] << ",";          
        }        
      }
      cout<<"}"<<endl;
    }
  
    /** 
      Function to add a particular value to the set. 
  
       Parameters: 
          value(char); the value being added to the set.
       Raises:
          Set::Full - If the set is full.    
    */ 
    void addElement( char value )
    {
        if( num_elements() < maxSize )
        {
          if (checkIfInSet(value))        // if value already exists in set
          {
            cout << "Set currently has "<<pos<<" elements: ";
            printSet();
            cout<<"Error in entry number "<<pos + 1<<" : "<<"'" << value << "' is not added because it already exists in the set."<< endl;  
          }
          else 
          {
            setElements[pos] = value;
            pos += 1;                  
          }           
        }
        else
        {
            throw Full();
        }
    }
  
    /** 
      Function to overwrite the present elements with the one next to it.
      In other words, it is simply moving all elements after the element being removed  
      in set by one position backwards.
  
       Parameters: 
          value(char); the value being removed from the set.   
    */ 
    void overwriteElements(char value)
    {
      for (int i = 0; i < pos; i++)
      {
        if (setElements[i] == value)           //When the value to remove is found in the set
        {
          for (int j = i; j < pos - 1; j++)
          {
            setElements[j] = setElements[j + 1];  // overwriting the present elements with next one        
          }          
          return;
        }
      }      
    }
  
    /** 
      Function to remove a particular value from the set. 
  
       Parameters: 
          value(char); the value being removed from the set.
       Raises:
          Set::Empty - If user is trying to remove elements from a null set.    
    */ 
    void removeElement(char value)
    {
      if (num_elements() > 0)
      {
        if (checkIfInSet(value)) 
        {
          overwriteElements(value);
          pos -= 1;
          cout << "Element '" << value << "' has been removed from the set."<< endl;            
        }
        else
        {
          cout << "The value '"<<value<<"' cannot be removed because it does not exist in set."<< endl;
        }
      }
      else
      {
        throw Empty();        
      }
    }
  
    /** 
      Function to perform intersection operation of two sets. 
  
       Parameters: 
          set2(Set); the set you want to find intersection with.
       Returns:
          resultingSet (Set) ; The resulting set you get after performing intersection of two sets.   
    */ 
    Set Intersection(Set set2)
    {
      int set1_elements = pos;
      int set2_elements = set2.num_elements();
      int totalElements = set1_elements + set2_elements;
      int count = 0;
      unique_ptr<char[]> intersection_elements(new char[totalElements]);
      for (int i=0; i<set1_elements; i++)
      { 
        if (set2.checkIfInSet(setElements[i]))           // If an element of set1 is in set2
        {
          intersection_elements[count] = setElements[i];
          count +=1;
        }        
      }
      
      Set resultingSet(count);      // Creating a Resulting Set of size "count"
      for(int j=0; j<count; j++)
      {
        resultingSet.addElement(intersection_elements[j]);
      }
      return resultingSet;
    }
  
    /** 
      Function to perform union operation of two sets. 
  
       Parameters: 
          set2(Set); the set you want to find Union with.
       Returns:
          resultingSet (Set) ; The resulting set you get after performing Union of two sets.   
    */   
    Set Union(Set set2)
    {
      int set1_elements = pos;
      int set2_elements = set2.num_elements();
      int totalElements = set1_elements + set2_elements;
      int count = 0;
      unique_ptr<char[]> union_elements(new char[totalElements]);
      for (int i=0; i<set1_elements; i++)
      { 
        if (!(set2.checkIfInSet(setElements[i])))         // if an element of set1 is NOT in set2
        {
          union_elements[count] = setElements[i];
          count +=1;
        }        
      }
      
      for (int j=0; j<set2_elements;j++)                  // simply adding all the elements in set2 to union_elements. 
      {
        union_elements[count] = set2.setElements[j];
        count += 1;
      }
      
      Set resultingSet(count);
      for(int k=0; k<count; k++)
      {
        resultingSet.addElement(union_elements[k]);       // Creating a Resulting Set of size "count"
      }
      
      return resultingSet;
    }
    
    /** 
      Function to perform difference operation of two sets (set1 - set2). 
  
       Parameters: 
          set2(Set); the set you want to find difference with.
       Returns:
          resultingSet (Set) ; Set that contains all of the elements of set1
                               which are not there in set2.
    */   
    Set Difference(Set set2)
    {
      int set1_elements = pos;
      int set2_elements = set2.num_elements();
      int totalElements = set1_elements + set2_elements;
      int count = 0;
      unique_ptr<char[]> difference_elements(new char[totalElements]);
      for (int i=0; i<set1_elements; i++)
      { 
        if (!(set2.checkIfInSet(setElements[i])))           // if an element of set1 is NOT in set2
        {
          difference_elements[count] = setElements[i];
          count +=1;
        }        
      }
      
      Set resultingSet(count);         // Creating a Resulting Set of size "count"
      for(int j=0; j<count; j++)
      {
        resultingSet.addElement(difference_elements[j]);
      }
      return resultingSet;
    }
  
};