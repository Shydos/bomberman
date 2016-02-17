#ifndef BUTTONSELECTOR_HH_
#define BUTTONSELECTOR_HH_

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
#include <string>
#include "AObject.hpp"
#include "MenuEngine.hh"

class MenuEngine;

class ButtonSelector: public AObject {
protected:
    std::string _picture;
    gdl::Texture _texture;
    gdl::Geometry _geometry;
    std::string _name;
    MenuEngine & _me;
public:
    std::string getName() const;
    void        setPosition(float x, float y, float z);
public:
    ButtonSelector(std::string name, float x, float y, std::string picturepath, MenuEngine & me);
    virtual ~ButtonSelector();
public:
    virtual bool initialize();
    virtual void update(const gdl::Clock& clock, gdl::Input& input);
    virtual void draw(gdl::AShader& shader, const gdl::Clock& clock);
};

#endif