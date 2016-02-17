
#ifndef AOBJECT_HPP_
# define AOBJECT_HPP_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class AObject
{
protected:
  glm::vec3		_position;
  glm::vec3		_rotation;
  glm::vec3		_scale;

public:
  AObject(): _position(0, 0, 0),
	     _rotation(0, 0, 0),
	     _scale(1, 1, 1)
  {
  }

  virtual ~AObject()
  {
  }

  virtual bool		initialize()
  {
    return (true);
  }

  virtual void		update(const gdl::Clock& clock, gdl::Input& input) = 0;

  virtual void		draw(gdl::AShader& shader, const gdl::Clock& clock) = 0;

  void			translate(const glm::vec3& v)
  {
    _position += v;
  }

  void			rotate(const glm::vec3& axis, float angle)
  {
    _rotation += axis * angle;
  }

  void			scale(const glm::vec3& scale)
  {
    _scale *= scale;
  }

  glm::mat4		getTransformation()
  {
    glm::mat4		transform(1);

    transform = glm::translate(transform, _position);

    transform = glm::rotate(transform, _rotation.x, glm::vec3(1, 0, 0));
    transform = glm::rotate(transform, _rotation.y, glm::vec3(0, 1, 0));
    transform = glm::rotate(transform, _rotation.z, glm::vec3(0, 0, 1));

    transform = glm::scale(transform, _scale);
    return (transform);
  }

  virtual const glm::vec3 & getPosition() const {
    return (_position);
  }

  virtual bool isAlwaysDisplayed() {
    return (false);
  }
};

#endif /* !AOBJECT_HPP_ */
