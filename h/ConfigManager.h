#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <boost/filesystem.hpp>

#include <string>
#include <Properties.h>

class ConfigManager {
private:
    static ConfigManager *INSTANCE;

    std::string TRAINER_BASE = "trainer/";
    std::string CONF_FILE = "conf.txt";
    std::string CACHE_FILE = "cache.txt";

    std::string rootPath;
    Properties *cache = NULL;
    Properties *config = NULL;

    ConfigManager();
    void initFileSystem();


public:
    ~ConfigManager();

    static ConfigManager* getInstance();

    Properties* getCache();

    Properties* getConf();

    std::string getTrainerDir();

    std::string getRootPath();


};

#endif // CONFIGMANAGER_H
