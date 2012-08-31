//
//  main.c
//  Singleton Test
//
//  Created by Simon McCallum on 31/08/2012.
//
//


#include "../Singleton.h"
#include <iostream>


int main(int argc, const char * argv[])
{

    Singleton *sing1,*sing2;
        
        sing1 = Singleton::getInstance();
        sing1->setTest(5);
        sing2 = Singleton::getInstance();
        sing2->getTest();
        
    return 0;

}

