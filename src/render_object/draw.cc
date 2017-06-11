#include "render_object.ih"

void RenderObject::draw(GLuint shaderProgramId, mat4 const &view, vec3 const &lightpos)
{
    mat4 model = translate(mat4(1.0f), d_position);
    float sc = 0.2;
    model = scale(model, vec3({sc, sc, sc}));
    model = rotate(model, d_rollPitchYaw.x, vec3(0,0,1));
    model = rotate(model, d_rollPitchYaw.y, vec3(1,0,0));
    model = rotate(model, d_rollPitchYaw.z, vec3(0,1,0));
    
    //mat3 normMat = transpose(inverse(mat3(view * model)));
    mat3 normMat = inverse(mat3(view * model));
    //mat3 normMat = mat3(view * model);
    
    
   /* cout << "Model ********************************************\n";
    cout << normMat[0][0] << ", " << normMat[0][1] << ", " << normMat[0][2] << "\n";
    cout << normMat[1][0] << ", " << normMat[1][1] << ", " << normMat[1][2] <<  "\n";
    cout << normMat[2][0] << ", " << normMat[2][1] << ", " << normMat[2][2] <<  "\n";*/
    //cout << normMat[3][0] << ", " << normMat[3][1] << ", " << normMat[3][2] <<  "\n";
    
    GLuint modelId = glGetUniformLocation(shaderProgramId, "model");
    glUniformMatrix4fv(modelId, 1, GL_FALSE, &model[0][0]);
    
    GLuint normMatId = glGetUniformLocation(shaderProgramId, "normalMat");
    glUniformMatrix3fv(normMatId, 1, GL_FALSE, &normMat[0][0]);
    
    GLuint lightId = glGetUniformLocation(shaderProgramId, "lightPos");
    glUniform3f(lightId, lightpos.x, lightpos.y, lightpos.z);
    glBindVertexArray(d_vaoId);
    
    
     //cout << d_vertIdc.size();
    glDrawArrays(GL_TRIANGLES,0,  d_vertices.size() / 2 );
    //glDrawElements(GL_TRIANGLES, d_vertIdc.size(), GL_UNSIGNED_SHORT, NULL);
    glBindVertexArray(0);
}