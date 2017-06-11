#include "render_object.ih"

void RenderObject::load()
{
    glGenVertexArrays(1, &d_vaoId);
 
    
    glGenBuffers(1, &d_vboId);
    //glGenBuffers(1, &d_eboId);
    //glGenBuffers(1, &d_vnbId);
    //glGenBuffers(1, &d_vnElId);
    
    glBindVertexArray(d_vaoId);
    
    glBindBuffer(GL_ARRAY_BUFFER, d_vboId);
    glBufferData(GL_ARRAY_BUFFER, d_vertices.size() * sizeof(GLfloat), d_vertices.data(), GL_STATIC_DRAW);
    ///glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, d_eboId);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, d_vertIdc.size() * sizeof(GLuint), d_vertIdc.data(), GL_STATIC_DRAW);
   
    glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat)  , (GLvoid*)NULL);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,3,GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)NULL + 3 * sizeof(GLfloat));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2,2,GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)NULL + 5 * sizeof(GLfloat));
    glEnableVertexAttribArray(2);
    

    
    /*glBindBuffer(GL_ARRAY_BUFFER, d_vnbId);
    glBufferData(GL_ARRAY_BUFFER, d_normals.size() * sizeof(GLfloat) * 3, d_normals.data(), GL_STATIC_DRAW);

    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, d_vnElId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, d_normIdc.size() * sizeof(GLuint), d_normIdc.data(), GL_STATIC_DRAW);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0,  (GLvoid*)NULL);
    glEnableVertexAttribArray(1);*/
    
    

    
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}