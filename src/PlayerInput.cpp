
#include "PlayerInput.hh"

PlayerInput::PlayerInput(int up, int down,
			 int left, int right,
			 int bomb)
{
  _up = up;
  _down = down;
  _left = left;
  _right = right;

  _bomb = bomb;
}

PlayerInput::~PlayerInput()
{
}

void			PlayerInput::operator=(const PlayerInput& other)
{
  _up = other.getKeyUp();
  _down = other.getKeyDown();
  _left = other.getKeyLeft();
  _right = other.getKeyRight();

  _bomb = other.getKeyBomb();
}

void			PlayerInput::setKeyUp(int k)
{
  _up = k;
}

void			PlayerInput::setKeyDown(int k)
{
  _down = k;
}

void			PlayerInput::setKeyLeft(int k)
{
  _left = k;
}

void			PlayerInput::setKeyRight(int k)
{
  _right = k;
}

void			PlayerInput::setKeyBomb(int k)
{
  _bomb = k;
}

int			PlayerInput::getKeyUp(void) const
{
  return (_up);
}

int			PlayerInput::getKeyDown(void) const
{
  return (_down);
}

int			PlayerInput::getKeyLeft(void) const
{
  return (_left);
}

int			PlayerInput::getKeyRight(void) const
{
  return (_right);
}

int			PlayerInput::getKeyBomb(void) const
{
  return (_bomb);
}
