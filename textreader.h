#ifndef TEXTREADER_H
#define TEXTREADER_H

#include <QFile>
#include <QSharedPointer>
#include <QMap>
#include <stdexcept>

class textReader
{

public:
    explicit textReader(QString& filePath);
    QSharedPointer< QMap<QString, QString> > exec();
    ~textReader();

private:
    void getIndex();
    void getData();

    QFile* file;

    int keyIndex;
    int valueIndex;

    QSharedPointer< QMap<QString, QString> > data;

    static QString keyName;
    static QString valueName;
    static int valueOffset;
    static QString dataPrefix;
};

#endif // TEXTREADER_H
