//
// IMICompileConfig.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_CORE_COMPILE_CONFIG_H
#define IMI_CORE_COMPILE_CONFIG_H

#include <stdio.h>

#define LOG_ENABLE

#if defined(__ANDROID__)
#define IMI_ANDROID
#define IMI_API

#include <jni.h>
#include <android/log.h>
#include <android/bitmap.h>
#include <GLES3/gl3.h>
#define __gl2_h_

#include <GLES2/gl2ext.h>
#include <GLES3/gl3ext.h>
#include <EGL/egl.h>
#include <EGl/eglext.h>
#include <EGl/eglplatform.h>

#ifdef LOG_ENABLE

#define  LOG_TAG  "IMIngine"
#define  IMI_LOG_DEBUG(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  IMI_LOG_INFO(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define  IMI_LOG_ERROR(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define  IMI_LOG_ERROR_TE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

#else

#define  IMI_LOG_DEBUG(...)
#define  IMI_LOG_INFO(...)
#define  IMI_LOG_ERROR(...)
#endif

#endif


//MAC平台 或 IPHONE平台
#if defined(__MACOSX__) || defined(__APPLE__)

#define IMI_API

#include <TargetConditionals.h>

#if TARGET_OS_IPHONE

#define IMI_IOS
#include <UIKit/UIKit.h>
#include <Foundation/Foundation.h>
#include <OpenGLES/EAGL.h>
#include <GLKit/GLKit.h>
#include <OpenGLES/ES3/gl.h>
#include <OpenGLES/ES3/glext.h>
#define __gl3_h_

#elif TARGET_OS_MAC
#define IMI_OSX
#include <AppKit/AppKit.h>
#include <AppKit/NSOpenGL.h>
#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#include <GLKit/GLKit.h>
#include <OpenGL/OpenGL.h>
#endif

#ifdef LOG_ENABLE
#define  IMI_LOG_INFO(...)   printf(__VA_ARGS__);
#define  IMI_LOG_ERROR(...)  printf(__VA_ARGS__);
#define  IMI_LOG_DEBUG(...)  printf(__VA_ARGS__);
#else
#define  IMI_LOG_DEBUG(...) ;
#define  IMI_LOG_INFO(...)  ;
#define  IMI_LOG_ERROR(...) ;
#endif  //LOG_ENABLE

#endif  //__MACOSX__ || __APPLE__

#define _IMI_MTL_MAX_TEXTURES_ 4

#define _IMI_HAS_S64


//namesapce
namespace imi{ };


#endif // IMI_CORE_COMPILE_CONFIG_H
