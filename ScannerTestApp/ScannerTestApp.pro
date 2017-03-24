TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += main.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../DocScannerLibrary/release/ -lDocScannerLibrary
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../DocScannerLibrary/debug/ -lDocScannerLibrary
else:unix: LIBS += -L$$OUT_PWD/../DocScannerLibrary/ -lDocScannerLibrary

INCLUDEPATH += $$PWD/../DocScannerLibrary
DEPENDPATH += $$PWD/../DocScannerLibrary

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../DocScannerLibrary/release/libDocScannerLibrary.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../DocScannerLibrary/debug/libDocScannerLibrary.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../DocScannerLibrary/release/DocScannerLibrary.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../DocScannerLibrary/debug/DocScannerLibrary.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../DocScannerLibrary/libDocScannerLibrary.a

LIBS += -lgtest -lgtest_main -lpthread
