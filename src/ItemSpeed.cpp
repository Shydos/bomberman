#include "ItemSpeed.hh"

gdl::Model ItemSpeed::_model;
bool ItemSpeed::_is_model_loaded = false;

ItemSpeed::ItemSpeed(std::size_t x, std::size_t y, GameEngine & engine) : _engine(engine) {
    _position = glm::vec3(x, y, 0.0);
    _elapsed_time = 0.0;
    _item_type = SPEED;
    _engine.addItem(this);
    _engine.addObject(this);
}

ItemSpeed::~ItemSpeed() {
    _engine.rmvObject(this);
}

bool ItemSpeed::initialize() {
  _scale = glm::vec3(0.30f, 0.30f, 0.30f);
    _rotation = glm::vec3(0.0f, 0.0f, 0.0f);

    if (_is_model_loaded == false) {
        if (!_model.load("./assets/boots.fbx")) {
            std::cerr << "Cannot load the model." << std::endl;
            return (false);
        }
        _is_model_loaded = true;
    }
    return (true);
}

void ItemSpeed::update(const gdl::Clock& clock, gdl::Input &input) {
    (void)input;

    _elapsed_time += clock.getElapsed();
}

void ItemSpeed::draw(gdl::AShader& shader, const gdl::Clock& clock) {
    _model.draw(shader, getTransformation(), clock.getElapsed());
}
