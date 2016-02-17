#ifndef NUMLABEL_HH_
#define NUMLABEL_HH_

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

#include "AObject.hpp"
#include <iostream>
#include <string>

class NumLabel : public AObject {
protected:
  std::list<std::string>	_nbtex;
  gdl::Texture			_tex1;
  gdl::Texture			_tex2;
  gdl::Texture			_tex3;
  gdl::Geometry			_geo1;
  gdl::Geometry			_geo2;
  gdl::Geometry			_geo3;
  std::string			_name;
  int				_value;
public:
  std::string getName() const;
  int	getValue() const;
  void	setValue(int);
  std::string	getTexture(int);
public:
  NumLabel(std::string name, float x, float y, int value);
  virtual ~NumLabel();
  bool	setLabel(int);
  void	init_texturepath();
public:
  virtual bool initialize();
  virtual void update(const gdl::Clock& clock, gdl::Input& input);
  virtual void draw(gdl::AShader& shader, const gdl::Clock& clock);
};

#endif
