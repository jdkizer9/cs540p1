//
//  Pool.cpp
//  XML Parser
//
//

#include "Pool.hpp"
#include <stdlib.h>
#include <iostream>
#include <assert.h>

static const size_t blockSize = 0x4000;
namespace xml {
    
    //if initObjects
    Pool::Pool(size_t s, size_t initObjects) : headObject(nullptr), headBlock(nullptr), count(0), typeSize(s) {
        //std::cout << "Pool constructor, size="<<typeSize<<std::endl;
        size_t initBlocks;
        
        objectsPerBlock = (blockSize - sizeof(Block *))/typeSize;
        
        if (initObjects > 0) {
            initBlocks = ( initObjects / objectsPerBlock) + 1;
            allocateBlocks (initBlocks);
        }
    }
    
    void Pool::allocateBlocks(size_t numBlocks) {
        
        for (size_t i=0; i<numBlocks; i++) {
            Block *b = (Block *)::operator new(blockSize);
            if(!b)
            {
                throw std::bad_alloc();
            }
            b->next = headBlock;
            headBlock = b;
            
            Object *o = &(b->first);
            for(size_t j=0; j<objectsPerBlock; j++) {
                o->next = headObject;
                headObject = o;
                //convert o to a pointer, then add typesize to it
                o = (Object *)(size_t(o)+typeSize);
            }
            
        }
        
    }
    
    Pool::~Pool() {
        //std::cout << "Pool destructor, size="<<typeSize<<std::endl;
        while (headBlock != nullptr) {
            void *p = headBlock;
            headBlock = headBlock->next;
            //free(p);
            ::operator delete(p);
            //count--;
        }
        //assert(count == 0);
    }
    
    void *Pool::allocate() {
        //std::cout << "Pool allocator, size="<<typeSize<<std::endl;
        //return malloc(typeSize);
        if (headObject == nullptr)
        {
            //assert (count == 0);
            //return malloc(typeSize);
            //return ::operator new(typeSize);
            
            //this means that all our blocks are filled,
            //allocate a new one
            allocateBlocks(1);
            
        } 
            //assert (count > 0);
        void *p = headObject;
        headObject = headObject->next;
            //count--;
        return p;
        
        
    }
    
    void Pool::deallocate(void *p) {
        //std::cout << "Pool deallocator, size="<<typeSize<<std::endl;
        //free(p);
        
        Object *o = (Object *)p;
        o->next = headObject;
        headObject = o;
        //count++;
        
    }

}