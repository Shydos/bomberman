#ifndef BLOCGROUND_HH
#define BLOCGROUND_HH

#include "ABlock.hh"
#include "GameEngine.hh"

class BlockGround : public ABlock {
protected:
    static gdl::Texture _texture;
    static bool _is_texture_loaded;
public:
    BlockGround(GameEngine& ge);
  BlockGround(GameEngine& ge, std::size_t x, std::size_t y);
    virtual ~BlockGround();
private:
  GameEngine&			_engine;
    virtual bool initialize();
    virtual void update(const gdl::Clock& clock, gdl::Input& input);
    virtual void draw(gdl::AShader& shader, const gdl::Clock& clock);
};

#endif // BLOCGROUND_HH
