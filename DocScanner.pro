TEMPLATE = subdirs
SUBDIRS += DocScannerLibrary
SUBDIRS += ScannerTestApp

ScannerTestApp.depends = DocScannerLibrary
