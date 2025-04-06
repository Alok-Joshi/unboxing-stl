#ifndef SHARED_PTR
#define SHARED_PTR

#include <stdint.h>
#include <atomic>

struct control_block {

    std::atomic<uint64_t> ref_count;
    control_block() {
        ref_count = 0;
    }
};

template <typename T>
class shared_ptr {

    private:
        T *ptr;
        control_block *cb;

    public:
        //Constructors
        shared_ptr(): ptr(nullptr), cb(nullptr) {}
        shared_ptr(T *ptr): ptr(ptr){
            cb = new control_block();
            this->cb->ref_count++;
        }
        //Copy constructors
        shared_ptr(const shared_ptr &sptr) {
            this->ptr = sptr.ptr;
            this->cb = sptr.cb;

            //Increase ref count
            this->cb->ref_count++;
        }

        //Move constructor
        shared_ptr(shared_ptr&& sptr): ptr(std::move(sptr.ptr)), cb(std::move(sptr.cb)) {
            sptr.ptr = nullptr;
            sptr.cb = nullptr;
        }


        //Operators
        shared_ptr& operator=(const shared_ptr& sptr) {
            this->ptr = sptr->ptr;
            this->cb = sptr->cb;
            
            //Increase ref count
            this->cb->ref_count++;
        }

        shared_ptr& operator=(shared_ptr&& sptr) {
            this->ptr = std::move(sptr.ptr);
            this->cb = std::move(sptr.cb);

            sptr->ptr = nullptr;
            sptr->cb = nullptr;
        }

        T& operator*() {
            return *ptr;
        }

        T* operator->() {
            return ptr;
        }

        //Member function
        T* get(){
            return ptr;
        }

        uint64_t get_ref_count(){
            return this->cb->ref_count;
        }

        //Destructor
        ~shared_ptr(){
            if(this->cb){ //Check to make sure we avoid cleanup for moved from shared_ptr
                this->cb->ref_count--;
                if(this->cb->ref_count == 0){
                    delete ptr;
                    delete cb;
                }
            }
        }
};

#endif
