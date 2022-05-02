cmake_minimum_required(VERSION 2.8)

#set(CMAKE_OSX_ARCHITECTURES ppc;x86_64)
#set(CMAKE_OSX_DEPLOYMENT_TARGET 10.4)
#set(CMAKE_OSX_SYSROOT "/Developer/SDKs/MacOSX10.4u.sdk")

project(WxReddit C CXX)

cmake_policy(SET CMP0054 OLD)
cmake_policy(SET CMP0015 OLD)

set(CMAKE_CXX_STANDARD 11)

option(HEADERBAR "Uses unified titlebar and toolbar (OSX/Gtk3 Only)" ON)
option(GTK_STYLE "Uses libhandy (Gtk3) / libgranite (Gtk3) styling" ON)

find_package(wxWidgets REQUIRED COMPONENTS core base adv html)
find_package(PkgConfig REQUIRED)

include(${wxWidgets_USE_FILE})

set(BUILD_TEST OFF)
add_subdirectory(lib/libreddit)

set(SOURCE src/main/main.cpp src/main/MainApp.cpp src/main/MainFrame.cpp src/main/Table.cpp src/main/Util.cpp src/main/MainFrameCust.cpp)
set(LIBS ${wxWidgets_LIBRARIES} -L${CMAKE_SOURCE_DIR}/lib)
set(INCLUDE DIRS "")
set(LINK_DIRS "")

if(APPLE)
    set(SOURCE ${SOURCE} src/main/specific/Cocoa.mm)
endif()

if(UNIX AND NOT APPLE)
    pkg_check_modules(GTK3 gtk+-3.0)
    pkg_check_modules(GTK2 gtk+-2.0)

    pkg_check_modules(GRANITE granite)
    pkg_check_modules(HANDY libhandy-1)

    find_package(Qt5 COMPONENTS Widgets)

if(${GTK3_FOUND})
	set(SOURCE ${SOURCE} src/main/specific/Gtk.c)
elseif(${Qt5_FOUND})
    set(SOURCE ${SOURCE} src/main/specific/Qt.cpp)
endif()

endif()

add_executable(WxReddit MACOSX_BUNDLE ${SOURCE})

target_include_directories(WxReddit PRIVATE lib/libreddit/include)

if(${GTK3_FOUND})
    set(INCLUDE_DIRS ${INCLUDE_DIRS} ${GTK3_INCLUDE_DIRS})
    set(LINK_DIRS ${LINK_DIRS} ${GTK3_LIBRARIES})
    set(LIBS ${LIBS} ${GTK3_LIBRARIES})
elseif(${Qt5_FOUND})
    set(LIBS ${LIBS} Qt5::Widgets)
endif()

if(HEADERBAR)
    message("Using headerbar")
    target_compile_definitions(WxReddit PUBLIC USE_HEADERBAR)
endif()

if("GTK_STYLE" AND "${GRANITE_FOUND}")
    message("Using elementary theming (granite)")
    target_compile_definitions(WxReddit PUBLIC USE_GRANITE)

    set(LIBS ${LIBS} ${GRANITE_LIBRARIES})
    set(LINK_DIRS ${LINK_DIRS} ${GRANITE_LIBRARIES})
    set(INCLUDE_DIRS ${INCLUDE_DIRS} ${GRANITE_INCLUDE_DIRS})
elseif("GTK_STYLE" AND "${HANDY_FOUND}")
    message("Using gnome theming (libhandy)")
    target_compile_definitions(WxReddit PUBLIC USE_HANDY)

    set(LIBS ${LIBS} ${HANDY_LIBRARIES})
    set(LINK_DIRS ${LINK_DIRS} ${HANDY_LIBRARIES})
    set(INCLUDE_DIRS ${INCLUDE_DIRS} ${HANDY_INCLUDE_DIRS})
endif()

#set_target_properties(WxReddit PROPERTIES
#        BUNDLE True
#        MACOSX_BUNDLE_GUI_IDENTIFIER uk.co.therhys.WxReddit
#        MACOSX_BUNDLE_BUNDLE_NAME MacTube
#        MACOSX_BUNDLE_BUNDLE_VERSION "${CMAKE_PROJECT_VERSION}"
#        MACOSX_BUNDLE_SHORT_VERSION_STRING "${CMAKE_PROJECT_VERSION}"
#        MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/res/Info.plist
#        MACOSX_BUNDLE_ICON_FILE "${CMAKE_SOURCE_DIR}/res/MacTube.icns"
#        )

#set_source_files_properties("${CMAKE_SOURCE_DIR}/res/MacTube.icns" PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
#file(COPY "${CMAKE_SOURCE_DIR}/res/MacTube.icns" DESTINATION "MacTube.app/Contents/Resources")

target_compile_definitions(WxReddit PUBLIC NO_EXPORT)

include_directories(${INCLUDE_DIRS})
link_directories(${LINK_DIRS})

target_link_libraries(WxReddit reddit request ${LIBS})
