#include "Actor.hpp"

#include <sstream>

using namespace sokoban::model;

/*
 * Dans ce cas, les images mesurent 64x64
 */
const float SPACE = 64.f;

/*
 * Ce constructeur va initialiser les différentes informations qui caractérisent notre acteur.
 * Sa coordonnée X.
 * Sa coordonnée Y.
 * L'asset pour le représenter graphiquement.
 */
Actor::Actor( float x, float y, std::array< float, 4 > asset_coords )
        : _x( x )
          , _y( y )
          , _asset_coords( asset_coords )
{
}

/*
 * Constructeur de copie
 */
Actor::Actor( const Actor &actor )
        : Actor( actor._x, actor._y, actor._asset_coords )
{
}

Actor &Actor::operator=( const Actor &actor )
{
    if ( &actor != this )
    {
        _x = actor._x;
        _y = actor._y;
        _asset_coords = actor._asset_coords;
    }
    return *this;
}

/*
 * Getter pour la coordonnée X.
 */
float Actor::get_x() const
{
    return _x;
}

/*
 * Setter pour la coordonnée X.
 */
void Actor::set_x( float x )
{
    this->_x = x;
}

/*
 * Getter pour la coordonnée Y.
 */
float Actor::get_y() const
{
    return _y;
}

/*
 * Setter pour la coordonnée Y.
 */
void Actor::set_y( float y )
{
    this->_y = y;
}

/*
 * Getter pour l'asset.
 */
std::array< float, 4 > Actor::get_asset_coords() const
{
    return _asset_coords;
}

/*
 * Setter pour l'asset.
 */
void Actor::set_asset_coords( std::array< float, 4 > asset_coords )
{
    this->_asset_coords = asset_coords;
}

/*
 * Définition basique de la fonction get_type
 * Toutes les sous-classes seront obligé de la redéfinir avec leur type d'acteur correspondant
 */
Actor::ID Actor::get_type() const
{
    return Actor::PLAYER;
}

/*
 * Fonction qui sert à vérifier si une collision par la gauche a lieu entre 2 acteurs.
 * Un acteur va faire appel à cette méthode et vérifiera le cas suivant:
 * Si la cordonnée X de l'acteur 1 - SPACE = la cordonnée X de l'acteur 2 (*actor)
 * et qu'ils sont sur le même axe Y
 * alors il y a bien collision entre les deux acteurs.
 */
bool Actor::is_left_collision( const Actor *actor ) const
{
    return get_x() - SPACE == actor->get_x() && get_y() == actor->get_y();
}

/*
 * Fonction qui sert à vérifier si une collision par la droite a lieu entre 2 acteurs.
 * Un acteur va faire appel à cette méthode et vérifiera le cas suivant:
 * Si la cordonnée X de l'acteur 1 + SPACE = la cordonnée X de l'acteur 2 (*actor)
 * et qu'ils sont sur le même axe Y
 * alors il y a bien collision entre les deux acteurs.
 */
bool Actor::is_right_collision( const Actor *actor ) const
{
    return get_x() + SPACE == actor->get_x() && get_y() == actor->get_y();
}

/*
 * Fonction qui sert à vérifier si une collision par le haut a lieu entre 2 acteurs.
 * Un acteur va faire appel à cette méthode et vérifiera le cas suivant:
 * Si la cordonnée Y de l'acteur 1 - SPACE = la cordonnée Y de l'acteur 2 (*actor)
 * et qu'ils sont sur le même axe X
 * alors il y a bien collision entre les deux acteurs.
 */
bool Actor::is_top_collision( const Actor *actor ) const
{
    return get_y() - SPACE == actor->get_y() && get_x() == actor->get_x();
}

/*
 * Fonction qui sert à vérifier si une collision par le bas a lieu entre 2 acteurs.
 * Un acteur va faire appel à cette méthode et vérifiera le cas suivant:
 * Si la cordonnée X de l'acteur 1 + SPACE = la cordonnée Y de l'acteur 2 (*actor)
 * et qu'ils sont sur le même axe X
 * alors il y a bien collision entre les deux acteurs.
 */
bool Actor::is_bottom_collision( const Actor *actor ) const
{
    return get_y() + SPACE == actor->get_y() && get_x() == actor->get_x();
}

std::string Actor::to_string() const
{
    std::stringstream ss;
    ss << "X: " << _x << " Y: " << _y;
    return ss.str();
}

/*
 * Fonction qui sert à redéfinir l'operateur <<
 * Cette redéfinition nous permettra d'afficer directement l'ostream
 */
std::ostream &sokoban::model::operator<<( std::ostream &os, const Actor &actor )
{
    os << actor.to_string();
    return os;
}

/*
 * Fonction qui sert à redéfinir l'operateur ==
 * Cette redéfinition nous permettra de vérifier l'égalité entre deux acteurs
 */
bool Actor::operator==( const Actor &actor ) const
{
    return _x == actor._x &&
            _y == actor._y &&
            _asset_coords == actor._asset_coords;
}

/*
 * Fonction qui sert à redéfinir l'operateur !=
 * Cette redéfinition nous permettra de vérifier l'inégalité entre deux acteurs
 */
bool Actor::operator!=( const Actor &actor ) const
{
    return !( actor == *this );
}
