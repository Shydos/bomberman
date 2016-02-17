#include "Explosion.hh"

gdl::Texture Explosion::_texture;
bool Explosion::_is_texture_loaded = false;

Explosion::Explosion(int x, int y, GameEngine& ge):_engine(ge)
{
  _position.x = x;
  _position.y = y;
  _position.z = -0.7;
  _elapsed_time = 0.0;
  _engine.addExplosion(this);
  _engine.addObject(this);
}

Explosion::~Explosion()
{
  _engine.rmvObject(this);
}

bool Explosion::initialize() {
    _scale = glm::vec3(1, 1, 1);

    if (_is_texture_loaded == false) {
        if (!_texture.load("./assets/Explosion.tga")) {
            std::cerr << "Cannot load the texture." << std::endl;
            return (false);
        }
        _is_texture_loaded = true;
    }

    _geometry.setColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

    _geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5));
    _geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5));
    _geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
    _geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5));

    _geometry.pushUv(glm::vec2(0.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 1.0f));
    _geometry.pushUv(glm::vec2(0.0f, 1.0f));

    _geometry.build();

    return (true);
}

void		Explosion::kill(void)
{
  std::list<Player*>::iterator it;

  it = _engine.setHumanPlayerList().begin();
  while (it != _engine.getHumanPlayerList().end())
    {
      if (isInExplosion(**it))
	(*it)->die();
      it++;
    }
  it = _engine.setAIPlayerList().begin();
  while (it != _engine.getAIPlayerList().end())
    {
      if (isInExplosion(**it))
	(*it)->die();
      it++;
    }
}

bool		Explosion::isInExplosion(const AObject& obj)
{
  if (obj.getPosition().x < (_position.x + 0.5) &&
      obj.getPosition().x > (_position.x - 0.5) &&
      obj.getPosition().y < (_position.y + 0.5) &&
      obj.getPosition().y > (_position.y - 0.5))
    return (true);
  return (false);
}

void Explosion::update(const gdl::Clock& clock, gdl::Input &input) {
    (void)input;

    kill();
    _elapsed_time += clock.getElapsed();
}

void Explosion::draw(gdl::AShader& shader, const gdl::Clock& clock) {
    (void)clock;

    _texture.bind();
    _geometry.draw(shader, getTransformation(), GL_QUADS);

}

const glm::vec3&  Explosion::getPosition(void) const {
    return _position;
}

double Explosion::getElapsedTime() const {
    return (_elapsed_time);
}
