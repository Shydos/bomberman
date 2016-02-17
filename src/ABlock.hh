#ifndef ABLOC_HH
#define ABLOC_HH

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

#include "AObject.hpp"

class ABlock : public AObject
{
protected:
  gdl::Geometry			_geometry;

protected:
  static glm::vec3		_vertices[4];

public:
  virtual ~ABlock() {}

  virtual bool	initialize();

  virtual void	update(const gdl::Clock& clock, gdl::Input& input) = 0;
  virtual void	draw(gdl::AShader& shader, const gdl::Clock& clock) = 0;
  virtual bool	isInBlock(const glm::vec3& position, float delta) const;
};

#endif // ABLOC_HH
