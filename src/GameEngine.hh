
#ifndef GAMEENGINE_HH_
# define GAMEENGINE_HH_

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

#include <list>

#include "Bomb.hh"
#include "Player.hh"
#include "Camera.hh"
#include "Map.hh"
#include "Explosion.hh"
#include "AItem.hh"
#include "GameBackground.hh"
#include "SoundEngine.hh"
#include "ScoreManager.hh"

class Bomb;
class Map;
class Player;
class HumanPlayer;
class AIPlayer;
class Explosion;
class Camera;
class GameBackground;

class GameEngine : public gdl::Game {
private:
  gdl::SdlContext &     _context;
  gdl::Clock			_clock;
  gdl::Input			_input;
private:
  Map*				_map;
  GameBackground*       _background;
  SoundEngine*          _sound_engine;
  ScoreManager*         _score_manager;
  size_t                _nb_human;
  int			_winner; 
  std::list<AObject*>		_objects;
  std::list<Player*>		_human_player_list;
  std::list<Player*>		_ai_player_list;
  std::list<Player*>		_players;
  std::list<Bomb*>		_bomb_list;
  std::list<Explosion*>		_explosion_list;
  std::list<AItem*>		_item_list;
  bool				_gameover;
public:
  GameEngine(gdl::SdlContext & context);
  ~GameEngine();
public:
  bool		initialize(std::size_t nb_players, std::size_t nb_ai,
			   std::size_t x, std::size_t y);
  bool		initialize();
  bool		update();
  void		draw();
public:
  void					addObject(AObject* obj);
  void					rmvObject(AObject* obj);
  const std::list<AObject*>&		getObjects(void) const;
public:
  void					addPlayer(Player* pl);
public:
  void					addExplosion(Explosion* e);
  const std::list<Explosion*>&		getExplosionList() const;
  std::list<Explosion*>&		setExplosionList();
public:
  void					addBomb(Bomb* b);
  const std::list<Bomb*>&		getBombList() const;
  std::list<Bomb*>&			setBombList();
public:
  void					addItem(AItem* i);
  const std::list<AItem*>&		getItemList() const;
  std::list<AItem*>&			setItemList();
public:
  void					addHumanPlayer(HumanPlayer* p);
  const std::list<Player*>&		getHumanPlayerList() const;
  std::list<Player*>&			setHumanPlayerList();
public:
  void					addAIPlayer(AIPlayer* p);
  const std::list<Player*>&		getAIPlayerList() const;
  std::list<Player*>&			setAIPlayerList();
public:
  void					setWinner(int);
  int					getWinner();
public:
  Map*					getMap();
  SoundEngine&				getSoundEngine();
};

#endif // !GAMEENGINE_HH_
