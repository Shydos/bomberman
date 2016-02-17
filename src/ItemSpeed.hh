#ifndef ITEMSPEED_HH
#define ITEMSPEED_HH

#include "AItem.hh"
#include "GameEngine.hh"

class ItemSpeed : public AItem {
protected:
    static gdl::Model _model;
    static bool _is_model_loaded;
    GameEngine & _engine;
public:
    ItemSpeed(std::size_t x, std::size_t y, GameEngine & engine);
    virtual ~ItemSpeed();
private:
    virtual bool initialize();
    virtual void update(const gdl::Clock& clock, gdl::Input& input);
    virtual void draw(gdl::AShader& shader, const gdl::Clock& clock);
};

#endif // ITEMSPEED_HH
