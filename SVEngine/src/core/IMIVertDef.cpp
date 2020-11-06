//
// IMIVertDef.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIVertDef.h"

using namespace imi;

std::map<std::string,s32> IMIJsonDef::g_vf_name;

std::map<std::string,s32> IMIJsonDef::g_sampler_name;

static IMIJsonDef g_json_def;

//
IMIJsonDef::IMIJsonDef() {
    g_vf_name.clear();
    //
    g_vf_name.insert(std::make_pair("E_NULL",E_VF_INDEX));
    g_vf_name.insert(std::make_pair("E_INDEX",E_VF_INDEX));
    g_vf_name.insert(std::make_pair("E_V2",E_VF_V2));
    g_vf_name.insert(std::make_pair("E_V3",E_VF_V3));
    g_vf_name.insert(std::make_pair("E_NOR",E_VF_NOR));
    g_vf_name.insert(std::make_pair("E_TAG",E_VF_TAG));
    g_vf_name.insert(std::make_pair("E_BTAG",E_VF_BTAG));
    g_vf_name.insert(std::make_pair("E_C0",E_VF_C0));
    g_vf_name.insert(std::make_pair("E_C1",E_VF_C1));
    g_vf_name.insert(std::make_pair("E_C2",E_VF_C2));
    g_vf_name.insert(std::make_pair("E_C3",E_VF_C3));
    g_vf_name.insert(std::make_pair("E_T0",E_VF_T0));
    g_vf_name.insert(std::make_pair("E_T1",E_VF_T1));
    g_vf_name.insert(std::make_pair("E_T2",E_VF_T2));
    g_vf_name.insert(std::make_pair("E_T3",E_VF_T3));
    g_vf_name.insert(std::make_pair("E_BONE",E_VF_BONE));
    g_vf_name.insert(std::make_pair("E_BONEW",E_VF_BONE_W));
    g_vf_name.insert(std::make_pair("E_PAETICLE",E_VF_PARTICLE));
    g_vf_name.insert(std::make_pair("E_INST",E_VF_INSOFFSET));
    //
    g_sampler_name.clear();
    g_sampler_name.insert(std::make_pair("IMI_P_FILTER_MAG",IMI_P_FILTER_MAG));
    g_sampler_name.insert(std::make_pair("IMI_P_FILTER_MIN",IMI_P_FILTER_MIN));
    g_sampler_name.insert(std::make_pair("IMI_V_FILTER_NEAREST",IMI_V_FILTER_NEAREST));
    g_sampler_name.insert(std::make_pair("IMI_V_FILTER_LINEAR",IMI_V_FILTER_LINEAR));
    g_sampler_name.insert(std::make_pair("IMI_P_WRAP_S",IMI_P_WRAP_S));
    g_sampler_name.insert(std::make_pair("IMI_P_WRAP_T",IMI_P_WRAP_T));
    g_sampler_name.insert(std::make_pair("IMI_V_WRAP_CLAMP",IMI_V_WRAP_CLAMP));
    g_sampler_name.insert(std::make_pair("IMI_V_WRAP_BORDER",IMI_V_WRAP_BORDER));
    g_sampler_name.insert(std::make_pair("IMI_V_WRAP_REPEAT",IMI_V_WRAP_REPEAT));
    g_sampler_name.insert(std::make_pair("IMI_V_WRAP_MIRROR",IMI_V_WRAP_MIRROR));
    g_sampler_name.insert(std::make_pair("IMI_V_WRAP_BLACK",IMI_V_WRAP_BLACK));
    g_sampler_name.insert(std::make_pair("IMI_V_WRAP_WHITE",IMI_V_WRAP_WHITE));
}

IMIJsonDef::~IMIJsonDef() {
    clear();
}

void IMIJsonDef::clear() {
    g_vf_name.clear();
}
