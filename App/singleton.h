/***************************************************************************
**
** Copyright (C) 2016 Medical Technologies CZ a.s.. All rights reserved.
** Contact: http://www.medictech.com
**
** This file is a part of BTL088 project, projects based on BTL088
** or related utilities.
**
** Without prior written permission from Medical Technologies CZ a.s.,
** the file must not be modified, distributed and/or otherwise used.
**
****************************************************************************/


#pragma once

/*!
  \author Andrej Repiský
  \date   14. 12. 2015
  \brief  Singleton template class

Inherit from this class to make sure that you have only one instance of your class, available from the header file.
If you require thread safety, make sure to compile this as C++11.
See http://stackoverflow.com/questions/11711920/how-to-implement-multithread-safe-singleton-in-c11-without-using-mutex

Usage example:

class MyClass : public MyBaseClass, public Singleton<MyClass>
{
    ...
};

*/

#include <QCoreApplication>

template<typename T>
class Singleton
{
public:
    static T &instance() {
        if(pInstance == nullptr)
            new T();
        return *pInstance;
    }

protected:
    Singleton() {
        Q_ASSERT_X(pInstance == nullptr, "Singleton", "There are multiple instances of a singleton class. "
                                                      "Make sure to use instance() method instead of calling constructor directly.");
        pInstance = static_cast<T *>(this);

        /* Following call ensures that destructor of Singleton and its subclasses is called
         * when the program terminates. It fixes the problem of gcc and MinGW, which do not
         * properly destroy heap-allocated objects. You may want to disable this code
         * with preprocessor directives if you compile this file in other compilers
         * or non-Qt environment.
         */
        QObject::connect(qApp, &QCoreApplication::aboutToQuit, [this](){
            delete pInstance;
            pInstance = nullptr;
        });
    }
    ~Singleton() { }

private:
    static T *pInstance;
};  // class Singleton


template<typename T>
T* Singleton<T>::pInstance = nullptr;

