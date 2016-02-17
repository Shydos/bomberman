
#include <cmath>
#include <fstream>
#include <unistd.h>
#include <iostream>

#include "GameEngine.hh"

#include "Bomb.hh"
#include "HumanPlayer.hh"
#include "AIPlayer.hh"
#include "Camera.hh"
#include "Map.hh"
#include "Explosion.hh"
#include "AItem.hh"
#include "GameBackground.hh"
#include "MenuEngine.hh"

GameEngine::GameEngine(gdl::SdlContext & context) : _context(context) {
}

GameEngine::~GameEngine()
{
  delete _map;
  delete _sound_engine;
  delete _score_manager;

  _objects.clear();
}

bool		GameEngine::initialize()
{
  return false;
}

bool		GameEngine::initialize(std::size_t nb_players, std::size_t nb_ai,
				       std::size_t x, std::size_t y)
{
  PlayerInput*	pi;
  std::size_t		i;

  _gameover = false;
  srand(time(NULL));

  _map = new Map(*this, x, y);
  _background = new GameBackground(*this);

  _sound_engine = new SoundEngine();
  _sound_engine->loadMusic("bg", "./assets/bgMusic.ogg");
  _sound_engine->volumeMusic(40);
  _sound_engine->playMusic("bg");
  _sound_engine->loadSound("explosion", "./assets/explosion.ogg");
  _sound_engine->loadSound("item", "./assets/item.ogg");
  _sound_engine->loadSound("peter", "./assets/peter.ogg");
  _sound_engine->volumeSound(60);

  _score_manager = new ScoreManager();

  i = 0;
  while (i < nb_players) {
    if (i == 0) {
      pi = new PlayerInput(SDLK_z, SDLK_s, SDLK_q, SDLK_d, SDLK_SPACE);
      new HumanPlayer(1, *this, *pi);
    }
    else if (i == 1) {
      pi = new PlayerInput(SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT, SDLK_RCTRL);
      new HumanPlayer(2, *this, *pi);
    }
    delete pi;
    i += 1;
  }
  if (nb_ai > 0) {
    i = 0;
    while (i < nb_ai) {
      new AIPlayer(*this);
      i += 1;
    }
  }
  _map->addCrate(70);
  return (true);
}

void	GameEngine::setWinner(int value)
{
  _winner = value;
}

int	GameEngine::getWinner()
{
  return (_winner);
}

bool		GameEngine::update()
{
  std::list<Player*>::iterator  it;
  std::list<Player*>::iterator  it5;
  std::list<Bomb*>::iterator  it2;
  std::list<Explosion*>::iterator  it3;
  std::list<AItem*>::iterator  it4;

  _context.updateClock(_clock);
  _context.updateInputs(_input);

  if (_gameover) {
    if (_human_player_list.size() == 1) {
      if (_human_player_list.front()->getId() == 1)
        _score_manager->saveNewScore("Player 1", _human_player_list.front()->getScore());
      else
        _score_manager->saveNewScore("Player 2", _human_player_list.front()->getScore());
      _score_manager->loadScores();
      _score_manager->clearScores();
      _score_manager->displayScores();
    }
      return (false);
  }
  if (_input.getKey(SDLK_ESCAPE) || _input.getKey(SDL_QUIT))
    return (false);

  it = _human_player_list.begin();
  while (it != _human_player_list.end())
  {
    (*it)->update(_clock, _input);
    if ((*it)->isDead())
    {
      rmvObject(*it);
      it = _human_player_list.erase(it);
    }
    else
      it++;
  }
  it5 = _ai_player_list.begin();
  while (it5 != _ai_player_list.end())
  {
    (*it5)->update(_clock, _input);
    if ((*it5)->isDead())
    {
      rmvObject(*it5);
      it5 = _ai_player_list.erase(it5);
    }
    else
      it5++;
  }
  it2 = _bomb_list.begin();
  while (it2 != _bomb_list.end())
  {
    (*it2)->update(_clock, _input);
    if ((*it2)->getElapsedTime() > 3.0) {
      (*it2)->explode();
      delete (*it2);
      it2 = _bomb_list.erase(it2);
    } else
      it2++;
  }
  it3 = _explosion_list.begin();
  while (it3 != _explosion_list.end())
  {
    (*it3)->update(_clock, _input);
    if ((*it3)->getElapsedTime() > 0.25) {
      delete (*it3);
      it3 = _explosion_list.erase(it3);
    } else
      it3++;
  }
  it4 = _item_list.begin();
  while (it4 != _item_list.end())
  {
    (*it4)->update(_clock, _input);
    if ((*it4)->getElapsedTime() > 10.0) {
      delete (*it4);
      it4 = _item_list.erase(it4);
    } else
      it4++;
  }
  _background->update(_clock, _input);

  if (_human_player_list.size() == 0)
  {
    setWinner(0);
    _gameover = true;
  }
  else if (_human_player_list.size() == 1 && _ai_player_list.size() == 0) {
    if (_human_player_list.front()->getId() == 1)
      setWinner(1);
    else
      setWinner(2);
    _gameover = true;
  }
  return (true);
}

void		GameEngine::draw()
{
  std::list<Player*>::const_iterator	it;
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (_human_player_list.size() == 2)
  {
    it = _human_player_list.begin();
    (*it)->getCamera().setProjection(glm::perspective(80.0f, 960.0f/1080.0f, 0.1f, 50.0f));
    (*it)->getCamera().draw(_clock);
    glViewport(0, 0, 960, 1080);

      it++;
      (*it)->getCamera().setProjection(glm::perspective(80.0f,
							960.0f/1080.0f,
							0.1f,
							50.0f));
      (*it)->getCamera().draw(_clock);
      glViewport(960, 0, 960, 1080);
    }
  else if (_human_player_list.size() == 1)
    {
      it = _human_player_list.begin();
      (*it)->getCamera().setProjection(glm::perspective(80.0f, 1920.0f/1080.0f, 0.1f, 50.0f));
      (*it)->getCamera().draw(_clock);
      glViewport(0, 0, 1920, 1080);
    }
  _context.flush();
}

void				GameEngine::addObject(AObject* obj)
{
  _objects.push_front(obj);
  if (!obj->initialize())
    exit(1);
}

void				GameEngine::addExplosion(Explosion* e)
{
  _explosion_list.push_front(e);
}

void				GameEngine::addBomb(Bomb* b)
{
  _bomb_list.push_front(b);
}

void				GameEngine::addItem(AItem* i)
{
  _item_list.push_front(i);
}

void				GameEngine::addHumanPlayer(HumanPlayer* p)
{
  _human_player_list.push_front(p);
}

void				GameEngine::addAIPlayer(AIPlayer* p)
{
  _ai_player_list.push_front(p);
}

void				GameEngine::rmvObject(AObject* obj)
{
  std::list<AObject*>::iterator	it;

  it = _objects.begin();
  while (it != _objects.end())
    {
      if (*it == obj)
	{
	  it = _objects.erase(it);
	}
      else
	it++;
    }
}

const std::list<AObject*>&	GameEngine::getObjects(void) const
{
  return (_objects);
}

Map*				GameEngine::getMap()
{
  return (_map);
}

const std::list<Bomb*>&		GameEngine::getBombList() const
{
  return (_bomb_list);
}

const std::list<Explosion*>&		GameEngine::getExplosionList() const
{
  return (_explosion_list);
}

const std::list<Player*>&		GameEngine::getHumanPlayerList() const
{
  return (_human_player_list);
}

const std::list<Player*>&		GameEngine::getAIPlayerList() const
{
  return (_ai_player_list);
}

const std::list<AItem*>&		GameEngine::getItemList() const
{
  return (_item_list);
}

std::list<Bomb*>&		GameEngine::setBombList()
 {
  return (_bomb_list);
}

std::list<Explosion*>&		GameEngine::setExplosionList()
 {
  return (_explosion_list);
}

std::list<Player*>&		GameEngine::setHumanPlayerList()
{
  return (_human_player_list);
}

std::list<Player*>&		GameEngine::setAIPlayerList()
{
  return (_ai_player_list);
}

std::list<AItem*>&		GameEngine::setItemList()
{
  return (_item_list);
}

SoundEngine&			GameEngine::getSoundEngine()
{
  return (*_sound_engine);
}
