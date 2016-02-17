#ifndef AIPLAYER_HH_
# define AIPLAYER_HH_

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

class AIPlayer : public Player
{
public:
  AIPlayer(GameEngine& engine);
  virtual ~AIPlayer();

  virtual bool			initialize();
  virtual void			update(const gdl::Clock& clock, gdl::Input& input);
  virtual void			draw(gdl::AShader& shader, const gdl::Clock& clock);
};

#endif // !AIPLAYER_HH_
