#include "loginservice.h"

LoginService::LoginService(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginService)
{
    ui->setupUi(this);
    ui->L_FORGOT->setText("<a href=\"" + LINK_FORGET + "\">" + ui->L_FORGOT->text() + "</a>");
    ui->L_REGISTER->setText("<a href=\"" + LINK_REGISTER + "\">" + ui->L_REGISTER->text() + "</a>");

    mW = new MainWindow(nullptr);
    QtConcurrent::run([=]()mutable{
        qDebug() << DatabaseItem::loadItem();
        qDebug() << "Items Loaded";
        mW->loaded();
    });
    QtConcurrent::run([=]{
        qDebug() << DatabaseMap::loadMap();
        qDebug() << "Maps Loaded";
        mW->loaded();
    });
    QtConcurrent::run([=]{
        qDebug() << DatabaseSkill::loadSkill();
        qDebug() << "Skills Loaded";
        mW->loaded();
    });
    QtConcurrent::run([=]{
        qDebug() << DatabaseMonster::loadMonster();
        qDebug() << "Monsters Loaded";
        mW->loaded();
    });
}

LoginService::~LoginService()
{
    delete ui;
}

void LoginService::on_PB_CONNECT_clicked()
{
    mW->show();
    /*QString email = ui->LE_EMAIL->text();
    QString password = ui->LE_PASSWORD->text();
    if(email.size() < 5)
    {

    }
    if(password.size() < 3) return;
    if(!email.contains("@") || !email.contains(".")) return;
*/
//    NetworkRequester netReq(this);
//    QByteArray json = "{"
//                      "\"email\":\"" + email.toUtf8() + "\","
//                      "\"password\":\"" + password.toUtf8() + "\""
//                      "}";
//    QNetworkRequest req(LINK_REQUEST);
//    req.setRawHeader("Connection", "Keep-Alive");
//    req.setRawHeader("Content-Length", QString(json.length()).toUtf8());
//    req.setRawHeader("User-Agent", "AyugraBot");
//    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
//    req.setRawHeader("Accept", "*/*");
//    req.setRawHeader("Accept-Encoding", "gzip, deflate, br");
//    req.setRawHeader("Accept-Language", "en-US,en;q=0.9");
//    QByteArray resp = netReq.post(json, req);
//    QJsonDocument jsonDoc = QJsonDocument::fromJson(resp);
//    QJsonObject jsonObj = jsonDoc.object();
//    QString jsonResp = jsonDoc.toJson();
    /*QString jsonResp = "\"error\": \"1\"";
    if(jsonResp.contains("\"e")) // Dirty code to avoid easy reversing based on string
    {
        qDebug() << "Ok";
        return;
    }
    else if(!jsonResp.contains("\"m"))
        return;*/
//    token = jsonObj.value(QString("token")).toString();
//    platformGameAccountID = jsonObj.value(QString("platformGameAccountId")).toString();
//    email = jsonObj.value(QString("email")).toString();
}
