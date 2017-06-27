#include "render_object.ih"

void RenderObject::load()
{
    //if (d_hasTexture)
    {
        if (d_hasTexture)
            d_texture->load();
        glGenVertexArrays(1, &d_vaoId);
    
        
        glGenBuffers(1, &d_vboId);
        
        glBindVertexArray(d_vaoId);
        
        glBindBuffer(GL_ARRAY_BUFFER, d_vboId);
        glBufferData(GL_ARRAY_BUFFER, d_vertices.size() * sizeof(GLfloat), d_vertices.data(), GL_STATIC_DRAW);
        d_hasUV = true;
        int stride = (d_hasUV ? 8 : 6) * sizeof(GLfloat);
        glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, stride, (GLvoid*)NULL);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1,3,GL_FLOAT, GL_FALSE, stride, (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);
        if(d_hasUV)
        {

            glVertexAttribPointer(2,2,GL_FLOAT, GL_FALSE, stride, (GLvoid*)(6 * sizeof(GLfloat)));
            glEnableVertexAttribArray(2);
        }

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    for( RenderObject& ro : d_childs)
        ro.load();
}