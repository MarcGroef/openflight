#include "shader.ih"

size_t getLength(ifstream& str)
{
    if(!str.good())
        return 0;
    str.tellg();
    str.seekg(0,ios::end);
    size_t len = str.tellg();
    str.seekg(0,ios::beg);
    return len;
}

void Shader::loadFromFile(string const &file)
{
    ifstream filestr;
    cout << "read" + file + "\n";
    filestr.open(file.c_str(), ios::in);
    size_t size = getLength(filestr);
    
    if(size == 0)
    {
        cout << "Shader " << file << " couldnt be loaded..\n";
        return;
    }
    
    stringstream strstr;
    while(filestr.good())
    {
        
        if(!filestr.eof())
        {
            d_shader.push_back((GLubyte) filestr.get());
            //cout << d_shader[d_shader.size() - 1];
        }
    }
   // d_shader = strstr.str();
    d_shader[d_shader.size() - 1] = '\0';
    //cout << d_shader << '\n';
}