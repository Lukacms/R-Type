//
// Created by kane on 14/12/23.
//

#include <rtype/Components/SpriteComponent.hh>
#include <SFML/Graphics.hpp>
#include <rtype/SparseArray.hpp>
#include <rtype/InputManager.hpp>

namespace rtype
{

    const constexpr int STANDARD_WIDTH{800};
    const constexpr int STANDARD_HEIGHT{600};
    const constexpr char *STANDARD_TITLE{"R-TYPE"};

    class GraphicModule
    {
        public:
            explicit GraphicModule(unsigned int width = STANDARD_WIDTH,
                                   unsigned int height = STANDARD_HEIGHT,
                                   const std::string &title = STANDARD_TITLE);
            ~GraphicModule() = default;
            GraphicModule(const GraphicModule &) = delete;
            GraphicModule(GraphicModule &&) = delete;
            GraphicModule &operator=(const GraphicModule &) = delete;
            GraphicModule &operator=(GraphicModule &&) = delete;

            void update();
            void draw_components(SparseArray<SpriteComponent> sprites);
            void draw(sf::Sprite &sprite);
            void display();
            void clear();
            bool is_input_pressed(sf::Keyboard::Key key);
            [[nodiscard]] bool is_window_open();

        private:
            sf::VideoMode m_mode;
            sf::RenderWindow m_window;
            InputManager m_input;
    };
} // namespace rtype
