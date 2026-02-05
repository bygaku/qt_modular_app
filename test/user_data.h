#ifndef USER_DATA_H
#define USER_DATA_H

#include <QObject>
#include "i_serializable.h"

class UserData : public QObject, public ISerializable {
    Q_OBJECT
public:
    explicit UserData(QObject *parent = nullptr)
        : QObject(parent)
        , name_("Guest")
        , age_(0){
    }

    QJsonObject toJson() const override {
        QJsonObject json;
        json["name"] = name_;
        json["age"]  = age_;
        return json;
    }

    bool fromJson(const QJsonObject &json) override{
        if (json.contains("name") && json["name"].isString()) {
            setName(json["name"].toString());
        }
        if (json.contains("age") && json["age"].isDouble()) {
            setAge(json["age"].toInt());
        }
        return true;
    }

    QString name() const { return name_; }

    void setName(const QString &new_name) {
        if (name_ == new_name) return;
        name_ = new_name;
    }

    int age() const { return age_; }

    void setAge(int new_age) {
        if (age_ == new_age) return;
        age_ = new_age;
    }

private:
    QString name_;
    int     age_;

};


#endif // USER_DATA_H
