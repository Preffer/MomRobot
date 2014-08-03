#include "excelreader.h"
#include <QDebug>

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

void excelReader::getData(){
    //getIndex first
    this->getIndex();
    QAxObject *range = worksheet->querySubObject( "Range(const QVariant&)", QVariant(pointToString(keyIndex, dataStart) + ":" + pointToString(keyIndex, rowEnd)));
    //range->dynamicCall( "SetValue(const QString&)", "from qt");
    qDebug() << range->property("Value").toList();
}

excelReader::~excelReader()
{
    workbook->dynamicCall("Save(void)");
    workbook->dynamicCall("Close (Boolean)", false);
}
