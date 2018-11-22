#pragma once

//
// Created by connor on 11/21/18.
//

#include <memory>
#include "Array.h"

namespace DsprMessage
{
    class Array;

    class CStr
    {
    public:
        template <class ...Args>
        static std::unique_ptr<CStr> make_cstr(Args&& ...args)
        {
            return std::unique_ptr<CStr>(new CStr(std::forward<Args>(args)...));
        }
        ~CStr();
        unsigned char at(unsigned char index);
        void subtractAt(unsigned int amount, unsigned int index);
        unsigned char size();
        unsigned char* getCharPtr();
    private:

        unsigned int number = 0;
        unsigned char *innerCstr = nullptr;

        CStr(unsigned char* otherCstr, unsigned int number);

        CStr(std::shared_ptr<CharVector> pVector);

        CStr(const Array& arr);

        CStr(const CStr&) = delete;
        CStr& operator=(const CStr&) = delete;
    };
}