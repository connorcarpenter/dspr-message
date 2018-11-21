#pragma once

#include <vector>
#include <assert.h>

namespace DsprMessage
{
    class _charVector
    {
    public:
        _charVector()
        {
            this->theVector = new std::vector<unsigned char>();
        }
        ~_charVector()
        {
            delete this->theVector;
        }
        int size() {return theVector->size();}
        unsigned char at(int i) {return theVector->at(i);}

        void push_back(unsigned char c)
        {
            theVector->push_back(c);
        }
        void push_back(unsigned int i)
        {
            assert(i < 255);
            theVector->push_back((unsigned char) i);
        }

        void push_back(long unsigned int i)
        {
            assert(i < 255);
            theVector->push_back((unsigned char) i);
        }
        template <class T>
        void push_back(T) = delete; //this enforces that no implicit casts happen
    private:
        std::vector<unsigned char>* theVector = nullptr;
    };

    class _cstr
    {
    public:
        _cstr(unsigned char* innerCstr, unsigned int number, bool dealloc = false)
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

        static _cstr fromVector(_charVector* pVector) {
            auto cvSize = pVector->size();
            auto cstr = new unsigned char[cvSize+1];
            for(int i=0;i<cvSize;i++)
            {
                cstr[i] = pVector->at(i)+1;
            }
            cstr[cvSize] = '\0';
            delete pVector;
            return _cstr(cstr, cvSize);
        }

        bool dealloc;

        unsigned char getDs(unsigned char index) {
            return this->innerCstr[index]-1;
        }

        unsigned char *innerCstr = nullptr;
    };

    class _number
    {
    public:
        _number(unsigned char name)
        {
            this->name = name;
        }

        void set(unsigned char value)
        {
            this->dataSize = 1;
            this->value = value;
            this->wasSet = true;
        }

        void set(unsigned int value)
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

        void set(int value)
        {
            assert(value>=0);
            this->set((unsigned int) value);
        }

        void set(bool value)
        {
            this->dataSize=1;
            this->value = (unsigned char) value;
            this->wasSet = true;
        }

        template <class T>
        void set(T) = delete; //this enforces that no implicit casts happen

        unsigned int get()
        {
            return this->value;
        }

        bool wasSet = false;

        void serialize(_charVector* charVector) {
            if (!wasSet) return;
            charVector->push_back(this->name);
            charVector->push_back(this->dataSize);
            for (int i=0;i<this->dataSize;i++)
            {
                unsigned char c = ((this->value >> (8*i)) & 0xFF);
                charVector->push_back(c);
            }
        }

        int deserialize(int index, _cstr cstr) {
            this->dataSize = cstr.getDs(index);index+=1;
            unsigned int val = 0;
            for(int i = 0;i<this->dataSize;i++)
            {
                val |= (cstr.getDs(index+i) << (8*i));
            }
            index += this->dataSize;
            this->set(val);
            return index;
        }

        static bool Equals(_number a, _number b) {
            if (a.value != b.value) return false;
            return true;
        }

    private:
        unsigned char name;
        unsigned int value = 0;
        unsigned int dataSize = 0;
    };

    class _array
    {
    public:
        _array(unsigned char name)
        {
            this->name = name;
        }

        ~_array()
        {
            if (this->cstr != nullptr)
                delete [] this->cstr;
        }

        void add(unsigned char value)
        {
            checkForDataSize(value);
            this->contents.push_back(value);
            this->wasSet = true;
            contentsHaveChanged = true;
        }

        void add(unsigned int value)
        {
            checkForDataSize(value);
            this->contents.push_back(value);
            this->wasSet = true;
            contentsHaveChanged = true;
        }

        void add(int value)
        {
            assert(value >= 0);
            this->add((unsigned int) value);
        }

        void checkForDataSize(unsigned int value)
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

        template <class T>
        void add(T) = delete; //this enforces that no implicit casts happen

        unsigned int get(unsigned int i)
        {
            return this->contents.at(i);
        }

        bool wasSet = false;

        void serialize(_charVector* charVector) {
            if (!wasSet) return;
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

        int deserialize(int index, _cstr cstr) {
            this->dataSize = cstr.getDs(index);index+=1;
            unsigned int numberElements = cstr.getDs(index);index+=1;
            for (int j=0;j<numberElements;j++)
            {
                unsigned int val = 0;
                for (int i = 0; i < this->dataSize; i++)
                {
                    val |= (cstr.getDs(index + i) << (8 * i));
                }
                index += this->dataSize;
                this->contents.push_back(val);
            }
            contentsHaveChanged = true;
            wasSet = true;
            return index;
        }

        static bool Equals(_array a, _array b) {
            if (a.dataSize != b.dataSize) return false;
            if (a.contents.size() != b.contents.size()) return false;
            for (int i=0;i<a.contents.size();i++)
            {
                if (a.contents.at(i) != b.contents.at(i)) return false;
            }
            return true;
        }

        _cstr getCstr()
        {
            assert(dataSize == 1);
            if (contentsHaveChanged)
                updateCstr();
            return _cstr(cstr, this->contents.size());
        }

        void setCstr(_cstr cstr)
        {
            for (int i=0;i<cstr.number;i++)
            {
                this->add(cstr.innerCstr[i]);
            }
            this->wasSet = true;
        }

        void updateCstr(){
            if (this->cstr != nullptr)
                delete [] this->cstr;
            this->cstr = new unsigned char[this->contents.size()];
            for (int i=0;i<this->contents.size();i++)
            {
                cstr[i] = this->contents.at(i);
            }
            contentsHaveChanged = false;
        }

        unsigned int size()
        {
            return contents.size();
        }

    private:
        unsigned char name;
        unsigned int dataSize = 1;
        std::vector<unsigned int> contents;
        bool contentsHaveChanged = true;
        unsigned char* cstr = nullptr;
    };
}