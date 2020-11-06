//
// IMISpine.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_SPINE_H
#define IMI_SPINE_H

#include "../third/spine4/include/spine/Skeleton.h"
#include "../third/spine4/include/spine/AnimationState.h"
#include "../third/spine4/include/spine/RegionAttachment.h"
#include "IMISpineListen.h"
#include "../mtl/IMITexture.h"
#include "../node/IMINode.h"
#include "../base/IMIArray.h"
#include "../base/imistr.h"

struct spMeshAttachment;

struct spMeshAttachment;

static const u16 quadTriangles[6] = {0, 1, 2, 2, 3, 0};

namespace imi {
    
    class SpineMeshData :public IMIObject{
    public:
        SpineMeshData();
        ~SpineMeshData();
        s32                     m_blendMode;
        s32                     m_indexCount;
        s32                     m_vertexCount;
        IMIRenderMeshPtr         m_pRenderMesh;
        IMIDataSwapPtr           m_pRenderVertex;
        IMIDataSwapPtr           m_pRenderIndex;
        IMIArray<V2_C_T0>        m_aRenderVecData;
        IMIArray<u16>            m_aRenderIndexData;
        IMITexturePtr            m_pTex;
    };
        
    //spine对象
    class IMISpine : public IMIGBaseEx {
    public:
        static IMISpinePtr
        createSpine(IMIInstPtr _app, cptr8 skefname,cptr8 atlasfname, f32 scale = 1.0f, bool enableMipMap = false);
        
        IMISpine(IMIInstPtr _app);
        
        ~IMISpine();
        
        void init(spSkeletonData *skedata, spAtlas *atlas, bool ownsSkeletonData = true);
        
        void setAnimationStateData(spAnimationStateData *stateData);
        
        void getAllAnimationName(IMIArray<IMIString>& _vecName);
        
        cptr8 getAnimationNameByIndex(s32 _index);
        
        spTrackEntry *setAnimationForTrack(s32 trackindex, cptr8 name, bool loop);
        
        spTrackEntry *addAnimationForTrack(s32 trackindex, cptr8 name, bool loop, s32 delay);
        
        void clearTracks();
        
        void clearTrack(s32 trackIndex);
        
        void setMixFrom(cptr8 fromAnimation, cptr8 toAnimation, f32 duration);
        
        spTrackEntry *getCurrentForTrack(s32 trackIndex);
        
        void setToSetupPose();
        
        void setBonesToSetupPose();
        
        void setSlotsToSetupPose();
        
        /* Returns 0 if the bone was not found. */
        spBone *findBone(cptr8 _boneName);
        
        /* Returns 0 if the slot was not found. */
        spSlot *findSlot(cptr8 _slotName);
        
        bool setSkin(cptr8 _skinName);
        
        /* Returns 0 if the slot or attachment was not found. */
        spAttachment *getAttachment(cptr8 _slotName, cptr8 _attachmentName);
        /* Returns false if the slot or attachment was not found. */
        bool setAttachment(cptr8 _slotName, cptr8 _attachmentName);
        
        // --- Convenience methods for common Skeleton_* functions.
        void updateWorldTransform();
        
        void setListenerForEntryByStart(spTrackEntry *entry, spStartListener listener);
        
        void setListenerForEntryByEnd(spTrackEntry *entry, spEndListener listener);
        
        void setListenerForEntryByComp(spTrackEntry *entry, spCompleteListener listener);
        
        void setListenerForEntryByEvent(spTrackEntry *entry, spEventListener listener);
        
        void onAnimationStateEvent(s32 trackIndex, spEventType type, spEvent *event, s32 loopCount);
        
        void onTrackEntryEvent(s32 trackIndex, spEventType type, spEvent *event, s32 loopCount);
        
        void update(f32 deltaTime);
        
        void setAlpha(f32 _alpha);
    protected:
        IMITexturePtr _getTexture(spAttachment *pAttach);
        
        IMITexturePtr _getTextureForRegion(spRegionAttachment *_attachment);
        
        IMITexturePtr _getTextureForMesh(spMeshAttachment *_attachment);
        
    public:
        spAtlas *m_pAtlas;
        
        spAnimationState *m_pSpineAniState;
        
        bool m_preMultAlpha;
        
        bool m_ownsSkeData;
        
        f32 *m_pWorldVerts;
        
        spSkeleton *m_pSkeleton;
        
        spBone *m_pRootBone;
        
        bool m_ownsAniStateData;
        
        f32 m_spineTimeScale;
        
        spStartListener m_cb_startListener;
        
        spEndListener m_cb_endListener;
        
        spCompleteListener m_cb_completeListener;
        
        spEventListener m_cb_eventListener;
        
    public:
        IMIString m_spineName;
        
        IMIString m_spine_json;
        
        IMIString m_spine_atlas;
        
        IMIString m_activeAct;
        
        cptr8 getSpineName();
        
        void setSpineName(cptr8 name);
        
        IMIBoundBox m_aabbBox;
        
        typedef IMIArray<SpineMeshDataPtr> SPINEDATAPOOL;
        SPINEDATAPOOL m_spineDataPool;
        
    protected:
        f32 m_alpha;
        
    public:
        //序列化接口
        void toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator, RAPIDJSON_NAMESPACE::Value &_objValue);
        
        void fromJSON(RAPIDJSON_NAMESPACE::Value &item);
    };
        
    
    
}//!namespace imi



#endif //IMI_SPINE_H
