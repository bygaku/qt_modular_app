#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <QObject>
#include <QJsonArray>
#include <QFile>
#include <QJsonDocument>
#include "i_serializable.h"

template<typename T>
concept SerializableObj = std::is_base_of_v<ISerializable, T>;

/**
 * @class Serializer
 * @brief Manipulates serialisable objects.
 */
class Serializer : public QObject {
    Q_OBJECT

public:
    /**
     * @brief Errors encountered during loading
     */
    enum class LoadError {
        NONE,
        FILE_NOT_FOUND,
        FILE_OPEN_FAILED,
        JSON_PARSE_ERROR,
        VALIDATION_ERROR
    };

public:
    /**
     * @brief Construct an instance of the serialiser.
     * @param filepath Json file.
     */
    explicit Serializer(const QString& filepath, QObject *parent = nullptr)
        : QObject(parent)
        , filepath_(filepath){
    }

    /**
     * @brief Saves a serialisable single object to a JSON file.
     * @param object Objects inheriting from the ISerializable class
     * @return Errors encountered during loading
     */
    LoadError saveToFile(const ISerializable *object) {
        QFile file(filepath_);
        if (!file.open(QIODevice::WriteOnly)) return LoadError::FILE_OPEN_FAILED;

        QJsonObject json = object->toJson();
        QJsonDocument doc(json);
        file.write(doc.toJson());

        return LoadError::NONE;
    }

    /**
     * @brief Loads a single serialisable object from a file.
     * @param object Objects inheriting from the ISerializable class
     * @return Errors encountered during loading
     */
    LoadError loadFromFile(ISerializable *object) {
        QFile file(filepath_);
        if (!file.open(QIODevice::ReadOnly)) return LoadError::FILE_OPEN_FAILED;

        QJsonParseError parseError;
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &parseError);

        if (parseError.error != QJsonParseError::NoError) return LoadError::JSON_PARSE_ERROR;
        if (!doc.isArray())                               return LoadError::VALIDATION_ERROR;
        if (!object->fromJson(doc.object()))              return LoadError::VALIDATION_ERROR;

        return LoadError::NONE;
    }

    /**
     * @brief Saves a serialisable array of objects to a file.
     * @param object Objects inheriting from the ISerializable class
     * @return Errors encountered during loading
     */
    template<SerializableObj T>
    LoadError saveArrayToFile(const QVector<T*>& objects) {
        QFile file(filepath_);
        if (!file.open(QIODevice::WriteOnly)) return LoadError::FILE_OPEN_FAILED;

        QJsonArray array;
        for (const auto* obj : objects) {
            array.append(obj->toJson());
        }

        QJsonDocument doc(array);
        file.write(doc.toJson());

        return LoadError::NONE;
    }

    /**
     * @brief Loads an array of serialisable objects from a file.
     * @param object Objects inheriting from the ISerializable class
     * @return Errors encountered during loading
     *
     * @note It is recommended that you call this before the application terminates.
     */
    template<SerializableObj T>
    LoadError loadArrayFromFile(QVector<T*>& objects) {
        QFile file(filepath_);
        if (!file.open(QIODevice::ReadOnly)) return LoadError::FILE_OPEN_FAILED;

        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        if (!doc.isArray()) return LoadError::VALIDATION_ERROR;

        const QJsonArray array = doc.array();

        QVector<T*> temp;

        for (const auto& value : array) {
            if (value.isObject()) {
                T* obj = new T();
                if (obj->fromJson(value.toObject())) {
                    temp.append(obj);
                } else {
                    delete obj;
                    qDeleteAll(temp);
                    return LoadError::VALIDATION_ERROR;
                }
            }
        }

        qDeleteAll(objects);
        objects = std::move(temp);

        return LoadError::NONE;
    }

private:
    QString filepath_;

};

#endif // SERIALIZER_H
