#include "MenuEngine.hh"

MenuEngine::MenuEngine()
{
  _active = true;
}

bool		MenuEngine::initialize()
{
  if (!_context.start(1920, 1080, "Bomberman",
		      SDL_INIT_VIDEO,
		      SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP))
    {
      std::cerr << "context start failed." << std::endl;
      return (false);
    }
  glEnable(GL_DEPTH_TEST);

  if (!_shader.load("./GDL/shaders/basic.fp", GL_FRAGMENT_SHADER) ||
      !_shader.load("./GDL/shaders/basic.vp", GL_VERTEX_SHADER) ||
      !_shader.build())
    {
      std::cerr << "shader load failed." << std::endl;
      return (false);
    }
  glm::mat4	projection;
  glm::mat4	transformation;

  projection = glm::perspective(60.0f, 800.0f/600.0f, 0.1f, 100.0f);
  transformation = glm::lookAt(glm::vec3(0.400, 0.300, 0.52), glm::vec3(0.400, 0.300, 0.0), glm::vec3(0, 1, 0));
  _shader.bind();
  _shader.setUniform("view", transformation);
  _shader.setUniform("projection", projection);
  if (_background.initialize() == false)
    {
      std::cerr << "Background init failed" << std::endl;
      return (false);
    }
  _sound_menu = new SoundEngine();
  _sound_menu->loadMusic("menubg", "./assets/menu.ogg");
  _sound_menu->volumeMusic(40);
  loadHome();
  return (true);
}

void		MenuEngine::loadHome()
{
  _sound_menu->playMusic("menubg");
  _objects.clear();
  _labels.clear();
  ButtonMenu*         button_play = new ButtonMenu("play", 0.500, 0.300, "buttonplay.tga");
  button_play->initialize();
  _objects.push_back(button_play);
  _current_button = button_play;

  ButtonMenu*         button_load = new ButtonMenu("load", 0.500, 0.200, "buttonload.tga");
  button_load->initialize();
  _objects.push_back(button_load);

  ButtonMenu*         button_exit = new ButtonMenu("exit", 0.500, 0.100, "buttonexit.tga");
  button_exit->initialize();
  _objects.push_back(button_exit);

  ButtonSelector*     button_bomb = new ButtonSelector("selector", 0.510, _current_button->getPosition().y, "selector.tga", *this);
  button_bomb->initialize();
  _selector = button_bomb;
}

void		MenuEngine::loadWinner(int winner)
{
  _sound_menu->playMusic("menubg");
  _objects.clear();
  _labels.clear();
  ButtonMenu*	button_win = new ButtonMenu("winner", 0.500, 0.350, "player1win.tga");
  if (winner == 1)
    button_win->setPicture("player1win.tga");
  else if (winner == 2)
    button_win->setPicture("player2win.tga");
  else
    button_win->setPicture("AIwin.tga");
  button_win->initialize();
  _objects.push_back(button_win);

  ButtonMenu*         button_home = new ButtonMenu("winner_home", 0.500, 0.200, "back.tga");
  button_home->initialize();
  _objects.push_back(button_home);
  _current_button = button_home;
  _selector->setPosition(_current_button->getPosition().x, _current_button->getPosition().y, _selector->getPosition().z);

  ButtonMenu*         button_exit = new ButtonMenu("winner_exit", 0.500, 0.100, "buttonexit.tga");
  button_exit->initialize();
  _objects.push_back(button_exit);
}

NumLabel*       MenuEngine::getLabel(std::string button_name)
{
  for (std::vector<NumLabel*>::iterator it = _labels.begin(); it != _labels.end(); it++)
    {
      if ((*it)->getName() == button_name)
	return (*it);
    }
  return (NULL);
}


void		MenuEngine::loadGameConfig()
{
  _objects.clear();
  _labels.clear();

  ButtonMenu*		button_nbplayer = new ButtonMenu("nb_player", 0.250, 0.350, "Human.tga");
  button_nbplayer->initialize();
  _objects.push_back(button_nbplayer);
  _current_button = button_nbplayer;

  NumLabel*		num_nbplayer = new NumLabel("nb_player", 0.550, 0.350, 1);
  num_nbplayer->initialize();
  _labels.push_back(num_nbplayer);

  ButtonMenu*		button_nbIA = new ButtonMenu("nb_IA", 0.250, 0.290, "IA_players.tga");
  button_nbIA->initialize();
  _objects.push_back(button_nbIA);

  NumLabel*		num_nbIA = new NumLabel("nb_IA", 0.550, 0.290, 0);
  num_nbIA->initialize();
  _labels.push_back(num_nbIA);

  ButtonMenu*		button_mapwidth = new ButtonMenu("mapwidth", 0.250, 0.230, "Map_x.tga");
  button_mapwidth->initialize();
  _objects.push_back(button_mapwidth);

  NumLabel*		num_mapwidth = new NumLabel("mapwidth", 0.550, 0.230, 16);
  num_mapwidth->initialize();
  _labels.push_back(num_mapwidth);

  ButtonMenu*		button_mapheight = new ButtonMenu("mapheight", 0.250, 0.170, "Map_y.tga");
  button_mapheight->initialize();
  _objects.push_back(button_mapheight);

  NumLabel*		num_mapheight = new NumLabel("mapheight", 0.550, 0.170, 16);
  num_mapheight->initialize();
  _labels.push_back(num_mapheight);

  ButtonMenu*		button_playgame = new ButtonMenu("playgame", 0.250, 0.110, "play.tga");
  button_playgame->initialize();
  _objects.push_back(button_playgame);

  ButtonMenu*		button_cancel = new ButtonMenu("cancel", 0.250, 0.050, "back.tga");
  button_cancel->initialize();
  _objects.push_back(button_cancel);

  _selector->setPosition(_current_button->getPosition().x, _current_button->getPosition().y, _selector->getPosition().z);

}

bool		MenuEngine::update()
{
  if (_input.getKey(SDLK_ESCAPE) || _input.getKey(SDL_QUIT) || _active == false)
    return (false);
  _context.updateClock(_clock);
  _context.updateInputs(_input);

  if (_input.getKey(SDLK_DOWN, true))
    {
      _current_button = getNextButton();
      if (_current_button->getName() == "winner")
	{
	  _current_button = getNextButton();
	}
    }
  if (_input.getKey(SDLK_LEFT, true))
    {
      if (_current_button->getName() == "nb_player")
	{
	  if (getLabel("nb_player")->getValue() == 1)
	    getLabel("nb_player")->setLabel(2);
	  else
	    getLabel("nb_player")->setLabel(getLabel("nb_player")->getValue() - 1);
	}
      if (_current_button->getName() == "nb_IA")
	{
	  if (getLabel("nb_IA")->getValue() == 0)
	    getLabel("nb_IA")->setLabel(100);
	  else
	    getLabel("nb_IA")->setLabel(getLabel("nb_IA")->getValue() - 1);
	}
      if (_current_button->getName() == "mapwidth")
	{
	  if (getLabel("mapwidth")->getValue() == 16)
	    getLabel("mapwidth")->setLabel(999);
	  else
	    getLabel("mapwidth")->setLabel(getLabel("mapwidth")->getValue() - 1);
	}
      if (_current_button->getName() == "mapheight")
	{
	  if (getLabel("mapheight")->getValue() == 16)
	    getLabel("mapheight")->setLabel(999);
	  else
	    getLabel("mapheight")->setLabel(getLabel("mapheight")->getValue() - 1);
	}
    }

  if (_input.getKey(SDLK_RIGHT, true))
    {
      if (_current_button->getName() == "nb_player")
	{
	  if (getLabel("nb_player")->getValue() == 2)
	    getLabel("nb_player")->setLabel(1);
	  else
	    getLabel("nb_player")->setLabel(getLabel("nb_player")->getValue() + 1);
	}
      if (_current_button->getName() == "nb_IA")
	{
	  if (getLabel("nb_IA")->getValue() == 100)
	    getLabel("nb_IA")->setLabel(0);
	  else
	    getLabel("nb_IA")->setLabel(getLabel("nb_IA")->getValue() + 1);
	}
      if (_current_button->getName() == "mapwidth")
	{
	  if (getLabel("mapwidth")->getValue() == 999)
	    getLabel("mapwidth")->setLabel(16);
	  else
	    getLabel("mapwidth")->setLabel(getLabel("mapwidth")->getValue() + 1);
	}
      if (_current_button->getName() == "mapheight")
	{
	  if (getLabel("mapheight")->getValue() == 999)
	    getLabel("mapheight")->setLabel(16);
	  else
	    getLabel("mapheight")->setLabel(getLabel("mapheight")->getValue() + 1);
	}
    }
  if (_input.getKey(SDLK_UP, true))
    {
      _current_button = getPrevButton();
      if (_current_button->getName() == "winner")
	{
	  _current_button = getPrevButton();
	}
    }
  if (_input.getKey(SDLK_RETURN, true))
    {
      if (_current_button->getName() == "play")
	{
	  loadGameConfig();
	  return (true);
	}
      if (_current_button->getName() == "load")
	{
	  return (true);
	}
      if (_current_button->getName() == "exit" || _current_button->getName() == "winner_exit")
	{
	  _active = false;
	  return (true);
	}
      if (_current_button->getName() == "playgame")
	{
	  GameEngine    engine(_context);
	  int		nbPlayer;
	  int		nbIA;
	  int		mapWidth;
	  int		mapHeight;

	  nbPlayer = getLabel("nb_player")->getValue();
	  nbIA = getLabel("nb_IA")->getValue();
	  mapWidth = getLabel("mapwidth")->getValue();
	  mapHeight = getLabel("mapheight")->getValue();

	  _sound_menu->stopMusic("menubg");
	  if (engine.initialize(nbPlayer, nbIA, mapWidth, mapHeight) == false)
	    {
	      std::cerr << "Init failed." << std::endl;
	      return (EXIT_FAILURE);
	    }
	  while (engine.update() == true)
	    engine.draw();
	  loadWinner(engine.getWinner());
	  return (true);
	}
      if (_current_button->getName() == "cancel" || _current_button-> getName() == "winner_home")
	{
	  loadHome();
	  return (true);
	}
    }
  return (true);
}

void		MenuEngine::draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  for (size_t i = 0; i < _objects.size(); i++)
    _objects[i]->draw(_shader, _clock);
  for (size_t i = 0; i < _labels.size(); i++)
    {
      _labels[i]->draw(_shader, _clock);
    }
  _background.draw(_shader, _clock);
  _selector->draw(_shader, _clock);
  glViewport(0, 0, 1920, 1080);
  _context.flush();
}

MenuEngine::~MenuEngine()
{
    delete _sound_menu;
    for (size_t i = 0; i < _objects.size(); i++)
        delete _objects[i];
    _context.stop();
}


ButtonMenu*     MenuEngine::getNextButton()
{
  if (_current_button->getName() == _objects[_objects.size() - 1]->getName())
    {
      _selector->setPosition(_selector->getPosition().x, _objects[0]->getPosition().y, _selector->getPosition().z);
      return (_objects[0]);
    }
  for (std::vector<ButtonMenu*>::iterator i = _objects.begin(); i != _objects.end(); ++i)
    {
      if ((*i)->getName() == _current_button->getName())
	{
	  _selector->setPosition(_selector->getPosition().x, (*++i)->getPosition().y, _selector->getPosition().z);
	  return ((*i));
	}
    }
  return (NULL);
}
ButtonMenu*     MenuEngine::getPrevButton()
{

  if (_current_button->getName() == _objects[0]->getName())
    {
      _selector->setPosition(_selector->getPosition().x, _objects[_objects.size() - 1]->getPosition().y, _selector->getPosition().z);
      return (_objects[_objects.size() - 1]);
    }
  for (std::vector<ButtonMenu*>::iterator i = _objects.begin(); i != _objects.end(); ++i)
    {
      if ((*i)->getName() == _current_button->getName())
	{
	  _selector->setPosition(_selector->getPosition().x, (*--i)->getPosition().y, _selector->getPosition().z);
	  return ((*i));
	}
    }
  return (NULL);
}

ButtonMenu* MenuEngine::getCurrButton() {
  return (_current_button);
}
