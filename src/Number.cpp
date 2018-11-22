//
// Created by connor on 11/20/18.
//

#include "Number.h"

namespace DsprMessage
{
    Number::Number(unsigned char name)
    {
        this->name = name;
    }

    void Number::set(unsigned char value)
    {
        this->dataSize = 1;
        this->value = value;
        this->wasSet = true;
    }

    void Number::set(unsigned int value)
    {
        this->dataSize=1;
        if (value >= 255) this->dataSize+=1;
        if (value >= 65535) this->dataSize+=1;
        if (value >= 16777215) {
            int i = 1/0; // what the heck is this big?
        }
        this->value = value;
        this->wasSet = true;
    }

    void Number::set(int value)
    {
        assert(value>=0);
        this->set((unsigned int) value);
    }

    void Number::set(bool value)
    {
        this->dataSize=1;
        this->value = (unsigned char) value;
        this->wasSet = true;
    }

    unsigned int Number::get() const
    {
        return this->value;
    }

    void Number::serialize(std::shared_ptr<CharVector> charVector) {
        if (!wasSet) return;
        charVector->push_back(this->name);
        charVector->push_back(this->dataSize);
        for (int i=0;i<this->dataSize;i++)
        {
            unsigned char c = ((this->value >> (8*i)) & 0xFF);
            charVector->push_back(c);
        }
    }

    int Number::deserialize(int index, std::shared_ptr<CStr> cstr) {
        this->dataSize = cstr->at(index);index+=1;
        unsigned int val = 0;
        for(int i = 0;i<this->dataSize;i++)
        {
            val |= (cstr->at(index+i) << (8*i));
        }
        index += this->dataSize;
        this->set(val);
        return index;
    }

    bool Number::Equals(const Number& a, const Number& b) {
        if (a.value != b.value) return false;
        return true;
    }

    bool Number::getWasSet() const {
        return this->wasSet;
    }
}