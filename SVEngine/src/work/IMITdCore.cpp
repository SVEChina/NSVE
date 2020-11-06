#include "IMITdCore.h"
#include <fcntl.h>
#include <cerrno>

using namespace imi;

IMILockSpin::IMILockSpin(){
}

IMILockSpin::~IMILockSpin(){
}

void IMILockSpin::lock() {
    //IMI_LOG_INFO("IMILockSpin lock \n!");
    while (mflag.test_and_set());
}

void IMILockSpin::unlock() {
    //IMI_LOG_INFO("IMILockSpin unlock \n!");
    mflag.clear();
}

//
IMILock::IMILock(){
    pthread_mutex_init(&mutex, nullptr);
}

IMILock::~IMILock(){
    pthread_mutex_destroy(&mutex);
}

void IMILock::lock() {
    pthread_mutex_lock(&mutex);
}

void IMILock::unlock() {
    //IMI_LOG_INFO("IMILock unlock \n!");
    pthread_mutex_unlock(&mutex);
}

s32 IMILock::trylock() {
    return pthread_mutex_trylock(&mutex);
}


//
IMICond::IMICond(){
    pthread_mutex_init(&m_mutex, nullptr);
    pthread_cond_init(&m_cond, nullptr);
}

IMICond::~IMICond(){
    pthread_cond_destroy(&m_cond);
    pthread_mutex_destroy(&m_mutex);
}

s32 IMICond::trylock() {
    return pthread_mutex_trylock(&m_mutex);
}

void IMICond::lock(){
     pthread_mutex_lock(&m_mutex);
}

void IMICond::unlock(){
    pthread_mutex_unlock(&m_mutex);
}

void IMICond::wait(){
    pthread_cond_wait(&m_cond, &m_mutex);
}

void IMICond::notice(){
    pthread_cond_signal(&m_cond);
}

void IMICond::broad() {
    pthread_cond_broadcast(&m_cond);
}


//
IMISem::IMISem(s32 _resvalue){
    sem_init(&psem, 0, _resvalue);
}

IMISem::~IMISem(){
    sem_destroy(&psem);
}

void IMISem::wait(){
    sem_wait(&psem);
}

void IMISem::post(){
    sem_post(&psem);
}

void IMISem::lastcheck() {
    s32 t_value = 0;
    sem_getvalue(&psem, &t_value);
    if(t_value == -1) {
        post();
    }
}
