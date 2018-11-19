#pragma once

#include <vector>

namespace DsprMessage
{
    class _cstr
    {
    public:
        _cstr(char* innerCstr, unsigned int number, bool dealloc = false)
        {
            this->innerCstr = innerCstr;
            this->number = number;
            this->dealloc = dealloc;
        }

        ~_cstr(){
            if (this->dealloc)
                delete [] this->innerCstr;
        }


        unsigned int number = 0;

        static _cstr fromVector(std::vector<char> *pVector) {
            auto cvSize = pVector->size();
            auto cstr = new char[cvSize+1];
            for(int i=0;i<cvSize;i++)
            {
                cstr[i] = pVector->at(i)+1;
            }
            cstr[cvSize] = '\0';
            delete pVector;
            return _cstr(cstr, cvSize);
        }

        bool dealloc;

        char getDs(char index) {
            return this->innerCstr[index]-1;
        }

        char *innerCstr = nullptr;
    };

    class _bytes
    {
    public:
        _bytes(char name)
        {
            this->name = name;
        }

        ~_bytes()
        {
            if (this->dealloc)
                delete [] this->array;
        }

        void initBytes(char numBytes)
        {
            this->numBytes = numBytes;
            this->array = new char[numBytes];
            this->dealloc = true;
        }

        void setArray(unsigned int index, char value)
        {
            this->array[index] = value;
            this->wasSet = true;
        }

        char getArray(unsigned int index)
        {
            return this->array[index];
        }

        void set(_cstr cstr) {
            this->numBytes = cstr.number;
            this->array = cstr.innerCstr;
            this->wasSet = true;
        }

        _cstr get()
        {
            return _cstr(array, numBytes);
        }

        char* array = nullptr;
        char numBytes = 0;

        bool wasSet = false;

        void serialize(std::vector<char> *charVector) {
            if (!wasSet) return;
            if (this->numBytes == 0)return;
            charVector->push_back(this->name);
            charVector->push_back(this->numBytes);
            for(int i=0;i<this->numBytes;i++)
            {
                charVector->push_back(this->array[i]);
            }
        }

        int deserialize(int index, _cstr cstr) {
            this->initBytes(cstr.getDs(index));
            index++;

            for(int i=0;i<this->numBytes;i++)
                this->setArray(i, cstr.getDs(index+i));

            index += this->numBytes;
            return index;
        }

        static bool Equals(_bytes a, _bytes b) {
            if (a.numBytes != b.numBytes)
                return false;
            for(int i=0;i<a.numBytes;i++)
                if (a.getArray(i) != b.getArray(i))
                    return false;
            return true;
        }

    private:
        char name;
        bool dealloc = false;
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
        unsigned int get()
        {
            return this->value;
        }

        void serialize(std::vector<char>* charVector)
        {
            if (!wasSet) return;
            charVector->push_back(this->name);
            charVector->push_back(this->value);
        }

        int deserialize(int index, _cstr cstr) {
            this->set(cstr.getDs(index));
            index++;
            return index;
        }

        bool wasSet = false;

        static bool Equals(_soloByte a, _soloByte b) {
            if (a.value != b.value) return false;
            return true;
        }

    private:
        char name;
        char value = 0;
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
        unsigned int get()
        {
            return this->value;
        }

        bool wasSet = false;

        void serialize(std::vector<char> *charVector) {
            if (!wasSet) return;
            charVector->push_back(this->name);
            this->serializeValue(charVector);
        }

        int deserialize(int index, _cstr cstr) {
            this->deserializeValue(cstr.getDs(index), cstr.getDs(index+1)); index+=2;
            return index;
        }

        void serializeValue(std::vector<char> *charVector) {
            char a = (this->value & 0xFF);
            char b = ((this->value >> 8) & 0xFF);
            charVector->push_back(a);
            charVector->push_back(b);
        }

        void deserializeValue(char a, char b) {
            this->set(a | b << 8);
        }

        static bool Equals(_duoByte a, _duoByte b) {
            if (a.value != b.value) return false;
            return true;
        }

    private:
        char name;
        unsigned int value = 0;
    };

    class _pair
    {
    public:
        enum DataType
        {
            SoloByte = 1,
            DuoByte = 2,
        };
        _pair(char name, _pair::DataType a, _pair::DataType b)
        {
            this->name = name;
            this->aType = a;
            this->bType = b;
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

        unsigned int getA()
        {
            return this->valueA;
        }

        unsigned int getB()
        {
            return this->valueB;
        }

        bool wasSet = false;

        void serialize(std::vector<char>* charVector)
        {
            if (!wasSet) return;
            charVector->push_back(this->name);

            charVector->push_back(this->aType);
            if (aType == SoloByte)
            {
                charVector->push_back(this->valueA);
            }
            else
            {
                _duoByte duoA(0);
                duoA.set(this->valueA);
                duoA.serializeValue(charVector);
            }

            charVector->push_back(this->bType);
            if (bType == SoloByte)
            {
                charVector->push_back(this->valueB);
            }
            else
            {
                _duoByte duoB(0);
                duoB.set(this->valueB);
                duoB.serializeValue(charVector);
            }
        }

        int deserialize(int index, _cstr cstr) {
            this->wasSet = true;
            this->aType = static_cast<DataType>(cstr.getDs(index)); index++;
            if (aType == SoloByte)
            {
                this->valueA = cstr.getDs(index); index++;
            }
            else
            {
                _duoByte duoA(0);
                duoA.deserializeValue(cstr.getDs(index), cstr.getDs(index+1)); index+=2;
                this->valueA = duoA.get();
            }


            this->bType = static_cast<DataType>(cstr.getDs(index)); index++;
            if (bType == SoloByte)
            {
                this->valueB = cstr.getDs(index); index++;
            }
            else
            {
                _duoByte duoB(0);
                duoB.deserializeValue(cstr.getDs(index), cstr.getDs(index+1)); index+=2;
                this->valueB = duoB.get();
            }

            return index;
        }

        static bool Equals(_pair a, _pair b) {
            if (a.valueA != b.valueA) return false;
            if (a.valueB != b.valueB) return false;
            return true;
        }

    private:
        char name;
        unsigned int valueA = 0;
        unsigned int valueB = 0;
        DataType aType;
        DataType bType;
    };
}