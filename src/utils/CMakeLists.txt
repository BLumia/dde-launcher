# SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
#
# SPDX-License-Identifier: CC0-1.0

find_package(Qt5 REQUIRED Quick)

add_library(launcher-utils OBJECT)

target_sources(launcher-utils
PRIVATE
    iconutils.h
    iconutils.cpp
    categoryutils.h
    categoryutils.cpp
)

target_include_directories(launcher-utils PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(launcher-utils PRIVATE Qt::Core Qt::Gui Qt::Svg Dtk::Widget)
