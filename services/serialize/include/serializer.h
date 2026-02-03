#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <QObject>
#include <QJsonArray>
#include <QFile>
#include <QJsonDocument>
#include "i_serializable.h"

template<typename T>
concept SerializableObj = std::is_base_of_v<ISerializable, T>;

class Serializer : public QObject {
    Q_OBJECT

public:
    explicit Serializer(const QString& filepath, QObject *parent = nullptr)
        : QObject(parent)
        , filepath_(filepath){
    }

    bool saveToFile(const ISerializable *object) {
        QFile file(filepath_);
        if (!file.open(QIODevice::WriteOnly)) {
            return false;
        }

        QJsonObject json = object->toJson();
        QJsonDocument doc(json);
        file.write(doc.toJson());
        return true;
    }

    bool loadFromFile(ISerializable *object) {
        QFile file(filepath_);
        if (!file.open(QIODevice::ReadOnly)) {
            return false;
        }

        QByteArray data = file.readAll();
        QJsonDocument doc(QJsonDocument::fromJson(data));

        if (doc.isNull() || !doc.isObject()) {
            return false;
        }

        return object->fromJson(doc.object());
    }

    template<SerializableObj T>
    bool saveArrayToFile(const QVector<T*>& objects) {
        QFile file(filepath_);
        if (!file.open(QIODevice::WriteOnly))
            return false;

        QJsonArray array;
        for (const auto* obj : objects) {
            array.append(obj->toJson());
        }

        QJsonDocument doc(array);
        file.write(doc.toJson());
        return true;
    }

    template<SerializableObj T>
    bool loadArrayFromFile(QVector<T*>& objects) {
        QFile file(filepath_);
        if (!file.open(QIODevice::ReadOnly)) return false;

        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        if (!doc.isArray()) return false;

        const QJsonArray array = doc.array();
        objects.clear();

        for (const auto& value : array) {
            if (value.isObject()) {
                T* obj = new T();
                if (obj->fromJson(value.toObject())) {
                    objects.append(obj);
                } else {
                    delete obj;
                }
            }
        }
        return true;
    }

private:
    QString filepath_;

};

#endif // SERIALIZER_H
