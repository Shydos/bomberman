#include "AItem.hh"

AItem::~AItem() {}

itemType AItem::getItemType() {
    return (_item_type);
}

double AItem::getElapsedTime() const {
    return (_elapsed_time);
}

bool AItem::isInItem(const AObject & obj) const
{
    if (obj.getPosition().x < (_position.x + 0.5) &&
                              obj.getPosition().x > (_position.x - 0.5) &&
        obj.getPosition().y < (_position.y + 0.5) &&
                              obj.getPosition().y > (_position.y - 0.5))
        return (true);
    return (false);
}