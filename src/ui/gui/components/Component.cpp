#include <ui/gui/components/Component.hpp>

using namespace sokoban::ui::gui;

/**
 * Component's initializer
 * By default, it is neither selected nor active
 */
Component::Component()
    : _is_selected( false )
      , _is_active( false )
{
}

/**
 * Destructor with no specific action
 */
Component::~Component()
= default;

/**
 * Getter meant to retrieve whether a component is selected or not
 */
bool Component::is_selected() const
{
    return _is_selected;
}

/**
 * Setter meant to define a component as selected
 */
void Component::select()
{
    _is_selected = true;
}

/**
 * Setter meant to define a component as deselected
 */
void Component::deselect()
{
    _is_selected = false;
}

/**
 * Getter meant to retrieve whether a component is active or not
 */
bool Component::is_active() const
{
    return _is_active;
}

/**
 * Setter meant to define a component as active
 */
void Component::activate()
{
    _is_active = true;
}

/**
 * Setter meant to define a component as non active
 */
void Component::deactivate()
{
    _is_active = false;
}
