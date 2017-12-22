#引入一个和日志相关的库文件
LOCAL_LDLIBS += -llog

#隐藏 都以JNIEXPORT为前缀 过滤 + gc-sections 丢弃未使用的函数
LOCAL_CPPFLAGS + = -ffunction-sections -fdata-sections -fvisibility = hidden
LOCAL_CPPFLAGS + = -ffunction-sections -fdata-sections -fvisibility = hidden
LOCAL_CFLAGS + = -ffunction-sections -fdata-sections LOCAL_LDFLAGS + = -Wl， -  gc -sections

ifeq ($(TARGET_ARCH),mips)
  LOCAL_LDFLAGS += -Wl,--gc-sections
else
  LOCAL_LDFLAGS += -Wl,--gc-sections,--icf=safe
endif