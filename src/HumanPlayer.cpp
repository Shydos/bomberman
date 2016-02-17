
#include "Player.hh"
#include "GameEngine.hh"
#include "PlayerInput.hh"

#include "HumanPlayer.hh"

HumanPlayer::HumanPlayer(const size_t id, GameEngine &ge, const PlayerInput& pi) : Player(ge)
{
  _id = id;
  _score = 0;
  glm::vec2 pos;
  _camera = new Camera(_engine);
  pos = _engine.getMap()->getPlayerStartPosition();
  _position = glm::vec3(pos, -0.5);
  _camera->initialize();
  _camera->follow(this);
  _player_input = pi;
  _engine.addHumanPlayer(this);
  _engine.addObject(this);
}

HumanPlayer::~HumanPlayer()
{
  _engine.rmvObject(this);
  delete _camera;
}

bool HumanPlayer::initialize()
{
  _scale = glm::vec3(0.0020f, 0.0016f, 0.0025f);
  _rotation = glm::vec3(90.0f, 0.0f, 0.0f);

  if (!_model.load("./assets/marvin.fbx")) {
    std::cerr << "Cannot load the model." << std::endl;
    return (false);
  }
  if (!_model.createSubAnim(0, _walk_anim, 36, 53)) {
    std::cerr << "Cannot generate sub-anim." << std::endl;
    return (false);
  }
  if (!_model.createSubAnim(0, _stop_anim, 0, 0)) {
    std::cerr << "Cannot generate sub-anim." << std::endl;
    return (false);
  }
  return (true);
}

void HumanPlayer::update(const gdl::Clock& clock, gdl::Input &input)
{
  glm::vec3		old_pos;
  bool          got_input;

  _direction = glm::vec3(0, 0, 0);
  got_input = false;
  if (input.getKey(_player_input.getKeyUp()))
  {
    _direction += glm::vec3(0, 1, 0);
    _rotation = glm::vec3(90.0f, 180.0f, 0.0f);
    got_input = true;
    if (!_moving) {
      _model.setCurrentSubAnim(_walk_anim);
      _moving = true;
    }
  }
  if (input.getKey(_player_input.getKeyDown())) {
    _direction += glm::vec3(0, -1, 0);
    _rotation = glm::vec3(90.0f, 0.0f, 0.0f);
    got_input = true;
    if (!_moving) {
      _model.setCurrentSubAnim(_walk_anim);
      _moving = true;
    }
  }
  if (input.getKey(_player_input.getKeyLeft()))
  {
    _direction += glm::vec3(-1, 0, 0);
    _rotation = glm::vec3(90.0f, 270.0f, 0.0f);
    got_input = true;
    if (!_moving) {
      _model.setCurrentSubAnim(_walk_anim);
      _moving = true;
    }
  }
  if (input.getKey(_player_input.getKeyRight()))
  {
    _direction += glm::vec3(1, 0, 0);
    _rotation = glm::vec3(90.0f, 90.0f, 0.0f);
    got_input = true;
    if (!_moving) {
      _model.setCurrentSubAnim(_walk_anim);
      _moving = true;
    }
  }

  old_pos = _position;
  translate(_direction * static_cast<float>(clock.getElapsed()) * _speed);
  _position = collide(old_pos, _position);

  if (!got_input) {
    _model.setCurrentSubAnim(_stop_anim);
    _moving = false;
  }

  if (input.getKey(_player_input.getKeyBomb(), true))
    {
      putBomb();
    }
  if (mustDie())
    _is_dead = true;
  grabItem();
}

void				HumanPlayer::draw(gdl::AShader& shader,
					     const gdl::Clock& clock)
{
  _model.draw(shader, getTransformation(), clock.getElapsed());
}
