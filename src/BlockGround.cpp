#include "BlockGround.hh"

gdl::Texture BlockGround::_texture;
bool BlockGround::_is_texture_loaded = false;

BlockGround::BlockGround(GameEngine& ge):_engine(ge)
{
  _engine.addObject(this);
}

BlockGround::BlockGround(GameEngine& ge, std::size_t x, std::size_t y):_engine(ge)
{
  _position.x = x;
  _position.y = y;
  _engine.addObject(this);
}

BlockGround::~BlockGround()
{
  _engine.rmvObject(this);
}

bool BlockGround::initialize() {
    _scale = glm::vec3(1, 1, 1);

    if (_is_texture_loaded == false) {
        if (_texture.load("./assets/BlockGround.tga") == false) {
            std::cerr << "Cannot load the cube texture" << std::endl;
            return (false);
        }
        _is_texture_loaded = true;
    }

    _geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5));
    _geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5));
    _geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5));
    _geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5));

    _geometry.pushUv(glm::vec2(0.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 1.0f));
    _geometry.pushUv(glm::vec2(0.0f, 1.0f));

    _geometry.build();

    return (true);
}

void BlockGround::update(const gdl::Clock& clock, gdl::Input& input) {
    (void)clock;
    (void)input;
}

void BlockGround::draw(gdl::AShader& shader, const gdl::Clock& clock) {
    (void)clock;

    _texture.bind();
    _geometry.draw(shader, getTransformation(), GL_QUADS);
}
