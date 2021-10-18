#include "Actor.hpp"

#include <utility>

using namespace sokoban::model;

/*
 * Dans ce cas, les images mesurent 64x64
 */
const int SPACE = 64;

/*
 * Ce constructeur va initialiser les différentes informations qui caractérisent notre acteur.
 * Sa coordonnée X.
 * Sa coordonnée Y.
 * L'asset pour le représenter graphiquement.
 */
Actor::Actor( int x, int y, std::string asset )
        : x( x )
          , y( y )
          , asset( std::move( asset ) )
{
}

/*
 * Constructeur de copie
 */
Actor::Actor( const Actor &actor )
        : x( actor.x )
          , y( actor.y )
          , asset( actor.asset )
{
}

/*
 * Destructeur par défaut
 */
Actor::~Actor() = default;

/*
 * Getter pour la coordonnée X.
 */
int Actor::get_x() const
{
    return x;
}

/*
 * Setter pour la coordonnée X.
 */
void Actor::set_x( int x )
{
    this->x = x;
}

/*
 * Getter pour la coordonnée Y.
 */
int Actor::get_y() const
{
    return y;
}

/*
 * Setter pour la coordonnée Y.
 */
void Actor::set_y( int y )
{
    this->y = y;
}

/*
 * Getter pour l'asset.
 */
std::string Actor::get_asset() const
{
    return asset;
}

/*
 * Setter pour l'asset.
 */
void Actor::set_asset( std::string asset )
{
    this->asset = std::move( asset );
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

/*
 * Fonction qui sert à redéfinir l'operateur <<
 * Cette redéfinition nous permettra d'afficer directement l'ostream
 */
std::ostream &sokoban::model::operator<<( std::ostream &os, const Actor &actor )
{
    os << "x: " << actor.x << " y: " << actor.y;
    return os;
}

/*
 * Fonction qui sert à redéfinir l'operateur ==
 * Cette redéfinition nous permettra de vérifier l'égalité entre deux acteurs
 */
bool Actor::operator==( const Actor &actor ) const
{
    return x == actor.x &&
            y == actor.y &&
            asset == actor.asset;
}

/*
 * Fonction qui sert à redéfinir l'operateur !=
 * Cette redéfinition nous permettra de vérifier l'inégalité entre deux acteurs
 */
bool Actor::operator!=( const Actor &actor ) const
{
    return !( actor == *this );
}
