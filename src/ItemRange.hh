#ifndef ITEMRANGE_HH
#define ITEMRANGE_HH

#include "AItem.hh"
#include "GameEngine.hh"

class ItemRange : public AItem {
protected:
    static gdl::Model _model;
    static bool _is_model_loaded;
    GameEngine & _engine;
public:
    ItemRange(std::size_t x, std::size_t y, GameEngine & engine);
    virtual ~ItemRange();
private:
    virtual bool initialize();
    virtual void update(const gdl::Clock& clock, gdl::Input& input);
    virtual void draw(gdl::AShader& shader, const gdl::Clock& clock);
};

#endif // ITEMRANGE_HH
