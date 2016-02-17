#include "ButtonSelector.hh"

ButtonSelector::ButtonSelector(std::string name, float x, float y, std::string picturepath, MenuEngine & me): _name(name), _me(me) {
    _position.x = x;
    _position.y = y + 0.004;
    _position.z = 0.002;
    _picture = "./assets/";
    _picture += picturepath;
}

ButtonSelector::~ButtonSelector() {

}

std::string ButtonSelector::getName() const {
    return (_name);
}

bool		ButtonSelector::initialize()
{
    if (_texture.load(_picture) == false)
    {
        std::cerr << "Cannot load the background texture" << std::endl;
        return (false);
    }
    _geometry.pushVertex(glm::vec3(0, 0, 0));
    _geometry.pushVertex(glm::vec3(0 + 0.035, 0, 0));
    _geometry.pushVertex(glm::vec3(0 + 0.035, 0 + 0.050, 0));
    _geometry.pushVertex(glm::vec3(0, 0 + 0.050, 0));
    
    _geometry.pushUv(glm::vec2(0.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 1.0f));
    _geometry.pushUv(glm::vec2(0.0f, 1.0f));
    
    _geometry.build();

    return (true);
}

void ButtonSelector::setPosition(float x, float y, float z) {
    _position.x = x;
    _position.y = y + 0.004;
    _position.z = z;
}

void		ButtonSelector::update(const gdl::Clock& clock, gdl::Input& input)
{
    (void)clock;
    (void)input;

}

void		ButtonSelector::draw(gdl::AShader& shader, const gdl::Clock& clock)
{
    (void)clock;
    _texture.bind();
    _geometry.draw(shader, getTransformation(), GL_QUADS);
}
