//
//  Singleton.h
//  IMT3601
//
//  Created by Simon McCallum on 30/08/2012.
//
//

#ifndef __IMT3601__Singleton__
#define __IMT3601__Singleton__


class Singleton{
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

#endif /* defined(__IMT3601__Singleton__) */
