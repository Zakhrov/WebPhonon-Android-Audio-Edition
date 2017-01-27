cmake_minimum_required(VERSION 2.8.11)
project(webphonon-android-audio-edition)
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)
find_package(Qt5Multimedia)
find_package(Qt5OpenGL)

set(webphonon_android_src main.cpp mainwindow.cpp visualizer.cpp)
set(webphonon_android_rsc icons.qrc shaders.qrc)

add_executable(webphonon_android ${webphonon_android_src} ${webphonon_android_rsc})
qt5_use_modules(webphonon_android Core Gui Widgets OpenGL Multimedia)

target_link_libraries(webphonon_android ${QT_LIBRARIES} ${OPENGL_LIBRARIES} ${PHONON_LIBRARY})
install(TARGETS webphonon_android DESTINATION bin)
set(CPACK_PACKAGE_VERSION 0.1.1)
SET(CPACK_GENERATOR "RPM")
SET(CPACK_SOURCE_PACKAGE_FILE_NAME "WebPhonon-Qt5-2.0")
include (CPack)
