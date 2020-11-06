//
// IMIMathHelper.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include <math.h>
#include <cstdlib>
#include "IMIMathHelper.h"
#define MAXREPT  4//积分迭代次数
#define f(x) sqrt(10*x-x*x)

using namespace imi;
//三次贝塞尔曲线
static f32 bezier3funcX(f32 uu, V2 *controlP) {
    f32 part0 = controlP[0].x * uu * uu * uu;
    f32 part1 = 3 * controlP[1].x * uu * uu * (1 - uu);
    f32 part2 = 3 * controlP[2].x * uu * (1 - uu) * (1 - uu);
    f32 part3 = controlP[3].x * (1 - uu) * (1 - uu) * (1 - uu);
    return part0 + part1 + part2 + part3;
}

static f32 bezier3funcY(f32 uu, V2 *controlP) {
    f32 part0 = controlP[0].y * uu * uu * uu;
    f32 part1 = 3 * controlP[1].y * uu * uu * (1 - uu);
    f32 part2 = 3 * controlP[2].y * uu * (1 - uu) * (1 - uu);
    f32 part3 = controlP[3].y * (1 - uu) * (1 - uu) * (1 - uu);
    return part0 + part1 + part2 + part3;
}


void
IMIMathHelper::createCurve(V2 *originpoint, s32 origincount, s32 step, V2 *outcurve, s32 &outptcount, bool covered) {
    //控制点收缩系数 ，经调试0.6较好
    f32 scale = 0.6;
    V2 midpoints[origincount];
    //生成中点
    for (s32 i = 0; i < origincount; i++) {
        s32 nexti = (i + 1) % origincount;
        midpoints[i].x = (originpoint[i].x + originpoint[nexti].x) / 2.0;
        midpoints[i].y = (originpoint[i].y + originpoint[nexti].y) / 2.0;
    }
    //平移中点
    V2 extrapoints[2 * origincount];
    for (s32 i = 0; i < origincount; i++) {
        //        s32 nexti = (i + 1) % origincount;
        s32 backi = (i + origincount - 1) % origincount;
        V2 midinmid;
        midinmid.x = (midpoints[i].x + midpoints[backi].x) / 2.0;
        midinmid.y = (midpoints[i].y + midpoints[backi].y) / 2.0;
        s32 offsetx = originpoint[i].x - midinmid.x;
        s32 offsety = originpoint[i].y - midinmid.y;
        s32 extraindex = 2 * i;
        extrapoints[extraindex].x = midpoints[backi].x + offsetx;
        extrapoints[extraindex].y = midpoints[backi].y + offsety;
        //朝 originpoint[i]方向收缩
        s32 addx = (extrapoints[extraindex].x - originpoint[i].x) * scale;
        s32 addy = (extrapoints[extraindex].y - originpoint[i].y) * scale;
        extrapoints[extraindex].x = originpoint[i].x + addx;
        extrapoints[extraindex].y = originpoint[i].y + addy;
        
        s32 extranexti = (extraindex + 1) % (2 * origincount);
        extrapoints[extranexti].x = midpoints[i].x + offsetx;
        extrapoints[extranexti].y = midpoints[i].y + offsety;
        //朝 originpoint[i]方向收缩
        addx = (extrapoints[extranexti].x - originpoint[i].x) * scale;
        addy = (extrapoints[extranexti].y - originpoint[i].y) * scale;
        extrapoints[extranexti].x = originpoint[i].x + addx;
        extrapoints[extranexti].y = originpoint[i].y + addy;
    }
    s32 t_outptcount = 0;
    V2 controlPoint[4];
    //生成4控制点，产生贝塞尔曲线
    for (s32 i = 0; i < origincount; i++) {
        V2 curpt = originpoint[i];
        controlPoint[0] = curpt;
        s32 extraindex = 2 * i;
        controlPoint[1] = extrapoints[extraindex + 1];
        s32 extranexti = (extraindex + 2) % (2 * origincount);
        controlPoint[2] = extrapoints[extranexti];
        s32 nexti = (i + 1) % origincount;
        controlPoint[3] = originpoint[nexti];
        if (covered) {
            outcurve[t_outptcount++] = curpt;
        }
        f32 u = 1;
        while (u > 0) {
            //u的步长决定曲线的疏密
            u -= 1.0 / (step+1);
            if (u <= 0) {
                break;
            }
            f32 px = bezier3funcX(u, controlPoint);
            f32 py = bezier3funcY(u, controlPoint);
            V2 tempP;
            tempP.x = px;
            tempP.y = py;
            //存入曲线点
            outcurve[t_outptcount++] = tempP;
        }
    }
    outptcount = t_outptcount;
}

f32 IMIMathHelper::getEllipseY(f32 ellipse_a, f32 ellipse_b, f32 ellipse_x) {
    return ellipse_b * sqrtf((1 - (ellipse_x * ellipse_x) / (ellipse_a * ellipse_a)));
}


f32 IMIMathHelper::fit_size(f32 srcw, f32 srch, f32 dstw, f32 dsth, s32 type) {
    f32 src_w_h_rate = srcw / srch;
    f32 dst_w_h_rate = dstw / dsth;
    f32 t_s_factor = 1.0f;
    if (type == 1) {
        //最小内接矩形
        if (src_w_h_rate > dst_w_h_rate) {
            t_s_factor = dstw / srcw;
        } else {
            t_s_factor = dsth / srch;
        }
    } else if (type == 2) {
        //最大外接矩形
        if (src_w_h_rate > dst_w_h_rate) {
            t_s_factor = dstw / srcw;
        } else {
            t_s_factor = dsth / srch;
        }
    }
    return t_s_factor;
}

f64 IMIMathHelper::rombergIntegration(f64 _low, f64 _high, f64 _e){
    f64 T1,T2,S1,S2,C1,C2,R1,R2,h;
    s32 m = 1;
    s32 n = 1;
    s32 k;
    h= _high - _low;
    T1=0.5*h*(f(_high)+f(_low));
    while(m<=MAXREPT)
    {
        double sum=0.0;
        for(k=0;k<n;k++)
        {
            double x=_low+(k+0.5)*h;
            sum=sum+f(x);
        }
        n=n*2;
        h=h*0.5;
        T2=0.5*(T1+2*h*sum);
        S1=(4*T2-T1)/3;
        if(m==1)
        {
            T1=T2;
            ++m;
            continue;
        }
        S2=(4*T2-T1)/3;
        C1=(16*S2-S1)/15;
        if(m==2)
        {
            S1=S2;
            T1=T2;
            ++m;
            continue;
        }
        S2=(4*T2-T1)/3;
        C2=(16*S2-S1)/15;
        if(m==3)
        {
            R1=(64*C2-C1)/63;
            C1=C2;
            S1=S2;
            T1=T2;
            ++m;
            continue;
        }
        if(m>=4)
        {
            R2=(64*C2-C1)/63;
            if(fabs(R2-R1)<_e)
                break;
            R1=R2;
            C1=C2;
            S1=S2;
            T1=T2;
            ++m;
        }
    }
    return R2;
}
