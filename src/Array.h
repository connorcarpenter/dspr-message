#pragma once

//
// Created by connor on 11/21/18.
//

#include <vector>
#include <memory>
#include "CharVector.h"
#include "CStr.h"

namespace DsprMessage {
    class CStr;

    class Array
    {
    public:

        Array(unsigned char name);

        ~Array();

        void add(unsigned char value);

        void add(unsigned int value);

        void add(int value);

        void checkForDataSize(unsigned int value);

        template <class T>
        void add(T) = delete; //this enforces that no implicit casts happen

        unsigned int get(unsigned int i) const;

        void serialize(std::shared_ptr<CharVector> charVector);

        int deserialize(int index, std::shared_ptr<DsprMessage::CStr> cstr);

        static bool Equals(const Array& a, const Array& b);

        unsigned int size() const;

        bool wasSet();

        void loadFromString(std::string str);

        void loadFromCstr(std::shared_ptr<CStr> cstr);

    private:

        //Array(const Array&) = delete;
        Array& operator=(const Array&) = delete;

        unsigned char name;
        unsigned int dataSize = 1;
        std::vector<unsigned int> contents;
        bool set = false;
    };
}