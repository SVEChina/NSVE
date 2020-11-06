//
// IMISpineListen.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMISpineListen.h"
#include "IMISpine.h"
#include <spine/extension.h>

using namespace imi;

void animationCallback (spAnimationState* state, spEventType type, spTrackEntry* entry, spEvent* event) {
    IMISpine* t_spine = (IMISpine*)state->rendererObject;
    if( t_spine ) {
        t_spine->onAnimationStateEvent(entry->trackIndex , type , event,0);
        //[t_ske_animate onAnimationStateEvent:trackIndex type:type event:event loopCount:loopCount];
    }
}

void trackEntryCallback (spAnimationState* state, spEventType type, spTrackEntry* entry, spEvent* event) {
    IMISpine* t_spine = (IMISpine*)state->rendererObject;
    if( t_spine )
    {
        t_spine->onTrackEntryEvent(entry->trackIndex , type ,event , 0);
        //[t_spine onTrackEntryEvent:trackIndex type:type event:event loopCount:loopCount];
    }
}

_TrackEntryListeners* getListeners (spTrackEntry* entry) {
    if (!entry->rendererObject) {
        entry->rendererObject = NEW(_TrackEntryListeners);
        entry->listener = trackEntryCallback;
    }
    return (_TrackEntryListeners*)entry->rendererObject;
}
//是不是可以不要
//void disposeTrackEntry (spTrackEntry* entry) {
//    if (entry->rendererObject) {
//        _TrackEntryListeners* listeners = (_TrackEntryListeners*)entry->rendererObject;
//        listeners->m_cb_startListener = nullptr;
//        listeners->m_cb_endListener = nullptr;
//        listeners->m_cb_completeListener = nullptr;
//        listeners->m_cb_eventListener = nullptr;
//        FREE(listeners);
//    }
//    _spAnimationState_disposeTrackEntry(entry);
//}
