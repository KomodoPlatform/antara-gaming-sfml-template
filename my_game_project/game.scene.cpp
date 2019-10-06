/******************************************************************************
 * Copyright © 2013-2019 The Komodo Platform Developers.                      *
 *                                                                            *
 * See the AUTHORS, DEVELOPER-AGREEMENT and LICENSE files at                  *
 * the top-level directory of this distribution for the individual copyright  *
 * holder information and the developer policies on copyright and licensing.  *
 *                                                                            *
 * Unless otherwise agreed in a custom licensing agreement, no part of the    *
 * Komodo Platform software, including this file may be copied, modified,     *
 * propagated or distributed except according to the terms contained in the   *
 * LICENSE file                                                               *
 *                                                                            *
 * Removal or modification of this copyright notice is prohibited.            *
 *                                                                            *
 ******************************************************************************/

#include <iostream>
#include <entt/entity/helper.hpp>
#include <antara/gaming/ecs/component.position.hpp>
#include <antara/gaming/ecs/component.layer.hpp>
#include <antara/gaming/sfml/component.drawable.hpp>
#include <antara/gaming/scenes/change.scene.event.hpp>
#include <antara/gaming/config/config.game.hpp>
#include "game.scene.hpp"
#include "intro.scene.hpp"

namespace my_game_name_space
{
    game_scene::game_scene(entt::registry &entity_registry) noexcept : base_scene(entity_registry)
    {
        std::cout << "hello from " << scene_name() << std::endl;

        //! load a font
        auto handle = resource_mgr.load_font("sansation.ttf");

        //! Get window information
        auto &window_info = entity_registry_.ctx<antara::gaming::config::game_cfg>().win_cfg;

        //! Create a dummy entity
        auto dummy_entity = entity_registry_.create();

        //! attach a text component to it
        auto &txt_cmp = entity_registry_.assign<antara::gaming::sfml::text>(dummy_entity,
                                                                            sf::Text("Game Scene", *handle, 30));
        sf::Text &txt = txt_cmp.drawable;
        txt.setFillColor(sf::Color::Green);
        txt.setOrigin(txt.getLocalBounds().width / 2.0f, txt.getLocalBounds().height / 2.0f);

        //! attach a component position to the entity
        this->entity_registry_.assign<antara::gaming::ecs::component::position>(dummy_entity,
                                                                                static_cast<float>(window_info.width) /
                                                                                2.f,
                                                                                static_cast<float>(window_info.height) /
                                                                                2.f);

        //! attach a tag component to the entity
        entity_registry_.assign<entt::tag<"game_scene"_hs >>(dummy_entity);

        //! attach a layer to the entity
        this->entity_registry_.assign<antara::gaming::ecs::component::layer<0>>(dummy_entity);
    }

    void game_scene::update() noexcept
    {

    }

    bool game_scene::on_key_released(const antara::gaming::event::key_released &) noexcept
    {
        return false;
    }

    bool game_scene::on_key_pressed(const antara::gaming::event::key_pressed &evt) noexcept
    {
        if (evt.key == antara::gaming::input::key::space) {
            this->dispatcher_.trigger<antara::gaming::event::change_scene>(
                    std::make_unique<intro_scene>(this->entity_registry_), false);
        }
        return false;
    }

    std::string game_scene::scene_name() noexcept
    {
        return "game_scene";
    }

    game_scene::~game_scene() noexcept
    {
        auto view = entity_registry_.view<entt::tag<"game_scene"_hs>>();
        entity_registry_.destroy(view.begin(), view.end());
    }
}
