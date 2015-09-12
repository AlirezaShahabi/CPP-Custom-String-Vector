
#include <iostream>
#include "StrVec.h"


// copy constructor
StrVec::StrVec(const StrVec& obj){
    // newdata is a pair containing beginning and end of filled data
    auto newdata = alloc_n_copy(obj.begin(), obj.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
    std::cout << "COPY constructor used" << std::endl;
}


// copy assignment operator (does the job of copy constructor and destructor)
StrVec& StrVec::operator=(const StrVec& obj){
    auto newdata = alloc_n_copy(obj.begin(), obj.end());
    free();
    elements   = newdata.first;
    first_free = cap = newdata.second;
    std::cout << "COPY assignment operator used" << std::endl;
    return *this;
}


// destructor
StrVec::~StrVec() {free();}


// move constructor: we do not need to allocate any new memory since we steal 
// the resources from the 'obj'. It's important to make the obj ready for destruc
StrVec::StrVec(StrVec&& obj) noexcept : elements(obj.elements),
                                        first_free(obj.first_free),cap(obj.cap){
    obj.elements = obj.first_free = obj.cap = nullptr;
    std::cout << "MOVE constructor used" << std::endl;
}


// move assignment operator (does the job of move constructor and destructor)
StrVec& StrVec::operator=(StrVec&& obj) noexcept {
    if (this != &obj){ // important
        free();
        elements   = obj.elements;
        first_free = obj.first_free;
        cap        = obj.cap;
        obj.elements = obj.first_free = obj.cap = nullptr;
    }
    std::cout << "MOVE assignment operator used" << std::endl;
    return *this;
}


void StrVec::push_back(const std::string& s){
    // first check if there is enough space and then construct
    check_n_alloc();
    alloc.construct(first_free++, s);
}


std::pair<std::string*, std::string*> StrVec::alloc_n_copy(const std::string* b,
                                                           const std::string* e){
    // allocate space to hold as many elements as defined by range: b,e
    auto data = alloc.allocate(e-b); // data points to the begining
    // construct the data and return a pair: <begining, 1 pass the end>
    return {data,std::uninitialized_copy(b, e, data)};
}


void StrVec::free(){
    // if elements is not nullptr, first destroy and then deallocate
    if (elements){
        for (auto p = first_free; p != elements; ) {alloc.destroy(--p);}
        alloc.deallocate(elements, cap-elements);
    }
    // after deallocation, the three pointers don't have any resources
    // they will be destroyed when they go out of scope
}


// call reallocate() if there is no free space
void StrVec::reallocate(){
    auto newcapacity = size() ? 2*size() : 1;
    // allocate the new memory
    auto newdata = alloc.allocate(newcapacity);
    auto dest = newdata; 
    // points to the next element in the old array
    auto elem = elements;
    for (size_t i = 0; i != size(); ++i){
        // construct the alloc by moving data from old memory
        alloc.construct(dest++, std::move(*elem++));
    }
    // free the old space once we've moved the elements 
    free(); 
    // update our data structure to point to the new elements
    elements   = newdata;
    first_free = dest;
    cap = elements + newcapacity;
}


// this is another version of reallocate that uses move iterators

// make_move_iterator takes an ordinary iterator and returns a move
// iterator if we are to use move iterator, we must make sure the moved
// from object will not be used later
/*
void StrVec::reallocate(){
    newcapacity = elements ? 2*size() : 1;
    auto new_first = alloc.allocate(newcapacity);
    std::uninitialized_copy(make_move_iterator(begin()),
                            make_move_iterator(end()), new_first);
    free();
    elements   = newdata;
    first_free = dest;
    cap = elements + newcapacity;
}
*/
