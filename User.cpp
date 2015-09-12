

#include "StrVec.h"
#include <utility>


// global StrVec object
StrVec s_vec_g;

// this function reurns an rvalue, so it can be used in
// move operators
StrVec func() { return s_vec_g;}


int main(){
    
    StrVec s1_vec;
    s1_vec.push_back("Alireza");
    s1_vec.push_back("safdar gholi");
    
    // copy constructor used
    StrVec s2_vec(s1_vec);
    
    StrVec s3_vec;
    // copy assignment used
    s3_vec = s1_vec;
    
    StrVec s4_vec;
    // move assignment used
    s4_vec = func();
    
    // move constructor used
    StrVec s5_vec(std::move(s3_vec));
        
    return 0;
}

