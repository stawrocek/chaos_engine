LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := libFreeImage
LOCAL_SRC_FILES := libs/libFreeImage.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := libcpufeatures
LOCAL_SRC_FILES := libs/libcpufeatures.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
TARGET_PLATFORM := android-7
LOCAL_ARM_MODE := arm
LOCAL_MODULE := ChaosWrapper
LOCAL_SRC_FILES += ChaosWrapper.cpp ../app.cpp ../../src/Window.cpp ../../src/Scene.cpp ../../src/SceneManager.cpp ../../src/Renderer.cpp ../../src/InputManager.cpp ../../src/Transform.cpp ../../src/Texture.cpp ../../src/Application.cpp ../../src/MeshPrefab.cpp ../../src/ShaderProgram.cpp ../../src/Shader.cpp ../../src/VertexArray.cpp
LOCAL_C_INCLUDES += ../app.hpp 
LOCAL_ARM_MODE := arm
COMMON_CFLAGS := -Werror -DANDROID -DDISABLE_IMPORTGL \
-isystem $(SYSROOT)/usr/include/
ifeq ($(TARGET_ARCH),x86)
LOCAL_CFLAGS := $(COMMON_CFLAGS)
else
LOCAL_CFLAGS := -mfpu=vfp -mfloat-abi=softfp \
-fno-short-enums $(COMMON_CFLAGS)
endif
LOCAL_LDLIBS := -llog -lGLESv2 -Wl,-s
LOCAL_CPPFLAGS += -std=gnu++0x
LOCAL_STATIC_LIBRARIES += FreeImage cpufeatures
include $(BUILD_SHARED_LIBRARY)