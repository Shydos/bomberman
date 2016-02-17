
#include "AIPlayer.hh"

AIPlayer::AIPlayer(GameEngine &ge) : Player(ge) {
  glm::vec2 pos;
  pos = _engine.getMap()->getPlayerStartPosition();
  _position = glm::vec3(pos, -0.5);
  _engine.addAIPlayer(this);
  _engine.addObject(this);
}

AIPlayer::~AIPlayer()
{
  _engine.rmvObject(this);
}

bool AIPlayer::initialize()
{
  _scale = glm::vec3(0.00015f, 0.00015f, 0.00015f);
  _rotation = glm::vec3(90.0f, 0.0f, 0.0f);

  if (!_model.load("./assets/AIPLayer/AIPlayer.fbx")) {
    std::cerr << "Cannot load the model." << std::endl;
    return (false);
  }
  return (true);
}

void AIPlayer::update(const gdl::Clock& clock, gdl::Input &input)
{
  (void)input;
  glm::vec3		old_pos;
  bool          got_input;
  int		rnd;

  _direction = glm::vec3(0, 0, 0);
  got_input = false;
  rnd = rand() % 5;
  if (rnd != 0)
  {
    if (rnd % 2)
    {
      if (rnd == 2)
      {
        _direction += glm::vec3(0, 1, 0);
        _rotation = glm::vec3(90.0f, 180.0f, 0.0f);
      }
      else
      {
        _direction += glm::vec3(0, -1, 0);
        _rotation = glm::vec3(90.0f, 0.0f, 0.0f);
      }
    }
    else
    {
      if (rnd == 1)
      {
        _direction += glm::vec3(-1, 0, 0);
        _rotation = glm::vec3(90.0f, 270.0f, 0.0f);
      }
      else
      {
        _direction += glm::vec3(1, 0, 0);
        _rotation = glm::vec3(90.0f, 90.0f, 0.0f);
      }
    }
    got_input = true;
    if (!_moving) {
      _model.setCurrentSubAnim(_walk_anim);
      _moving = true;
    }
  }
  else
    putBomb();

  old_pos = _position;
  translate(_direction * static_cast<float>(clock.getElapsed()) * _speed);
  _position = collide(old_pos, _position);

  if (!got_input) {
    _model.setCurrentSubAnim(_stop_anim);
    _moving = false;
  }

  if (mustDie())
    _is_dead = true;
  grabItem();
}

void				AIPlayer::draw(gdl::AShader& shader,
					     const gdl::Clock& clock)
{
  _model.draw(shader, getTransformation(), clock.getElapsed());
}
