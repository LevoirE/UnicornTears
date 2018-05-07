#include "filehelper.h"
#include <QFile>
#include <QTextStream>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonParseError>
#include <QTextCodec>
#include <QDebug>

FileHelper::FileHelper()
{

}

FileHelper::~FileHelper()
{

}

void FileHelper::doSearch(const QString &fileName)
{
    changeFileCodeToUtf8(fileName);
    QJsonDocument *doc = getJsonDocument(fileName);
    if (doc->isNull())
        return;
    QJsonObject json = doc->object();
    if (json.contains("name")) {
        QJsonValue value = json.value("name");
        qDebug() << value.toString();
    }
}

QJsonDocument* FileHelper::getJsonDocument(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return NULL;
    QByteArray rawData = file.readAll();
    file.close();
    QJsonParseError jsonError;
    QJsonDocument *document = new QJsonDocument(QJsonDocument::fromJson(rawData, &jsonError));
    qDebug() << rawData;
    if (jsonError.error != QJsonParseError::NoError)
        qDebug() << jsonError.errorString() << ", Offset: " << jsonError.offset;
    if (!document->isObject())
        qDebug("Invaild content");
    return document;
}

void FileHelper::changeFileCodeToUtf8(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
        return;
    QTextStream stream(&file);
    stream.setCodec(QTextCodec::codecForName("UTF-8"));
    QString text = stream.readAll();
    qDebug() << text;
    stream.seek(0);

    stream << text;
    file.close();
}
