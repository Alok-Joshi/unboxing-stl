#ifndef UNIQUE_PTR
#define UNIQUE_PTR
#include <utility>

template<typename T>
class unique_ptr {

    private: 
        T *ptr;

        void delete_ptr() {
            delete ptr;
            ptr = nullptr;
        }

    public:

        //Constructors
        unique_ptr(): ptr(nullptr) {}
        unique_ptr(T *ptr): ptr(ptr) {}
        //Move Constructor
        unique_ptr(unique_ptr&& uptr): ptr(std::move(uptr.ptr)) {
            uptr.ptr = nullptr;
        }
    //
        //operators
        unique_ptr& operator=(unique_ptr&& uptr) {
            //Release the ownership of current pointer and free it
            this->delete_ptr();

            //Move ptr
            this->ptr = std::move(uptr.ptr);

            uptr.ptr = nullptr;
            return *this;
        }

        T& operator*() {
            return *ptr;
        }

        T* operator->() {
            return ptr;
        }

        //Destructor
        ~unique_ptr(){
            this->delete_ptr();
        }
        
        //Member functions
        T* get(){
            return this->ptr;
        }

        T* release(){
            T *temp = this->ptr;
            this->ptr = nullptr;
            return temp;
        }
        
        void reset(T *ptr){
            this->delete_ptr(this->ptr);
            this->ptr = ptr;
        }
    
        //deleting copy methods
        unique_ptr(unique_ptr& rhs) = delete;
        unique_ptr& operator=(unique_ptr& rhs) = delete;
};

#endif
