#include "render_object.ih"

void RenderObject::draw()
{
    glBindVertexArray(d_vaoId);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}