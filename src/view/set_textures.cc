#include "view.ih"

void View::setTextures()
{
    std::vector<WorldObject>& objects = d_world.getObjects();
    for (WorldObject &wo : objects)
    {
        std::string file = wo.getTextureFile();
        if (file != "")
        {
            d_textureManager.addTexture(file);
            wo.setTexture(d_textureManager.getTexturePtr(file));
        }
        for(RenderObject &ro : wo.getChilds())
        {
            file = ro.getTextureFile();
            if (file != "")
            {
                d_textureManager.addTexture(ro.getTextureFile());
            
                ro.setTexture(d_textureManager.getTexturePtr(ro.getTextureFile()));
            }
        }
    }
}