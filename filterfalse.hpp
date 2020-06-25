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

namespace itertools{
    template<typename F, typename C>
    class filterfalse {
        F function;
        C container;
        
    public:
        filterfalse(F f, C count): function(f), container(count){}

        class iterator{
            typename C::iterator iter;
            typename C::iterator end;
            F function;
        public:
            explicit iterator(typename C::iterator start, typename C::iterator end, F f)
                : iter(start), end(end), function(f){

                while (iter != end && function(*iter))
                    ++iter;
            }

            iterator& operator=(const iterator& other){
                if(this != &other) {
                    this->iter = other.iter;
                    this->end = other.end;
                    this->function = other.function;
                }
                return *this;
            };
            iterator& operator ++(){
                do{
                    ++iter;
                } while (iter != end && function(*iter));
                return *this;
            }
            
            iterator& operator ++(int){
                      iterator temp=*this;
                      ++(*this);
                      return temp;
                  }

            bool operator ==(const iterator& other) const{
                return (iter == other.iter);
            }
            bool operator !=(const iterator& other) const {
                return (iter != other.iter);
            }
            auto operator *(){
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
