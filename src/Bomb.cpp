
#include "Bomb.hh"
#include "Explosion.hh"
#include "ItemRange.hh"
#include "ItemCount.hh"
#include "ItemSpeed.hh"

gdl::Model Bomb::_model;
bool Bomb::_is_model_loaded = false;

Bomb::Bomb(int x, int y, GameEngine& ge, float range, Player *player) : _engine(ge)
{
  _player = player;
  _position = glm::vec3(x, y, -0.60);
  _range = range;
  _elapsed_time = 0.0;
  _engine.addBomb(this);
  _engine.addObject(this);
}

Bomb::~Bomb()
{
  _engine.rmvObject(this);
}

bool Bomb::initialize()
{
  _scale = glm::vec3(0.0018f, 0.0018f, 0.0018f);
  _rotation = glm::vec3(90.0f, 0.0f, 0.0f);
  
  if (_is_model_loaded == false) {
    if (!_model.load("./assets/Bomb.fbx")) {
      std::cerr << "Cannot load the model." << std::endl;
      return (false);
    }
    _is_model_loaded = true;
  }
  return (true);
}

void Bomb::update(const gdl::Clock& clock, gdl::Input &input)
{
    (void)input;

    _elapsed_time += clock.getElapsed();
}

void Bomb::draw(gdl::AShader& shader, const gdl::Clock& clock) {
    _model.draw(shader, getTransformation(), clock.getElapsed());
}

const Player*		Bomb::getPlayer(void) const
{
  return (_player);
}

void			Bomb::setPlayer(Player* p)
{
  _player = p;
}

void Bomb::explodeCrate(glm::vec3 pos) const {
    int nb;

    _engine.getMap()->destroyCrate(pos);
    new Explosion(pos.x, pos.y, _engine);

    nb = rand() % 100;
    if (nb <= 20) {
        new ItemRange(pos.x, pos.y, _engine);
    }
    else if ((nb > 20) && (nb <= 40)) {
        new ItemCount(pos.x, pos.y, _engine);
    }
    else if ((nb > 40) && (nb <= 60)) {
        new ItemSpeed(pos.x, pos.y, _engine);
    }
    if (_player)
        _player->addScore(10);
}

void Bomb::explode() {
    int i;
    bool spread;
    glm::vec3 pos;

    _engine.getSoundEngine().playSound("explosion");
    new Explosion(_position.x, _position.y, _engine);
    i = 1;
    pos.x = _position.x;
    pos.y = _position.y;
    pos.z = 0;
    spread = true;
    while (spread && (i <= (int)_range)) {
        i++;
        pos.x++;
        if (_engine.getMap()->isWall(pos)) {
            spread = false;
        } else if (_engine.getMap()->isCrate(pos)) {
            explodeCrate(pos);
            spread = false;
        } else {
	    new Explosion(pos.x, pos.y, _engine);
	  }
    }
    i = 1;
    pos.x = _position.x;
    pos.y = _position.y;
    spread = true;
    while (spread && (i <= (int)_range)) {
        i++;
        pos.x--;
        if (_engine.getMap()->isWall(pos)) {
            spread = false;
        } else if (_engine.getMap()->isCrate(pos)) {
            explodeCrate(pos);
            spread = false;
        } else {
	  new Explosion(pos.x, pos.y, _engine);
        }
    }
    i = 1;
    pos.x = _position.x;
    pos.y = _position.y;
    spread = true;
    while (spread && (i <= (int)_range)) {
        i++;
        pos.y++;
        if (_engine.getMap()->isWall(pos)) {
            spread = false;
        } else if (_engine.getMap()->isCrate(pos)) {
            explodeCrate(pos);
            spread = false;
        } else {
	  new Explosion(pos.x, pos.y, _engine);
        }
    }
    i = 1;
    pos.x = _position.x;
    pos.y = _position.y;
    spread = true;
    while (spread && (i <= (int)_range)) {
        i++;
        pos.y--;
        if (_engine.getMap()->isWall(pos)) {
            spread = false;
        } else if (_engine.getMap()->isCrate(pos)) {
            explodeCrate(pos);
            spread = false;
        } else {
	  new Explosion(pos.x, pos.y, _engine);
        }
    }
    if (_player) {
        _player->setBombCount(_player->getBombCount() - 1);
    }
}

const glm::vec3&  Bomb::getPosition(void) const {
    return _position;
}

double Bomb::getElapsedTime() const {
    return (_elapsed_time);
}
