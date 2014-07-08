#ifndef GUILOGGER_H
#define GUILOGGER_H

#include <Logger.h>

#include <QTextEdit>

class GUILogger : public Logger {
private:
    Logger *instance;
    QTextEdit *logText;

    Logger();
    ~Logger();

public:
    static Logger* getInstance();
    static void release();

    void setLogField(QTextEdit* logText);
    void trace(std::string message);
    void debug(std::string message);
};

#endif // GUILOGGER_H
