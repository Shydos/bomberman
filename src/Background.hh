#ifndef BACKGROUND_HH_
#define BACKGROUND_HH_

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

#include "AObject.hpp"
#include <iostream>

class Background: public AObject {
private:
    gdl::Texture _texture;
    gdl::Geometry _geometry;
public:
    Background();
    virtual ~Background();
public:
    virtual bool initialize();
    virtual void update(const gdl::Clock& clock, gdl::Input& input);
    virtual void draw(gdl::AShader& shader, const gdl::Clock& clock);
};

#endif /* !BACKGROUND_HH_ */