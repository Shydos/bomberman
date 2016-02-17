#ifndef BLOCKWALL_HH
#define BLOCKWALL_HH

#include "ABlock.hh"
#include "GameEngine.hh"

class BlockWall : public ABlock
{
private:
  GameEngine&			_engine;
protected:
    static gdl::Texture _texture;
    static bool _is_texture_loaded;
public:
    BlockWall(GameEngine& ge);
  BlockWall(GameEngine& ge, std::size_t x, std::size_t y);
    virtual ~BlockWall();
public:
    virtual bool initialize();
    virtual void update(const gdl::Clock& clock, gdl::Input& input);
    virtual void draw(gdl::AShader& shader, const gdl::Clock& clock);
};

#endif // !BLOCKWALL_HH
