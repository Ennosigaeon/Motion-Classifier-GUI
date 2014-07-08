#include "../../h/gui/PropertiesLayout.h"

#include <QLineEdit>
#include <QLabel>
#include <iostream>

PropertiesLayout::PropertiesLayout(Properties *properties) {
    PropertiesLayout::properties = properties;

    for (std::map<std::string, std::string>::iterator it = properties->getValues().begin(); it != properties->getValues().end(); ++it) {
        QLineEdit *text = new QLineEdit(QString::fromStdString(it->second));
        addRow(QString::fromStdString(it->first), text);
    }
}

Properties* PropertiesLayout::getProperties() {
    return properties;
}

void PropertiesLayout::storeValues() {
    for (int i = 0; i < rowCount(); ++i) {
        QLabel *label = (QLabel*) itemAt(i, QFormLayout::LabelRole)->widget();
        QLineEdit *text = (QLineEdit*) itemAt(i, QFormLayout::FieldRole)->widget();
        properties->set(label->text().toStdString(), text->text().toStdString());
    }
}
