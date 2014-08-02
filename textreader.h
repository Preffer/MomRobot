#ifndef TEXTREADER_H
#define TEXTREADER_H

#include <QMessageBox>
#include <QFileDialog>

class textReader
{

public:
    explicit textReader(QString& filePath);
    void getIndex();
    void getData();
    ~textReader();

private:
    QFile* file;
    static QString keyName;
    static QString valueName;
    int keyIndex;
    int valueIndex;
    static int valueOffset;
    static QString dataPrefix;
};

#endif // TEXTREADER_H
