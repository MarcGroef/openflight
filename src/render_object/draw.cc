#include "render_object.ih"

void RenderObject::draw(GLuint shaderProgramId, mat4 const &view, vec3 const &lightpos)
{
    mat4 model = translate(mat4(1.0f), d_position);
    model = scale(model, vec3({d_scale, d_scale, d_scale}));
    model = rotate(model, d_rollPitchYaw.x, vec3(0,0,1));
    model = rotate(model, d_rollPitchYaw.y, vec3(1,0,0));
    model = rotate(model, d_rollPitchYaw.z, vec3(0,1,0));
    
    mat3 normMat = inverse(mat3(view * model));

    
    GLuint modelId = glGetUniformLocation(shaderProgramId, "model");
    glUniformMatrix4fv(modelId, 1, GL_FALSE, &model[0][0]);
    
    GLuint normMatId = glGetUniformLocation(shaderProgramId, "normalMat");
    glUniformMatrix3fv(normMatId, 1, GL_FALSE, &normMat[0][0]);
    
    GLuint lightId = glGetUniformLocation(shaderProgramId, "lightPos");
    glUniform3f(lightId, lightpos.x, lightpos.y, lightpos.z);
    
    
    
    glBindVertexArray(d_vaoId);
    if(d_hasTexture)
        d_texture->bind();
    
    GLuint textId = glGetUniformLocation(shaderProgramId, "text");
    glUniform1i(textId, 0);
    
     //cout << d_vertIdc.size();
    glDrawArrays(GL_TRIANGLES,0,  (d_vertices.size() * 3)/ 8 );
    //glDrawElements(GL_TRIANGLES, d_vertIdc.size(), GL_UNSIGNED_SHORT, NULL);
    
   
    glBindVertexArray(0);
}