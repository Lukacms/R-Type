//
// Created by kane on 11/01/24.
//

#pragma once

#include <array>
#include <rtype/Components/SpriteComponent.hh>
#include <rtype/Components/TransformComponent.hh>

using njson = nlohmann::json;

namespace rclient
{

    constexpr int BG_SIZE{1024};
    constexpr std::string_view BG_BASE{"Background"};
    constexpr std::string_view BG_JSON_PATH{"./assets/configs/Backgrounds.json"};

    /**
     * @class BackgroundSpecifier
     * @brief Utils for background, to apply transform and sprite components
     *
     */
    struct BackgroundSpecifier {
        public:
            rtype::TransformComponent transform;
            rtype::SpriteComponent sprite;
    };

    /**
     * @class BackgroundRectangle
     * @brief Structure for the background. Has a texture's name, with its rectangle
     *
     */
    struct BackgroundRectangle {
        public:
            std::string name;
            rtype::utils::TextureRect rectangle;
    };

    /**
     * @class BackgroundManager
     * @brief Manage the game's backgrounds
     *
     */
    class BackgroundManager
    {
        public:
            BackgroundManager();
            BackgroundManager(BackgroundManager const &to_copy) = default;
            BackgroundManager(BackgroundManager &&to_move) = default;
            ~BackgroundManager() = default;
            BackgroundManager &operator=(BackgroundManager const &to_copy) = default;
            BackgroundManager &operator=(BackgroundManager &&to_move) = default;

            [[nodiscard]] std::array<BackgroundSpecifier, 2> get_backgrounds() const;
            void change_background(std::string &name);
            void update();

        private:
            void handle_change();

            std::string m_current_background{};
            std::string m_new_background{};
            bool is_fading_in{false};
            std::array<BackgroundSpecifier, 2> m_backgrounds{};
            std::vector<BackgroundRectangle> m_rectangles{};
    };
} // namespace rclient
