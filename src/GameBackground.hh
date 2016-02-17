#ifndef GAMEBACKGROUND_HH_
#define GAMEBACKGROUND_HH_

# include <SdlContext.hh>
# include <Clock.hh>
# include <Input.hh>
# include <Texture.hh>
# include <Geometry.hh>
# include <BasicShader.hh>
# include <Model.hh>

# include <OpenGL.hh>
# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include "AObject.hpp"
#include "GameEngine.hh"

class GameBackground : public AObject {
private:
    gdl::Texture _texture;
    gdl::Geometry _geometry;
    std::string _path;
    GameEngine &_engine;
public:
    GameBackground(GameEngine & engine);
    virtual ~GameBackground();
public:
    virtual bool initialize();
    virtual void update(const gdl::Clock& clock, gdl::Input& input);
    virtual void draw(gdl::AShader& shader, const gdl::Clock& clock);
    virtual bool isAlwaysDisplayed();
};

#endif /* !GAMEBACKGROUND_HH_ */