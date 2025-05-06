project(ASGUI)

add_executable(ASGUI
    src/ASGUIApp.cpp
    src/CMainFrame.cpp
 )

 target_include_directories(ASGUI PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(ASGUI PRIVATE ASCORE)

if (MSVC)
    target_compile_definitions(ASGUI PRIVATE -D_AFXDLL -DUNICODE -D_UNICODE)
    target_link_options(ASGUI PRIVATE /SUBSYSTEM:WINDOWS)

    # 가장 중요: MFC를 사용하겠다고 선언
    set_target_properties(ASGUI PROPERTIES
        VS_GLOBAL_UseOfMfc "Static"  # 또는 "Dynamic"
    )
endif()

set_target_properties(ASGUI PROPERTIES
    WIN32_EXECUTABLE TRUE
)
