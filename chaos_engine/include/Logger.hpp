#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "Export.hpp"
#ifdef ANDROID
#include <android/log.h>
#define SHOUT(...) ((void)__android_log_print(ANDROID_LOG_INFO,"ChaosDbg", __VA_ARGS__))
#else
#include <cstdio>
#define SHOUT(...) ((void)printf(__VA_ARGS__))
#endif

#endif //LOGGER_HPP
