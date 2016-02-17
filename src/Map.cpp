#include <iostream>
#include <cmath>

#include "Map.hh"
#include <list>

Map::Map(GameEngine& ge, std::size_t w, std::size_t h):_engine(ge)
{
  ABlock*	b;
  std::size_t	x, y;

  _width = w;
  _height = h;
  if (_width > 100)
    _width = 100;
  if (_height > 100)
    _height = 100;

  x = 0;
  while (x < _width)
    {
      y = 0;
      while (y < _height)
	{
	  if (x == 0 || y == 0 ||
	      x == (_width - 1) ||
	      y == (_height - 1))
	    {
	      b = new BlockWall(_engine, x, y);
	      _walls.push_back(b);
	    }
	  else if ((x % 2) == 0 && (y % 2) == 0)
	    {
	      b = new BlockWall(_engine, x, y);
	      _walls.push_back(b);
	    }
	  else
	    {
	      b = new BlockGround(_engine, x, y);
	      _grounds.push_back(b);
	    }
	  y += 1;
	}
      x += 1;
    }
}

Map::~Map()
{
}

glm::vec2		Map::getPlayerStartPosition(void) const
{
  std::list<Player*>::const_iterator	it;
  std::list<ABlock*>::const_iterator	it2;
  glm::vec2		start_pos;

  while (true)
    {
      start_pos = glm::vec2(rand() % (_width - 1) + 1,
			    rand() % (_height - 1) + 1);
      it = _engine.getHumanPlayerList().begin();
      while (it != _engine.getHumanPlayerList().end())
	{
	  if ((*it)->getPosition().x == start_pos.x &&
	      (*it)->getPosition().y == start_pos.y)
	    break;
	  it++;
	}
      if (isReachable(glm::vec3(start_pos, 0)))
	return (start_pos);
    }
}

bool                  Map::isAloneOn(Player* pl, ABlock* b)
{
  std::list<Player*>::const_iterator	it;
  std::list<Bomb*>::const_iterator	it2;

  it = _engine.getHumanPlayerList().begin();
  while (it != _engine.getHumanPlayerList().end())
    {
      if (*it != pl &&
	  getGroundFromPosition((*it)->getPosition()) == b)
	return (false);
      it++;
    }
  it = _engine.getAIPlayerList().begin();
  while (it != _engine.getAIPlayerList().end())
    {
      if (*it != pl &&
	  getGroundFromPosition((*it)->getPosition()) == b)
	return (false);
      it++;
    }
  it2 = _engine.getBombList().begin();
  while (it2 != _engine.getBombList().end())
    {
      if (getGroundFromPosition((*it2)->getPosition()) == b)
	return (false);
      it2++;
    }
  return (true);
}

bool		Map::playerIsAround(int x, int y, float dist_max, Player* pl)
{
  std::list<Player*>::const_iterator	it;
  float	dist;

  it = _engine.getHumanPlayerList().begin();
  while (it != _engine.getHumanPlayerList().end())
    {
      dist = pow((*it)->getPosition().y - y, 2) +
	pow((*it)->getPosition().x - x, 2);
      if (pl != *it &&
	  dist < dist_max)
	return (true);
      it++;
    }
  it = _engine.getAIPlayerList().begin();
  while (it != _engine.getAIPlayerList().end())
    {
      dist = pow((*it)->getPosition().y - y, 2) +
	pow((*it)->getPosition().x - x, 2);
      if (pl != *it &&
	  dist < dist_max)
	return (true);
      it++;
    }
  return (false);
}

void Map::addCrate(const int percent)
{
  ABlock*	b;
  std::size_t x;
  std::size_t y;

  x = 1;
  while (x < (_width - 2))
  {
    y = 1;
    while (y < (_height - 2))
    {
      if (!playerIsAround(x, y, 4, NULL) &&
	  (rand() % 100 < percent) && ((x % 2) != 0 || (y % 2) != 0))
      {
        b = new BlockCrate(_engine, x, y);
        _crates.push_back(b);
      }
      y++;
    }
    x++;
  }
}

bool				Map::isReachable(const glm::vec3& pos) const
{
  std::vector<ABlock*>::const_iterator	it;

  it = _walls.begin();
  while (it != _walls.end())
    {
      if ((*it)->getPosition().x == pos.x &&
	  (*it)->getPosition().y == pos.y)
	return (false);
      it++;
    }
  it = _crates.begin();
  while (it != _crates.end())
    {
      if ((*it)->getPosition().x == pos.x &&
	  (*it)->getPosition().y == pos.y)
	return (false);
      it++;
    }
  return (true);
}

bool				Map::playerIsOut(const Player& player) const
{
  std::vector<ABlock*>::const_iterator	it;


  if (player.getPosition().x < 0 ||
      player.getPosition().x > _width ||
      player.getPosition().y < 0 ||
      player.getPosition().y > _height)
    return (true);
  it = _walls.begin();
  while (it != _walls.end())
    {
      if ((*it)->isInBlock(player.getPosition(), 0.7))
        return (true);
      it++;
    }
  it = _crates.begin();
  while (it != _crates.end())
    {
      if ((*it)->isInBlock(player.getPosition(), 0.7))
        return (true);
      it++;
    }
  return (false);
}

ABlock*		Map::getGroundFromPosition(const glm::vec3& pos)
{
  std::vector<ABlock*>::const_iterator it;

  it = _grounds.begin();
  while (it != _grounds.end())
    {
      if ((*it)->isInBlock(pos, 0.5))
	return (*it);
      it++;
    }
  return (NULL);
}

bool			Map::destroyCrate(const glm::vec3& pos)
{
  std::vector<ABlock*>::iterator  it;
  ABlock*	b = NULL;

  if (isWall(pos))
    return (false);

  it = _crates.begin();
  while (it != _crates.end())
  {
    if ((*it)->getPosition() == pos) {
      b = static_cast<ABlock*>(*it);
      it = _crates.erase(it);
    } else
      it++;
  }
  if (b == NULL)
    return (true);
  it = _board.begin();
  while (it != _board.end())
  {
    if (b == *it) {
      it = _board.erase(it);
    } else
      it++;
  }
  delete b;
  return (false);
}

std::vector<ABlock*>* Map::getWalls() {
  return (&_walls);
}

std::vector<ABlock*>* Map::getCrates() {
  return (&_crates);
}

bool Map::isWall(const glm::vec3 & pos) const {
  std::vector<ABlock*>::const_iterator  it;

  it = _walls.begin();
  while (it != _walls.end()) {
    if ((*it)->getPosition() == pos)
      return (true);
    it++;
  }
  return (false);
}

bool Map::isCrate(const glm::vec3 & pos) const {
  std::vector<ABlock*>::const_iterator  it;

  it = _crates.begin();
  while (it != _crates.end()) {
    if ((*it)->getPosition() == pos)
      return (true);
    it++;
  }
  return (false);
}

std::size_t Map::getWidth() const {
  return (_width);
}

std::size_t Map::getHeight() const {
  return (_height);
}
