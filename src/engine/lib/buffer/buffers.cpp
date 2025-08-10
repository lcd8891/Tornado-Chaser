#include <lite3D/glutils/texture.hpp>
#include <lite3D/glutils/shader.hpp>
#include <map>
#include <lite3D/lite_utils.hpp>
#include <filesystem>

namespace {
    std::map<std::string,Texture*> t_buffer;
    std::map<std::string,Shader*> s_buffer;
}

namespace TextureBuffer{
    Texture* load_from_res(std::string _path,std::string _i){
        std::string full_path = "./res/textures/"+_path+".png";
        if(!std::filesystem::exists(full_path)){
            throw EXIT_INFO("Couldn't find texture: "+full_path);
        }
        Texture* t = loadFromFile(full_path);
        auto it = t_buffer.find(_i);
        if(it!=t_buffer.end()){
            delete it->second;
            it->second = t;
            Logger::waning("texture "+full_path+" exists and has been reloaded.");
        }else{
            t_buffer[_i] = t;
        }
        return t;
    }
    Texture* get(std::string _i){
        auto it = t_buffer.find(_i);
        return (it != t_buffer.end()) ? it->second : nullptr;
    }
    void delete_texture(std::string _i){
        auto it = t_buffer.find(_i);
        if(it != t_buffer.end()){
            delete it->second;
            t_buffer.erase(_i);
        }else{
            Logger::error("trying to delete non exists texture!");
        }
    }
    void delete_all(){
        for (auto& pair : t_buffer) {
            delete pair.second;
        }
        t_buffer.clear();
    }
}

namespace ShaderBuffer{
    Shader* load_from_res(std::string _path,std::string _i){
        std::string not_full_path = "./res/shaders/"+_path;
        Shader* s;
        if(std::filesystem::exists(not_full_path+".geom")){
            s = initShaderFromFile(not_full_path+".vert",not_full_path+".frag",not_full_path+".geom");
        }else{
            s = initShaderFromFile(not_full_path+".vert",not_full_path+".frag");
        }
        auto it = s_buffer.find(_i);
        if(it != s_buffer.end()){
            delete it->second;
            it->second = s;
            Logger::waning("shader "+_path+" exists and has been reloaded.");
        }else{
            s_buffer[_i] = s;
        }
        return s;
    }
    Shader* get(std::string _i){
        auto it = s_buffer.find(_i);
        return (it != s_buffer.end()) ? it->second : nullptr;
    }
    void delete_shader(std::string _i){
        auto it = s_buffer.find(_i);
        if(it != s_buffer.end()){
            delete it->second;
            s_buffer.erase(_i);
        }else{
            Logger::error("trying to delete non exists shader!");
        }
    }
    void delete_all(){
        for (auto& pair : s_buffer) {
            delete pair.second;
        }
        s_buffer.clear();
    }
}