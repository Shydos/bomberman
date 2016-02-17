
#include "ABlock.hh"

glm::vec3       ABlock::_vertices[4] = {
  glm::vec3(-0.5, -0.5, -0.5),
  glm::vec3(0.5, 0.5, -0.5),
  glm::vec3(0.5, -0.5, -0.5),
  glm::vec3(-0.5, 0.5, -0.5)
};

bool		ABlock::initialize()
{
  return (true);
}

bool		ABlock::isInBlock(const glm::vec3& position, float delta) const
{
  if (position.x < (_position.x + delta) && position.x > (_position.x - delta) &&
      position.y < (_position.y + delta) && position.y > (_position.y - delta))
    return (true);
  return (false);
}
