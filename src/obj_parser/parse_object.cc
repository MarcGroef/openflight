#include "obj_parser.ih"

void ObjParser::parseObject(std::string const &line)
{

    
    if (d_activeObject.d_name != "")
    {
        //std::cout << d_activeObject.d_name << '\n';

        rollout();
        //std::cout << d_interleaved.size() << '\n';
        d_activeObject.d_interleaved = std::move(d_interleaved);
        //d_interleaved.clear();
        d_objects.push_back(d_activeObject);
        //std::cout << "pushed back " << d_activeObject.d_name << '\n';

    }
    std::stringstream str(line);
    std::string firstbit;
    str >> firstbit;
    str >> d_activeObject.d_name;  
    d_activeObject.d_material.d_map_Kd = "";
    //std::cout << "parsed " << d_activeObject.d_name << "at line " << line << '\n';
}