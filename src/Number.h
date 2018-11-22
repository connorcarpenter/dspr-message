#pragma once

#include <vector>
#include <assert.h>
#include <memory>
#include "CharVector.h"
#include "CStr.h"

namespace DsprMessage
{
    class Number
    {
    public:
        Number(unsigned char name);

        void set(unsigned char value);
        void set(unsigned int value);
        void set(int value);
        void set(bool value);
        template <class T>
        void set(T) = delete; //this enforces that no implicit casts happen

        unsigned int get() const;
        bool getWasSet();

        void serialize(std::shared_ptr<CharVector> charVector);
        int deserialize(int index, std::shared_ptr<CStr> cstr);

        static bool Equals(const Number& a, const Number& b);

    private:
        //Number(const Number&) = delete;
        Number& operator=(const Number&) = delete;
        unsigned char name;
        unsigned int value = 0;
        unsigned int dataSize = 0;
        bool wasSet = false;
    };
}