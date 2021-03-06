#include "Door.h"
#include "Switch.h"
#include "Entities.h"
#include "ResourceManager.h"
#include "Animation.h"
#include <iostream>

#include "util/parsing.h"

Door::Door(unsigned int id, std::string name, std::vector<std::string> params) :
    Entity(id, name, params)
{
}

Door::~Door()
{

}

void Door::initParameters(std::vector<std::string> params)
{
    Entity::initParameters(params);

    for (auto it : params)
    {
        auto key = it.substr(0, it.find(" "));
        auto value = it.substr(it.find(" ") + 1);

        if (key == "openSwitches")
        {
            auto switches = parse_ints(value);

            for (auto id : switches)
            {
                openSwitches.push_back((Switch*) Entities::getById(id));
            }
        }
        else if (key == "openSwitchesRequired")
        {
            openSwitchesRequired = std::stoi(value);   
        }
    }
}

EntityType Door::getEntityType()
{
    return ET_DOOR;
}

std::string Door::getEntityDescription()
{
    // TODO --- this entity vector to IDs string will probably be used elsewhere, so maybe move it
    std::string openSwitchesString = "";
    for (auto it : openSwitches)
    {
        openSwitchesString += std::to_string(it->getId()) + " ";
    }

    return std::to_string(id) + " Door " + name + "\n"
        + getCommonParameters()
        + writeParameter("texture", "world_entities.png")
        + writeParameter("animation", "door_closed")
        + writeParameter("openSwitchesRequired", openSwitchesRequired)
        + writeParameter("openSwitches", openSwitchesString);
}

void Door::update(float dt)
{
    Entity::update(dt);

    int numSwitchesPressed = 0;

    for (auto s : openSwitches)
    {
        if (s->isPressed())
        {
            numSwitchesPressed++;       
        }
    }

    if (numSwitchesPressed >= openSwitchesRequired)
    {
        open();
    }
    else
    {
        close();
    }
}

void Door::handleEntityCollision(Entity *other)
{
    switch (other->getEntityType())
    {
    default:
        break;
    }
}

void Door::open()
{
    auto currentAnimationName = currentAnimation->getName();
    if (currentAnimationName == "door_closed")
    {
        playAnimation("door_opening");
    }
    else if (currentAnimationName == "door_closing")
    {
        int fromFrame = currentAnimation->getFrameCount() - currentFrame;
        playAnimation("door_opening", fromFrame);
    }
}

void Door::close()
{
    auto currentAnimationName = currentAnimation->getName();

    if (currentAnimationName == "door_opening")
    {
        int fromFrame = currentAnimation->getFrameCount() - currentFrame;
        playAnimation("door_closing", fromFrame);
    }
}