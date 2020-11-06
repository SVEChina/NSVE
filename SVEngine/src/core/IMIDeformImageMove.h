//
// IMIDeformImageMove.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_DEFORMIMAGEMOVE_H
#define IMI_DEFORMIMAGEMOVE_H

#include "../base/IMIGBase.h"
#include "../base/IMIMap.h"
#include "../core/IMIImageUsingMove.h"
#include "../mtl/IMITexture.h"
#include "../base/IMIArray.h"

namespace imi {
    
        class IMIParamDeform{
        public:
            IMIParamDeform();
            ~IMIParamDeform();
            void reset(){
                m_pointMap.clear();
                m_areaPoint.clear();
            }
            void copy(IMIParamDeformPtr _param){
                m_pointMap=_param->m_pointMap;
                m_areaPoint=_param->m_areaPoint;
            }
            
            void addTagPoint(u32 _postion,V2 _point){
                m_pointMap.append(_postion, _point);
            }
            
            IMIMap<u32, V2> m_pointMap;
            IMIMap<u32,V2> m_areaPoint;
            
        };
        
        //deform imagemove 算法
        class IMIDeformImageMove : public IMIGBaseEx {
        public:
            IMIDeformImageMove(IMIInstPtr _app);
            
            ~IMIDeformImageMove();
            
            void reset();
            
            void init(IMITexturePtr _tex,IMITexturePtr _texout);

            void update(f32 dt);
            
            void render();
            
            void setParam(IMIParamDeformPtr _param){
                m_param->copy(_param);
            }
            
            void setScaleSmooth(f32 _smooth);
            
            void pushScaleCrl(u32 _postion);
            
            void setSmooth(f32 _smooth){
                m_smooth=_smooth;
            }
            
            void clearCrl();
            
            void setTagPoint(u32 _postion,V2 _point);
            
            void setTagAreaPoint(u32 _postion,V2 _point);
            
            void pointMove(V2 *_data);
            
            void setPoint(V2 *_data);
            
            inline void setFlip(bool _flip){
                m_flip=_flip;
            }
            
            inline void setIsDetect(bool _isdetect){
                is_detect=_isdetect;
            }
            
            s32 getWidth();
            
            s32 getHeight();
            
            V2 MSL(V2 point);
            
            void updatePointMSL();
            
            void setDeformSwitch(bool _swith);
            
            void updatePointMesh( V2* _facepoint);
            
            void setvisiPoint(bool _ispoint){
                m_is_point = _ispoint;
            }
            
            virtual void toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator,
                                RAPIDJSON_NAMESPACE::Value &_objValue);
            
            virtual void fromJSON(RAPIDJSON_NAMESPACE::Value &item);
        
        public:
            s32 m_rule;
        
        protected:
            
            void _updateControl(V2 *t_data);
            
            void _updateMesh();
            
            void _refreshScreenRectMesh(V2 *t_data,V2 *t_targetData);
            
            void _initPoint();
            
            IMITexturePtr m_pTexBg;
            IMITexturePtr m_pPointTex;
            IMIMtlCorePtr m_pMtlBg;
            IMIRenderMeshPtr m_pMeshBg;
            IMIRenderMeshPtr m_pMeshPoint;
            IMIImageUsingMovePtr m_pIUMP;
            IMIArray<u32> m_scaleCtlArray;
            IMIPassPtr m_passDeform;
            IMIPassPtr m_passPoint;
            IMIPassPtr m_passBack;
            V2 m_pointScreen[21*41];     //31*81
            IMIParamDeformPtr m_param;
            IMIDeformScalePtr m_deformScale;

            V2 *m_dataPoint;
            s32 m_wPointCount;
            s32 m_hPointCont;
            
            bool is_swith;
            bool m_flip;
            bool m_is_point;
            bool is_detect;
            
            f32 m_smooth;
            f32 m_scaleSmooth;
            s32 m_tt_w;
            s32 m_tt_h;
            s32 m_inw;
            s32 m_inh;
       
        };

    
    
}//!namespace imi

#endif /* IMI_DEFORMIMAGEMOVE_H */
