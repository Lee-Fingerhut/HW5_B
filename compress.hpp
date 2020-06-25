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

namespace itertools {
template<typename C , typename B> class compress {
    C container;
    B bool_container;
    
public:
    explicit compress (C container, B bool_container) : container(container), bool_container(bool_container) {}
    
    class iterator{
        typename C:: iterator iter;
        typename C:: iterator end;
        typename B:: iterator bool_iter;
    public:
        iterator(typename C::iterator start,  typename C::iterator last,  typename B::iterator bool_it) : iter(start), end(last), bool_iter(bool_it) {
            while( iter != end &&!(*bool_iter)){
                ++iter;
                ++bool_iter;
            }
        }
    
        bool operator == (const iterator& other) {
            return (iter==other.iter);
        }
        
        bool operator != (const iterator& other) {
            return (iter != other.iter);
        }
        
        iterator& operator = (const iterator& other) {
            if (*this != other){
                this->iter       = other.iter;
                this->end        = other.end;
                this->bool_iter  = other.bool_iter;
            }
            return *this;
        }
        
        iterator& operator ++() {
            ++iter;
            ++bool_iter;
            while(iter  != end && !(*bool_iter)) {
                ++iter;
                ++bool_iter;
            }
            return *this;
        }
        
        iterator& operator ++(int) {
            iterator temp=*this;
            ++(*this);
            return temp;
        }
        
        auto operator*() {
            return *iter;
        }
    };
    iterator begin() {
        return iterator(container.begin(),container.end(),bool_container.begin());
    }
    iterator end() {
        return iterator(container.end(),container.end(),bool_container.end());
    };
};
}
