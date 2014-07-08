#ifndef PROPERTIESLAYOUT_H
#define PROPERTIESLAYOUT_H

#include <QFormLayout>
#include <Properties.h>

class PropertiesLayout : public QFormLayout {
    Q_OBJECT

private:
    Properties *properties;
public:
    PropertiesLayout(Properties *properties);
    Properties* getProperties();

public slots:
    void storeValues();

};

#endif // PROPERTIESLAYOUT_H
