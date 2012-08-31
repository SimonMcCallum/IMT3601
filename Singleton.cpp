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
class Singleton
{
private:
    static Singleton *m_instance;
    Singleton();
    int m_data;
    
public:
    static Singleton* getInstance();
    void setTest(int setValue);
    int getTest();
    ~Singleton()
    {
        //delete m_instance;
    }
};

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
    cout << "Test setting" << endl;
    m_data = setValue;
}

int Singleton::getTest()
{
    cout << "Test getting " << m_data << endl;
    return m_data;
}


int main()
{
    Singleton *sing1,*sing2;
    
    sing1 = Singleton::getInstance();
    sing1->setTest(5);
    sing2 = Singleton::getInstance();
    sing2->getTest();
    
    return 0;
}