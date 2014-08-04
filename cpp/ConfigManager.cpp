#include <sstream>
#include "../h/ConfigManager.h"

ConfigManager* ConfigManager::INSTANCE = new ConfigManager;

ConfigManager::ConfigManager() {
    initFileSystem();
    cache = new Properties(getRootPath() + CACHE_FILE);
    config = new Properties(getRootPath() + CONF_FILE);
}

ConfigManager::~ConfigManager() {
    if (cache != NULL) {
        cache->store();
        delete cache;
    }
    if (config != NULL) {
        config->store();
        delete config;
    }
}

ConfigManager* ConfigManager::getInstance() {
    return INSTANCE;
}

void ConfigManager::initFileSystem() {
    std::stringstream ss;
    if (getenv("HOME") == NULL)
        ss << getenv("HOMEDRIVE") << getenv("HOMEPATH") << "/Documents/Motion-Classifier/";
    else
        ss << getenv("HOME") << "/Documents/Motion-Classifier/";
    rootPath = ss.str();
    std::replace(rootPath.begin(), rootPath.end(), '\\', '/');
    boost::filesystem::path p(rootPath);
    std::cout << rootPath << std::endl;
    if (!boost::filesystem::exists(p)) {
        boost::filesystem::create_directories(p);
        boost::filesystem::create_directory(rootPath + "classifer");
        boost::filesystem::create_directories(rootPath + "trainer");

        std::ofstream out(rootPath + CONF_FILE);
        out << "sample.rows = 0" << std::endl;
        out << "sample.columns = 0" << std::endl;
        out << "interval.nrSamples = 0" << std::endl;
        out << "emgProvider.bufferWarning = 1000" << std::endl;
        out << "blockingQueue.maxWaitTime = 5000" << std::endl;
        out << "trainer.baseDir = C:/Tmp/Trainer/" << std::endl;
        out << "trainer.trainingsSize = 3000" << std::endl;
        out << "trainer.nrRuns = 1" << std::endl;
        out << "graph.maxdisplay = 50" << std::endl;
        out.close();

        //Create File
        out.open(rootPath + CACHE_FILE);
        out.close();
    }
}

std::string ConfigManager::getTrainerDir() {
    return getRootPath() + TRAINER_BASE;
}

std::string ConfigManager::getRootPath() {
    return rootPath;
}

Properties* ConfigManager::getCache() {
    return cache;
}

Properties* ConfigManager::getConf() {
    return config;
}
