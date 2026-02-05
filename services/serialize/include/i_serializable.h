#ifndef I_SERIALIZABLE_H
#define I_SERIALIZABLE_H

#include <QJsonObject>

/**
 * @class ISerializable.
 * @brief Serializable objects inherit from this interface.
 */
class ISerializable {
public:
    virtual ~ISerializable() = default;

    virtual QJsonObject toJson() const = 0;

    virtual bool fromJson(const QJsonObject &json) = 0;
};

#endif // I_SERIALIZABLE_H
