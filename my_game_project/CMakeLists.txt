add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE main.cpp my_game_project.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC antara::sfml antara::world antara::scenes)

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