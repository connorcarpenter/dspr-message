#pragma once

namespace DsprMessage
{
    class _bytes
    {
    public:
        _bytes(char name)
        {
            this->name = name;
        }

        ~_bytes()
        {
            if (this->array != nullptr)
                delete this->array;
        }

        void initBytes(char numBytes)
        {
            this->numBytes = numBytes;
            this->array = new char[numBytes];
        }

        void setArray(unsigned int index, char value)
        {
            this->array[index] = value;
            this->wasSet = true;
        }

        char* array = nullptr;
        char numBytes = 0;
    private:
        char name;
        bool wasSet = false;
    };

    class _soloByte
    {
    public:
        _soloByte(char name)
        {
            this->name = name;
        }

        void set(char value)
        {
            this->value = value;
            this->wasSet = true;
        }
    private:
        char name;
        char value = 0;
        bool wasSet = false;
    };

    class _duoByte
    {
    public:
        _duoByte(char name)
        {
            this->name = name;
        }

        void set(unsigned int value)
        {
            this->value = value;
            this->wasSet = true;
        }
    private:
        char name;
        unsigned int value = 0;
        bool wasSet = false;
    };

    template <class A, class B>
    class _pair
    {
    public:
        _pair(char name)
        {
            this->name = name;
        }

        void setA(unsigned int value)
        {
            this->valueA = value;
            this->wasSet = true;
        }

        void setB(unsigned int value)
        {
            this->valueB = value;
            this->wasSet = true;
        }
    private:
        char name;
        unsigned int valueA = 0;
        unsigned int valueB = 0;
        bool wasSet = false;
    };
}