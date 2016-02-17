#ifndef HUMANPLAYER_HH_
# define HUMANPLAYER_HH_

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

# include "GameEngine.hh"

class PlayerInput;
class Camera;
class GameEngine;

class HumanPlayer : public Player
{
protected:
  PlayerInput		_player_input;
public:
  HumanPlayer(const size_t id, GameEngine& engine, const PlayerInput&);
  virtual ~HumanPlayer();

  virtual bool			initialize();
  virtual void			update(const gdl::Clock& clock, gdl::Input& input);
  virtual void			draw(gdl::AShader& shader, const gdl::Clock& clock);
};

#endif // !HUMANPLAYER_HH_
