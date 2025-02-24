QT       += core gui
QT += network
QT += charts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Adm_sala_satis.cpp \
    Adm_user_manage.cpp \
    Adm_user_satis.cpp \
    Admin.cpp \
    Admin_salary_manage.cpp \
    FileBackup.cpp \
    FindUser.cpp \
    Find_password.cpp \
    User.cpp \
    User_per_manage.cpp \
    User_salary.cpp \
    base_lei.cpp \
    check.cpp \
    inquiry_base_information.cpp \
    inquiry_base_salary.cpp \
    io_base.cpp \
    main.cpp \
    login.cpp \
    satis.cpp \
    send_email.cpp \
    sort_base_information.cpp \
    sort_salary.cpp \
    sta_function.cpp

HEADERS += \
    Adm_sala_satis.h \
    Adm_user_manage.h \
    Adm_user_satis.h \
    Admin.h \
    Admin_salary_manage.h \
    Filebackup.h \
    FindUser.h \
    Find_password.h \
    User.h \
    User_per_manage.h \
    User_salary.h \
    base_lei.h \
    check.h \
    inquiry_base_information.h \
    inquiry_base_salary.h \
    io_base.h \
    login.h \
    satatis.h \
    send_email.h \
    sort_base_information.h \
    sort_salary.h

FORMS += \
    adm_sala_satis.ui \
    adm_user_manage.ui \
    adm_user_satis.ui \
    admin.ui \
    admin_salary_manage.ui \
    find_password.ui \
    login.ui \
    user.ui \
    user_per_manage.ui \
    user_salary.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    pic.qrc
