#ifndef FILEHELPER_H
#define FILEHELPER_H

#include <QJsonObject>
#include <QObject>

class FileHelper : public QObject
{
    Q_OBJECT

private slots:
    void doSearch(const QString &fileName);
public:
    FileHelper();
    ~FileHelper();
    QJsonDocument* getJsonDocument(const QString &fileName);
private:
    void changeFileCodeToUtf8(const QString &fileName);
};

#endif // FILEHELPER_H
