//
//  filterfalse.hpp
//  itertools-cfar-a
//
//  Created by Lee Fingerhut on 08/06/2020.
//  Copyright © 2020 Lee Fingerhut. All rights reserved.
//
#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

//מקבל כקלט שני פרמטרים: הראשון הוא פונקטור בוליאני המייצג תנאי,
// והשני הוא מיכל או דמוי-מיכל. מחזיר דמוי-מיכל חדש, 
//הכולל רק את האיברים בדמוי-המיכל הנתון, שאינם מקיימים את התנאי

namespace itertools{
    template<typename F, typename C>
    class filterfalse {
        F function;
        C container;
        
    public:
        explicit filterfalse(F f, C count): function(f), container(count){}

        class iterator{
            F function;
            typename C::iterator iter;
            typename C::iterator last;

        public:
            explicit iterator(typename C::iterator first, typename C::iterator last, F f)
                : iter(first), last(last), function(f){
                while (iter != last && function(*iter))
                    ++iter;
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
                this->function   = other.function;
            }
            return *this;
        }
        //i++
        iterator& operator ++() {
            do{
                ++iter;
        } while (iter != last && function(*iter));
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

    iterator begin(){
        return iterator(container.begin(), container.end(), function);
    }
    iterator end(){
        return iterator(container.end(), container.end(), function);
    }
    };
}
