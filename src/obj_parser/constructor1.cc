#include "obj_parser.ih"

ObjParser::ObjParser(std::string const &objfile)
{
    
    std::string mtlfile(objfile);
    mtlfile[mtlfile.size() - 1] = 'l';
    mtlfile[mtlfile.size() - 2] = 't';
    mtlfile[mtlfile.size() - 3] = 'm';
    
    d_objFolder = objfile;
    char c;
    for(c = d_objFolder[d_objFolder.size() - 1]; c != '/'; c = d_objFolder[d_objFolder.size() - 1])
        d_objFolder.resize(d_objFolder.size() - 1);
    
    d_mtlParser.parseMTL(mtlfile);
    
    d_activeObject.d_name = "";
    
    std::ifstream filestr;
    filestr.open(objfile.c_str(), std::ios::in);
    if(!filestr.good())
        std::cout << "error opening " << objfile << '\n';
    while(filestr.good())
    {
        std::string line;
        std::getline(filestr, line);
        parseLine(line);
    }
    rollout();
    d_activeObject.d_interleaved = std::move(d_interleaved);
    d_interleaved.clear();
    d_objects.push_back(d_activeObject);
    std::cout << "read " << d_objects.size() << " objects\n";
}