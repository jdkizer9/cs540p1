//
//  Pool.cpp
//  XML Parser
//
//

#include "Pool.hpp"
#include <stdlib.h>
#include <iostream>
#include <assert.h>

namespace xml {
    
    Pool::Pool(size_t s) : head(nullptr), count(0), typeSize(s) {
        //std::cout << "Pool constructor, size="<<typeSize<<std::endl;
    }
    
    Pool::~Pool() {
        //std::cout << "Pool destructor, size="<<typeSize<<std::endl;
        while (head != nullptr) {
            void *p = head;
            head = head->next;
            free(p);
            //count--;
        }
        //assert(count == 0);
    }
    
    void *Pool::allocate() {
        //std::cout << "Pool allocator, size="<<typeSize<<std::endl;
        //return malloc(typeSize);
        if (head == nullptr)
        {
            //assert (count == 0);
            return malloc(typeSize);
        } else {
            //assert (count > 0);
            void *p = head;
            head = head->next;
            //count--;
            return p;
        }
        
    }
    
    void Pool::deallocate(void *p) {
        //std::cout << "Pool deallocator, size="<<typeSize<<std::endl;
        //free(p);
        
        Object *o = (Object *)p;
        o->next = head;
        head = o;
        //count++;
        
    }

}