/**
    122COM - Introduction to Algorithms
    lab_set_test.cpp
    Purpose: To Test the operations of implemented Set ADT in lab_set.h  

    Author : Rithin Chalumuri
    Version: 1.3 
    Date   : 15/07/16     
*/

#include <cxxtest/TestSuite.h>
#include "lab_set.h"
#include <vector>
#include <memory>
using namespace std;

class SetTest : public CxxTest::TestSuite 
{
private:
    shared_ptr<Set> set1;
    shared_ptr<Set> set2;
    vector<char> testvalues1;
    vector<char> testvalues2;

public:    
    /** Function that is done before running each test **/
    void setUp()
    {
        testvalues1 = {'a','b','d','e','f'};
        testvalues2 = {'e','d','c','g','b','p'};
        set1 = make_shared<Set>( testvalues1.size() );
        set2 = make_shared<Set>( testvalues2.size() );
    }
    
    /** Function that is done after running each test **/
    void tearDown()
    {
        set1.reset();
        set2.reset();
    }

    /** Test that Set reports the correct number of things in the set **/
    void test_size()
    {
        for( int i=0; i<(testvalues1.size()); ++i )
        {
            TS_ASSERT_EQUALS( i, set1->num_elements() );

            set1->addElement( testvalues1[i] );        // adding elements
        }

        for( int i=(testvalues1.size()); i>=0; i-- )
        {
            set1->removeElement( testvalues1[i]);        // removing elements
            TS_ASSERT_EQUALS( set1->num_elements(), i );
                        
        }

        TS_ASSERT_EQUALS( set1->num_elements(), 0 );
    }

    /** Test that Set raises Empty exception when removing an element from a null set **/
  
      void test_empty()
    {
        TS_ASSERT_THROWS( set1->removeElement('z'), Set::Empty );

        set1->addElement( testvalues1[0] );
        set1->removeElement(testvalues1[0]);

        TS_ASSERT_THROWS_ANYTHING( set1->removeElement('z'));
    }
  
   /** Test that the Set raises Full exception when adding an element to a full set **/
    void test_full()
    {
        for( int i=0; i<testvalues1.size(); ++i )
        {
            set1->addElement( testvalues1[i] );
        }

        TS_ASSERT_THROWS( set1->addElement('z'), Set::Full );
    }
  
  /** Test that Set reports if an element is in the set **/
    void test_checkInSet()
    {
        for( int i=0; i<testvalues1.size(); ++i )
        {
            set1->addElement( testvalues1[i] );
        }
      
        for( int i=0; i<testvalues1.size(); ++i)
        {
          TS_ASSERT_EQUALS(set1->checkIfInSet(testvalues1[i]) , true);  
        }
      
    }
  
  /** Test that Set performs the Intersection operation of two sets **/
   void test_intersection()
    {
      
        for( int i=0; i<testvalues1.size(); ++i )
        {
            set1->addElement( testvalues1[i] );
        }
      
        for( int i=0; i<testvalues2.size(); ++i )
        {
            set2->addElement( testvalues2[i] );
        }
        
        Set set3 = set1->Intersection(*set2);
 
        array<char, 3> intersection_ans = {'e','d','b'}; // correct results to verify with
      
        for (int i=0; i<intersection_ans.size(); ++i)
        {
          TS_ASSERT_EQUALS(set3.checkIfInSet(intersection_ans[i]) , true);  
        }
   }
  
  
   /** Test that Set performs the Union operation of two sets **/
    void test_union()
    {
      
        for( int i=0; i<testvalues1.size(); ++i )
        {
            set1->addElement( testvalues1[i] );
        }
      
        for( int i=0; i<testvalues2.size(); ++i )
        {
            set2->addElement( testvalues2[i] );
        }
        
        Set set3 = set1->Union(*set2);
        array<char, 8> union_ans = {'a','b','d','e','f','c','g','p'};  // correct results to verify with
      
        for (int i=0; i< union_ans.size(); ++i)
        {
          TS_ASSERT_EQUALS(set3.checkIfInSet(union_ans[i]) , true);  
        }
           
    }
  
  /** Test that Set performs the difference operation of two sets **/
    void test_difference()
    {
      
        for( int i=0; i<testvalues1.size(); ++i )
        {
            set1->addElement( testvalues1[i] );
        }
      
        for( int i=0; i<testvalues2.size(); ++i )
        {
            set2->addElement( testvalues2[i] );
        }
        
        Set set3 = set1->Difference(*set2);
        array<char, 2> difference_ans = {'a','f'}; // correct results to verify with
      
        for (int i=0; i<difference_ans.size(); ++i)
        {
          TS_ASSERT_EQUALS(set3.checkIfInSet(difference_ans[i]) , true);  
        }      
    }
  
};

