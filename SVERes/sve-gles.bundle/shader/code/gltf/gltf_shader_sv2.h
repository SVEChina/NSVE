//
// Created by lidm on 2020-04-20.
//

#ifndef MAGICADENGINE_GLTF_SHADER_SV2_H
#define MAGICADENGINE_GLTF_SHADER_SV2_H


#include "ShaderUtil.h"
#include "MaShaderDef.h"
#include "gltf_pbr_frag.h"


static std::string getGltfVS_sv2(
        int _maxBoneSize,
        bool _useNormalBone,
        bool _hasMorph,
        bool _useColor0,
        bool _useTangent,
        UVInfo &_uvInfo) {
    CREATE()
    SS(GLSL_VERSION_3)
    SS("precision highp float;")
    SS("layout(location = 0) in vec3 aPosition;")
    SS("layout(location = 1) in vec3 aNormal;")
    if (_useColor0) {
        SS("layout(location = 2) in vec4 aColor;")
    }
    SS("layout(location = 4) in vec2 aTexcoord0;")
    if (_uvInfo.uvSize >= 2) {
        SS("layout(location = 4) in vec2 aTexcoord1;")
    }
    if (_uvInfo.uvSize >= 3) {
        SS("layout(location = 4) in vec2 aTexcoord2;")
    }
    if (_uvInfo.uvSize >= 4) {
        SS("layout(location = 4) in vec2 aTexcoord3;")
    }
    //bone
    if (_maxBoneSize > 0) {
        SS("layout(location = 8) in vec4 aBoneID;")
        SS("layout(location = 9) in vec4 aBoneWeight;")
    }
    //morph
    if (_hasMorph) {
        SS("layout(location = 10) in vec3 aMorphPosition;")
    }
    if (_useTangent) {
        SS("layout(location = 13) in vec4 aTangent;")
    }
    SS("uniform mat4 aMatrixM;")
    SS("uniform mat4 aMatrixVP;")  //aMatrixVP: TAA时增加了抖动
    SS("uniform mat4 aMatrixNormal;")
    SS("uniform mat4 aMatrixCubeMapM;")

    SS("out vec2 vTexcoord0;")
    if (_uvInfo.uvSize >= 2) {
        SS("out vec2 vTexcoord1;")
    }
    if (_uvInfo.uvSize >= 3) {
        SS("out vec2 vTexcoord2;")
    }
    if (_uvInfo.uvSize >= 4) {
        SS("out vec2 vTexcoord3;")
    }
    if (_useTangent) {
        SS("out mat3 vTBN;")
    } else {
        SS("out vec3 vNormal0;")
    }
    if (_useColor0) {
        SS("out vec4 vColor0;")
    }
    SS("out vec3 vWorldPos0;")
    //bone
    if (_maxBoneSize > 0) {
        SS("uniform mat4 aBones[" + std::to_string(_maxBoneSize) + "];")
        if (_useNormalBone) {
            SS("uniform mat4 aNormalBones[" + std::to_string(_maxBoneSize) + "];")
        }
        SS("mat4 getSkinningMatrix() {")
        SS("    mat4 skin = mat4(0);")
        SS("    skin += aBoneWeight.x * aBones[int(floor(aBoneID.x))];")
        SS("    skin += aBoneWeight.y * aBones[int(floor(aBoneID.y))];")
        SS("    skin += aBoneWeight.z * aBones[int(floor(aBoneID.z))];")
        SS("    skin += aBoneWeight.w * aBones[int(floor(aBoneID.w))];")
        SS("    return skin;")
        SS("}")
        if (_useNormalBone) {
            SS("mat4 getSkinningNormalMatrix() {")
            SS("    mat4 skin = mat4(0);")
            SS("    skin += aBoneWeight.x * aNormalBones[int(floor(aBoneID.x))];")
            SS("    skin += aBoneWeight.y * aNormalBones[int(floor(aBoneID.y))];")
            SS("    skin += aBoneWeight.z * aNormalBones[int(floor(aBoneID.z))];")
            SS("    skin += aBoneWeight.w * aNormalBones[int(floor(aBoneID.w))];")
            SS("    return skin;")
            SS("}")
        }
    }

    SS("void main() {")
    SS("    vec3 resultPos     =    vec3(0.0);")
    SS("    vec3 resultNormal  =    vec3(0.0);")
    if (_useColor0) {
        SS("vColor0            =    aColor;")
    }
    SS("    vTexcoord0         =    aTexcoord0;")
    if (_uvInfo.uvSize >= 2) {
        SS("vTexcoord1         =    aTexcoord1;")
    }
    if (_uvInfo.uvSize >= 3) {
        SS("vTexcoord2         =    aTexcoord2;")
    }
    if (_uvInfo.uvSize >= 4) {
        SS("vTexcoord3         =    aTexcoord3;")
    }
    //morph
    if (_hasMorph) {
        SS("    vec4 PosL      =    vec4(aPosition.xyz + aMorphPosition.xyz, 1.0);")
    } else {
        SS("    vec4 PosL      =    vec4(aPosition.xyz, 1.0);")
    }
    if (_useTangent) {
        SS("vec4 tangentL      = aTangent;")
        SS("vec4 resultTangent = vec4(0.0);")
    }
    //bone
    if (_maxBoneSize > 0) {
        SS("mat4 skinningMat4  = getSkinningMatrix();")
        SS("resultPos          = vec4(skinningMat4*PosL).xyz;")
        if (_useNormalBone) {
            SS("resultNormal       = vec4(getSkinningNormalMatrix()*vec4(aNormal, 0.0)).xyz;")
        } else {
            SS("resultNormal       = aNormal;")
        }
        if (_useTangent) {
            SS("resultTangent  = skinningMat4*tangentL;")
        }
    } else {
        SS("resultPos          =   vec3(PosL.xyz);")
        SS("resultNormal       =   aNormal;")
        if (_useTangent) {
            SS("resultTangent  = tangentL;")
        }
    }
    if (_useTangent) {
        SS("vec4 tangent       = normalize(resultTangent);")
        SS("vec3 normalW       = normalize(vec3(aMatrixNormal*vec4(resultNormal.xyz, 0.0)));")
        SS("vec3 tangentW      = normalize(vec3(aMatrixM * vec4(tangent.xyz, 0.0)));")
        SS("vec3 bitangentW    = cross(normalW, tangentW) * tangent.w;")
        SS("vTBN               = mat3(tangentW, bitangentW, normalW);")
    } else {
        SS("vNormal0           = normalize(vec3(aMatrixNormal*vec4(resultNormal.xyz, 0.0)));")
//        SS("vNormal0    = normalize(resultNormal);")
    }
    SS("    vec4 pos4          = (aMatrixM * vec4(resultPos.xyz, 1.0));")
//    SS("    vec4 pos4_fs       = (aMatrixCubeMapM * vec4(resultPos.xyz, 1.0));")
    SS("    vWorldPos0         = pos4.xyz / pos4.w;")

    SS("    gl_Position        = aMatrixVP * pos4;")

    SS("}")
    return TOShaderStr()
}

//_useBaseAlbedoTextureRGBA 底图是否是4通到的
//aTexture0 albedo base
//aTexture1 metallic-roughness 或 specular-glossiness
//aTexture2 normal
//aTexture3 emissive
//aTexture4 occlusionTexture ao
//aTexture5 diffuse
//aTexture6 brdf
static std::string getGltfPbrFs_sv2(
        bool _useVertexColor0,
        TextureInfo &_emissive,
        TextureInfo &_ao,
        TextureInfo &_baseColor,
        TextureInfo &_baseColorTexture,
        TextureInfo &_normalTexture,
        bool _useTangent,
        UVInfo &_uvInfo,
        MetallicRoughness &_pbrMR,
        SpecularGlossiness &_pbrSG,
        MapExposure &_exposure,
        IBL &_ibl,
        MMLight &_mulLight) {


    bool _pbrModel = _pbrMR.enable || _pbrSG.enable || _ibl.enable;

    CREATE()

    SS(GLSL_VERSION_3)
    SS("precision highp float;")

    SS("in vec2 vTexcoord0;")
    if (_uvInfo.uvSize >= 2) {
        SS("in vec2 vTexcoord1;")
    }
    if (_uvInfo.uvSize >= 3) {
        SS("in vec2 vTexcoord2;")
    }
    if (_uvInfo.uvSize >= 4) {
        SS("in vec2 vTexcoord3;")
    }
    if (_useTangent) {
        SS("in mat3 vTBN;")
    } else {
        SS("in vec3 vNormal0;")
    }
    if (_useVertexColor0) {
        SS("in vec4 vColor0;")
    }
    SS("in vec3 vWorldPos0;")

    if (_baseColor.enable) {
        SS("uniform vec4 uBaseColor;")//albedo base color
    }
    if (_baseColorTexture.enable) {
        SS("uniform sampler2D aTexture0;")//albedo base
    }
    if (_pbrMR.mrTexture.enable || _pbrSG.sgTexture.enable) {
        SS("uniform sampler2D aTexture1;")//metallic-roughness 或 specular-glossiness
    }
    if (_normalTexture.enable) {
        SS("uniform sampler2D aTexture2;")//normal
    }
    if (_emissive.enable) {
        SS("uniform sampler2D aTexture3;")//emissive
    }
    if (_ao.enable) {
        SS("uniform sampler2D aTexture4;")//occlusionTexture ao
    }
    if (_pbrSG.diffTexture.enable) {
        SS("uniform sampler2D aTexture5;")//diffuse
    }
    if (_pbrSG.enable) {
        SS("uniform vec4 uDiffuseFactor;")
        SS("uniform vec3 uSpecularFactor;")
        SS("uniform float uGlossinessFactor;")
    }
    if (_ibl.enable) {
        SS("uniform sampler2D aTexture6;")//brdf
        SS("uniform samplerCube aTextureCube0;")//irradiance
        SS("uniform samplerCube aTextureCube1;")//prefilter
    }
    SS("uniform vec3 uCamPos0;")
    SS("uniform float uNormalAmbient;")
    SS("uniform float uPbrAmbient;")
    SS("uniform float uMetallicFactor;")
    SS("uniform float uRoughnessFactor;")
    if (_exposure.enable) {
        SS("uniform float uExposureFactor;")
    }

    SS("layout(location = 0) out vec4 outColor;")
#ifdef ENABLE_OPENGL_TAA
    SS("layout(location = 1) out vec3 outVelocity;")
#endif
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

    if (_pbrModel) {
        SS(gammaFunc())
    }

    //普通光照相关函数
    SS(normalLightFunc(_mulLight))

    //顶点颜色
//    SS(pbrVertexColor(_useVertexColor0))

    //处理发现
    SS(normalFromMap(_useTangent, _normalTexture))

    //PBR
    SS(pbrIBL(_ibl))

    //exposure
    SS(pbrToneMap(_exposure))

    SS("void main() {")
    SS("    vec3 F0             = vec3(0.04);")
    SS("    vec3 albedo         = vec3(0.0, 0.0, 0.0);")
    SS("    float colorA        = 1.0;")
    SS("    vec3 diffuseColor   = vec3(0.0);")
    SS("    vec3 specularColor  = vec3(0.0);")
    SS("    float metallic      = 0.0;")
    SS("    float roughness     = 0.0;")
    SS("    vec3 color          = vec3(0.0);")
    SS("    vec3 LO             = vec3(0.0);")
    SS("    vec3 N              = getNormalFromMap();")
    SS("    vec3 V              = normalize(uCamPos0 - vWorldPos0);")

    //普通贴图和metallic-roughness使用 baseColorTexture 和 baseColor
    //有贴图时不使用BaseColor的a通道

    SS(pbrBaseTexture(_baseColor, _baseColorTexture, _pbrMR, _pbrSG, _ibl))


    SS("roughness = clamp(roughness, 0.0, 1.0);")
    SS("metallic  = clamp(metallic, 0.0, 1.0);")

    SS("float alphaRoughness = roughness * roughness;")
    SS("float reflectance = max(max(specularColor.r, specularColor.g), specularColor.b);")
    SS("vec3 specularEnvironmentR0 = specularColor.rgb;")
    SS("vec3 specularEnvironmentR90 = vec3(clamp(reflectance * 50.0, 0.0, 1.0));")

    SS("MaterialInfo mi = MaterialInfo(roughness, alphaRoughness, diffuseColor, specularColor, specularEnvironmentR0, specularEnvironmentR90);")
    if (_mulLight.getLightCount() > 0) {
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
    SS("color += LO;")

    //IBL
    if (_ibl.enable) {
        SS("color += getIBLContribution(mi, N, V);")
    }

    //环境光
    if(_pbrModel) {
        SS("color += albedo.rgb*uPbrAmbient;")
    } else {
        SS("color += albedo.rgb*uNormalAmbient;")
    }

    //AO
    if (_ao.enable) {
        SS("float ao = texture(aTexture4, " + _ao.getUVName() + ").r;")
        SS("color = mix(color,color*ao, " + _ao.getStrength() + ");")
    }
    //emission
    if (_emissive.enable) {
        SS("color += texture(aTexture3, " + _emissive.getUVName() + ").rgb * " + _emissive.getFactorVec3() + ";")
    }
    if (_exposure.enable) {
        SS("color *= uExposureFactor;")
        if (_exposure.type == 0) {
            SS("color = toneMapUncharted(color);")
        } else if (_exposure.type == 1) {
            SS("color = toneMapHejlRichard(color);")
        } else if (_exposure.type == 2) {
            SS("color = toneMapACES(color);")
        } else {
            if (_pbrModel) {
//                SS("color = color / (color + vec3(1.0));")
                SS("color = LINEARtoSRGB(color);")
            } else {
                SS("color = color;")
            }
        }
        SS("outColor.rgba = vec4(color.rgb, colorA);")
    } else {
        if (_pbrModel) {
            SS("outColor.rgba = vec4(LINEARtoSRGB(color), colorA);")
        } else {
            SS("outColor.rgba = vec4(color, colorA);")
        }
    }

    SS("}")
    return TOShaderStr()
}


#endif //MAGICADENGINE_GLTF_SHADER_SV2_H
