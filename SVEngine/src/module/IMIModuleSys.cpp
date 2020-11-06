//
// IMIModuleSys.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIModuleSys.h"
#include "IMIModuleBase.h"
#include "../work/IMITdCore.h"

using namespace imi;

IMIModuleSys::IMIModuleSys(IMIInstPtr _app)
:IMISysBase(_app) {
    m_subsysType = 8;
    m_moduleLock = MakeSharedPtr<IMILock>();
}

IMIModuleSys::~IMIModuleSys() {
    m_moduleLock = nullptr;
}

void IMIModuleSys::init() {

}

void IMIModuleSys::destroy() {
    m_moduleLock->lock();
    m_modulePool.clear();
    m_moduleLock->unlock();
}

void IMIModuleSys::update(f32 _dt) {
    m_moduleLock->lock();
    MODULEPOOL::Iterator it = m_modulePool.begin();
    while(it!=m_modulePool.end() && it->data) {
        if( it->data->isOpen() ) {
            it->data->update(_dt);
        }
        it++;
    }
    m_moduleLock->unlock();
}

void IMIModuleSys::regist(IMIModuleBasePtr _module,cptr8 _name) {
    m_moduleLock->lock();
    if (hasRegist(IMIString(_name))) {
        return;
    }
    m_modulePool.append(IMIString(_name),_module);
    m_moduleLock->unlock();
}

void IMIModuleSys::unregist(cptr8 _name) {
    m_moduleLock->lock();
    IMIMap<IMIString, IMIModuleBasePtr>::Iterator it = m_modulePool.find(IMIString(_name));
    if (it != m_modulePool.end()) {
        m_modulePool.remove(_name);
    }
    m_moduleLock->unlock();
}

bool IMIModuleSys::hasRegist(cptr8 _name){
    IMIMap<IMIString, IMIModuleBasePtr>::Iterator it = m_modulePool.find(IMIString(_name));
    if (it != m_modulePool.end()) {
        return true;
    }
    return false;
}

IMIModuleBasePtr IMIModuleSys::getModule(cptr8 _name){
    IMIMap<IMIString, IMIModuleBasePtr>::Iterator it = m_modulePool.find(IMIString(_name));
    if (it != m_modulePool.end()) {
        IMIModuleBasePtr t_module = it->data;
        return t_module;
    }
    return nullptr;
}

bool IMIModuleSys::openModule(cptr8 _name){
    bool t_ret = false;
    m_moduleLock->lock();
    IMIMap<IMIString, IMIModuleBasePtr>::Iterator it = m_modulePool.find(IMIString(_name));
    if (it != m_modulePool.end()) {
        IMIModuleBasePtr t_module = it->data;
        if(t_module){
            t_module->open();
            t_ret = true;
        }
    }
    m_moduleLock->unlock();
    return t_ret;
}

bool IMIModuleSys::closeModule(cptr8 _name) {
    bool t_ret = false;
    m_moduleLock->lock();
    IMIMap<IMIString, IMIModuleBasePtr>::Iterator it = m_modulePool.find(IMIString(_name));
    if (it != m_modulePool.end()) {
        IMIModuleBasePtr t_module = it->data;
        if(t_module){
            t_module->close();
            t_ret = true;
        }
    }
    m_moduleLock->unlock();
    return t_ret;
}
