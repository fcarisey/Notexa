#pragma once

#include <stdio.h>

#define LOG_RAW(msg, line, file) printf("LOG: %s (line %d, file %s)\n", msg, line, file)
#define LOG(msg) LOG_RAW(msg, __LINE__, __FILE__)
