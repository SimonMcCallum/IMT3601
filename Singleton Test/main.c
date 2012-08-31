//
//  main.c
//  Singleton Test
//
//  Created by Simon McCallum on 31/08/2012.
//
//


#include "../Singleton.h"
#include <iostream>
#include <assert.h>


int main(int argc, const char * argv[])
{

    Singleton *sing1,*sing2;
    int testValue = 5;
        
    sing1 = Singleton::getInstance();
    sing1->setTest(testValue);
    sing2 = Singleton::getInstance();
    
    assert(sing2->getTest() == sing1->getTest());
    std::cout << sing2->getTest();
    return 0;

}

