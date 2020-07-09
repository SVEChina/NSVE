//
// SVFboObject.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_FBOOBJECT_H
#define SV_FBOOBJECT_H

#include "SVRRes.h"
#include "SVRFbo.h"
#include "SVRenderDef.h"
#include "../base/SVColor.h"
#include "../base/SVMat4.h"

namespace sv {
        
        class SVFboObject : public SVRRes {
        public:
            SVFboObject(SVInstPtr _app);
            
            virtual ~SVFboObject();
            
            virtual void create(SVRendererPtr _renderer);
            
            virtual void destroy(SVRendererPtr _renderer);
            
            virtual void refresh();
            
            virtual void bind();
            
            virtual void clear();
            
            virtual void unbind();
            
            u32 getFboID();
            
            u32 getWidth();
            
            u32 getHeight();
            
            bool hasDepth();
            
            bool hasStencil();
            
            void setProjMat(FMat4 _mat);
            
            void setViewMat(FMat4 _view);
            
            void setLink(bool _link);
            
        protected:
            FMat4 m_mat_proj;
            FMat4 m_mat_view;
            FMat4 m_mat_vp;
            bool m_link;
            SVRFboPtr m_objFBOPtr;
        };

}//!namespace sv



#endif //SV_FBOOBJECT_H
