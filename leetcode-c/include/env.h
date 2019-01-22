//
// Created by zhang_li on 2018/10/12.
//
#pragma once
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdint.h"
#include "stdbool.h"
#include "stdarg.h"


#ifdef _WIN32
#define ALog(format, ...) { printf(format, __VA_ARGS__); \
							printf("\n%s", "");}
#else
#include "android/log.h"
#define ALog(...) __android_log_print(ANDROID_LOG_INFO, "foxlee", __VA_ARGS__)
#endif
