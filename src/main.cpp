#include "GameEngine.hh"
#include "MenuEngine.hh"
#include "Map.hh"
#include "ScoreManager.hh"

int		main()
{
  MenuEngine me;

  me.initialize();
  while (me.update()) {
    me.draw();
  }

  return (EXIT_SUCCESS);
}
