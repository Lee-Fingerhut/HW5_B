//
//  accumulate.hpp
//  itertools-cfar-a
//
//  Created by Lee Fingerhut on 08/06/2020.
//  Copyright © 2020 Lee Fingerhut. All rights reserved.
//
#pragma once
#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

typedef struct {
    template <typename S>
    auto operator()(const S& a , const S& b) const{
        return a + b;
    }
} _plus;

namespace itertools{
template<class C,class F = _plus>
class accumulate{
    const C& container;
    const F& function;
public:
    accumulate(const C& c, const F& f = _plus()) : container(c), function(f){}
    
    class iterator {
        const accumulate& a;
        decltype(container.begin()) iter;
        typename std::decay<decltype(*(container.begin()))>::type data;
        
    public:
        
        iterator(const accumulate& a, decltype(container.begin()) i)
        : a(a), iter(i){
            if (iter != a.container.end())
                data = *iter;
        }
        
        auto operator*() const {
            return data;
        }
        iterator& operator++() {
            ++iter;
            if(iter != a.container.end())
                data = a.function(data,*(iter));
            return *this;
        }
        
        const iterator operator++(int) {
            iterator temp = *this;
            if(iter != a.container.end())
                data = a.function(data,*(iter));
            return *temp;
        }
        
        bool operator==(const iterator& iterator) const {
            return iterator.iter==iter;
        }
        
        bool operator!=(const iterator& iterator) const {
            return iterator.iter!=iter;
        }
    };
    
    iterator begin() const {
        return iterator(*this,container.begin());
    }
    
    iterator end() const {
        return iterator(*this, container.end());
    }
};
}
