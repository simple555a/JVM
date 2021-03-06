//
// Created by xuranus on 2/6/19.
//

#ifndef JVM_ENTRY_H
#define JVM_ENTRY_H

#include "../classfile/basicType.h"
#include <iostream>
#include <vector>

/*
 * std::pair<byte[],int> readClass(),
 * return byte array and lenth of byte,
 * if byte==0 and len==0 means no file found,
 * if bytes not null means file found,
 * if len < 0 means error occured.
 * */

class Entry { //interface
public:
    virtual std::pair<byte*,int> readClass(std::string classname)=0;
    virtual std::string toString()=0;

    static Entry* createEntry(std::string path);//public factory method
    static Entry* createCompositeEntry(std::string path);
    static Entry* createDirEntry(std::string path);
    static Entry* createZipEntry(std::string path);
    static Entry* createWildcardEntry(std::string path);
};

struct DirEntry :public Entry{ //common dirs
    std::string absPath; //absolute path

    std::pair<byte*,int> readClass(std::string classname) override;
    std::string toString() override;
    explicit DirEntry(std::string path) ;
};

struct ZipEntry :public Entry{ // *.zip ,*.jar file
    std::string absFilePath;

    std::pair<byte*,int> readClass(std::string classname) override;
    std::string toString() override;

    explicit ZipEntry(std::string zipfileName);
};

struct CompositeEntry :public Entry { //multiple directory,file separator ";" or "*"
    std::vector<Entry*> entries;

    std::pair<byte*,int> readClass(std::string classname) override;
    std::string toString() override;
    explicit CompositeEntry(std::string paths);
};




#endif //JVM_ENTRY_H
