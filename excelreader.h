#ifndef EXCELREADER_H
#define EXCELREADER_H

#include <QAxObject>

class excelReader
{
public:
    explicit excelReader(QString& filePath);
    void getIndex();
    void getData();
    static QString pointToString(int x, int y);

    ~excelReader();

private:
    int keyIndex;
    int valueIndex;
    int dataStart;

    int rowStart;
    int colStart;
    int rowEnd;
    int colEnd;

    QAxObject* excel;
    QAxObject* workbooks;
    QAxObject* workbook;
    QAxObject* worksheet;
    QAxObject* usedRange;

    static QString keyName;
    static QString valueName;
    static QString dataPrefix;
};

#endif // EXCELREADER_H
