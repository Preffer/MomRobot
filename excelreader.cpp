#include "excelreader.h"
#include <QDebug>

int excelReader::keyLength = 17;
QString excelReader::keyName = "账号";
QString excelReader::valueName = "贷款余额";
QString excelReader::dataPrefix = "PL";

QString excelReader::pointToString(int x, int y)
{
    int A = 'A';
    return QChar(A + x -1) + QString::number(y);
}

excelReader::excelReader(QString& filePath)
{
    if(!filePath.isEmpty()){
        excel = new QAxObject("Excel.Application");
        excel->setProperty("Visible", false);
        excel->setProperty("DisplayAlerts", false);

        workbooks = excel->querySubObject("WorkBooks");
        workbooks->dynamicCall("Open (const QString&)", filePath);
        workbook = excel->querySubObject("ActiveWorkBook");
        //prepare
        worksheet = workbook->querySubObject("Worksheets(int)", 1);
        usedRange = worksheet->querySubObject("UsedRange");
        rowStart = usedRange->property("Row").toInt();
        colStart = usedRange->property("Column").toInt();
        rowEnd = usedRange->querySubObject("Rows")->property("Count").toInt() + rowStart - 1;
        colEnd = usedRange->querySubObject("Columns")->property("Count").toInt() + colStart - 1;

        //qDebug() << rowStart << colStart << rowEnd << colEnd;
    }
}

void excelReader::getIndex()
{
    QAxObject* cell;
    for (int i = rowStart; i <= rowEnd; i++) {
        for (int j = colStart; j <= colEnd; j++) {
            cell = worksheet->querySubObject("Cells(Int, Int)", i, j);
            //QVariant cellValue = cell->property("Value");
            //cell->dynamicCall("SetValue(QString)", QString("(%1, %2)").arg(i).arg(j));
            if(cell->property("Value").toString() == keyName) {
                qDebug() << j;
                keyIndex = j;
            } else{
                if(cell->property("Value").toString() == valueName) {
                    qDebug() << j;
                    valueIndex = j;
                    dataStart = i + 1;
                    return;
                }
            }
        }
    }
}

void excelReader::getKey(){
    QAxObject *range = worksheet->querySubObject( "Range(const QVariant&)", QVariant(pointToString(keyIndex, dataStart) + ":" + pointToString(keyIndex, rowEnd)));
    //range->dynamicCall( "SetValue(const QString&)", "from qt");
    QVariantList all = range->property("Value").toList();
    int count = all.count();
    for(int i = 0; i < count; i++) {
        QString key = all.at(i).toList().at(0).toString();
        if(key.isEmpty()){
            dataEnd = dataStart + i - 1;
            qDebug() << dataStart << dataEnd;
            return;
        } else{
            //qDebug() << key.rightJustified(keyLength, '0');
            keyList.append(key.rightJustified(keyLength, '0'));
        }
    }
}

void excelReader::getValue()
{
    int count = keyList.count();
    for(int i = 0; i < count; i++){
        //qDebug() << map->value(keyList.at(i));
        valueList.append(keyValueMap->value(keyList.at(i)));
    };
}

void excelReader::pushValue()
{
    QAxObject *range = worksheet->querySubObject( "Range(const QVariant&)", QVariant(pointToString(valueIndex, dataStart) + ":" + pointToString(valueIndex, dataEnd)));
    //qDebug() << range->property("Value").toList();
    //range->dynamicCall("SetValue(const QString&", "from qt");
    int count = valueList.count();
    QVariantList box;
    QVariantList temp;
    for(int i = 0; i < count; i++) {
        temp.clear();
        temp.append(valueList.at(i));
        box.append(QVariant(temp));
    }
    //qDebug() << box;
    range->dynamicCall("SetValue(const QVariant&)", QVariant(box));
}

void excelReader::exec(QSharedPointer<QMap<QString, QString> > map)
{
    keyValueMap = map;
    this->getIndex();
    this->getKey();
    this->getValue();
    this->pushValue();
}

excelReader::~excelReader()
{
    workbook->dynamicCall("Save(void)");
    workbook->dynamicCall("Close (Boolean)", false);
}
