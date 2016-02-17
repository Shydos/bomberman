#include "Background.hh"

Background::Background() {

}

Background::~Background() {
}

bool		Background::initialize()
{

    if (_texture.load("./assets/background.tga") == false)
    {
        std::cerr << "Cannot load the background texture" << std::endl;
        return (false);
    }
    _geometry.pushVertex(glm::vec3(0, 0, 0.0));
    _geometry.pushVertex(glm::vec3(0.800, 0, 0.0));
    _geometry.pushVertex(glm::vec3(0.800, 0.600, 0.0));
    _geometry.pushVertex(glm::vec3(0, 0.600, 0.0));
    _geometry.pushUv(glm::vec2(0.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 1.0f));
    _geometry.pushUv(glm::vec2(0.0f, 1.0f));
    _geometry.build();

    return (true);
}

void		Background::update(const gdl::Clock& clock, gdl::Input& input)
{
    (void)input;
    (void)clock;
}

void		Background::draw(gdl::AShader& shader, const gdl::Clock& clock)
{
    (void)clock;
    _texture.bind();
    _geometry.draw(shader, getTransformation(), GL_QUADS);

}