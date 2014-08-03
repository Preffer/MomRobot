#include "textreader.h"
#include <QDebug>

QString textReader::keyName = "贷款账号";
QString textReader::valueName = "贷款余额";
QString textReader::dataPrefix = "000000";
int textReader::valueOffset = -3;

textReader::textReader(QString& filePath)
{
    file = new QFile(filePath);
    if(!file->open(QIODevice::ReadOnly)) {
        QMessageBox::warning(NULL, "Failed", "Open file failed!");
    }
}

void textReader::getIndex()
{
    QSharedPointer<QTextStream> stream = (QSharedPointer<QTextStream>) new QTextStream(file);
    QString line;
    QStringList fields;

    while(!(line = stream->readLine()).isNull()) {
        fields = line.split(" ", QString::SkipEmptyParts);
        if(fields.indexOf(keyName) != -1) {
            //qDebug() << fields;
            keyIndex = fields.indexOf(keyName);
            // because have space around 月, so have to the additional 3 index
            valueIndex = fields.indexOf(valueName) + valueOffset;
            break;
        }
    }
}

QSharedPointer< QMap<QString, QString> > textReader::getData()
{
    //call getIndex first
    this->getIndex();
    QSharedPointer<QTextStream> stream = (QSharedPointer<QTextStream>) new QTextStream(file);
    QString line;
    QStringList fields;

    data = (QSharedPointer< QMap<QString, QString> >) new QMap<QString, QString>;
    while(!(line = stream->readLine()).isNull()) {
        if(line.indexOf(dataPrefix) != -1){
            fields = line.split(" ", QString::SkipEmptyParts);
            data->insert(fields.at(keyIndex), fields.at(valueIndex));
        }
    }
    return data;
}

textReader::~textReader()
{
    delete file;
}
