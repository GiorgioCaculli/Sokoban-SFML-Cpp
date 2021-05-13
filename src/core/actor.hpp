#ifndef SOKOBAN_CPP_ACTOR_HPP
#define SOKOBAN_CPP_ACTOR_HPP

namespace com
{
    namespace masticass
    {
        namespace sokoban
        {
            namespace core
            {
                class Actor
                {
                private:
                    const int SPACE = 20;
                    int _x;
                    int _y;

                public:
                    Actor( int x, int y );

                    virtual ~Actor();

                    void setX( int x );

                    int getX() const;

                    void setY( int y );

                    int getY() const;

                    bool is_left_collision( Actor *actor );

                    bool is_right_collision( Actor *actor );

                    bool is_top_collision( Actor *actor );

                    bool is_bottom_collision( Actor *actor );
                };
            }
        }
    }
}


#endif //SOKOBAN_CPP_ACTOR_HPP
