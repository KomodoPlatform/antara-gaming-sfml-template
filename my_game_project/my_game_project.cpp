#include <antara/gaming/sfml/graphic.system.hpp>
#include <antara/gaming/sfml/input.system.hpp>
#include <antara/gaming/scenes/scene.manager.hpp>

#ifdef USE_LUA_ANTARA_WRAPPER

#include <antara/gaming/lua/lua.system.hpp>

#endif

#include "my_game_project.hpp"
#include "intro.scene.hpp"

namespace my_game_name_space
{
    my_game_project::my_game_project() noexcept
    {
        //! Here it's the initialization of needed systems for the antara sfml game

#ifdef USE_LUA_ANTARA_WRAPPER
        auto &lua_scripting_system = this->system_manager_.create_system<antara::gaming::lua::scripting_system>();
#endif
        auto &graphic_system = this->system_manager_.create_system<antara::gaming::sfml::graphic_system>();
        this->system_manager_.create_system<antara::gaming::sfml::input_system>(graphic_system.get_window());

        //! Here you can choose to use scene through cpp files or lua
        auto &scene_manager = this->system_manager_.create_system<antara::gaming::scenes::manager>();

#ifdef USE_LUA_ANTARA_WRAPPER
        //!Uncomment the line below for using a lua scene system instead of the c++ one and comment the above c++ one.
        //lua_scripting_system.load_scripted_system("scenes_system.lua")
#endif

        //! Here you can initialize your own systems

        //! Here you can choose the starting scene (intro_scene by default)
        scene_manager.change_scene(std::make_unique<intro_scene>(entity_registry_), true);
    }
}
