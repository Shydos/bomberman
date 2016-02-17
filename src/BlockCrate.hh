#ifndef BLOCCRATE_HH
#define BLOCCRATE_HH

#include "ABlock.hh"
#include "GameEngine.hh"

class BlockCrate : public ABlock {
protected:
    static gdl::Texture _texture;
    static bool _is_texture_loaded;
public:
  BlockCrate(GameEngine& ge);
  BlockCrate(GameEngine& ge, std::size_t x, std::size_t y);
  virtual ~BlockCrate();
private:
  GameEngine&		_engine;
    virtual bool initialize();
    virtual void update(const gdl::Clock& clock, gdl::Input& input);
    virtual void draw(gdl::AShader& shader, const gdl::Clock& clock);
};

#endif // BLOCCRATE_HH
