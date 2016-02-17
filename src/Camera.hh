
#ifndef CAMERA_HH_
# define CAMERA_HH_

# include <BasicShader.hh>
# include <Input.hh>

#include <OpenGL.hh>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "GameEngine.hh"

class Camera
{
private:
  GameEngine&		_engine;
  gdl::BasicShader	_shader;
private:
  glm::mat4		_projection;
  glm::mat4		_transformation;
  glm::mat4		_view;
protected:
  static glm::vec3	_vertices[4];
private:
  glm::vec3		_position;
  glm::vec3		_viewPoint;
  Player*		_player;

public:
  Camera(GameEngine&);
  ~Camera();

  bool			initialize();
  void			follow(Player*);
  void			setProjection(const glm::mat4&);
  bool			setViewPoint(const glm::vec3&);
  void		        draw(const gdl::Clock& clock);
  bool			translate(const glm::vec3&);
  bool			setPosition(const glm::vec3&);

  bool			isInCamView(const AObject&) const;
};

#endif // !CAMERA_HH_
