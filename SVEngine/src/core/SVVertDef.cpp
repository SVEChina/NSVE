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
    //
    g_vf_name.insert(std::make_pair("E_NULL",SV_SMT_NULL));
    g_vf_name.insert(std::make_pair("E_INDEX",SV_SMT_INDEX));
    g_vf_name.insert(std::make_pair("E_V2",SV_SMT_V2));
    g_vf_name.insert(std::make_pair("E_V3",SV_SMT_V3));
    g_vf_name.insert(std::make_pair("E_NOR",SV_SMT_NOR));
    g_vf_name.insert(std::make_pair("E_TAG",SV_SMT_TAG));
    g_vf_name.insert(std::make_pair("E_BTAG",SV_SMT_BTAG));
    g_vf_name.insert(std::make_pair("E_C0",SV_SMT_C0));
    g_vf_name.insert(std::make_pair("E_C1",SV_SMT_C1));
    g_vf_name.insert(std::make_pair("E_C2",SV_SMT_C2));
    g_vf_name.insert(std::make_pair("E_C3",SV_SMT_C3));
    g_vf_name.insert(std::make_pair("E_T0",SV_SMT_T0));
    g_vf_name.insert(std::make_pair("E_T1",SV_SMT_T1));
    g_vf_name.insert(std::make_pair("E_T2",SV_SMT_T2));
    g_vf_name.insert(std::make_pair("E_T3",SV_SMT_T3));
    g_vf_name.insert(std::make_pair("E_BONE",SV_SMT_BONE));
    g_vf_name.insert(std::make_pair("E_BONEW",SV_SMT_BONE_W));
    g_vf_name.insert(std::make_pair("E_PAETICLE",SV_SMT_PARTICLE));
    g_vf_name.insert(std::make_pair("E_INST",SV_SMT_INSOFFSET));
    //
    g_sampler_name.clear();
    g_sampler_name.insert(std::make_pair("SV_P_FILTER_MAG",SV_P_FILTER_MAG));
    g_sampler_name.insert(std::make_pair("SV_P_FILTER_MIN",SV_P_FILTER_MIN));
    g_sampler_name.insert(std::make_pair("SV_V_FILTER_NEAREST",SV_V_FILTER_NEAREST));
    g_sampler_name.insert(std::make_pair("SV_V_FILTER_LINEAR",SV_V_FILTER_LINEAR));
    g_sampler_name.insert(std::make_pair("SV_P_WRAP_S",SV_P_WRAP_S));
    g_sampler_name.insert(std::make_pair("SV_P_WRAP_T",SV_P_WRAP_T));
    g_sampler_name.insert(std::make_pair("SV_V_WRAP_CLAMP",SV_V_WRAP_CLAMP));
    g_sampler_name.insert(std::make_pair("SV_V_WRAP_BORDER",SV_V_WRAP_BORDER));
    g_sampler_name.insert(std::make_pair("SV_V_WRAP_REPEAT",SV_V_WRAP_REPEAT));
    g_sampler_name.insert(std::make_pair("SV_V_WRAP_MIRROR",SV_V_WRAP_MIRROR));
    g_sampler_name.insert(std::make_pair("SV_V_WRAP_BLACK",SV_V_WRAP_BLACK));
    g_sampler_name.insert(std::make_pair("SV_V_WRAP_WHITE",SV_V_WRAP_WHITE));
}

SVJsonDef::~SVJsonDef() {
    clear();
}

void SVJsonDef::clear() {
    g_vf_name.clear();
}
