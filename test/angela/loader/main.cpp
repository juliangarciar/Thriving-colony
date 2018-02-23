#include <iostream>
#include <fstream>
#include <json/json.hpp>

using json = nlohmann::json;

int main(){
    json j;
    //MAP
    std::string heightmap, texture_map, detail_texture_map;
    int size_map [3];
    //CAMERA
    int zoomDistanceFromTarget, delta_x, delta_y;
    //LIGHT
    int light_position [3];
    //PLAYER
    int initial_crystal, initial_metal, siderurgy_productivity, quarry_productivity;


    try{
        std::ifstream i;
        i.open("map.json");
        i >> j;
        i.close();
    }
    catch(std::ifstream::failure e){
        std::cout<<"EEEEEEERRORRRRR ACHO"<<std::endl;
        exit(0);
    }

    heightmap = j["map"]["heightmap"].get<std::string>();
    texture_map = j["map"]["texture"].get<std::string>();
    detail_texture_map = j["map"]["detail_texture"].get<std::string>();
    size_map[0] = j["map"]["size"]["x"].get<int>();
    size_map[1] = j["map"]["size"]["y"].get<int>();
    size_map[2] = j["map"]["size"]["z"].get<int>();

    zoomDistanceFromTarget = j["camera"]["zoomDistanceFromTarget"].get<int>();
    delta_x = j["camera"]["delta_x"].get<int>();
    delta_y = j["camera"]["delta_y"].get<int>();

    light_position[0] = j["light"][0]["position"]["x"].get<int>();
    light_position[1] = j["light"][0]["position"]["y"].get<int>();
    light_position[2] = j["light"][0]["position"]["z"].get<int>();

    initial_crystal = j["player"][0]["initial_crystal"].get<int>();
    initial_metal = j["player"][0]["initial_crystal"].get<int>();
    siderurgy_productivity = j["player"][0]["initial_crystal"].get<int>();
    quarry_productivity = j["player"][0]["initial_crystal"].get<int>();

    std::cout<<"MAP "<<std::endl;
    std::cout<<"heightmap: "<<heightmap<<std::endl;
    std::cout<<"texture_map: "<<texture_map<<std::endl;
    std::cout<<"detail_texture_map: "<<detail_texture_map<<std::endl;
    std::cout<<"size_map[x]: "<<size_map[0]<<std::endl;
    std::cout<<"size_map[y]: "<<size_map[1]<<std::endl;
    std::cout<<"size_map[z]: "<<size_map[2]<<std::endl;

    std::cout<<"CAMERA "<<std::endl;
    std::cout<<"zoomDistanceFromTarget: "<<zoomDistanceFromTarget<<std::endl;
    std::cout<<"delta_x: "<<delta_x<<std::endl;
    std::cout<<"delta_y: "<<delta_y<<std::endl;

    std::cout<<"LIGHT "<<std::endl;
    std::cout<<"light_position[x]: "<<light_position[0]<<std::endl;
    std::cout<<"light_position[y]: "<<light_position[1]<<std::endl;
    std::cout<<"light_position[z]: "<<light_position[2]<<std::endl;

    std::cout<<"PLAYER "<<std::endl;
    std::cout<<"initial_crystal: "<<initial_crystal<<std::endl;
    std::cout<<"initial_metal: "<<initial_metal<<std::endl;
    std::cout<<"siderurgy_productivity: "<<siderurgy_productivity<<std::endl;
    std::cout<<"quarry_productivity: "<<quarry_productivity<<std::endl;

}