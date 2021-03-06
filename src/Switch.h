#ifndef SWITCH_H_INCLUDED
#define SWITCH_H_INCLUDED

#include "Entity.h"

enum SwitchType
{
    ST_FLOOR,
    ST_TOGGLE
};

class Switch : public Entity
{
public:
    Switch(unsigned int id, std::string name, std::vector<std::string> params);
    ~Switch();

    void initParameters(std::vector<std::string> params);
    void update(float dt);
    std::string getEntityDescription();
    EntityType getEntityType();
    void handleEntityCollision(Entity* other);
    bool isPressed();

    void drawInspectorWidgets();

private:

    SwitchType type;
    bool pressed;
};

#endif