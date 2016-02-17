
#ifndef MAP_HH_
# define MAP_HH_

# include <vector>
# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>

# include "Camera.hh"
# include "ABlock.hh"
# include "BlockWall.hh"
# include "BlockGround.hh"
# include "BlockCrate.hh"

class Camera;

class Map
{
private:
  GameEngine&			_engine;
  std::vector<ABlock*>	_grounds;
  std::vector<ABlock*>	_board;
  std::vector<ABlock*>	_walls;
  std::vector<ABlock*>	_crates;
  std::size_t		_width;
  std::size_t		_height;
public:
  Map(GameEngine&, std::size_t, std::size_t);
  ~Map();

  void			addCrate(const int percent);
  bool			destroyCrate(const glm::vec3& pos);
  bool			playerIsOut(const Player& player) const;
  bool			isReachable(const glm::vec3& pos) const;
  bool			playerIsAround(int, int, float, Player*);
  std::vector<ABlock*> * getWalls();
  std::vector<ABlock*> * getCrates();
  std::size_t		getWidth() const;
  std::size_t		getHeight() const;
  bool			isAloneOn(Player*, ABlock*);
  glm::vec2		getPlayerStartPosition(void) const;
  ABlock*		getGroundFromPosition(const glm::vec3&);
  bool isWall(const glm::vec3 & pos) const;
  bool isCrate(const glm::vec3 & pos) const;
};

#endif /* !MAP_HH_ */
