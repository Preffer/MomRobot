#ifndef TEXTREADER_H
#define TEXTREADER_H

#include <QMessageBox>
#include <QFileDialog>
#include <QSharedPointer>
#include <QMap>

class textReader
{

public:
    explicit textReader(QString& filePath);
    void getIndex();
    QSharedPointer< QMap<QString, QString> > getData();
    ~textReader();

private:
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
