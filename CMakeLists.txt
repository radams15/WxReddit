cmake_minimum_required(VERSION 3.0)
project(WxReddit)

set(CMAKE_CXX_STANDARD 11)

include_directories(lib)
find_package(wxWidgets REQUIRED COMPONENTS core base adv)
find_package(PkgConfig REQUIRED)

include(${wxWidgets_USE_FILE})

#set(CMAKE_OSX_ARCHITECTURES ppc;x86_64)

set(SOURCE main.cpp MainApp.cpp MainFrame.cpp Table.cpp Util.cpp MainFrameCust.cpp)
set(LIBS ${wxWidgets_LIBRARIES} -L${CMAKE_SOURCE_DIR}/lib)

if(APPLE)
    set(SOURCE ${SOURCE} MacOsSpecific.mm)
endif()

if(UNIX AND NOT APPLE)
    pkg_check_modules(GTK gtk+-3.0 REQUIRED)
    set(SOURCE ${SOURCE} GtkSpecific.c)
endif()

add_executable(WxReddit MACOSX_BUNDLE ${SOURCE})

if(UNIX AND NOT APPLE)
    target_include_directories(WxReddit PRIVATE ${GTK_INCLUDE_DIRS})
    target_link_directories(WxReddit PRIVATE ${GTK_LIBRARIES})
    set(LIBS ${LIBS} ${GTK_LIBRARIES})
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

target_link_libraries(WxReddit reddit ${LIBS})
