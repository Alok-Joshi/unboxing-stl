#ifndef LOCK_GUARD
#define LOCK_GUARD

#include <mutex>

class lock_guard {

    private: 
    std::mutex& m_mutex;
    
    public:
    lock_guard(std::mutex& mutex_ref);
    ~lock_guard();

    //no copying
    lock_guard(lock_guard& lg) = delete;
    lock_guard& operator=(lock_guard& lg) = delete;

    //no moving
    lock_guard(lock_guard&& lg) = delete;
    lock_guard& operator=(lock_guard&& lg) = delete;

};

#endif
