#ifndef INCLUDED_MTL_PARSER_H_
#define INCLUDED_MTL_PARSER_H_

#include <glm/glm.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>

struct material
{
    std::string d_name;
    float d_Ns;
    glm::vec3 d_Ka;
    glm::vec3 d_Kd;
    glm::vec3 d_Ks;
    glm::vec3 d_Ke;
    float d_Ni;
    float d_d;
    int d_illum;
    std::string d_map_Kd;
};

class MTLParser
{
    std::map<std::string, material> d_materials;
    
public:
    void parseMTL(std::string const &file);
    material get(std::string const &key);
    
private:
    void parseMaterial(std::ifstream &str);
    glm::vec3 parseVec3(std::ifstream &str);
};

inline material MTLParser::get(std::string const &key)
{
    return d_materials.at(key);
}

inline void MTLParser::parseMTL(std::string const &file)
{
    std::ifstream str(file.c_str());
    while(str)
        parseMaterial(str);
}

inline glm::vec3 MTLParser::parseVec3(std::ifstream &str)
{
    glm::vec3 vec;
    float num;
    str >> num;
    vec[0] = num;
    str >> num;
    vec[1] = num;
    str >> num;
    vec[2] = num;
    return vec;
}

inline void MTLParser::parseMaterial(std::ifstream &str)
{
    material mtl;
    std::string lineId;
    
    str >> lineId;
//FIXME this shit doesnt work, handle #
    str >> mtl.d_name;
    std::cout << mtl.d_name << '\n';
    
    str >> lineId;
    str >> mtl.d_Ns;
    
    str >> lineId;
    mtl.d_Ka = parseVec3(str);
    
    str >> lineId;
    mtl.d_Kd = parseVec3(str);
    
    str >> lineId;
    mtl.d_Ks = parseVec3(str);
    
    str >> lineId;
    mtl.d_Ke = parseVec3(str);
    
    str >> lineId;
    str >> mtl.d_Ni;
    
    str >> lineId;
    str >> mtl.d_d;
    
    str >> lineId;
    str >> mtl.d_illum;
    
    str >> lineId;
    str >> mtl.d_map_Kd;
    
    d_materials.emplace(mtl.d_name, mtl);
}
#endif