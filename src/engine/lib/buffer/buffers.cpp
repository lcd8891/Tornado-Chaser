#include <lite3D/glutils/texture.hpp>
#include <lite3D/glutils/shader.hpp>
#include <map>
#include <lite3D/lite_utils.hpp>
#include <filesystem>

namespace {
    std::map<uint64,Texture*> t_buffer;
    
}

namespace TextureBuffer{
    Texture* load_from_res(std::string _path,Identificator _i){
        std::string full_path = "./res/textures/"+_path+".png";
        if(!std::filesystem::exists(full_path)){
            throw EXIT_INFO("Couldn't find texture: "+full_path);
        }
        Texture* t = loadFromFile(full_path);
        uint64 key = Identifier::of(_i);
        auto it = t_buffer.find(key);
        if(it!=t_buffer.end()){
            delete it->second;
            it->second = t;
            Logger::waning("texture "+full_path+" exists and has been reloaded.");
        }else{
            t_buffer[key] = t;
        }
        return t;
    }
    Texture* get(Identificator _i){
        auto it = t_buffer.find(Identifier::of(_i));
        return (it != t_buffer.end()) ? it->second : nullptr;
    }
    void delete_texture(Identificator _i){
        uint64 key = Identifier::of(_i);
        auto it = t_buffer.find(key);
        if(it != t_buffer.end()){
            delete it->second;
            t_buffer.erase(key);
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