#include "view.ih"

void View::setProjection()
{
            
        vec3 camera = {0,0,0};
        
        mat4 projection = perspective(radians(45.f), 1.33f, 0.1f, 1000.f);
        d_view = translate(mat4(1.0f), camera);
        
        
        //cout << d_xRotation << ", " << d_yRotation << '\n';
        d_view = rotate(d_view, radians(d_yRotation), vec3({1,0,0}));
        d_view = rotate(d_view, radians(d_xRotation), vec3({0,1,0}));

        GLuint viewId = glGetUniformLocation(d_activeShader->id(), "view");
        glUniformMatrix4fv(viewId, 1, GL_FALSE, &d_view[0][0]);
        GLuint projId = glGetUniformLocation(d_activeShader->id(), "projection");
        glUniformMatrix4fv(projId, 1, GL_FALSE, &projection[0][0]);
}