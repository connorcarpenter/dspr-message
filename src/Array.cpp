//
// Created by connor on 11/21/18.
//

#include "Array.h"
#include "Number.h"
#include <string>

namespace DsprMessage{
    Array::Array(unsigned char name)
    {
        this->name = name;
    }

    Array::~Array()
    {
    }

    void Array::add(unsigned char value)
    {
        checkForDataSize(value);
        this->contents.push_back(value);
        this->wasSet = true;
    }

    void Array::add(unsigned int value)
    {
        checkForDataSize(value);
        this->contents.push_back(value);
        this->wasSet = true;
    }

    void Array::add(int value)
    {
        assert(value >= 0);
        this->add((unsigned int) value);
    }

    void Array::checkForDataSize(unsigned int value)
    {
        unsigned int newDataSize = 1;
        if (value >= 255) newDataSize+=1;
        if (value >= 65535) newDataSize+=1;
        if (value >= 16777215) {
            int i = 1/0; // what the heck is this big?
        }
        if (newDataSize > this->dataSize)
            this->dataSize = newDataSize;
    }

    unsigned int Array::get(unsigned int i) const
    {
        return this->contents.at(i);
    }

    void Array::serialize(std::shared_ptr<CharVector> charVector) {
        if (!this->getWasSet()) return;
        charVector->push_back(this->name);
        charVector->push_back(this->dataSize);
        charVector->push_back(this->contents.size());
        for (int j=0;j<this->contents.size();j++)
        {
            unsigned int value = this->contents.at(j);
            for (int i = 0; i < this->dataSize; i++)
            {
                unsigned char c = ((value >> (8 * i)) & 0xFF);
                charVector->push_back(c);
            }
        }
    }

    int Array::deserialize(int index, std::shared_ptr<CStr> cstr) {
        this->dataSize = cstr->at(index);index+=1;
        unsigned int numberElements = cstr->at(index);index+=1;
        for (int j=0;j<numberElements;j++)
        {
            unsigned int val = 0;
            for (int i = 0; i < this->dataSize; i++)
            {
                val |= (cstr->at(index + i) << (8 * i));
            }
            index += this->dataSize;
            this->contents.push_back(val);
        }
        this->wasSet = true;
        return index;
    }

    bool Array::Equals(const Array& a, const Array& b) {
        if (a.dataSize != b.dataSize) return false;
        if (a.contents.size() != b.contents.size()) return false;
        for (int i=0;i<a.contents.size();i++)
        {
            if (a.contents.at(i) != b.contents.at(i)) return false;
        }
        return true;
    }

    unsigned int Array::size() const
    {
        return contents.size();
    }

    bool Array::getWasSet () const {
        return this->wasSet;
    }

    void Array::loadFromString(const std::string& str) {
        this->contents.clear();
        this->wasSet = true;
        for(int i=0;i<str.size();i++)
        {
            this->contents.push_back(str.at(i));
        }

    }

    void Array::loadFromCstr(std::shared_ptr<CStr> cstr) {
        this->contents.clear();
        this->wasSet = true;
        for(int i=0;i<cstr->size();i++)
        {
            this->contents.push_back(cstr->at(i));
        }
    }
}