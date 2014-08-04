#include "textreader.h"
#include <QDebug>

QString textReader::keyName = "贷款账号";
QString textReader::valueName = "贷款余额";
QString textReader::dataPrefix = "0000";
int textReader::valueOffset = -3;

textReader::textReader(QString& filePath)
{
    if(!filePath.isEmpty()){
        file = new QFile(filePath);
        if(file->open(QIODevice::ReadOnly)) {
            stream = new QTextStream(file);
        } else{
            throw std::invalid_argument("无法打开文本文件");
        }
    } else{
        throw std::invalid_argument("请选择文本文件");
    }
}

void textReader::getIndex()
{
    QString line;
    QStringList fields;

    while(!(line = stream->readLine()).isNull()) {
        fields = line.split(" ", QString::SkipEmptyParts);
        if(fields.indexOf(keyName) != -1) {
            keyIndex = fields.indexOf(keyName);
            // because have space around 月, so have to the additional 3 index
            valueIndex = fields.indexOf(valueName) + valueOffset;
            return;
        }
    }
    throw std::invalid_argument("选择的文本文件有问题");
}

void textReader::getData()
{
    QString line;
    QStringList fields;

    data = (QSharedPointer< QMap<QString, QString> >) new QMap<QString, QString>;
    while(!(line = stream->readLine()).isNull()) {
        if(line.indexOf(dataPrefix) != -1){
            fields = line.split(" ", QString::SkipEmptyParts);
            data->insert(fields.at(keyIndex), fields.at(valueIndex));
        }
    }
}
QSharedPointer<QMap<QString, QString> > textReader::exec()
{
    this->getIndex();
    this->getData();
    return data;
}

textReader::~textReader()
{
    file->close();
    delete file;
    delete stream;
}
