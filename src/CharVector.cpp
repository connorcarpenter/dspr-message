//
// Created by connor on 11/21/18.
//

#include "CharVector.h"
#include "Main.h"

namespace DsprMessage {

    CharVector::~CharVector() {
        delete this->theVector;
    }

    int CharVector::size() { return theVector->size(); }

    unsigned char CharVector::at(int i) { return theVector->at(i); }

    void CharVector::push_back(unsigned char c) {
        theVector->push_back(c);
    }

    void CharVector::push_back(unsigned int i) {
        assert(i < DsprMessage::MaxByteValue);
        theVector->push_back((unsigned char) i);
    }

    void CharVector::push_back(long unsigned int i) {
        assert(i < DsprMessage::MaxByteValue);
        theVector->push_back((unsigned char) i);
    }

    CharVector::CharVector() {
        this->theVector = new std::vector<unsigned char>();
    }

    void CharVector::addAt(unsigned int amount, unsigned int index) {
        theVector->at(index) += amount;
    }
}