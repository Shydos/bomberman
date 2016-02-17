#ifndef BUTTONMENU_HH_
#define BUTTONMENU_HH_

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
#include <string>

class ButtonMenu : public AObject {
protected:
    std::string _picture;
    gdl::Texture _texture;
    gdl::Geometry _geometry;
    std::string _name;
public:
    std::string getName() const;
    void	setPicture(std::string);
public:
    ButtonMenu(std::string name, float x, float y, std::string picturepath);
    virtual ~ButtonMenu();
public:
    virtual bool initialize();
    virtual void update(const gdl::Clock& clock, gdl::Input& input);
    virtual void draw(gdl::AShader& shader, const gdl::Clock& clock);
};

#endif
