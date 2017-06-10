#include "render_object.ih"

void RenderObject::load()
{
    glGenVertexArrays(1, &d_vaoId);
    glGenBuffers(1, &d_vboId);
    glGenBuffers(1, &d_eboId);
    
    glBindVertexArray(d_vaoId);
    glBindBuffer(GL_ARRAY_BUFFER, d_vboId);
    glBufferData(GL_ARRAY_BUFFER, d_vertices.size() * sizeof(GLfloat), d_vertices.data(), GL_STATIC_DRAW);
    cout.flush();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, d_eboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, d_vertIdc.size() * sizeof(GLfloat), d_vertIdc.data(), GL_STATIC_DRAW);
    
    glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)NULL);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}