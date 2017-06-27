#include "render_object.ih"

void RenderObject::drawSlave(GLuint shaderProgramId)
{
    if(!d_hasTexture)//HACK
        return;
        
    glBindVertexArray(d_vaoId);
    if(d_hasTexture)
        d_texture->bind();
    bindMaterial(shaderProgramId);
    GLuint textId = glGetUniformLocation(shaderProgramId, "text");
    glUniform1i(textId, 0);
    
    GLuint useText = glGetUniformLocation(shaderProgramId, "useTexture");
    if(d_hasTexture)
        glUniform1i(useText, 1);
    else
        glUniform1i(useText, 0);
     //cout << d_vertIdc.size();
    glDrawArrays(GL_TRIANGLES,0,  (d_vertices.size() * 3)/ 8 );
    glBindVertexArray(0);
}