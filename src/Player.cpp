#include "Player.hh"

Player::Player(GameEngine &ge) :_engine(ge)
{
  _position = glm::vec3(0, 0, -0.5);
  _destination = _position;
  _moving = false;
  _bomb_range = 2;
  _bomb_max = 1;
  _bomb_count = 0;
  _is_dead = false;
  _speed = 5.0f;
  _direction = glm::vec3(0, 0, 0);
  _walk_anim = "walk";
  _stop_anim = "stop";
  _id = 0;
}

Player::~Player()
{
  std::list<Bomb*>::const_iterator	it;

  it = _engine.getBombList().begin();
  while (it != _engine.getBombList().end())
  {
    if ((*it)->getPlayer() == this)
      (*it)->setPlayer(NULL);
    it++;
  }
}

void	Player::die(void)
{
  _is_dead = true;
}

bool Player::isDead(void) const
{
  return (_is_dead);
}

bool Player::initialize() {
  return (false);
}

void Player::update(const gdl::Clock& clock, gdl::Input &input) {
  (void)clock;
  (void)input;
}

void				Player::draw(gdl::AShader& shader,
                                 const gdl::Clock& clock) {
  (void)shader;
  (void)clock;
}

glm::vec3			Player::collide(const glm::vec3& old_pos,
						const glm::vec3& new_pos)
{
  if (_engine.getMap()->playerIsOut(*this))
    return (old_pos);
  if (!_engine.getMap()->isAloneOn(this, _engine.getMap()->getGroundFromPosition(new_pos)) &&
      _engine.getMap()->isAloneOn(this, _engine.getMap()->getGroundFromPosition(old_pos)))
    return (old_pos);
  return (new_pos);
}

bool				Player::mustDie(void)
{
  return (false);
}

void                Player::grabItem() {
  std::list<AItem*>::iterator	it;

  it = _engine.setItemList().begin();
  while (it != _engine.getItemList().end())
  {
    if ((*it)->isInItem(*this)) {
      _engine.getSoundEngine().playSound("item");
      if ((*it)->getItemType() == RANGE) {
        _bomb_range++;
      } else if ((*it)->getItemType() == COUNT) {
        _bomb_max++;
      } else if ((*it)->getItemType() == SPEED) {
        _speed += 0.20;
      }
      delete (*it);
      it = _engine.setItemList().erase(it);
      _score += 15;
    }
    it++;
  }
}

void				Player::setPosition(int x, int y)
{
  _position = glm::vec3(x, y, -0.5);
}

const glm::vec3&		Player::getPosition(void) const
{
  return (_position);
}

void				Player::putBomb()
{
  if (_bomb_count < _bomb_max) {
    new Bomb(_position.x + 0.5, _position.y + 0.5, _engine, _bomb_range, this);
    _bomb_count++;
    if (_id > 0) {
      _engine.getSoundEngine().playSound("peter");
    }
  }
}

void Player::dead() {
  _rotation = glm::vec3(180.0f, 0.0f, 0.0f);
}

std::size_t Player::getBombCount() const {
    return (_bomb_count);
}

void Player::setBombCount(std::size_t count) {
    _bomb_count = count;
}

Camera& Player::getCamera() {
  return (*_camera );
}

size_t Player::getScore() const {
  return (_score);
}

void Player::addScore(size_t score) {
  _score += score;
}

size_t Player::getId() const {
  return (_id);
}
