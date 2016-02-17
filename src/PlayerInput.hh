
#ifndef PLAYERINPUT_HH_
# define PLAYERINPUT_HH_

class PlayerInput
{
private:
  int		_up;
  int		_down;
  int		_left;
  int		_right;
  int		_bomb;

public:
  PlayerInput() {};
  PlayerInput(int, int, int, int, int);
  ~PlayerInput();

  void		operator=(const PlayerInput& other);

  void		setKeyUp(int k);
  void		setKeyDown(int k);
  void		setKeyLeft(int k);
  void		setKeyRight(int k);

  void		setKeyBomb(int k);

  int		getKeyUp(void) const;
  int		getKeyDown(void) const;
  int		getKeyLeft(void) const;
  int		getKeyRight(void) const;

  int		getKeyBomb(void) const;
};

#endif // !PLAYERINPUT_HH_
