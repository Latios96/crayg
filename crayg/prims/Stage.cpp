//
// Created by Jan Honsbrok on 09.10.18.
//

#include <iostream>
#include "Stage.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include <fstream>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/istreamwrapper.h>

StageStats Stage::getStats() {
    StageStats stats;
    stats.primCount = static_cast<int>(primMaps.size());
    stats.attributeCount = static_cast<int>(attributeImpls.size());
    return stats;
}

std::map<std::string, GenericAttributeImpl*>*  Stage::createPrimMap(const std::string& path) {
    auto * prim = new std::map<std::string, GenericAttributeImpl*>();
    primMaps[path] = prim;
    return prim;
}

Stage::~Stage() {
    for (auto primMap : primMaps){
        delete primMap.second;
    }
    for(auto attributeImpl : attributeImpls){
        delete attributeImpl;
    }
}
AttributeImpl<int>* getAsIntImpl(GenericAttributeImpl* impl){
    return static_cast<AttributeImpl<int>*>(impl);
}
AttributeImpl<Vector3f>* getAsVector3fImpl(GenericAttributeImpl* impl){
    return static_cast<AttributeImpl<Vector3f>*>(impl);
}

AttributeImpl<std::string>* getAsStringImpl(GenericAttributeImpl* impl){
    return static_cast<AttributeImpl<std::string>*>(impl);
}
void Stage::printNice() {
    for(auto primMap : primMaps){
        std::cout << primMap.first << std::endl;
        for(auto primAttr : *(primMap.second)){
            std::cout << "   " << primAttr.second->attr_type << " " << primAttr.first;
            if (primAttr.second->isInt()){
                AttributeImpl<int> *impl = getAsIntImpl(primAttr.second);
                std::cout << " " << impl->value << std::endl;
            }
            else if (primAttr.second->isString()){
                std::string value = getAsStringImpl(primAttr.second)->value;
                std::cout << " " << value << std::endl;
            }
            else if (primAttr.second->isVector3f()){
                Vector3f value = getAsVector3fImpl(primAttr.second)->value;
                std::cout << " " << "x=" << value.x << " y=" << value.y << " z=" << value.z<< std::endl;
            }
        }
    }
}

std::map<std::string, GenericAttributeImpl *>* Stage::getPrimMapAt(const std::string &path) {
    return primMaps[path];
}

void Stage::writeToFile(const std::string fileName) {
    std::ofstream ofs(fileName);
    rapidjson::OStreamWrapper osw(ofs);
    rapidjson::PrettyWriter<rapidjson::OStreamWrapper> writer(osw);
    writer.StartObject();

    writer.Key("Prims");
    writer.StartObject();

    for(auto primMap : primMaps){
        // path
        writer.Key(primMap.first.c_str());
        writer.StartObject();

        // attributes
        for(auto primAttr : *(primMap.second)){
            // key
            writer.Key(primAttr.first.c_str());
            // value
            writer.StartObject();
            if (primAttr.second->isInt()){
                writer.Key("type");
                writer.String("int");
                writer.Key("value");
                int value = getAsIntImpl(primAttr.second)->value;
                writer.Int(value);
            }
            else if (primAttr.second->isString()){
                writer.Key("type");
                writer.String("String");
                writer.Key("value");
                std::string value = getAsStringImpl(primAttr.second)->value;
                writer.String(value.c_str());
            }
            else if (primAttr.second->isVector3f()){
                writer.Key("type");
                writer.String("Vector3f");
                writer.Key("value");
                Vector3f value = getAsVector3fImpl(primAttr.second)->value;
                writer.StartArray();
                writer.Double(value.x);
                writer.Double(value.y);
                writer.Double(value.z);
                writer.EndArray();
            }
            writer.EndObject();
        }
        writer.EndObject();
    }

    writer.EndObject();
    writer.EndObject();

    ofs.close();
}

void Stage::readFromFile(std::string fileName) {
    std::ifstream ifs(fileName);
    rapidjson::IStreamWrapper isw(ifs);
    rapidjson::Document d;
    d.ParseStream(isw);

    rapidjson::Value& prims = d["Prims"];
    if (prims.IsObject()){
        // for every prim
        for (rapidjson::Value::ConstMemberIterator itr = prims.MemberBegin(); itr != prims.MemberEnd(); ++itr) {
            const char *primPath = itr->name.GetString();
            const rapidjson::Value& prim = prims[primPath];

            // create the prim map
            std::map<std::string, GenericAttributeImpl*>* primMap = createPrimMap(std::string(primPath));

            for (rapidjson::Value::ConstMemberIterator primMemberItr = prim.MemberBegin(); primMemberItr != prim.MemberEnd(); ++primMemberItr) {
                const rapidjson::Value& primAttr = prim[primMemberItr->name.GetString()];
                std::string attributeType = primAttr["type"].GetString();

                // create the attribute
                if (attributeType == "int"){
                    AttributeImpl<int>* impl = createAttributeImpl<int>();
                    impl->value = primAttr["value"].GetInt();
                    primMap->insert(std::make_pair(primMemberItr->name.GetString(), impl));
                }
                else if (attributeType == "String"){
                    AttributeImpl<std::string>* impl = createAttributeImpl<std::string>();
                    impl->value = primAttr["value"].GetString();
                    primMap->insert(std::make_pair(primMemberItr->name.GetString(), impl));
                }
                else if (attributeType == "Vector3f"){
                    AttributeImpl<Vector3f>* impl = createAttributeImpl<Vector3f>();
                    auto array = primAttr["value"].GetArray();
                    impl->value = Vector3f(array[0].GetFloat(), array[1].GetFloat(), array[2].GetFloat());
                    primMap->insert(std::make_pair(primMemberItr->name.GetString(), impl));
                }

            }
        }
    }
    else{
        std::cout << "error" << std::endl;
    }


}


