//
// Created by lidm on 2020-06-17.
//

#ifndef MAGICADENGINE_GLTF_PBR_FRAG_H
#define MAGICADENGINE_GLTF_PBR_FRAG_H

#include "ShaderUtil.h"
#include "MaShaderDef.h"




static std::string pbrIBL(IBL &_ibl) {
    CREATE()
    if (_ibl.enable) {

//        SS("vec3 fresnelSchlickRoughness(float cosTheta, vec3 F0, float roughness) {")
//        SS("    return F0 + (max(vec3(1.0 - roughness), F0) - F0) * pow(1.0 - cosTheta, 5.0);")
//        SS("}")

        SS("vec2 integrateSpecularBRDF(float dotNV, float roughness) {")
        SS("    const vec4 c0 = vec4(-1,-0.0275,-0.572,0.022);")
        SS("    const vec4 c1 = vec4(1,0.0425,1.04,-0.04);")
        SS("    vec4 r = roughness * c0 + c1;")
        SS("    float a004 = min(r.x*r.x,exp2(-9.28*dotNV))*r.x+r.y;")
        SS("    return vec2(-1.04,1.04)*a004+r.zw;")
        SS("}")

        SS("vec3 getIBLContribution(MaterialInfo mi, vec3 n, vec3 v) {")
//        SS("    float NdotV = clamp(dot(n, -v), 0.0, 1.0);")
        SS("    float NdotV = max(dot(n, v), 0.0);")
        SS("    vec2 brdfSamplePoint = integrateSpecularBRDF(NdotV, mi.roughness);")
        SS("    vec2 brdf = texture(aTexture6, brdfSamplePoint).rg;")
        SS("    vec3 diffuseSample = texture(aTextureCube0, n).rgb;")
        SS("    vec3 rr = normalize(reflect(-v, n));")
        if (_ibl.mipmapSize > 0) {
            SS("float lod = clamp(mi.roughness * float(" + std::to_string(_ibl.mipmapSize) + "), 0.0, float(" + std::to_string(_ibl.mipmapSize) + "));")
            SS("vec3 specularSample = textureLod(aTextureCube1, rr, lod).rgb;")
        } else {
            SS("vec3 specularSample = texture(aTextureCube1, rr).rgb;")
        }

        if (_ibl.enableHDR) {
            SS("    vec3 diffuseLight = diffuseSample.rgb;")
            SS("    vec3 specularLight = specularSample.rgb;")
        } else {
            SS("    vec3 diffuseLight = SRGBtoLINEAR(diffuseSample.rgb);")
            SS("    vec3 specularLight = SRGBtoLINEAR(specularSample.rgb);")
        }
        SS("    vec3 diffuse = diffuseLight * mi.diffuseColor;")
//        SS("    vec3 F = fresnelSchlickRoughness(NdotV, mi.specularColor, mi.roughness);")
//        SS("    vec3 specular = specularLight * (F * brdf.x + brdf.y);")
        SS("    vec3 specular = specularLight * (mi.specularColor * brdf.x + brdf.y);")
        SS("    return diffuse + specular;")
        SS("}")
    }
    return TOShaderStr()
}

static std::string pbrVertexColor(bool _useVertexColor0) {
    CREATE()
    SS("vec4 getVertexColor()")
    SS("{")
    SS("    vec4 ret = vec4(1.0, 1.0, 1.0, 1.0);")
    if (_useVertexColor0) {
        SS("ret      = vColor0;")
    }
    SS("    return ret;")
    SS("}")
    return TOShaderStr()
}

static std::string normalLightFunc(MMLight &_mulLight) {
    CREATE()

    if (_mulLight.isExist()) {
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
        SS("    float NdotL = clamp(dot(n, l), 0.001, 1.0);")
        SS("    float NdotV = clamp(dot(n, v), 0.001, 1.0);")
        SS("    float NdotH = clamp(dot(n, h), 0.0, 1.0);")
        SS("    float LdotH = clamp(dot(l, h), 0.0, 1.0);")
        SS("    float VdotH = clamp(dot(v, h), 0.0, 1.0);")
        SS("    return AngularInfo(NdotL, NdotV, NdotH, LdotH, VdotH, vec3(0, 0, 0));")
        SS("}")

        SS("vec3 diffuse(MaterialInfo mi) {")
        SS("    return max(mi.diffuseColor / PI, 0.0);")
        SS("}")

        SS("vec3 specularReflection(MaterialInfo mi, AngularInfo ai) {")
        SS("    return mi.reflectance0 + (mi.reflectance90 - mi.reflectance0) * pow(clamp(1.0 - ai.VdotH, 0.0, 1.0), 5.0);")
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
        
        SS("vec3 shadeFilter(vec3 shade) {")
        SS("    return shade;")
        SS("}")
    }
    if (_mulLight.dirLightCount) {
        SS("vec3 applyDirectionalLight(Light light, MaterialInfo mi, vec3 n, vec3 v) {")
        SS("    vec3 shade = getPointShade(-light.direction, mi, n, v);")
        SS("    return vec3(light.intensity) * light.color * shadeFilter(shade);")
        SS("}")
    }
    if (_mulLight.pointLightCount) {
        SS("vec3 applyPointLight(Light light, MaterialInfo mi, vec3 n, vec3 v) {")
        SS("    vec3 pointToLight = light.position - vWorldPos0;")
        SS("    float distance = length(pointToLight);")
        SS("    float attenuation = getRangeAttenuation(light.range, distance);")
        SS("    vec3 shade = getPointShade(pointToLight, mi, n, v);")
//        SS("    return light.intensity * light.color * shadeFilter(shade);")
        SS("    return attenuation * light.intensity * light.color * shadeFilter(shade);")
        SS("}")
    }
    if (_mulLight.spotLightCount) {
        SS("vec3 applySpotLight(Light light, MaterialInfo mi, vec3 n, vec3 view) {")
        SS("    vec3 pointToLight = light.position - vWorldPos0;")
        SS("    float distance = length(pointToLight);")
        SS("    float rangeAttenuation = getRangeAttenuation(light.range, distance);")
        SS("    float spotAttenuation = getSpotAttenuation(pointToLight, light.direction, light.outerConeCos, light.innerConeCos);")
        SS("    vec3 shade = getPointShade(pointToLight, mi, n, view);")
        SS("    return rangeAttenuation * spotAttenuation * light.intensity * light.color * shadeFilter(shade);")
        SS("}")
    }

    return TOShaderStr()
}

static std::string gammaFunc() {
    CREATE()
    SS("vec3 LINEARtoSRGB(vec3 color) {");
    SS("    return pow(color, vec3(0.4545));");
    SS("}");

    SS("vec3 SRGBtoLINEAR(vec3 srgbIn) {");
    SS("    return pow(srgbIn.xyz, vec3(2.2));");
    SS("}");
    return TOShaderStr()
}

static std::string pbrToneMap(MapExposure &_exposure) {
    CREATE()
    if (_exposure.enable) {
        if (_exposure.type == 0) {//toneMapUncharted
            SS("vec3 toneMapUncharted2Impl(vec3 color) {");
            SS("    const float A = 0.15;");
            SS("    const float B = 0.50;");
            SS("    const float C = 0.10;");
            SS("    const float D = 0.20;");
            SS("    const float E = 0.02;");
            SS("    const float F = 0.30;");
            SS("    return ((color*(A*color+C*B)+D*E)/(color*(A*color+B)+D*F))-E/F;");
            SS("}");
            SS("vec3 toneMapUncharted(vec3 color) {");
            SS("    const float W = 11.2;");
            SS("    color = toneMapUncharted2Impl(color * 2.0);");
            SS("    vec3 whiteScale = 1.0 / toneMapUncharted2Impl(vec3(W));");
            SS("    return LINEARtoSRGB(color * whiteScale);");
            SS("}");
        } else if (_exposure.type == 1) {//toneMapHejlRichard
            SS("vec3 toneMapHejlRichard(vec3 color) {");
            SS("    color = max(vec3(0.0), color - vec3(0.004));");
            SS("    return (color*(6.2*color+0.5))/(color*(6.2*color+1.7)+0.06);");
            SS("}");
        } else if (_exposure.type == 2) {//toneMapACES
            SS("vec3 toneMapACES(vec3 color) {");
            SS("    const float A = 2.51;");
            SS("    const float B = 0.03;");
            SS("    const float C = 2.43;");
            SS("    const float D = 0.59;");
            SS("    const float E = 0.14;");
            SS("   return LINEARtoSRGB(clamp((color*(A*color+B))/(color*(C*color+D)+E),0.0,1.0));");
            SS("}");
        }
    }
    return TOShaderStr()
}


static std::string normalFromMap(bool _useTangent, TextureInfo &_normalTexture) {
    CREATE()

    SS("vec3 getNormalFromMap() {")
    if (_useTangent) {
        SS("mat3 tbn    = vTBN;")
    } else {
        SS("vec3 pos_dx = dFdx(vWorldPos0);")
        SS("vec3 pos_dy = dFdy(vWorldPos0);")
        SS("vec3 tex_dx = dFdx(vec3(" + _normalTexture.getUVName() + ", 0.0));")
        SS("vec3 tex_dy = dFdy(vec3(" + _normalTexture.getUVName() + ", 0.0));")
        SS("vec3 t      = (tex_dy.t*pos_dx-tex_dx.t*pos_dy)/(tex_dx.s*tex_dy.t-tex_dy.s*tex_dx.t);")
//        SS("vec3 ng = cross(pos_dx, pos_dy);")
        SS("vec3 ng     = vec3(vNormal0);")

        SS("     t      = normalize(t - ng * dot(ng, t));")
        SS("vec3 b      = normalize(cross(ng, t));")
        SS("mat3 tbn    = mat3(t, b, ng);")
    }
    if (_normalTexture.enable) {
        SS("vec3 n      = texture(aTexture2, " + _normalTexture.getUVName() + ").rgb;")
        SS("     n      = normalize(tbn * (2.0 * n - 1.0));")
    } else {
        SS("vec3 n      = normalize(tbn[2].xyz);")
    }
    SS("    return n;")
    SS("}")

    return TOShaderStr()
}

static std::string pbrBaseTexture(
        TextureInfo &_baseColor,
        TextureInfo &_baseColorTexture,
        MetallicRoughness &_pbrMR,
        SpecularGlossiness &_pbrSG,
        IBL &_ibl) {

    CREATE()

    if (_baseColor.enable && !_baseColorTexture.enable) {
        SS("colorA = uBaseColor.a;")
    }

    if (_baseColorTexture.enable) {
        if (_baseColorTexture.isRGBA) {
            SS("vec4 bc4 = texture(aTexture0, " + _baseColorTexture.getUVName() + ");")
            SS("colorA = bc4.a;")
            if (_baseColorTexture.compressed) {
                SS("bc4.rgb = bc4.rgb * bc4.a;")
            }
        } else {
            SS("vec4 bc4 = vec4(texture(aTexture0, " + _baseColorTexture.getUVName() + ").rgb, 1.0);")
        }
    }

    if (_pbrMR.enable || _ibl.enable) {
        if (_baseColorTexture.enable && _baseColor.enable) {
            SS("albedo = SRGBtoLINEAR(bc4.rgb) * uBaseColor.rgb;")
        } else if (_baseColorTexture.enable) {
            SS("albedo = SRGBtoLINEAR(bc4.rgb);")
        } else if (_baseColor.enable) {
            SS("albedo = SRGBtoLINEAR(uBaseColor.rgb);")
        }
    } else {
        if (_baseColorTexture.enable && _baseColor.enable) {
            SS("albedo = bc4.rgb * uBaseColor.rgb;")
        } else if (_baseColorTexture.enable) {
            SS("albedo = bc4.rgb;")
        } else if (_baseColor.enable) {
            SS("albedo = uBaseColor.rgb;")
        }
    }

    //优先是用metallic-roughness
    if (_pbrMR.enable) {
        if (_pbrMR.mrTexture.enable) {
            SS("vec3 mr         = texture(aTexture1, " + _pbrMR.mrTexture.getUVName() + ").rgb;")
            SS("metallic        = mr.b * uMetallicFactor;")
            SS("roughness       = mr.g * uRoughnessFactor;")
        } else {
            SS("metallic        = uMetallicFactor;")
            SS("roughness       = uRoughnessFactor;")
        }
        SS("diffuseColor        = albedo * (vec3(1.0)-F0)*(1.0-metallic);")
        SS("specularColor       = mix(F0, albedo, metallic);")
    } else if (_pbrSG.enable) {
        if (_pbrSG.sgTexture.enable) {
            if (_pbrSG.sgTexture.isRGBA) {
                SS("vec4 sg     = texture(aTexture1, " + _pbrSG.sgTexture.getUVName() + ");")
                SS("roughness   = (1.0 - sg.a * uGlossinessFactor);")
            } else {
                SS("vec3 sg     = texture(aTexture1, " + _pbrSG.sgTexture.getUVName() + ").rgb;")
                SS("roughness   = 1.0 - uGlossinessFactor;")
            }
            SS("F0              = SRGBtoLINEAR(sg.rgb) * uSpecularFactor;")
        } else {
            SS("F0              = uSpecularFactor;")
            SS("roughness       = 1.0 - uGlossinessFactor;")
        }
        if (_pbrSG.diffTexture.enable) {
            if (_pbrSG.diffTexture.isRGBA) {
                SS("vec4 dc4    = texture(aTexture5, " + _pbrSG.diffTexture.getUVName() + ");")
                SS("albedo      = SRGBtoLINEAR(dc4.rgb) * uDiffuseFactor.rgb;")
                SS("colorA      = dc4.a * uDiffuseFactor.a;")
            } else {
                SS("albedo      = SRGBtoLINEAR(texture(aTexture5, " + _pbrSG.diffTexture.getUVName() + ").rgb) * uDiffuseFactor.rgb;")
                SS("colorA      = uDiffuseFactor.a;")
            }
        } else {
            SS("albedo          = uDiffuseFactor.rgb;")
            SS("colorA          = uDiffuseFactor.a;")
        }
        SS("specularColor       = F0;")
        SS("diffuseColor        = albedo * (1.0 - max(max(F0.r, F0.g), F0.b));")
    } else {
        //默认普通模型
        SS("metallic        = uMetallicFactor;")
        SS("roughness       = uRoughnessFactor;")
        SS("diffuseColor  = albedo * (vec3(1.0)-F0)*(1.0-metallic);")
        SS("specularColor = mix(F0, albedo, metallic);")
    }

    return TOShaderStr()
}

#endif //MAGICADENGINE_GLTF_PBR_FRAG_H
