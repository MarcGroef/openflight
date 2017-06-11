
#include "../view/view.h"
#include "../shader/shader.h"
#include "../shader_program/shader_program.h"
#include "../physics_model/physics_model.h"
#include "../world_object/world_object.h"
#include "../world/world.h"
#include "../obj_parser/obj_parser.h"

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
    
    world.addObject(WorldObject({-40,40,200}));
    world.addObject(WorldObject({-40,-40,200}));
    world.addObject(WorldObject({40,40,200}));
    world.addObject(WorldObject({40,-40,200}));
    
    ShaderProgram shaders("shaders/simple_fragment.glsl","shaders/phong_vertex.glsl");
    //ShaderProgram shaders("shaders/simple_fragment.glsl","shaders/simple_vertex.glsl");
    View view(800,600, world);
    view.addShaders(shaders);
    view.loop(); //runs render loop
    
    
    return 0;
}