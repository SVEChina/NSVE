//
// IMIObject.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_OBJECT_H
#define IMI_OBJECT_H

#include "IMIDef.h"
#include "IMIPreDeclare.h"
#include "IMILuaBase.h"

/* c++ 11 标准 sharepter
 * share_ptr是一个模版类
 * share_ptr
 * unique_ptr
 * weak_pter
 * 本质是模版，重载了->和*
 * 转换类型
 * static_point_case<T>(), const_pointer_case<T>(),dynamic_pointer_cast<T>()
 * 创建 make_shared 而不是new
 */

namespace imi {

//对象
class IMIObject : public std::enable_shared_from_this<IMIObject> {
public:
    IMIObject();
    
    virtual ~IMIObject();
    
    std::shared_ptr<IMIObject> shareObject() {
        return shared_from_this();
    }
    
    virtual void listenData(IMIObjectPtr datagen) {};
};

//数据监听函数指针
typedef void (IMIObject::*dataListenFunc)(IMIObjectPtr datagen);

LUA_REG_DECLARE(IMIObject);

}//!namespace imi



#endif //IMI_OBJECT_H
