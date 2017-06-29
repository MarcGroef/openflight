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
    material d_active;
public:
    void parseMTL(std::string const &file);
    material get(std::string const &key);
    
private:

    glm::vec3 parseVec3(std::stringstream &str);
};

inline material MTLParser::get(std::string const &key)
{
    return d_materials.at(key);
}





#endif