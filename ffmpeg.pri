#如果用的是ffmpeg4内核请将ffmpeg3改成ffmpeg4,两种内核不兼容,头文件也不一样
DEFINES += ffmpeg4

#ffmpeg4则使用ffmpeg4的目录
contains(DEFINES, ffmpeg4) {
strPath = ffmpeg4
} else {
strPath = ffmpeg3
}

#表示64位的构建套件
strLib = winlib64
strInclude = include64
#由于Qt4不支持QT_ARCH所以会执行下面的
#如果用的64位的Qt4则需要自行修改
strLib = winlib
strInclude = include
}

INCLUDEPATH += $$PWD/$$strPath/$$strInclude
LIBS += -L$$PWD/$$strPath/$$strLib/ -lavcodec -lavfilter -lavformat -lswscale -lavutil -lswresample -lavdevice
