

#include <string>
#include <memory>
#include <utility>


class StrVec{

public:
    // constructor, alloc is impilicitly default initialized
    StrVec():elements(nullptr),first_free(nullptr),cap(nullptr) {}
    // copy constructor
    StrVec(const StrVec&);
    // assignment operator overloading
    StrVec& operator=(const StrVec&);
    // destructor
    ~StrVec();
    // other member functions
    void push_back(const std::string&);
    size_t size() const {return first_free-elements;}
    size_t capacity() const {return cap-elements;}
    std::string* begin() const {return elements;}
    std::string* end() const {return first_free;}
    // move constructor
    StrVec(StrVec&&) noexcept;
    // move assignment operator
    StrVec& operator=(StrVec&&) noexcept;
    
    
private:
    // allocator of string type
    std::allocator<std::string> alloc;
    // this function is used by functions that add element to StrVec
    void check_n_alloc() {if (size()==capacity()) reallocate();}
    
    // utility functions used by copy-control
    std::pair<std::string*, std::string*> alloc_n_copy(const std::string*,
                                                       const std::string*);
    void free();   // destroy the elements and free the allocated space
    void reallocate(); // get more space and copy the existing elements

    std::string* elements;  // pointer to the first element in the memory
    std::string* first_free;// pointer to the first free element in the array
    std::string* cap;       // pointer to one past the end of the array
};
