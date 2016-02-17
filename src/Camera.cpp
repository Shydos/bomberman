
#include <cmath>
#include <list>
#include "Camera.hh"

glm::vec3	Camera::_vertices[4] = {
  glm::vec3(-0.5, -0.5, -0.5),
  glm::vec3(0.5, 0.5, -0.5),
  glm::vec3(0.5, -0.5, -0.5),
  glm::vec3(-0.5, 0.5, -0.5)
};

Camera::Camera(GameEngine& ge):_engine(ge)
{
}

Camera::~Camera()
{
}

bool			Camera::initialize()
{
  _position = glm::vec3(0, 0, 8);

  if (!_shader.load("./GDL/shaders/basic.fp", GL_FRAGMENT_SHADER) ||
      !_shader.load("./GDL/shaders/basic.vp", GL_VERTEX_SHADER) ||
      !_shader.build())
    {
      std::cerr << "shader load failed." << std::endl;
      return (false);
    }
  
  _projection = glm::perspective(180.0f, 960.0f/1080.0f, 0.1f, 50.0f);

  _shader.bind();
  _shader.setUniform("projection", _projection);

  return (true);
}

void			Camera::setProjection(const glm::mat4& project)
{
  _projection = project;

  _shader.bind();
  _shader.setUniform("projection", _projection);
}

void			Camera::follow(Player* p)
{
  _player = p;
}

void			Camera::draw(const gdl::Clock& clock)
{
  std::list<AObject*>::const_iterator	it;

  _viewPoint = _player->getPosition();
  _position.x = _viewPoint.x;
  _position.y = _viewPoint.y - 4;
  
  _transformation = glm::lookAt(_position,
				_viewPoint,
				glm::vec3(0, 1, 0));
  _view = _projection * _transformation;

  _shader.bind();
  _shader.setUniform("view", _transformation);

  it = _engine.getObjects().begin();
  while (it != _engine.getObjects().end())
    {
      if (isInCamView(**it) || (*it)->isAlwaysDisplayed())
        (*it)->draw(_shader, clock);
      it++;
    }
}

bool			Camera::isInCamView(const AObject& obj) const
{
  glm::vec4		pclip;
  int			i;

  i = 0;
  while (i < 4)
    {
      pclip = _view * glm::vec4(obj.getPosition() + _vertices[i], 1.0);
      if (abs(pclip.x) < pclip.w && 
          abs(pclip.y) < pclip.w &&
          0 < pclip.z &&
          pclip.z < pclip.w)
        return (true);
      i += 1;
    }
  return (false);
}

bool			Camera::setPosition(const glm::vec3& p)
{
  _position = p;
  return (true);
}

bool			Camera::translate(const glm::vec3& t)
{
  _position += t;
  return (true);
}
