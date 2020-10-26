//
// Created by lidm on 2019-09-26.
//

#ifndef MAGICADENGINE_GLTF_SHADER_V2_H
#define MAGICADENGINE_GLTF_SHADER_V2_H



#include "ShaderUtil.h"
#include "MaShaderDef.h"

static std::string getGltfVS_v2(
        int _maxBoneSize,
        bool _hasMorph) {

    CREATE()
    SS("precision highp float;")
    SS("attribute vec3 aPosition;")
    SS("attribute vec3 aNormal;")
    SS("attribute vec2 aTexcoord0;")
    //bone
    if (_maxBoneSize > 0) {
        SS("attribute vec4 aBoneID;")
        SS("attribute vec4 aBoneWeight;")
    }
    //morph
    if (_hasMorph) {
        SS("attribute vec3 aMorphPosition;")
    }
    SS("uniform mat4 aMatrixM;")
    SS("uniform mat4 aMatrixVP;")
    SS("uniform mat4 aMatrixNormal;")

    SS("varying vec3 vNormal0;")
    SS("varying vec2 vTexcoord0;")
    SS("varying vec3 vWorldPos0;")
    //bone
    if (_maxBoneSize > 0) {
        SS("uniform mat4 aBones[" + std::to_string(_maxBoneSize) + "];")
        SS("mat4 getSkinningMatrix() {")
        SS("    mat4 skin = mat4(0);")
        SS("    skin += aBoneWeight.x * aBones[int(floor(aBoneID.x))];")
        SS("    skin += aBoneWeight.y * aBones[int(floor(aBoneID.y))];")
        SS("    skin += aBoneWeight.z * aBones[int(floor(aBoneID.z))];")
        SS("    skin += aBoneWeight.w * aBones[int(floor(aBoneID.w))];")
        SS("    return skin;")
        SS("}")
    }

    SS("void main() {")
    SS("    vec3 resultPos     =    vec3(0.0);")
    SS("    vec3 resultNormal  =    vec3(0.0);")
    SS("    vTexcoord0         =    aTexcoord0;")
    //morph
    if (_hasMorph) {
        SS("    vec4 PosL      =    vec4(aPosition.xyz + aMorphPosition.xyz, 1.0);")
    } else {
        SS("    vec4 PosL      =    vec4(aPosition.xyz, 1.0);")
    }
    //bone
    if (_maxBoneSize > 0) {
        SS("mat4 skinningMat4  = getSkinningMatrix();")
        SS("resultPos          = vec4(skinningMat4*PosL).xyz;")
        SS("resultNormal       = vec4(skinningMat4*vec4(aNormal, 0.0)).xyz;")
    } else {
        SS("resultPos          =   vec3(PosL.xyz);")
        SS("resultNormal       =   vec3(aNormal.xyz);")
    }
    SS("vNormal0    = normalize(vec3(aMatrixNormal*vec4(resultNormal.xyz, 0.0)));")
    SS("vec4 pos4   = (aMatrixM * vec4(resultPos, 1.0));")
    SS("vWorldPos0  = pos4.xyz / pos4.w;")
    SS("gl_Position = aMatrixVP * pos4;")
    SS("}")
    return TOShaderStr()
}

static std::string getGltfPbrFs_v2(
        bool _useBaseColor,
        bool _useBaseAlbedoTexture,
        MMLight &_mulLight) {

    CREATE()
    SS("precision highp float;")

    SS("varying vec2 vTexcoord0;")
    SS("varying vec3 vNormal0;")
    SS("varying vec3 vWorldPos0;")
    if (_useBaseColor) {
        SS("uniform vec4 uBaseColor;")//albedo base color
    }
    if (_useBaseAlbedoTexture) {
        SS("uniform sampler2D aTexture0;")//albedo base
    }
    SS("uniform vec3 uCamPos0;")
    SS("uniform float uPbrAmbient;")

    if (_mulLight.isExist()) {
        SS("const float PI = 3.14159265359;")

        SS("struct MaterialInfo {")
        SS("    float roughness;")
        SS("    float alphaRoughness;")
        SS("    vec3  diffuseColor;")
        SS("    vec3  specularColor;")
        SS("    vec3  reflectance0;")
        SS("    vec3  reflectance90;")
        SS("};")

        SS("struct AngularInfo {")
        SS("    float NdotL;")// cos angle between normal and light direction
        SS("    float NdotV;")// cos angle between normal and view direction
        SS("    float NdotH;")// cos angle between normal and half vector
        SS("    float LdotH;")// cos angle between light direction and half vector
        SS("    float VdotH;")// cos angle between view direction and half vector
        SS("    vec3 padding;")
        SS("};")

        SS("struct Light {")
        SS("    vec3 direction;")
        SS("    float range;")
        SS("    vec3 color;")
        SS("    float intensity;")
        SS("    vec3 position;")
        SS("    float innerConeCos;")
        SS("    float outerConeCos;")
        SS("    int type;")
        SS("    vec2 padding;")
        SS("};")
        SS("uniform Light uLights[" + std::to_string(_mulLight.getLightCount()) + "];")

        SS("AngularInfo getAngularInfo(vec3 pointToLight, vec3 n, vec3 v) {")
        SS("    vec3 l = normalize(pointToLight);")     // Direction from surface point to light
        SS("    vec3 h = normalize(l + v);")            // Direction of the vector between l and v
        SS("    float NdotL = clamp(dot(n, l), 0.0, 1.0);")
        SS("    float NdotV = clamp(dot(n, v), 0.0, 1.0);")
        SS("    float NdotH = clamp(dot(n, h), 0.0, 1.0);")
        SS("    float LdotH = clamp(dot(l, h), 0.0, 1.0);")
        SS("    float VdotH = clamp(dot(v, h), 0.0, 1.0);")
        SS("    return AngularInfo(NdotL, NdotV, NdotH, LdotH, VdotH, vec3(0, 0, 0));")
        SS("}")

        SS("vec3 diffuse(MaterialInfo mi) {")
        SS("    return max(mi.diffuseColor / PI, 0.0);")
        SS("}")

        SS("vec3 specularReflection(MaterialInfo mi, AngularInfo ai) {")
        SS("    return mi.reflectance0 + (mi.reflectance90 - mi.reflectance0) * pow(1.0 - ai.VdotH, 5.0);")
        SS("}")

        SS("float visibilityOcclusion(MaterialInfo mi, AngularInfo ai) {")
        SS("    float NdotL = ai.NdotL;")
        SS("    float NdotV = ai.NdotV;")
        SS("    float alphaRoughnessSq = mi.alphaRoughness * mi.alphaRoughness;")
        SS("    float GGXV = NdotL * sqrt(NdotV * NdotV * (1.0 - alphaRoughnessSq) + alphaRoughnessSq);")
        SS("    float GGXL = NdotV * sqrt(NdotL * NdotL * (1.0 - alphaRoughnessSq) + alphaRoughnessSq);")
        SS("    float GGX = GGXV + GGXL;")
        SS("    return GGX > 0.0 ? 0.5 / GGX : 0.0;")
        SS("}")

        SS("float microfacetDistribution(MaterialInfo mi, AngularInfo ai) {")
        SS("    float alphaRoughnessSq = mi.alphaRoughness * mi.alphaRoughness;")
        SS("    float f = (ai.NdotH * alphaRoughnessSq - ai.NdotH) * ai.NdotH + 1.0;")
        SS("    return alphaRoughnessSq / (PI * f * f);")
        SS("}")

        SS("vec3 getPointShade(vec3 pointToLight, MaterialInfo mi, vec3 n, vec3 v) {")
        SS("    AngularInfo ai = getAngularInfo(pointToLight, n, v);")
        SS("    if (ai.NdotL > 0.0 || ai.NdotV > 0.0) {")
        SS("        vec3 F = specularReflection(mi, ai);")
        SS("        float Vis = visibilityOcclusion(mi, ai);")
        SS("        float D = microfacetDistribution(mi, ai);")
        SS("        vec3 diffuseContrib = (1.0 - F) * diffuse(mi);")
        SS("        vec3 specContrib = F * Vis * D;")
        SS("        return ai.NdotL * (diffuseContrib + specContrib);")
        SS("    }")
        SS("    return vec3(0.0, 0.0, 0.0);")
        SS("}")

        SS("float getRangeAttenuation(float range, float distance) {")
        SS("    return range < 0.0 ? 1.0 : max(min(1.0 - pow(distance / range, 4.0), 1.0), 0.0) / pow(distance, 2.0);")
        SS("}")
        if (_mulLight.dirLightCount) {
            SS("vec3 applyDirectionalLight(Light light, MaterialInfo mi, vec3 n, vec3 v) {")
            SS("    vec3 shade = getPointShade(-light.direction, mi, n, v);")
            SS("    return vec3(light.intensity) * light.color * shade;")
            SS("}")
        }
        if (_mulLight.pointLightCount) {
            SS("vec3 applyPointLight(Light light, MaterialInfo mi, vec3 n, vec3 v) {")
            SS("    vec3 pointToLight = light.position - vWorldPos0;")
            SS("    float distance = length(pointToLight);")
            SS("    float attenuation = getRangeAttenuation(light.range, distance);")
            SS("    vec3 shade = getPointShade(pointToLight, mi, n, v);")
            SS("    return vec3(attenuation) * vec3(light.intensity) * light.color * shade;")
            SS("}")
        }
        if (_mulLight.spotLightCount) {
            SS("vec3 applySpotLight(Light light, MaterialInfo mi, vec3 normal, vec3 view) {")
            SS("    vec3 pointToLight = light.position - vWorldPos0;")
            SS("    float distance = length(pointToLight);")
            SS("    float rangeAttenuation = getRangeAttenuation(light.range, distance);")
            SS("    float spotAttenuation = getSpotAttenuation(pointToLight, light.direction, light.outerConeCos, light.innerConeCos);")
            SS("    vec3 shade = getPointShade(pointToLight, mi, normal, view);")
            SS("    return vec3(rangeAttenuation) * vec3(spotAttenuation) * vec3(light.intensity) * light.color * shade;")
            SS("}")
        }
    }

    SS("void main() {")
    SS("    vec3 F0             = vec3(0.04);")
    SS("    vec3 albedo         = vec3(0.0, 0.0, 0.0);")
    SS("    float colorA        = 1.0;")
    SS("    vec3 diffuseColor   = vec3(0.0);")
    SS("    vec3 specularColor  = vec3(0.0);")
    SS("    float metallic      = 0.05;")
    SS("    float roughness     = 0.85;")

    if (_useBaseAlbedoTexture && _useBaseColor) {
        SS("vec4 color4     = texture2D(aTexture0, vTexcoord0) * uBaseColor;")
        SS("colorA          = color4.a;")
        SS("albedo          = vec3(color4.rgb);")
    } else if(_useBaseColor){
        SS("albedo          = uBaseColor.rgb;")
        SS("colorA          = uBaseColor.a;")
    } else if(_useBaseAlbedoTexture){
        SS("vec4 color4     = texture2D(aTexture0, vTexcoord0);")
        SS("colorA          = color4.a;")
        SS("albedo          = vec3(color4.rgb);")
    }

    SS("specularColor = mix(F0, albedo.rgb, metallic);")
    SS("diffuseColor  = albedo.rgb * (vec3(1.0)-F0)*(1.0-metallic);")

    SS("float alphaRoughness = roughness * roughness;")
    SS("float reflectance = max(max(specularColor.r, specularColor.g), specularColor.b);")
    SS("vec3 specularEnvironmentR0 = specularColor.rgb;")
    SS("vec3 specularEnvironmentR90 = vec3(clamp(reflectance * 50.0, 0.0, 1.0));")

    SS("vec3 LO = vec3(0.0);")
    if (_mulLight.isExist()) {
        SS("MaterialInfo mi = MaterialInfo(roughness, alphaRoughness, diffuseColor, specularColor, specularEnvironmentR0, specularEnvironmentR90);")
        SS("vec3 N     = normalize(vNormal0);")
        SS("vec3 V     = normalize(uCamPos0 - vWorldPos0);")

        SS("for (int i = 0; i < " + std::to_string(_mulLight.getLightCount()) + "; ++i) {")
        SS("    Light lightItem = uLights[i];")
        SS("    if (lightItem.type == 0) {")
        if (_mulLight.dirLightCount > 0) {
            SS("    LO += applyDirectionalLight(lightItem, mi, N, V);")
        }
        SS("    } else if (lightItem.type == 1) {")
        if (_mulLight.pointLightCount > 0) {
            SS("    LO += applyPointLight(lightItem, mi, N, V);")
        }
        SS("    } else if (lightItem.type == 2) {")
        if (_mulLight.spotLightCount > 0) {
            SS("    LO += applySpotLight(lightItem, mi, N, V);")
        }
        SS("    }")
        SS("}")
    }
    //
    SS("vec3 ambient            = albedo * uPbrAmbient;")
    SS("vec3 color              = ambient + LO;")
    //
    SS("gl_FragColor.rgb        = color;")
    SS("gl_FragColor.a          = colorA;")

    SS("}")
    return TOShaderStr()
}


#endif //MAGICADENGINE_GLTF_SHADER_V2_H
