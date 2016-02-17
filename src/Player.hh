#ifndef PLAYER_HH_
# define PLAYER_HH_

# include <SdlContext.hh>
# include <Clock.hh>
# include <Input.hh>
# include <Texture.hh>
# include <Geometry.hh>
# include <BasicShader.hh>
# include <Model.hh>

# include <OpenGL.hh>
# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>

# include <iostream>
# include <list>

# include "AObject.hpp"
# include "GameEngine.hh"
# include "PlayerInput.hh"

class PlayerInput;
class Camera;
class GameEngine;

class Player : public AObject
{
protected:
  GameEngine&		_engine;
  gdl::Geometry		_geometry;
  Camera*		_camera;
  glm::vec3		_direction;
  std::string   _walk_anim;
  std::string   _stop_anim;
  bool			_moving;
  bool			_is_dead;
  glm::vec3		_destination;
  float			_speed;
  gdl::Model	_model;
  std::size_t		_bomb_range;
  std::size_t		_bomb_max;
  std::size_t		_bomb_count;
  size_t            _score;
  size_t            _id;
public:
  Player(GameEngine& engine);
  virtual ~Player();
  
  virtual bool			initialize();
  virtual void			setPosition(int x, int y);
  virtual void			update(const gdl::Clock& clock, gdl::Input& input);
  virtual glm::vec3		collide(const glm::vec3&, const glm::vec3&);
  virtual void			draw(gdl::AShader& shader, const gdl::Clock& clock);
  virtual void			putBomb();
  virtual const glm::vec3&	getPosition(void) const;

  virtual void dead();
  virtual bool			isDead(void) const;
  virtual bool			mustDie(void);
  virtual void			die(void);
  virtual void          grabItem();
  virtual std::size_t getBombCount() const;
  virtual void setBombCount(std::size_t count);
  virtual Camera&		getCamera(void);
  virtual size_t        getScore() const;
  virtual void          addScore(size_t score);
  virtual size_t        getId() const;
};

#endif // !PLAYER_HH_
