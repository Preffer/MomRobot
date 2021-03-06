#ifndef EXCELREADER_H
#define EXCELREADER_H

#include <QAxObject>
#include <QSharedPointer>
#include <QDir>
#include <stdexcept>

class excelReader : public QObject
{
    Q_OBJECT

public:
    explicit excelReader(QString& filePath);
    void exec(QSharedPointer< QMap<QString, QString> > map);
    ~excelReader();

    QString saveFilePath;
    static QString pointToString(int x, int y);

    QString keyName;
    QString valueName;
    QString dateName;
    int keyLength;
    int headerWithin;
    int newMonthBound;

signals:
    void progressBarInit(int min, int max);
    void progressBarUpdate(int value);

private:
    void getIndex();
    void getKey();
    void getValue();
    void pushValue();
    void checkNewMonth();

    QSharedPointer<QVariant> pack(QSharedPointer<QStringList> list);
    //abort to build an unpack function because many additional works done in its iteration

    int keyIndex;
    int valueIndex;
    int dateIndex;
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

    QSharedPointer<QStringList> keyList;
    QSharedPointer<QStringList> valueList;
    QSharedPointer< QMap<QString, QString> > keyValueMap;
};

#endif // EXCELREADER_H
