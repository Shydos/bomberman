#include "ButtonMenu.hh"

std::string		ButtonMenu::getName() const
{
    return (_name);
}

ButtonMenu::ButtonMenu(std::string name, float x, float y, std::string picturepath): _name(name)
{
    _position.x = x;
    _position.y = y;
    _position.z = 0.001;
    _picture = "./assets/";
    _picture += picturepath;
}

ButtonMenu::~ButtonMenu()
{
}

void		ButtonMenu::setPicture(std::string picture_path)
{
  _picture = "./assets/";
  _picture += picture_path;
}

bool		ButtonMenu::initialize()
{
    if (_texture.load(_picture) == false)
    {
        std::cerr << "Cannot load the background texture" << std::endl;
        return (false);
    }
    _geometry.pushVertex(glm::vec3(0, 0, 0));
    _geometry.pushVertex(glm::vec3(0 + 0.238, 0, 0));
    _geometry.pushVertex(glm::vec3(0 + 0.238, 0 + 0.057, 0));
    _geometry.pushVertex(glm::vec3(0, 0 + 0.057, 0));
    _geometry.pushUv(glm::vec2(0.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 1.0f));
    _geometry.pushUv(glm::vec2(0.0f, 1.0f));
    _geometry.build();

    return (true);
}

void		ButtonMenu::update(const gdl::Clock& clock, gdl::Input& input)
{
    (void)input;
    (void)clock;
}

void		ButtonMenu::draw(gdl::AShader& shader, const gdl::Clock& clock)
{
    (void)clock;
    _texture.bind();
    _geometry.draw(shader, getTransformation(), GL_QUADS);
}
