//
// IMIParseParticles.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIParseParticles.h"
#include "../node/IMIParticlesNode.h"

using namespace imi;

IMINodePtr
IMIParseParticles::parseParticles(IMIInstPtr _app, RAPIDJSON_NAMESPACE::Value &item, s32 _resid, cptr8 _path) {
    IMIParticlesNodePtr t_particlesNode = MakeSharedPtr<IMIParticlesNode>(_app);
    t_particlesNode->m_rootPath = _path;
    t_particlesNode->fromJSON(item);
    return t_particlesNode;
}


