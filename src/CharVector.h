#pragma once

//
// Created by connor on 11/21/18.
//

#include <vector>
#include <assert.h>
#include <memory>

namespace DsprMessage
{
    class CharVector
    {

    public:

        template <class ...Args>
        static std::unique_ptr<CharVector> make_charVector(Args&& ...args)
        {
            return std::unique_ptr<CharVector>(new CharVector(std::forward<Args>(args)...));
        }

        ~CharVector();
        int size();
        unsigned char at(int i);
        void push_back(unsigned char c);
        void push_back(unsigned int i);
        void push_back(long unsigned int i);
        template <class T>
        void push_back(T) = delete; //this enforces that no implicit casts happen

        void addAt(unsigned int amount, unsigned int index);

    private:

        CharVector();
        CharVector(const CharVector&) = delete;
        CharVector& operator=(const CharVector&) = delete;

        std::vector<unsigned char>* theVector = nullptr;
    };
}