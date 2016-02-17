
#ifndef BOMB_HH_
# define BOMB_HH_

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

# include "AObject.hpp"
# include "GameEngine.hh"

class GameEngine;
class Player;

class Bomb : public AObject
{
protected:
  static gdl::Model _model;
  static bool _is_model_loaded;
protected:
  GameEngine&			_engine;
  gdl::Geometry		_geometry;
  std::size_t			_range;
  double			_elapsed_time;
  Player*			_player;
public:
  Bomb(int x, int y, GameEngine& ge, float range, Player *player);
  virtual ~Bomb();
public:
  virtual bool initialize();
  virtual void update(const gdl::Clock& clock, gdl::Input& input);
  virtual void draw(gdl::AShader& shader, const gdl::Clock& clock);
public:
  virtual const Player*	getPlayer(void) const;
  virtual void		setPlayer(Player*);
  virtual void explode();
  virtual void explodeCrate(glm::vec3 pos) const;
  virtual const glm::vec3&  getPosition(void) const;
  double getElapsedTime() const;
};

#endif // BOMB_HH_
