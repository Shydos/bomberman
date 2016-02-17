#ifndef MENUENGINE_HH_
#define MENUENGINE_HH_

#include <Game.hh>
#include <SdlContext.hh>
#include <Clock.hh>
#include <Input.hh>
#include <Texture.hh>
#include <Geometry.hh>
#include <BasicShader.hh>
#include <Model.hh>

#include <OpenGL.hh>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <string>

#include "Background.hh"
#include "ButtonMenu.hh"
#include "ButtonSelector.hh"
#include "NumLabel.hh"
#include "GameEngine.hh"
#include "SoundEngine.hh"


class ButtonSelector;
class Scene;
class SceneManager;
class MenuEngine : public gdl::Game {
private:
  gdl::SdlContext		_context;
  gdl::Clock			_clock;
  gdl::Input			_input;
  gdl::BasicShader		_shader;
  glm::vec3			_cam_pos;
  Background			_background;
  std::vector<ButtonMenu*>	_objects;
  std::vector<NumLabel*>	_labels;
  ButtonSelector*		_selector;
  ButtonMenu*			_current_button;
  bool				_active;
  SoundEngine*			_sound_menu;
    
public:
    bool		initialize();
    bool		update();
    void		draw();
    void		loadHome();
    void		loadGameConfig();
    NumLabel*	        getLabel(std::string);
    void		loadWinner(int);
public:
    MenuEngine();
    ~MenuEngine();
    ButtonMenu* getPrevButton();
    ButtonMenu* getNextButton();
    ButtonMenu* getCurrButton();
};

#endif /* !MENUENGINE_HH_ */
