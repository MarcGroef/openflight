
#include "../view/view.h"
#include "../shader/shader.h"
#include "../shader_program/shader_program.h"
#include "../physics_model/physics_model.h"
#include "../world_object/world_object.h"
#include "../obj_parser/obj_parser.h"
#include "../world/world.h"

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
//#include <GL/glu.h>
#include <GL/glext.h>

#include <string>

using namespace std;

int main(int argc, char** argv)
{
    //ObjParser objp("objects/teapod/teapot.obj");

    World world;
    
    
    world.addObject(WorldObject({-60,2,0}, "objects/ASK21-MI/ask21mi.obj", 5, ""));
    world.addObject(WorldObject({32.5,8.5,2.5}, "objects/C-2A/c-2a.obj", 5, ""));
    world.addObject(WorldObject({-0,-3,-0}, "objects/ground/ground.obj", 1000, ""));
    world.addObject(WorldObject({-0,-3,-0}, "objects/sky/sky.obj", 900, ""));

    //world.addObject(WorldObject({-40,-40,200}, "objects/sphere.obj", 0.1, 1));

    
    ShaderProgram shaders("shaders/simple_fragment.glsl","shaders/phong_vertex.glsl");
   // ShaderProgram shaders2("shaders/simple_fragment_notexture.glsl","shaders/phong_vertex.glsl");
    View view(1920,1080, world);
    //view.addTexture("objects/ASK21-MI/textures/texture.png");
    //view.addTexture("objects/C-2A/textures/texture.png");
    //view.addTexture("textures/moon.png");
    //view.addTexture("textures/earth.png");
    view.addShaders(shaders);
   // view.addShaders(shaders2);

    view.loop(); //runs render loop
    
    
    return 0;
}