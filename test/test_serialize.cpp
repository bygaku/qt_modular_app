#include <QGuiApplication>
#include <iostream>
#include <QSharedPointer>
#include "user_data.h"
#include "serializer.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    Serializer file("test_data.json", &app);

    UserData* user001 = new UserData(&app);
    user001->setName("Gaku");
    user001->setAge(5);
    UserData* user002 = new UserData(&app);
    user002->setName("Rindai");
    user002->setAge(2);
    UserData* user003 = new UserData(&app);
    user003->setName("Hiroto");
    user003->setAge(3);

    QVector<UserData*> users;
    users.append(user001);
    users.append(user002);
    users.append(user003);

    file.saveArrayToFile(users);
    for (auto&& i : users) {
        std::cout << i->name().toStdString() << ":" << i->age() << std::endl;
    }

    user001->setAge(1);
    user002->setAge(1);
    user003->setAge(1);
    file.loadArrayFromFile(users);

    for (auto&& i : users) {
        std::cout << i->name().toStdString() << ":" << i->age() << std::endl;
    }

    return app.exec();
}
