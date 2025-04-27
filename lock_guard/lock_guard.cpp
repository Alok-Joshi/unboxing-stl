#include <mutex>
#include "lock_guard.h"

lock_guard::lock_guard(std::mutex& mutex_ref): m_mutex(mutex_ref) {
    this->m_mutex.lock();
}

lock_guard::~lock_guard(){
    this->m_mutex.unlock();
}
