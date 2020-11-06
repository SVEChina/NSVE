//
//  screen.metal
//  IMITools
//
//  Created by 付一洲 on 2020/7/18.
//  Copyright © 2020 付一洲. All rights reserved.
//

#include <metal_stdlib>

using namespace metal;

//
struct Vertex {
    float2 position [[attribute(0)]];
    float2 texcoord0 [[attribute(1)]];
};

//
struct VertexOut {
    float4 position [[position]];
    float2 texcoord0;
};

//
struct FSOutput{
    float4 frag0 [[color(0)]];
};

struct FTParam {
    float shadows;
    float highlights;
    float contrast;
    float saturation;
    float brightness;
    float whitening;
    float gamma;
    float redShift;
    float greenShift;
    float blueShift;
    float sdredShift;
    float sdgreenShift;
    float sdblueShift;
    float hhredShift;
    float hhgreenShift;
    float hhblueShift;
    float temperature;
    float tint;
};

const float3 warmFilter = float3(0.93, 0.54, 0.0);

const float3 luminanceWeight = float3(0.3, 0.3, 0.3);

const float3 saturationWeight = float3(0.2125, 0.7154, 0.0721);

const float3x3 RGBtoYIQ = float3x3(0.299, 0.587, 0.114,
                                   0.596, -0.274, -0.322,
                                   0.212, -0.523, 0.311);

const float3x3 YIQtoRGB = float3x3(1.0, 0.956, 0.621,
                                   1.0, -0.272, -0.647,
                                   1.0, -1.105, 1.702);

//阴影
float4 fhightshadows(float4 color,FTParam param){
    float t_shadows = shadows;
    float t_highlights = highlights;
    float luminance = dot(color.rgb, luminanceWeight);
    float shadow = clamp((pow(luminance, 1.0/(t_shadows+1.0)) + (-0.76)*pow(luminance, 2.0/(t_shadows+1.0))) - luminance, 0.0, 1.0);
    float highlight = clamp( (1.0 - (pow(1.0-luminance, 1.0/(2.0-t_highlights)) + (-0.8)*pow(1.0-luminance, 2.0/(2.0-t_highlights)))) - luminance, -1.0, 0.0);
    float3 result = float3(0.0, 0.0, 0.0) + ((luminance + t_shadows + t_highlights) - 0.0) * ((color.rgb - float3(0.0, 0.0, 0.0))/(luminance - 0.0));
    return float4(result.rgb, color.a);
}

//
float4 fcontrast(float4 color,FTParam param){
    return float4( ((color.rgb - float3(0.5)) * (contrast+1.0) + float3(0.5) ), color.w );
}

//
float4 fsaturation(float4 color,FTParam param){
    float luminance = dot(color.rgb, saturationWeight);
    float3 greyScaleColor = float3(luminance);
    return float4(mix(greyScaleColor, color.rgb, saturation+1.0), color.w);
}

//明亮
float4 fbrightness(float4 color,FTParam param){
    float4 src = color;
    float fac = 1.0 / (brightness+0.1);
    float fac2 = 1.0 - fac;
    float3 tmp1 = fac2 - src.rgb;
    float3 tmp2 = sqrt(fac2 * fac2 + (4.0 * fac) * src.rgb);
    src.rgb = tmp1 + tmp2 * (step(0.0, brightness+0.01) * 2.0 - 1.0);
    return src;
}

//查询表
float4 fwhitening(float4 color,FTParam param){
    float4 textureColor = color;
    float blueColor = textureColor.b * 63.0;
    float2 quad1;
    quad1.y = floor(floor(blueColor) / 8.0);
    quad1.x = floor(blueColor) - (quad1.y * 8.0);
    float2 quad2;
    quad2.y = floor(ceil(blueColor) /8.0);
    quad2.x = ceil(blueColor) - (quad2.y * 8.0);
    float2 texPos1;
    texPos1.x = (quad1.x * 1.0/8.0)+ 0.5/512.0 + ((1.0/8.0 - 1.0/512.0) * textureColor.r);
    texPos1.y = (quad1.y * 1.0/8.0) + ((1.0/8.0 - 1.0/512.0) * textureColor.g);
    float2 texPos2;
    texPos2.x = (quad2.x * 1.0/8.0)+ 0.5/512.0 + ((1.0/8.0 - 1.0/512.0) * textureColor.r);
    texPos2.y = (quad2.y * 1.0/8.0)+ 0.5/512.0 + ((1.0/8.0 - 1.0/512.0) * textureColor.g);
    float4 newColor1 = texture2D(aTexture1, texPos1);
    float4 newColor2 = texture2D(aTexture1, texPos2);
    float4 newColor = mix(newColor1, newColor2, fract(blueColor));
    return mix(textureColor, float4(newColor.rgb, textureColor.w),whitening);
}

//
float4 fgamma(float4 color){
    return float4( pow(color.rgb, float3(gamma)), color.w);
}

float RGBToL(float3 color){
    float fmin = min(min(color.r, color.g), color.b);    //Min. value of RGB
    float fmax = max(max(color.r, color.g), color.b);    //Max. value of RGB
    return (fmax + fmin) / 2.0; // Luminance
}

float3 RGBToHSL(float3 color){
    float3 hsl; // init to 0 to avoid warnings ? (and reverse if + remove first part)
    float minc = min(min(color.r, color.g), color.b);    //Min. value of RGB
    float maxc = max(max(color.r, color.g), color.b);    //Max. value of RGB
    float delta = maxc - minc;             //Delta RGB value
    hsl.z = (maxc + minc) / 2.0; // Luminance
    if (delta == 0.0){       //This is a gray, no chroma...
        hsl.x = 0.0;    // Hue
        hsl.y = 0.0;    // Saturation
    } else { //Chromatic data...
        if (hsl.z < 0.5) {
            hsl.y = delta / (maxc + minc); // Saturation
        } else {
            hsl.y = delta / (2.0 - maxc - minc); // Saturation
        }
        float deltaR = (((maxc - color.r) / 6.0) + (delta / 2.0)) / delta;
        float deltaG = (((maxc - color.g) / 6.0) + (delta / 2.0)) / delta;
        float deltaB = (((maxc - color.b) / 6.0) + (delta / 2.0)) / delta;
        if (color.r == maxc ) {
            hsl.x = deltaB - deltaG; // Hue
        } else if (color.g == maxc) {
            hsl.x = (1.0 / 3.0) + deltaR - deltaB; // Hue
        } else if (color.b == maxc) {
            hsl.x = (2.0 / 3.0) + deltaG - deltaR; // Hue
        }
        //
        if (hsl.x < 0.0) {
            hsl.x += 1.0; // Hue
        } else if (hsl.x > 1.0) {
            hsl.x -= 1.0; // Hue
        }
    }
    return hsl;
}

float HueToRGB(float f1, float f2, float hue){
    if (hue < 0.0) {
         hue += 1.0;
    } else if (hue > 1.0) {
        hue -= 1.0;
    }
    float res;
    if ((6.0 * hue) < 1.0) {
        res = f1 + (f2 - f1) * 6.0 * hue;
    } else if ((2.0 * hue) < 1.0) {
        res = f2;
    } else if ((3.0 * hue) < 2.0) {
        res = f1 + (f2 - f1) * ((2.0 / 3.0) - hue) * 6.0;
    } else {
        res = f1;
    }
    return res;
}

float3 HSLToRGB(float3 hsl){
    float3 rgb;
    if (hsl.y == 0.0) {
        rgb = float3(hsl.z); // Luminance
    } else {
        float f2;
        if (hsl.z < 0.5) {
            f2 = hsl.z * (1.0 + hsl.y);
        } else {
            f2 = (hsl.z + hsl.y) - (hsl.y * hsl.z);
        }
        float f1 = 2.0 * hsl.z - f2;
        rgb.r = HueToRGB(f1, f2, hsl.x + (1.0/3.0));
        rgb.g = HueToRGB(f1, f2, hsl.x);
        rgb.b = HueToRGB(f1, f2, hsl.x - (1.0/3.0));
    }
    return rgb;
}

//彩色平衡
float4 fcolorBalance(float4 color,FTParam param){
    //
    float4 textureColor = color;
    // New way:
    float lightness = RGBToL(textureColor.rgb);
    float3 shift = float3(param.redShift, param.greenShift, param.blueShift)*0.5;
    float3 shiftShadows = float3(param.sdredShift, param.sdgreenShift, param.sdblueShift) * 0.5;
    float3 shiftHighlights = float3(param.hhredShift, param.hhgreenShift, param.hhblueShift) * 0.5;
    //
    const float a = 0.55;
    const float b = 0.5;
    const float scale = 0.7;
    //
    float3 shadows = (clamp((0.33333-lightness)*4.0+0.5, 0.0, 1.0) * 0.5) * shiftShadows;
    float3 midtones = (clamp((lightness-b)/a+0.5, 0.0, 1.0) * clamp((lightness+b-1.0)/-a+0.5,0.0,1.0) * scale) * shift;
    float3 highlights =  (clamp((lightness-0.33333)*4.0+0.5, 0.0, 1.0) * 0.15) * shiftHighlights;
    float3 newColor = textureColor.rgb + shadows;
    newColor = newColor + midtones;
    newColor = newColor + highlights;
    newColor = clamp(newColor, 0.0, 1.0);
    // preserve luminosity
    float3 newHSL = RGBToHSL(newColor);
    float oldLum = RGBToL(textureColor.rgb);
    textureColor.rgb = HSLToRGB(float3(newHSL.x, newHSL.y, oldLum));
    return textureColor;
}

//白平衡
float4 fwhiteBalance(float4 color0,FTParam param){
    float4 source = color0;
    float3 yiq = RGBtoYIQ * source.rgb; //adjusting tint
    yiq.b = clamp(yiq.b + tint*0.5226*0.1, -0.5226, 0.5226);
    float3 rgb = YIQtoRGB * yiq;
    float3 processed = float3(
                          (rgb.r < 0.5 ? (2.0 * rgb.r * warmFilter.r) : (1.0 - 2.0 * (1.0 - rgb.r) * (1.0 - warmFilter.r))), //adjusting temperature
                          (rgb.g < 0.5 ? (2.0 * rgb.g * warmFilter.g) : (1.0 - 2.0 * (1.0 - rgb.g) * (1.0 - warmFilter.g))),
                          (rgb.b < 0.5 ? (2.0 * rgb.b * warmFilter.b) : (1.0 - 2.0 * (1.0 - rgb.b) * (1.0 - warmFilter.b))));
    return float4(mix(color0, processed, temperature), source.a);
}

//
vertex VertexOut vsMain( Vertex input [[stage_in]] ) {
    VertexOut vert;
    vert.position = float4(input.position,0.0,1.0);
    vert.texcoord0 = input.texcoord0;
    return vert;
}

//
fragment FSOutput fsMain(VertexOut input [[stage_in]],
                         sampler sam0 [[sampler(0)]],
                         texture2d<float> tex0 [[texture(0)]],
                         constant FTParam& param [[buffer(1)]] ) {
    FSOutput out;
    float4 color = tex0.sample(sam0, input.texcoord0);
    if(temperature!=0.0){
        color = fwhiteBalance(color,param);
    }
    if(gamma!=0.0){
        color = fgamma(color);
    }
    if(redShift!=0.0||greenShift!=0.0||blueShift!=0.0||sdredShift!=0.0||sdgreenShift!=0.0||sdblueShift!=0.0||hhredShift!=0.0||hhgreenShift!=0.0||hhblueShift!=0.0){
        color = fcolorBalance(color,param);
    }
    if(whitening != 0.0){
        color = fwhitening(color,param);
    }
    if(shadows != 0.0|| highlights != 0.0){
        color = fhightshadows(color,param);
    }
    if(contrast != 0.0){
        color = fcontrast(color,param);
    }
    if(saturation != 0.0){
        color = fsaturation(color,param);
    }
    if(brightness!=0.0){
        color = fbrightness(color,param);
    }
    out.frag0 = color;
    return out;
}
