#ffmpeg4则使用ffmpeg4的目录
strLib = lib
strInclude = include

INCLUDEPATH += $$PWD/$$strInclude
LIBS += -L$$PWD/$$strLib/ -lavcodec -lavfilter -lavformat -lswscale -lavutil -lavdevice
