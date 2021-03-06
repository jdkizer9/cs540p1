//
//  Element.cpp
//  XML Parser
//
//

#include "Element.hpp"
#include "Visitor.hpp"
#include "Node.hpp"
#include "Text.hpp"
#include "Pool.hpp"
#include <iostream>
#include <typeindex>
#include <typeinfo>
#include <assert.h>
#include <new>

namespace xml {
    
    static Pool elementPool(sizeof(Element), 600000);
    
    Element::Element() : definedNSIs(nullptr), cSize(0), cMaxSize(4) {
        children = new const Node *[cMaxSize];
        //children = nullptr;
    }
    
    Element::~Element() {
        //std::cout << "Destructing Element" <<std::endl;
        //needs to destroy all children by removing them from
        //the deque and deleting them
        //Elements are dynamically allocated in processStartTag
//        while( !children.empty() ) {
//            const Node *child = children.back();
//            children.pop_back();
//            delete child;
//        }
        
        while (cSize > 0) {
            const Node *child = children[cSize-1];
            cSize--;
            delete child;
        }
        
//        if (children != nullptr)
//            delete[] children;
        
        delete[] children;
        
        //delete definedNSIs
        //assert(definedNSIs == nullptr);
//        if (definedNSIs != nullptr)
//            delete definedNSIs;        
        
    }
    
    void Element::addChild(const Node *node) {
        //children.push_back(node);
        
//        if (children == nullptr)
//            children = new const Node *[cMaxSize];
        //if array is full, double size and copy existing elements
        //to new array
        if (cSize == cMaxSize) {
            cMaxSize = cMaxSize*2;
            const Node **newChildren = new const Node *[cMaxSize];
            //copy values to new array
            for (size_t i=0; i<cSize; i++) {
                newChildren[i] = children[i];
            }
            //delete old array
            delete[] children;
            //reassign children
            children = newChildren;
        }
        
        //set the cSize-th element to node and increment cSize by 1
        children[cSize] = node;
        cSize++;
    }
    
    const String &Element::name() const {
        return eName;
    }
    
    const String &Element::nmspace() const {
        return URI;
    }
    
    size_t Element::n_children() const {
        //return children.size();
        
        return cSize;
    }
    
    const Node *Element::child(size_t i) const {
//        if (i >= children.size())
//            return nullptr;
//        return children[i];
        
        if (i >= cSize)
            return nullptr;
        return children[i];        
    }
    
    void Element::accept(Visitor *v) const {
        this->handleVisitor(v);        
    }
    
    bool Element::is_Element(const Node *n) {
        return typeid(*n) == typeid(Element);
    }
    
    const Element *Element::to_Element(const Node *n) {
        //assert(typeid(*n) == typeid(Element));
        return (Element*)n;
    }
    
    
    void Element::handleVisitor(Visitor *v) const {
        v->start_element_visit(*this);
        
        for(size_t i=0; i<n_children(); i++)
            child(i)->handleVisitor(v);
        
        v->end_element_visit(*this);      
    }
    
    
    void *Element::operator new(size_t)
    {
        void *p;
        //std::cout << "In overloaded new.";
        //assert( elementPool.checkSize(size));
        p =  elementPool.allocate();
        //p =  malloc(size);
        if(!p)
        {
            throw std::bad_alloc();  //Throw directly than with named temp variable
        }
        return p;
    }
    
    void Element::operator delete(void *p)
    {
        //std::cout << "In overloaded delete.\n";
        elementPool.deallocate(p);
        //free(p);
    }
    
    
    void Element::set_eName(const String &s) {
        eName = s;
    }
    
    void Element::set_nsi(const String &s) {
        nsi = s;
    }
    
    void Element::set_URI(const String &s) {
        URI = s;
    }
    
    void Element::PrintElement() const {
        std::cout << "Element Name: " <<eName<<std::endl;
        std::cout << "NSI: " <<nsi<<std::endl;
        std::cout << "URI: " <<URI<<std::endl;
        std::cout << "Its NSI bindings are as follows:"<<std::endl;
//        for (std::deque<String>::iterator it = definedNSIs->begin(); it!=definedNSIs->end(); ++it)
//            std::cout << *it <<std::endl;
    }
    
}