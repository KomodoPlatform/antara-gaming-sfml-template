set(ICON)
configure_icon_osx(data/osx/kmd_logo.icns ICON kmd_logo.icns)
add_executable(${PROJECT_NAME} MACOSX_BUNDLE ${ICON})
target_sources(${PROJECT_NAME} PRIVATE main.cpp my_game_project.cpp game.scene.cpp intro.scene.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC antara::sfml antara::world antara::scenes)
if (USE_LUA_ANTARA_WRAPPER)
    target_link_libraries(${PROJECT_NAME} PUBLIC antara::lua)
endif ()

set_target_properties(${PROJECT_NAME}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/"
        )

magic_game_app_image_generation("${CMAKE_CURRENT_SOURCE_DIR}/data/linux"
        "org.antara.gaming.sfml.my_game_project.desktop"
        "org.antara.gaming.sfml.my_game_project.appdata.xml"
        "komodo_icon.png"
        ${PROJECT_NAME}
        MyGameProjectAppDir
        ${CMAKE_CURRENT_SOURCE_DIR}/assets
        )

if (APPLE)
    file(COPY assets DESTINATION ${CMAKE_BINARY_DIR}/bin/my_game_project.app/Contents/Resources)
    include(${CMAKE_CURRENT_SOURCE_DIR}/data/osx/my_game_project.cmake)
endif ()

if (WIN32)
    file(COPY assets DESTINATION ${CMAKE_BINARY_DIR}/bin/)
    file(COPY assets DESTINATION ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE})
    ADD_CUSTOM_COMMAND(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory "${SFML_BINARY_DIR}/lib" "${CMAKE_BINARY_DIR}/bin/"
            COMMENT "copying dlls …"
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
            )
endif ()

