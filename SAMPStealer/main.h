#pragma once

#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS 1

typedef signed char					int8_t;
typedef unsigned char				uint8_t;
typedef signed short				int16_t;
typedef unsigned short				uint16_t;
typedef signed int					int32_t;
typedef unsigned int				uint32_t;
typedef signed long long			int64_t;
typedef unsigned long long			uint64_t;

// API/SDK
#include <windows.h>
#include <stdio.h> 
#include <stddef.h>
#include <stdlib.h>
#include <process.h>

void SetupHook(void);

// Main stuff
#include "samp.h"
