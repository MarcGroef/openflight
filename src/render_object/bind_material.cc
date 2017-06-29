#include "render_object.h"

void RenderObject::bindMaterial(GLuint shaderProgramId)
{
    GLuint matId = glGetUniformLocation(shaderProgramId, "Ka");
    glUniform3f(matId, d_material.d_Ka.x, d_material.d_Ka.y, d_material.d_Ka.z);
    
    matId = glGetUniformLocation(shaderProgramId, "Kd");
    glUniform3f(matId, d_material.d_Kd.x, d_material.d_Kd.y, d_material.d_Kd.z);
    
    matId = glGetUniformLocation(shaderProgramId, "Ks");
    glUniform3f(matId, d_material.d_Ks.x, d_material.d_Ks.y, d_material.d_Ks.z);
    
    matId = glGetUniformLocation(shaderProgramId, "Ke");
    glUniform3f(matId, d_material.d_Ke.x, d_material.d_Ke.y, d_material.d_Ke.z);
    
    matId = glGetUniformLocation(shaderProgramId, "Ni");
    glUniform1f(matId, d_material.d_Ni);
    
    matId = glGetUniformLocation(shaderProgramId, "d");
    glUniform1f(matId, d_material.d_d);
    
    matId = glGetUniformLocation(shaderProgramId, "illum");
    glUniform1i(matId, d_material.d_illum);
}
