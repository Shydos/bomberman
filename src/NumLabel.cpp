#include "NumLabel.hh"

std::string		NumLabel::getName() const
{
    return (_name);
}

NumLabel::NumLabel(std::string name, float x, float y, int value): _name(name)
{
    _position.x = x;
    _position.y = y;
    _position.z = 0.001;
    _value = value;
}

NumLabel::~NumLabel()
{
}

std::string	NumLabel::getTexture(int num)
{
  int	i = 0;
  std::list<std::string>::iterator it = _nbtex.begin();
  while (i < num)
    {
      it++;
      i++;
    }
  return (*it);
}

bool			NumLabel::setLabel(int nb)
{
  int			mod;
  float			width_size = 0.040;
  float			height_size = 0.050;

  _value = nb;
  if (nb < 10)
    {
      mod = nb % 10;
      if (_tex1.load(getTexture(mod)) == false)
	{
	  std::cerr << "Cannot load the number texture" << std::endl;
	  return (false);
	}	      
      if (_tex2.load(getTexture(0)) == false)
	{
	  std::cerr << "Cannot load the number texture" << std::endl;
	  return (false);
	}	      
      if (_tex3.load(getTexture(0)) == false)
	{
	  std::cerr << "Cannot load the number texture" << std::endl;
	  return (false);
	}
    }
  if (nb < 100)
    {
      mod = nb % 10;
      if (_tex1.load(getTexture(mod)) == false)
	{
	  std::cerr << "Cannot load the number texture" << std::endl;
	  return (false);
	}	      
      mod = (nb/10) % 10;
      if (_tex2.load(getTexture(mod)) == false)
	{
	  std::cerr << "Cannot load the number texture" << std::endl;
	  return (false);
	}	      
      if (_tex3.load(getTexture(0)) == false)
	{
	  std::cerr << "Cannot load the number texture" << std::endl;
	  return (false);
	}
    }
  else
    {      
      mod = nb % 10;
      if (_tex1.load(getTexture(mod)) == false)
	{
	  std::cerr << "Cannot load the number texture" << std::endl;
	  return (false);
	}	      
      mod = (nb / 10) % 10;
      if (_tex2.load(getTexture(mod)) == false)
	{
	  std::cerr << "Cannot load the number texture" << std::endl;
	  return (false);
	}
      mod = (nb / 100) % 10;
      if (_tex3.load(getTexture(mod)) == false)
	{
	  std::cerr << "Cannot load the number texture" << std::endl;
	  return (false);
	}
    }

  _geo1.pushVertex(glm::vec3(width_size * 2, 0, 0)); 
  _geo1.pushVertex(glm::vec3(width_size * 3, 0, 0)); 
  _geo1.pushVertex(glm::vec3(width_size * 3, height_size, 0)); 
  _geo1.pushVertex(glm::vec3(width_size * 2, height_size, 0)); 
  _geo1.pushUv(glm::vec2(0.0f, 0.0f));
  _geo1.pushUv(glm::vec2(1.0f, 0.0f));
  _geo1.pushUv(glm::vec2(1.0f, 1.0f));
  _geo1.pushUv(glm::vec2(0.0f, 1.0f));
  _geo1.build();

  _geo2.pushVertex(glm::vec3(width_size, 0, 0)); 
  _geo2.pushVertex(glm::vec3(width_size * 2, 0, 0)); 
  _geo2.pushVertex(glm::vec3(width_size * 2, height_size, 0)); 
  _geo2.pushVertex(glm::vec3(width_size, height_size, 0)); 
  _geo2.pushUv(glm::vec2(0.0f, 0.0f));
  _geo2.pushUv(glm::vec2(1.0f, 0.0f));
  _geo2.pushUv(glm::vec2(1.0f, 1.0f));
  _geo2.pushUv(glm::vec2(0.0f, 1.0f));
  _geo2.build();

  _geo3.pushVertex(glm::vec3(0, 0, 0)); 
  _geo3.pushVertex(glm::vec3(width_size, 0, 0)); 
  _geo3.pushVertex(glm::vec3(width_size, height_size, 0)); 
  _geo3.pushVertex(glm::vec3(0, height_size, 0)); 
  _geo3.pushUv(glm::vec2(0.0f, 0.0f));
  _geo3.pushUv(glm::vec2(1.0f, 0.0f));
  _geo3.pushUv(glm::vec2(1.0f, 1.0f));
  _geo3.pushUv(glm::vec2(0.0f, 1.0f));
  _geo3.build();

  return (true);
}

void		NumLabel::init_texturepath()
{
  _nbtex.push_back("./assets/num/0.tga");
  _nbtex.push_back("./assets/num/1.tga");
  _nbtex.push_back("./assets/num/2.tga");
  _nbtex.push_back("./assets/num/3.tga");
  _nbtex.push_back("./assets/num/4.tga");
  _nbtex.push_back("./assets/num/5.tga");
  _nbtex.push_back("./assets/num/6.tga");
  _nbtex.push_back("./assets/num/7.tga");
  _nbtex.push_back("./assets/num/8.tga");
  _nbtex.push_back("./assets/num/9.tga");
}

bool		NumLabel::initialize()
{
  init_texturepath();
  if (setLabel(_value) == false)
    {
      std::cerr << "Cannot set the NumLabel" << std::endl;
      return (false);
    }
  return (true);
}

void		NumLabel::update(const gdl::Clock& clock, gdl::Input& input)
{
    (void)input;
    (void)clock;
}

void		NumLabel::draw(gdl::AShader& shader, const gdl::Clock& clock)
{
  (void)clock;
  _tex1.bind();
  _geo1.draw(shader, getTransformation(), GL_QUADS);
  _tex2.bind();
  _geo2.draw(shader, getTransformation(), GL_QUADS);
  _tex3.bind();
  _geo3.draw(shader, getTransformation(), GL_QUADS);
}

int		NumLabel::getValue() const
{
  return (_value);
}
