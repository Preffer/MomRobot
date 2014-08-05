#ifndef TEXTREADER_H
#define TEXTREADER_H

#include <QFile>
#include <QTextStream>
#include <QSharedPointer>
#include <QMap>
#include <stdexcept>

class textReader : public QObject
{

    Q_OBJECT

public:
    explicit textReader(QString& filePath);
    QSharedPointer< QMap<QString, QString> > exec();
    ~textReader();

    QString keyName;
    QString valueName;
    QString dataPrefix;
    int valueOffset;

private:
    void getIndex();
    void getData();

    QFile* file;
    QTextStream* stream;

    int keyIndex;
    int valueIndex;

    QSharedPointer< QMap<QString, QString> > data;
};

#endif // TEXTREADER_H
