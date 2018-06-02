#include "shadow.h"

Shadow::Shadow(Location* masa_center)
{
    this->masa_center = masa_center;
}

Shadow::~Shadow()
{
    for(int i = 0; i < this->forms.size(); i++)
    {
        delete this->forms[i];
    }
    delete this->masa_center;
}

void Shadow::AddForm(Circle* circle)
{
    this->forms.push_back(circle);
}

bool Shadow::CollidesWith(Shadow* other_shadow)
{
    bool collides = false;
    int i = 0;
    while(!collides && i < this->forms.size())
    {
        //TODO
    }
}

void Shadow::Move(Location* location)
{
    for(int i = 0; i < this->forms.size(); i++)
    {
        Location* center = this->forms[i]->GetCenter();
    }
}
