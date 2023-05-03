cmake_minimum_required(VERSION 3.7)

add_library(DDELauncherPlugin INTERFACE)
add_library(DDELauncher::Plugin ALIAS DDELauncherPlugin)
set_target_properties(DDELauncherPlugin PROPERTIES OUTPUT_NAME Plugin)
target_include_directories(DDELauncherPlugin INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
install(TARGETS DDELauncherPlugin EXPORT DDELauncherPluginTargets)
install(EXPORT DDELauncherPluginTargets
    FILE DDELauncherPluginTargets.cmake
    NAMESPACE DDELauncher::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/dde-launcher
)
