QT -= core gui
TEMPLATE = lib
CONFIG += staticlib
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += \
    scan_lib.cpp


HEADERS += \
    scan_lib.hpp \
    scan_lib_test.hpp
