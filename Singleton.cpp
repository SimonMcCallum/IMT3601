//
//  Singleton.cpp
//  IMT3601
/*!
   Created by Simon McCallum on 30/08/2012.
 */

#include "Singleton.h"
#include <iostream>
using namespace std;


/*!
   One of the most useful Design Patterns the Singleton Pattern
   There are good examples on Wiki, and the Game Programming Wiki
 */


Singleton* Singleton::m_instance = NULL;

Singleton::Singleton()
{
    m_data = 0;
};


Singleton* Singleton::getInstance()
{
    if(m_instance == NULL)
    {
        m_instance = new Singleton();
        return m_instance;
    }
    else
    {
        return m_instance;
    }
}

void Singleton::setTest(int setValue)
{
    m_data = setValue;
}

int Singleton::getTest()
{
    return m_data;
}


