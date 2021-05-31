QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    cpp_httplib/httplib.h \
    include/Python-ast.h \
    include/Python.h \
    include/abstract.h \
    include/accu.h \
    include/asdl.h \
    include/ast.h \
    include/bitset.h \
    include/bltinmodule.h \
    include/boolobject.h \
    include/bytearrayobject.h \
    include/bytes_methods.h \
    include/bytesobject.h \
    include/cellobject.h \
    include/ceval.h \
    include/classobject.h \
    include/code.h \
    include/codecs.h \
    include/compile.h \
    include/complexobject.h \
    include/datetime.h \
    include/descrobject.h \
    include/dictobject.h \
    include/dtoa.h \
    include/dynamic_annotations.h \
    include/enumobject.h \
    include/errcode.h \
    include/eval.h \
    include/fileobject.h \
    include/fileutils.h \
    include/floatobject.h \
    include/frameobject.h \
    include/funcobject.h \
    include/genobject.h \
    include/graminit.h \
    include/grammar.h \
    include/import.h \
    include/intrcheck.h \
    include/iterobject.h \
    include/listobject.h \
    include/longintrepr.h \
    include/longobject.h \
    include/marshal.h \
    include/memoryobject.h \
    include/metagrammar.h \
    include/methodobject.h \
    include/modsupport.h \
    include/moduleobject.h \
    include/namespaceobject.h \
    include/node.h \
    include/object.h \
    include/objimpl.h \
    include/opcode.h \
    include/osdefs.h \
    include/parsetok.h \
    include/patchlevel.h \
    include/pgen.h \
    include/pgenheaders.h \
    include/py_curses.h \
    include/pyarena.h \
    include/pyatomic.h \
    include/pycapsule.h \
    include/pyconfig.h \
    include/pyctype.h \
    include/pydebug.h \
    include/pyerrors.h \
    include/pyexpat.h \
    include/pyfpe.h \
    include/pygetopt.h \
    include/pyhash.h \
    include/pymacconfig.h \
    include/pymacro.h \
    include/pymath.h \
    include/pymem.h \
    include/pyport.h \
    include/pystate.h \
    include/pystrcmp.h \
    include/pystrtod.h \
    include/pythonrun.h \
    include/pythread.h \
    include/pytime.h \
    include/rangeobject.h \
    include/setobject.h \
    include/sliceobject.h \
    include/structmember.h \
    include/structseq.h \
    include/symtable.h \
    include/sysmodule.h \
    include/token.h \
    include/traceback.h \
    include/tupleobject.h \
    include/typeslots.h \
    include/ucnhash.h \
    include/unicodeobject.h \
    include/warnings.h \
    include/weakrefobject.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
