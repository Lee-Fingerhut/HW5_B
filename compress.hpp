//
//  compress.hpp
//  itertools-cfar-a
//
//  Created by Lee Fingerhut on 08/06/2020.
//  Copyright © 2020 Lee Fingerhut. All rights reserved.
//
#pragma once
#include <iostream>
#include <string>

using namespace std;

//מקבל כקלט שני מיכלים או דמויי-מיכלים, שחייבים להיות באותו אורך. הראשון כולל עצמים מסוג כלשהו, והשני חייב לכלול עצמים מסוג בוליאני.
// מחזיר דמוי-מיכל חדש שבו מופיעים איברים מהדמוי-מיכל הראשון, שהאיבר המתאים להם בדמוי-מיכל השני הוא true. לדוגמה, הביטוי compress(range(5,9),vector({true,true,false,true})) מייצג את המספרים 5, 6, 8;
//compress(string("abcd"),vector({true,true,false,true})) מייצג את האותיות a, b, d.
namespace itertools {
template<typename C , typename B> class compress {
    C container;
    B bool_container;
    
public:
    explicit compress (C container, B bool_container) : container(container), bool_container(bool_container) {}
    
    class iterator{
        typename C:: iterator iter;
        typename C:: iterator last;
        typename B:: iterator bool_iter;
    public:
        iterator(typename C::iterator first,  typename C::iterator last,  typename B::iterator bool_it) : iter(first), last(last), bool_iter(bool_it) {
            while( iter != last &&!(*bool_iter)){//boolean is false
                ++iter;
                ++bool_iter;
            }
        }
    
        bool operator==(const iterator &other) const {
            return (iter==other.iter);
        }
        
        bool operator!=(const iterator &other) const{
            return (iter != other.iter);
        }
        
        iterator& operator = (const iterator& other) {
            if (*this!= other){
                this->iter       = other.iter;
                this->last       = other.last;
                this->bool_iter  = other.bool_iter;
            }
            return *this;
        }
        //i++
        iterator& operator ++() {
            ++iter;
            ++bool_iter;
            while(iter!=last && !(*bool_iter)) {
                ++iter;
                ++bool_iter;
            }
            return *this;
        }

        //++i
        iterator operator ++(int) {
            iterator temp=*this;
            ++(*this);
            return temp;
        }
        
        auto operator*() {
            return *iter;
        }
    };
    iterator begin() {
        return iterator(container.begin() ,container.end() ,bool_container.begin());
    }
    iterator end() {
        return iterator(container.end(),container.end(), bool_container.end());
    };
};
}
