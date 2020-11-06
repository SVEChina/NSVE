//
// IMIFaceBeautyFilter.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_FACEBEAUTYFILTER_H
#define IMI_FACEBEAUTYFILTER_H


#include "IMIFilterBase.h"
#include "../mtl/IMIMtlDeclare.h"
#include "../node/IMINodeDeclare.h"

namespace imi {

    class IMIGenFBParam : public IMIObject {
        public :
        
        IMIGenFBParam(){
            reset();
        };
        
        f32 m_smooth;
        f32 m_param01;
        f32 m_param02;
        f32 m_param03;
        f32 m_param04;
        f32 m_param05;
        f32 m_param06;
        
        void reset(){
             m_smooth = 0.0;
             m_param01 = 0.0;
             m_param02 = 0.0;
             m_param03 = 0.0;
             m_param04 = 0.0;
             m_param05 = 0.0;
             m_param06 = 0.0;
        }
        
        void copy(IMIGenFBParamPtr _p){
             m_smooth = _p->m_smooth;
             m_param01 = _p->m_param01;
             m_param02 = _p->m_param02;
             m_param03 = _p->m_param03;
             m_param04 = _p->m_param04;
             m_param05 = _p->m_param05;
             m_param06 = _p->m_param06;
        }
        
    };
    
    class IMIFaceBeautyBase  : public IMIFilterBase{
    public:
        IMIFaceBeautyBase(IMIInstPtr _app);
        
        ~IMIFaceBeautyBase();
        
        virtual bool create();
        
        virtual void destroy();
        
        virtual void update(f32 dt);
        
        virtual void refreshData(IMIGenFBParamPtr _param);
        
        //序列化
        virtual void toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator,
                            RAPIDJSON_NAMESPACE::Value &_objValue);
        
        virtual void fromJSON(RAPIDJSON_NAMESPACE::Value &item);
        
        void setSmooth(f32 _smooth);
        
        void setParam01(f32 _smooth);
        
        void setParam02(f32 _smooth);
        
        void setParam03(f32 _smooth);
        
        void setParam04(f32 _smooth);
        
        void setParam05(f32 _smooth);
        
        void setParam06(f32 _smooth);
        
    protected:
        
        IMIGenFBParamPtr m_pParam;
        
    };
    
    class IMIFairDataBlur : public IMIFaceBeautyBase {
    public:
        IMIFairDataBlur(IMIInstPtr _app);
        
        ~IMIFairDataBlur();
        
        virtual bool create();
        
        virtual void destroy();
        
        virtual void update(f32 dt);
        
        //序列化
        virtual void toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator,
                            RAPIDJSON_NAMESPACE::Value &_objValue);
        
        virtual void fromJSON(RAPIDJSON_NAMESPACE::Value &item);
        
        IMIMtlCorePtr m_mtl_a;
        IMIMtlCorePtr m_mtl_b;
        IMIMtlCorePtr m_mtl_c;
        IMIMtlBlurFairPtr m_mtl_d;
        IMIMtlCorePtr m_mtl_e;
        IMIMtlCorePtr m_mtl_f;
        IMIMtlCorePtr m_mtl_back;
        
    };
    
    class IMIFairLtraLow : public IMIFilterBase {
    public:
        IMIFairLtraLow(IMIInstPtr _app);
        
        ~IMIFairLtraLow();
        
        virtual  bool create();
        
        virtual void destroy();
        
        virtual  void update(f32 dt);
        
        IMIMtlCorePtr m_mtl_a;
        
        IMIMtlCorePtr m_mtl_back;

        
        inline void setSmooth(f32 _smooth) {
            m_smooth = _smooth;
        }
        
        inline f32 getSmooth() {
           return m_smooth;
        }
        
    protected:
        f32 m_smooth;
        
    };
    
}

#endif /* IMI_FACEBEAUTYFILTER_H */
