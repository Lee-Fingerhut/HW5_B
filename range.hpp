//
//  range.hpp
//  itertools-cfar-a
//
//  Created by Lee Fingerhut on 08/06/2020.
//  Copyright © 2020 Lee Fingerhut. All rights reserved.
//
#pragma once
#include <iostream>
#include <vector>
using namespace std;

namespace itertools{
class range{
protected:
    int first_number;
    int last_number;
    
public:
    range(int start, int end) : first_number(start),last_number(end){}

    class iterator{
    private:
        int current_number;
        
    public:
        iterator(int current_number) : current_number(current_number) {}
        
        iterator& operator++() {
            current_number++;
            return *this;
        }
        
        iterator& operator++(int) {
            ++current_number;
            return *this;
        }
        
        bool operator==(const iterator &other) const {
            return current_number == other.current_number;
        }
        
        bool operator!=(const iterator &other) const {
            return current_number != other.current_number;
        }
        
        int operator*() {
            return current_number;
        }
        
        iterator &operator=(const iterator &other) {
            if (*this != other) {
                this->current_number = other.current_number;
            }
            return *this;
        }
    };
    iterator begin() const {
        return iterator(first_number);
    }
    
    iterator end() const {
        return iterator(last_number);
    }
};
}
