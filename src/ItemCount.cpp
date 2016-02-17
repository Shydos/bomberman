#include "ItemCount.hh"

gdl::Model ItemCount::_model;
bool ItemCount::_is_model_loaded = false;

ItemCount::ItemCount(std::size_t x, std::size_t y, GameEngine & engine) : _engine(engine) {
    _position = glm::vec3(x, y, -0.60);
    _elapsed_time = 0.0;
    _item_type = COUNT;
    _engine.addItem(this);
    _engine.addObject(this);
}

ItemCount::~ItemCount() {
    _engine.rmvObject(this);
}

bool ItemCount::initialize() {
    _scale = glm::vec3(0.0018f, 0.0018f, 0.0018f);
    _rotation = glm::vec3(90.0f, 0.0f, 0.0f);

    if (_is_model_loaded == false) {
        if (!_model.load("./assets/BombCount.fbx")) {
            std::cerr << "Cannot load the model." << std::endl;
            return (false);
        }
        _is_model_loaded = true;
    }
    return (true);
}

void ItemCount::update(const gdl::Clock& clock, gdl::Input &input) {
    (void)input;

    _elapsed_time += clock.getElapsed();
}

void ItemCount::draw(gdl::AShader& shader, const gdl::Clock& clock) {
    _model.draw(shader, getTransformation(), clock.getElapsed());
}
