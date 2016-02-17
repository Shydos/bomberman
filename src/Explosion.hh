#ifndef EXPLOSION_HH_
#define EXPLOSION_HH_

#include <SdlContext.hh>
#include <Clock.hh>
#include <Input.hh>
#include <Texture.hh>
#include <Geometry.hh>
#include <BasicShader.hh>
#include <Model.hh>

#include <OpenGL.hh>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#include "AObject.hpp"
#include "GameEngine.hh"

class GameEngine;

class Explosion : public AObject {
protected:
    GameEngine&			_engine;
    gdl::Geometry		_geometry;
    static gdl::Texture	_texture;
    static bool		_is_texture_loaded;
    double _elapsed_time;
public:
    Explosion(int x, int y, GameEngine& ge);
    virtual ~Explosion();
  
    virtual bool initialize();
  virtual void	kill(void);
    virtual void update(const gdl::Clock& clock, gdl::Input& input);
    virtual void draw(gdl::AShader& shader, const gdl::Clock& clock);
    virtual const glm::vec3&  getPosition(void) const;
    double getElapsedTime() const;
  bool		isInExplosion(const AObject&);
};

#endif // EXPLOSION_HH_
