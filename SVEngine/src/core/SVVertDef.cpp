//
// SVVertDef.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVVertDef.h"

using namespace sv;

std::map<std::string,s32> SVJsonDef::g_vf_name;

std::map<std::string,s32> SVJsonDef::g_sampler_name;

static SVJsonDef g_json_def;

//
SVJsonDef::SVJsonDef() {
    g_vf_name.clear();
    g_vf_name.insert(std::make_pair("E_VF_INDEX",E_VF_INDEX));
    g_vf_name.insert(std::make_pair("E_VF_V2",E_VF_V2));
    g_vf_name.insert(std::make_pair("E_VF_V2_T0",E_VF_V2_T0));
    g_vf_name.insert(std::make_pair("E_VF_V2_T0_T1",E_VF_V2_T0_T1));
    g_vf_name.insert(std::make_pair("E_VF_V2_T0_T1_T2",E_VF_V2_T0_T1_T2));
    g_vf_name.insert(std::make_pair("E_VF_V2_C",E_VF_V2_C));
    g_vf_name.insert(std::make_pair("E_VF_V2_C_T0",E_VF_V2_C_T0));
    g_vf_name.insert(std::make_pair("E_VF_V2_C_T0_T1",E_VF_V2_C_T0_T1));
    g_vf_name.insert(std::make_pair("E_VF_V3",E_VF_V3));
    g_vf_name.insert(std::make_pair("E_VF_V3_T0",E_VF_V3_T0));
    g_vf_name.insert(std::make_pair("E_VF_V3_T0_T1",E_VF_V3_T0_T1));
    g_vf_name.insert(std::make_pair("E_VF_V3_N",E_VF_V3_N));
    g_vf_name.insert(std::make_pair("E_VF_V3_N_T0",E_VF_V3_N_T0));
    g_vf_name.insert(std::make_pair("E_VF_V3_N_T0_T1",E_VF_V3_N_T0_T1));
    g_vf_name.insert(std::make_pair("E_VF_V3_C",E_VF_V3_C));
    g_vf_name.insert(std::make_pair("E_VF_V3_N_C_T0",E_VF_V3_N_C_T0));
    g_vf_name.insert(std::make_pair("E_VF_V3_N_C_T0_T1",E_VF_V3_N_C_T0_T1));
    g_vf_name.insert(std::make_pair("E_VF_V3_N_T0_BONE_W",E_VF_V3_N_T0_BONE_W));
    g_vf_name.insert(std::make_pair("E_VF_V3_N_C_T0_BONE_W",E_VF_V3_N_C_T0_BONE_W));
    g_vf_name.insert(std::make_pair("E_VF_V3_C_BTAG",E_VF_V3_C_BTAG));
    g_vf_name.insert(std::make_pair("E_VF_V3_N_T_T0",E_VF_V3_N_T_T0));
    g_vf_name.insert(std::make_pair("E_VF_V3_PARTICLE",E_VF_V3_PARTICLE));
}

SVJsonDef::~SVJsonDef() {
    clear();
}

void SVJsonDef::clear() {
    g_vf_name.clear();
}
