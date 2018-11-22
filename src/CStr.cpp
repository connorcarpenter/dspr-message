//
// Created by connor on 11/21/18.
//

#include "CStr.h"

namespace DsprMessage
{

    CStr::~CStr(){
        delete [] this->innerCstr;
    }
    unsigned char CStr::at(unsigned char index) {
        return this->innerCstr[index];
    }
    unsigned char CStr::size() {
        return this->number;
    }
    unsigned char* CStr::getCharPtr() {
        return this->innerCstr;
    }

    CStr::CStr(unsigned char* otherCstr, unsigned int number)
    {
        this->innerCstr = otherCstr;
        this->number = number;
        this->innerCstr = new unsigned char[this->number];
        for(int i=0;i<this->number;i++)
            this->innerCstr[i] = otherCstr[i];
    }

    CStr::CStr(std::shared_ptr<CharVector> pVector)
    {
        this->number = pVector->size();
        this->innerCstr = new unsigned char[this->number];
        for(int i=0;i<this->number;i++)
        {
            this->innerCstr[i] = pVector->at(i);
        }
    }

    CStr::CStr(const Array& arr)
    {
        this->number = arr.size();
        this->innerCstr = new unsigned char[this->number];
        for(int i=0;i<this->number;i++)
        {
            this->innerCstr[i] = arr.get(i);
        }
    }

    void CStr::subtractAt(unsigned int amount, unsigned int index) {
        this->innerCstr[index] -= amount;
    }
}