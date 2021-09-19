#ifndef SOKOBAN_CPP_ACTOR_HPP
#define SOKOBAN_CPP_ACTOR_HPP

#include "../util/logger.hpp"

#include <SFML/Graphics.hpp>

namespace sokoban
{
    namespace core
    {
        using namespace sokoban::util;

        class Actor
        {
        private:
            const int SPACE = 20;
            float _x{};
            float _y{};
            Logger* logger{};
            sf::Sprite* sprite;
        public:
            Actor( float x, float y );

            virtual ~Actor();

            sf::Sprite get_texture();

            void set_texture( sf::Texture *texture );

            void setX( float x );

            float getX() const;

            void setY( float y );

            float getY() const;

            bool is_left_collision( Actor* actor ) const;

            bool is_right_collision( Actor* actor ) const;

            bool is_top_collision( Actor* actor ) const;

            bool is_bottom_collision( Actor* actor ) const;
        };
    }
}

#endif //SOKOBAN_CPP_ACTOR_HPP
