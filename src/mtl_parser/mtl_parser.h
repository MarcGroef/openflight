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

inline void MTLParser::parseMTL(std::string const &file)
{
    std::ifstream str(file.c_str());
    std::cout << "parseMTL\n";
    if(!str.good())
        std::cout << "couldn't open " << file << '\n';
    
    d_active.d_name = "";

            
    while(str)
    {
        //parseMaterial(str);
        std::string line;
        std::getline(str, line);
        //std::cout << line << '\n';
        std::stringstream sstr(line);
        
        std::string firstbit;
        
        switch(line[0])
        {
            case '#':
                break;
            case 'n': //newmat

                if(d_active.d_name != "")
                {
                    d_materials.emplace(d_active.d_name, d_active);
                    d_active.d_map_Kd = "";
                    //std::cout << "added obj " << d_active.d_name << '\n';
                }
                sstr >> firstbit;
                sstr >> d_active.d_name;
                //std::cout << "newname : " << d_active.d_name << '\n';
                break;
            case 'N':
                switch(line[1])
                {
                    case 's':
                        //Ns
                        sstr >> firstbit;
                        sstr >> d_active.d_Ns;
                        break;
                    case 'i':
                        sstr >> firstbit;
                        sstr >> d_active.d_Ni;
                        
                        //Ni
                        break;
                }
                break;
            case 'K':
                //std::cout << "readK\n";
                sstr >> firstbit;
                
                switch(line[1])
                {
                    case 'a':
                        d_active.d_Ka = parseVec3(sstr);
                        break;
                    case 'd':
                        d_active.d_Kd = parseVec3(sstr);
                        break;
                    case 's':
                        d_active.d_Ks = parseVec3(sstr);
                        break;
                    case 'e':
                        d_active.d_Ke = parseVec3(sstr);
                        break;
                        
                }
                break;
            case 'd':
                sstr >> firstbit;
                sstr >> d_active.d_d;
                break;
            case 'i':
                sstr >> firstbit;
                sstr >> d_active.d_illum;
                break;
            case 'm':
                sstr >> firstbit;
                sstr >> d_active.d_map_Kd;
                break;
                        
        }
    }
    d_materials.emplace(d_active.d_name, d_active);
    d_active.d_map_Kd = "";
    //std::cout  << "emplaced " << d_materials.size() << " mats\n";
}

inline glm::vec3 MTLParser::parseVec3(std::stringstream &str)
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

#endif