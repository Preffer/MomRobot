#ifndef EXCELREADER_H
#define EXCELREADER_H

#include <QAxObject>
#include <QSharedPointer>

class excelReader
{
public:
    explicit excelReader(QString& filePath);
    void exec(QSharedPointer< QMap<QString, QString> > map);

    static QString pointToString(int x, int y);

    ~excelReader();

private:
    void getIndex();
    void getKey();
    void getValue();
    void pushValue();

    int keyIndex;
    int valueIndex;
    int dataStart;
    int dataEnd;

    int rowStart;
    int colStart;
    int rowEnd;
    int colEnd;

    QAxObject* excel;
    QAxObject* workbooks;
    QAxObject* workbook;
    QAxObject* worksheet;
    QAxObject* usedRange;

    QStringList keyList;
    QStringList valueList;

    QSharedPointer< QMap<QString, QString> > keyValueMap;

    static int keyLength;
    static QString keyName;
    static QString valueName;
    static QString dataPrefix;
};

#endif // EXCELREADER_H
