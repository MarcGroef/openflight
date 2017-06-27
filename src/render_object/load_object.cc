#include "render_object.ih"

void RenderObject::loadObject(ObjParser &&objParser)
{
    setTextureFile(objParser.d_objects[0].d_material.d_map_Kd);
   // std::cout << "set texture from object " << objParser.d_objects[0].d_name << ": " << objParser.d_objects[0].d_material.d_map_Kd << '\n';
    d_vertices = std::move(objParser.d_objects[0].d_interleaved);
    d_hasUV = true;//objParser.d_uv.size() != 0;//TODO remove d_hasUV
    d_loaded = true;
    size_t nObjects = objParser.d_objects.size();
    
    d_material.d_Ka = objParser.d_objects[0].d_material.d_Ka;
    d_material.d_Kd = objParser.d_objects[0].d_material.d_Kd;
    d_material.d_Ks = objParser.d_objects[0].d_material.d_Ks;
    d_material.d_Ke = objParser.d_objects[0].d_material.d_Ke;
    d_material.d_Ni = objParser.d_objects[0].d_material.d_Ni;
    d_material.d_d = objParser.d_objects[0].d_material.d_d;
    d_material.d_illum = objParser.d_objects[0].d_material.d_illum;
    
    
    for (size_t idx = 1; idx != nObjects; ++idx)
    {
        d_childs.push_back(RenderObject());
        d_childs[idx - 1].setTextureFile(objParser.d_objects[idx].d_material.d_map_Kd);
        
        d_childs[idx - 1].d_material.d_Ka = objParser.d_objects[idx].d_material.d_Ka;
        d_childs[idx - 1].d_material.d_Kd = objParser.d_objects[idx].d_material.d_Kd;
        d_childs[idx - 1].d_material.d_Ks = objParser.d_objects[idx].d_material.d_Ks;
        d_childs[idx - 1].d_material.d_Ke = objParser.d_objects[idx].d_material.d_Ke;
        d_childs[idx - 1].d_material.d_Ni = objParser.d_objects[idx].d_material.d_Ni;
        d_childs[idx - 1].d_material.d_d = objParser.d_objects[idx].d_material.d_d;
        d_childs[idx - 1].d_material.d_illum = objParser.d_objects[idx].d_material.d_illum;
        
        
        
        //std::cout << objParser.d_objects[idx].d_material.d_map_Kd << '\n';
        
        d_childs[idx - 1].loadObject(objParser.d_objects[idx].d_interleaved);
    }
}