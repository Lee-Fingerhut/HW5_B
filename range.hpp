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

//מקבל כקלט שני מספרים שלמים, ומייצג את כל המספרים שבין הראשון לאחרון, כולל הראשון ולא כולל האחרון. לדוגמה, range(5,9) מייצג את המספרים 5,6,7,8. 
//ניתן להניח שהפרמטר האחרון גדול או שווה לראשון; אם הפרמטרים שווים אז הטווח ריק.
namespace itertools{
class range{
protected:
    int first_index;
    int last_index;
    
public:
    range(int first, int last) : first_index(first), last_index(last){}

    class iterator{
    int current_number;
        
    public:
        iterator(int current_number) : current_number(current_number) {}
        
        //i++
        iterator& operator++() {
            current_number++;
            return *this;
        }

        //++i
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
        
        iterator& operator=(const iterator &other) {
            if (*this != other) {
                this->current_number = other.current_number;
            }
            return *this;
        }
    };
    iterator begin() const {
        return iterator(first_index);
    }
    
    iterator end() const {
        return iterator(last_index);
    }
};
}
