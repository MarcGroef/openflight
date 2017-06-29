#include "mtl_parser.ih"

void MTLParser::parseMTL(std::string const &file)
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