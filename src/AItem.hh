#ifndef AITEM_HH
#define AITEM_HH

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

enum itemType { RANGE, COUNT, SPEED };

class AItem : public AObject {
protected:
  itemType _item_type;
  double _elapsed_time;
public:
  virtual ~AItem();

  virtual bool	initialize() = 0;
  virtual void	update(const gdl::Clock& clock, gdl::Input& input) = 0;
  virtual void	draw(gdl::AShader& shader, const gdl::Clock& clock) = 0;
  double getElapsedTime() const;
  itemType getItemType();
  virtual bool isInItem(const AObject & obj) const;

};

#endif // AITEM_HH
