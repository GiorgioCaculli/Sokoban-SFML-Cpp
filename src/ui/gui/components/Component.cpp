#include "Component.hpp"

using namespace sokoban::ui::gui;

Component::Component()
: _is_selected( false )
, _is_active( false )
{
}

Component::~Component()
{
}

bool Component::is_selected() const
{
    return _is_selected;
}

void Component::select()
{
    _is_selected = true;
}

void Component::deselect()
{
    _is_selected = false;
}

bool Component::is_active() const
{
    return _is_active;
}

void Component::activate()
{
    _is_active = true;
}

void Component::deactivate()
{
    _is_active = false;
}
