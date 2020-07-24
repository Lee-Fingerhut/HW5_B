//
//  accumulate.hpp
//  itertools-cfar-a
//
//  Created by Lee Fingerhut on 08/06/2020.
//  Copyright © 2020 Lee Fingerhut. All rights reserved.
//
#pragma once
#include <iostream>
#include <iterator>

using namespace std;

namespace itertools{

    typedef struct {
    template <typename T>
    auto operator()(const T& a , const T& b) const{
        return a + b;
        }
    } _plus;

    template <typename C, typename F = _plus> 
    class accumulate{
        C container;
        F function;

    public:
        accumulate(C c, F f = _plus()) : container(c), function(f) {}

        class iterator {
        protected:
            F function;
            typename C::iterator iter; 
            typename C::iterator last;
            typename decay<decltype(*(container.begin()))>::type data;
            

        public:
            iterator(typename C::iterator first, typename C::iterator l, F fun) : iter(first), last(l), function(fun) {
                if (iter != last) 
                    data = *iter;
            }

            // ++i;
            iterator &operator++(){
                ++iter;
                if (iter != last)
                    data = function(data, *iter);
                return *this;
            }
            // i++;
            iterator operator++(int){
                iterator i = *this;
                ++(*i);
                return i;
            }
            bool operator==(const iterator &other) const{
                return (iter == other.iter);
            }

            bool operator!=(const iterator &other) const{
                return (iter != other.iter);
            }

            auto operator*() const{
                return data;
            }

            iterator &operator=(const iterator &other){
                if  (*this        != other){
                    this->iter     = other.it;
                    this->last     = other.last;
                    this->data     = other.data;
                    this->function = other.function;
                }
                return *this;
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