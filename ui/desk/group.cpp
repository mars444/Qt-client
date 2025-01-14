#include "Group.h"
#include "Groups.h"

#include "style/stylecontainer.h"
using namespace styles;
#include "screensfactory.h"

#include "nlohmann/json.hpp"
#include <iostream>
#include <set>


#include <QLabel>
#include <QNetworkAccessManager>
#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QJsonObject>
#include <QJsonDocument>
#include <QSettings>
#include <QMessageBox>
#include <QJsonArray>

#include <ui/view/waitingspinnerwidget.h>

#include <iostream>
#include <set>

#include <ui/view/qsvgbutton.h>
#include <ui/view/waitingspinnerwidget.h>
using namespace screens;

#include "ui/auth/user_data.h"


Group::Group() {

    std::string IDstd = GetId();

    ID_QSTRING = QString::fromUtf8(IDstd.c_str());

    std::string GroupTitil = GetGroupTitle();

    std::string GroupID = GetGroupID();

    GROUP_ID = QString::fromUtf8(GroupID.c_str());

    group_id_label = new QLabel(GROUP_ID);

    group_id_label->hide();

    GROUP_TITLE_QSTRING = QString::fromUtf8(GroupTitil.c_str());

    mainVLayout = new QVBoxLayout;
    QVBoxLayout *inputContainer = new QVBoxLayout;

    QHBoxLayout *titleContainer = new QHBoxLayout;
    QSvgButton *backButton = new QSvgButton(":/resc/resc/arrow_back.svg", QSize(24,24));

    GrouptitleLabel = new QLabel(GROUP_TITLE_QSTRING);

    createButton = new QPushButton(tr("Add Friends"));



    QHBoxLayout *GroupContainerMain = new QHBoxLayout;

    GroupContainerMain->setAlignment(Qt::AlignCenter);

    GroupContainerMain->setContentsMargins(0,20,0,0);




    QLabel *groupEventMain = new QLabel(tr("Meeting start"));
    QLabel *groupEventendMain = new QLabel(tr("Meeting end"));



    groupEventMain->setStyleSheet(SETTINGS_LABEL);
    groupEventendMain->setStyleSheet(SETTINGS_LABEL);


    //GroupContainerMain->addWidget(groupEventDateLabelMain);
    GroupContainerMain->addWidget(groupEventMain);
    GroupContainerMain->addWidget(groupEventendMain);



    QHBoxLayout *groupButtonsContainer = new QHBoxLayout;

    groupList = new QPushButton(tr("Members"));

    groupMeets = new QPushButton(tr("Meets"));

    groupDelete = new QPushButton(tr("             Delete group         "));

    QPixmap pixmapgroupDelete(":/resc/resc/cross.svg");
    QIcon ButtonIcongroupDelete(pixmapgroupDelete);

    groupDelete->setIcon(ButtonIcongroupDelete);
    groupDelete-> setLayoutDirection ( Qt :: RightToLeft );
    groupDelete-> setStyleSheet("text-align: right");
    groupDelete->setIconSize(QSize(20,20));
    groupDelete->setStyleSheet(BUTTON_PROFILE_RED);
    groupDelete->setMaximumWidth(227);
    groupDelete->setMinimumWidth(227);

    deleteLabel = new QLabel(tr("You are sure?"));
    deleteLabel->setContentsMargins(0,0,0,3); // чтобы при нажатии delete group  выровнять слои хз почему разная высота
    groupDeleteYes = new QSvgButton(":/resc/resc/check.svg", QSize(35,35));
    groupDeleteNo = new QSvgButton(":/resc/resc/cross.svg", QSize(30,30));






    deleteLabel->setAlignment(Qt::AlignCenter);
    deleteLabel->setMaximumWidth(150);




    //groupDeleteNo->setContentsMargins(30,0,0,0);

    connect(groupDeleteYes, &QPushButton::clicked, this, &Group::groupDeleteYesPressed);
    connect(groupDeleteNo, &QPushButton::clicked, this, &Group::groupDeleteNoPressed);


    connect(groupList, &QPushButton::clicked, this, &Group::groupListPressed);

    connect(groupMeets, &QPushButton::clicked, this, &Group::groupMeetsPressed);

    connect(groupDelete, &QPushButton::clicked, this, &Group::groupDeletePressed);







    deleteLayout = new QHBoxLayout;

    deleteLabel->setStyleSheet(DELETE_GROUP_FRAME);

    deleteLayout->addWidget(groupDeleteYes);
    deleteLayout->addWidget(deleteLabel);

    deleteLayout->addWidget(groupDeleteNo);

    deleteLabel->hide();
    groupDeleteYes->hide();
    groupDeleteNo->hide();


    groupMeets->setStyleSheet(BUTTON_SOLID);
    groupList->setStyleSheet(BUTTON_DISABLED);


    groupButtonsContainer->addWidget(groupMeets);

    groupButtonsContainer->addWidget(groupList);

    groupButtonsContainer->addWidget(groupDelete);

    groupButtonsContainer->addLayout(deleteLayout);





    QHBoxLayout *daysButtonsContainer = new QHBoxLayout;
    QDate date =   QDate::currentDate();


    day1Button = new QPushButton(date.toString("dddd\n dd MMMM"));
    day2Button = new QPushButton(date.addDays(1).toString("dddd\n dd MMMM"));
    day3Button = new QPushButton(date.addDays(2).toString("dddd\n dd MMMM"));
    day4Button = new QPushButton(date.addDays(3).toString("dddd\n dd MMMM"));
    day5Button = new QPushButton(date.addDays(4).toString("dddd\n dd MMMM"));
    day6Button = new QPushButton(date.addDays(5).toString("dddd\n dd MMMM"));
    day7Button = new QPushButton(date.addDays(6).toString("dddd\n dd MMMM"));

    day1Button->setStyleSheet(BUTTON_SOLID);
    day2Button->setStyleSheet(BUTTON_DISABLED);
    day3Button->setStyleSheet(BUTTON_DISABLED);
    day4Button->setStyleSheet(BUTTON_DISABLED);
    day5Button->setStyleSheet(BUTTON_DISABLED);
    day6Button->setStyleSheet(BUTTON_DISABLED);
    day7Button->setStyleSheet(BUTTON_DISABLED);

    daysButtonsContainer->addWidget(day1Button);
    daysButtonsContainer->addWidget(day2Button);
    daysButtonsContainer->addWidget(day3Button);
    daysButtonsContainer->addWidget(day4Button);
    daysButtonsContainer->addWidget(day5Button);
    daysButtonsContainer->addWidget(day6Button);
    daysButtonsContainer->addWidget(day7Button);

    connect(day1Button, &QPushButton::clicked, this, &Group::getIventsDatePressed);
    connect(day2Button, &QPushButton::clicked, this, &Group::getIventsDatePressed);
    connect(day3Button, &QPushButton::clicked, this, &Group::getIventsDatePressed);
    connect(day4Button, &QPushButton::clicked, this, &Group::getIventsDatePressed);
    connect(day5Button, &QPushButton::clicked, this, &Group::getIventsDatePressed);
    connect(day6Button, &QPushButton::clicked, this, &Group::getIventsDatePressed);
    connect(day7Button, &QPushButton::clicked, this, &Group::getIventsDatePressed);






    //QFrame *loadingContaiter = new QFrame;
    // loading = new WaitingSpinnerWidget(loadingContaiter, true, false);
    //loading->setColor(QT_COLOR_PRIMARY);
    //loadingContaiter->setMinimumWidth(100);


    GrouptitleLabel->setStyleSheet(TITLE_LABLE);
    connect(backButton, &QSvgButton::clicked, this, &Group::onBackPressed);

    titleContainer->addWidget(group_id_label);
    titleContainer->addWidget(backButton);
    titleContainer->addWidget(GrouptitleLabel);
    titleContainer->setContentsMargins(0,24,0,16);

    titleContainer->setAlignment(Qt::AlignCenter);

    GrouptitleLabel->setContentsMargins(16,0,0,0);



    inputContainer->setAlignment(Qt::AlignTop);
    inputContainer->addLayout(titleContainer);

    stackMeets = new QVBoxLayout;

    stackMeets->addLayout(daysButtonsContainer);
    stackMeets->addLayout(GroupContainerMain);

    stackMeets->setAlignment(Qt::AlignCenter);


    QWidget *loadWidget = new QWidget;


    loading = new WaitingSpinnerWidget(loadWidget, true, false);

    loading->setColor(QT_COLOR_PRIMARY);

    loading->start();

    stackMeets->addWidget(loadWidget);







    stackList = new QVBoxLayout;

    stack = new QStackedWidget;

    QFrame *stackMeetsWidget = new QFrame;

    stackMeetsWidget->setLayout(stackMeets);


    stackListWidget = new QFrame;
    stackListWidget->setLayout(stackList);

    stackList->setAlignment(Qt::AlignCenter);


    stack->addWidget(stackMeetsWidget);
    stack->addWidget(stackListWidget);
    stack->setCurrentIndex(0);


    mainVLayout->setAlignment(Qt::AlignCenter);
    inputContainer->setAlignment(Qt::AlignTop);
    groupButtonsContainer->setAlignment(Qt::AlignTop);
    daysButtonsContainer->setAlignment(Qt::AlignTop);
    stackList->setAlignment(Qt::AlignTop);

    stackMeets->setAlignment(Qt::AlignTop);


    mainVLayout->addLayout(inputContainer);

    mainVLayout->addLayout(groupButtonsContainer);



    mainVLayout->addWidget(stack);








    mainVLayout->setAlignment(Qt::AlignTop);
    mainVLayout->addStretch();

    this->setLayout(mainVLayout);
    this->setStyleSheet(BACK_WHITE);
    this->setObjectName("fragment");


    networkManagerloadFriends = new QNetworkAccessManager();
    connect(networkManagerloadFriends, &QNetworkAccessManager::finished, this, &Group::onHttpResultnetworkManagerGetList);

    networkManagerGetMeets = new QNetworkAccessManager();
    connect(networkManagerGetMeets, &QNetworkAccessManager::finished, this, &Group::onHttpResultnetworkManagerGetMeets);

    networkManagerDeleteFriendFromGroup = new QNetworkAccessManager();
    connect(networkManagerDeleteFriendFromGroup, &QNetworkAccessManager::finished, this, &Group::onHttpResultnetworkManagerDeleteFriendFromGroup);

    networkManagerDeleteGroup = new QNetworkAccessManager();
    connect(networkManagerDeleteGroup, &QNetworkAccessManager::finished, this, &Group::onHttpResultDeleteGroup);



    getMeets();

}

Group::~Group() {


}

void Group::getMeets() {

    QDate curDate = QDate::currentDate();

    QJsonObject getMeetsJson;
    QJsonObject bodyJson;
    bodyJson.insert("date", (curDate.toString("yyyy-MM-dd")));
    bodyJson.insert("group_id", (GROUP_ID));

    getMeetsJson.insert("get_meetup", bodyJson);

    qDebug() << "create request" << endl;



    QNetworkRequest request(QUrl(SERVER_URL + ""));
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      QStringLiteral("application/json"));
    qDebug() << "request data"<< QJsonDocument(getMeetsJson).toJson(QJsonDocument::Compact) << endl;

    request.setRawHeader("JSON_DATA", QJsonDocument(getMeetsJson).toJson(QJsonDocument::Compact));
    networkManagerGetMeets->post(
                request,
                QJsonDocument(getMeetsJson).toJson(QJsonDocument::Compact)
                );
    qDebug() << "request send" << endl;


}

void Group::onBackPressed() {
    back();
}


void Group::groupMeetsPressed() {

   // getMeets();


    groupMeets->setStyleSheet(BUTTON_SOLID);

    groupList->setStyleSheet(BUTTON_DISABLED);

    stack->setCurrentIndex(0);

}


void Group::groupListPressed() {


    groupMeets->setStyleSheet(BUTTON_DISABLED);

    groupList->setStyleSheet(BUTTON_SOLID);

    stack->setCurrentIndex(1);






}


void Group::loadFriends() {

    //TEST get_group_data: {"get_data_group":{"title":"Texnosrac"}}



    QJsonObject loadFriendsGroupJson;
    QJsonObject usernameGroupJson;

    // nlohmann::json aaa = nlohmann::json::parse(loadFriendsJson);

    usernameGroupJson.insert("group_id", GROUP_ID);
    loadFriendsGroupJson.insert("get_group_members", usernameGroupJson);

    qDebug() << "create request" << endl;



    QNetworkRequest request(QUrl(SERVER_URL + ""));

    request.setRawHeader("JSON_DATA", QJsonDocument(loadFriendsGroupJson).toJson(QJsonDocument::Compact));

    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      QStringLiteral("application/json;charset=utf-8"));
    qDebug() << "request data"<< QJsonDocument(loadFriendsGroupJson).toJson(QJsonDocument::Compact) << endl;
    networkManagerloadFriends->post(
                request,
                QJsonDocument(loadFriendsGroupJson).toJson(QJsonDocument::Compact)
                );
    qDebug() << "request send" << endl;
}


void Group::onHttpResultnetworkManagerGetList(QNetworkReply *reply) {

    //str = "{\"userID\":\"213564544\",\"Friends\":[\"66666\", \"Igor\",  \"Alex\",  \"qwe\", \"piotr\"]}";



    qDebug() << "http finished" << endl;

    if(!reply->error()) {
        QByteArray resp = reply->readAll();
        qDebug() <<"ETO OTVET SERVERA get_data_group :  " + resp  << endl;
        QJsonDocument doc = QJsonDocument::fromJson(resp);
        QJsonObject obj;

        std::string str = resp.toStdString();


        nlohmann::json j = nlohmann::json::parse(str);




        nlohmann::json::iterator it = j.begin();

        std::string key = it.key();

        nlohmann::json value = j[key];

        for (auto& element : value) {

            nlohmann::json members = element["members"];

            for (auto& member : members) {

                friendContainer2 = new QHBoxLayout;
                QLabel *friendImageLabel2 = new QLabel("");
                QPixmap friendImage2(":/resc/resc/user_circle.svg");
                friendImageLabel2->setPixmap(friendImage2);
                friendImageLabel2->setStyleSheet(FRIEND_IMAGE);

                friendName2 = new QLabel(QString::fromStdString(member.dump()).remove('"'));

                qDebug() << friendName2 << endl;

                friendName2->setStyleSheet(FRIEND_NAME_SURNAME);
                friendName2->setContentsMargins(0,15,0,0);


                QLabel *friendOnlineStatusLabel2 = new QLabel("");
                QPixmap friendOnlineStatusImage2(":/resc/resc/online_status_off.svg");
                friendOnlineStatusLabel2->setPixmap(friendOnlineStatusImage2.scaled(15,15, Qt::KeepAspectRatio));

                //friendOnlineStatusLabel2->setStyleSheet(ONLINE_STATUS);



                QPushButton *inviteGroupButton2 = new QPushButton(tr("Invite to Group"));

                QPushButton *deleteFriendButton2 = new QPushButton(tr("      Delete from group     "));

                QPixmap pixmapdeleteFriend(":/resc/resc/bin_white.svg");
                QIcon ButtonIcondeleteFriend(pixmapdeleteFriend);

                deleteFriendButton2->setIcon(ButtonIcondeleteFriend);
                deleteFriendButton2 -> setLayoutDirection ( Qt :: RightToLeft );
                deleteFriendButton2 -> setStyleSheet("text-align: right");
                deleteFriendButton2->setIconSize(QSize(20,20));

                deleteFriendButton2->setMaximumWidth(250);
                deleteFriendButton2->setMinimumWidth(250);


                inviteGroupButton2->setStyleSheet(BUTTON_SOLID);


                deleteFriendButton2->setStyleSheet(BUTTON_SOLID);

                QHBoxLayout *friendButtonContainer2 = new QHBoxLayout;


                //friendButtonContainer2->addWidget(inviteGroupButton2);
                friendButtonContainer2->addWidget(deleteFriendButton2);



                friendImageLabel2->setStyleSheet("QFrame {""background: transparent""}");
                friendImageLabel2->setContentsMargins(0,15,0,0);
                friendOnlineStatusLabel2->setStyleSheet("QFrame {""background: transparent""}");
                friendImageLabel2->setContentsMargins(0,15,0,0);


                friendContainer2->addWidget(friendImageLabel2);
                friendContainer2->addWidget(friendName2);

                friendContainer2->addWidget(friendOnlineStatusLabel2);
                friendContainer2->addLayout(friendButtonContainer2);

                connect(deleteFriendButton2, &QPushButton::clicked, this, &Group::deleteFriendPressed);

                // friendContainer2->setAlignment(Qt::AlignCenter);


                QFrame  *FriendFrame = new QFrame;

                FriendFrame->setStyleSheet(GROUPS_FRAME);

                FriendFrame->setLayout(friendContainer2);

                stackList->addWidget(FriendFrame);


                mButtonToLayoutMap.insert(deleteFriendButton2,friendContainer2);
                mButtonToFrameMap.insert(deleteFriendButton2,FriendFrame);





                std::cout << member.get<std::string>() << std::endl;  // выводит в cout участников всех групп. Если подается одна группа, то в рамках одной группы
            }
        }
    }

    else {

        qDebug() << reply->errorString();

        qDebug() << "Server answer: " +  reply->readAll() << endl;

        qDebug () << reply -> error ();

        QMessageBox::warning(this, tr("Error"),
                             "Connection ERROR!\n");

    }

    reply->deleteLater();
    networkManagerloadFriends->clearAccessCache();

}

void Group::onHttpResultnetworkManagerGetMeets(QNetworkReply *reply) {


    qDebug() << "http finished meeeets" << endl;

    if(!reply->error()) {
        QByteArray resp = reply->readAll();
        qDebug() <<"ETO OTVET SERVERA GET MEETS :  " + resp  << endl;
        QJsonDocument doc = QJsonDocument::fromJson(resp);
        QJsonObject obj;

        std::string str = resp.toStdString();

        std::cout << "str  " + str << std::endl;

        nlohmann::json j = nlohmann::json::parse(str);



        if(j["get_meetup"] != "Not found events"){

            nlohmann::json::iterator it = j.begin();

            nlohmann::json value = j[it.key()];

            for (auto& element : value)
            {

                std::string time_end_str;
                std::string time_begin_str;


                if(element.contains("time_begin"))
                {
                    time_begin_str = element["time_begin"].get<std::string>();


                }

                if(element.contains("time_end"))
                {
                    time_end_str = element["time_end"].get<std::string>();


                }



        groupEventstart = new QLabel(time_begin_str.c_str());
        groupEventstart->setAlignment(Qt::AlignCenter);
        groupEventstart->setStyleSheet(MEET_TIME);

        groupEventend = new QLabel(time_end_str.c_str());
        groupEventend->setAlignment(Qt::AlignCenter);
        groupEventend->setStyleSheet(MEET_TIME);


        GroupContainer = new QHBoxLayout;

        GroupContainer->setAlignment(Qt::AlignCenter);

        QFrame *GroupContainerFrame = new QFrame;

        GroupContainer->setContentsMargins(0,0,0,20);

        GroupContainerFrame->setStyleSheet(MEETS_FRAME_STYLE);

        GroupContainer->addWidget(groupEventstart);

        GroupContainer->addWidget(groupEventend);

        GroupContainerFrame->setLayout(GroupContainer);




        stackMeets->addWidget(GroupContainerFrame);





}





    } else {

        qDebug() << reply->errorString();

        qDebug() <<  reply->readAll() << endl;

        qDebug () << reply -> error ();

        QMessageBox::warning(this, tr("Error"),
                             "Connection ERROR!\n");


    }
    reply->deleteLater();


    networkManagerGetMeets->clearAccessCache();

        loadFriends();



}

}

void Group::onHttpResultnetworkManagerDeleteFriendFromGroup(QNetworkReply *reply) {


    qDebug() << "http finished" << endl;
    if(!reply->error()) {
        QByteArray resp = reply->readAll();
        qDebug() <<"ETO OTVET SERVERA DELETE FRIEND FROM GROUP :  " + resp  << endl;
        QJsonDocument doc = QJsonDocument::fromJson(resp);
        QJsonObject obj;

        std::string str = resp.toStdString();

        std::cout << "str  " + str << std::endl;

        nlohmann::json j = nlohmann::json::parse(str);

        std::string delete_group_result = j["kick"].get<std::string>();

        if(delete_group_result == "OK") {



            std::cout << "delete friebd from group: " << delete_group_result << std::endl;

        }

    } else {

        qDebug() << reply->errorString();

        qDebug() <<  reply->readAll() << endl;

        qDebug () << reply -> error ();

        QMessageBox::warning(this, tr("Error"),
                             "Connection ERROR!\n");


    }
    reply->deleteLater();


    networkManagerDeleteFriendFromGroup->clearAccessCache();




}

void Group::deleteFriendPressed() {


    QPushButton *button = qobject_cast<QPushButton*>(sender());

    QHBoxLayout *layout = mButtonToLayoutMap.take(button);


    QFrame *frame = mButtonToFrameMap.take(button);

    frame->hide();


    QWidget * widget =  layout->itemAt(1)->widget();



    QLabel* xxx = dynamic_cast<QLabel*>(widget);


    QString nameGroup = xxx->text();



    //QString friendq = button->text();



    //emit sendGroupNameSignal(friendq); //вызывая сигнал нужно в скобочках указать текст, который мы передаем другому классу,


    QJsonObject deleFromGroupJson;
    QJsonObject bodyJson;

    QJsonArray arrayUsers;
    arrayUsers.push_back(nameGroup);

    bodyJson.insert("group_id", GROUP_ID);
    bodyJson.insert("members", arrayUsers);

    deleFromGroupJson.insert("kick", bodyJson);

    qDebug() << "create request" << endl;


    QNetworkRequest request(QUrl(SERVER_URL + ""));
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      QStringLiteral("application/json;charset=utf-8"));
    qDebug() << "request data"<< QJsonDocument(deleFromGroupJson).toJson(QJsonDocument::Compact) << endl;

    request.setRawHeader("JSON_DATA", QJsonDocument(deleFromGroupJson).toJson(QJsonDocument::Compact));

    qDebug() << "JSON_DATA send" << endl;

    networkManagerDeleteFriendFromGroup->post(
                request,
                QJsonDocument(deleFromGroupJson).toJson(QJsonDocument::Compact)
                );
    qDebug() << "request send" << endl;



    while (layout->count() != 0) {
        QLayoutItem *item = layout->takeAt(0);
        delete item->widget();
        delete item;
    }

    delete button;
    delete layout;

}

void Group::loadGroup() {

}

void Group::getIventsDatePressed() {
    day1Button->setStyleSheet(BUTTON_DISABLED);
    day2Button->setStyleSheet(BUTTON_DISABLED);
    day3Button->setStyleSheet(BUTTON_DISABLED);
    day4Button->setStyleSheet(BUTTON_DISABLED);
    day5Button->setStyleSheet(BUTTON_DISABLED);
    day6Button->setStyleSheet(BUTTON_DISABLED);
    day7Button->setStyleSheet(BUTTON_DISABLED);

    QPushButton *button = qobject_cast<QPushButton*>(sender());

    QString Date = button->text();

    button->setStyleSheet(BUTTON_SOLID);

    qDebug() << Date << endl;


}


void Group::sendGroupNameSlot(const QString &text)
{

    QString abc = text;

    GrouptitleLabel->setText(text);
}


void Group::groupDeleteYesPressed(){

    QJsonObject deleteGroupJson;
    QJsonObject bodyJson;
    bodyJson.insert("group_id", GROUP_ID);


    deleteGroupJson.insert("delete_group", bodyJson);

    qDebug() << "create request" << endl;


    QNetworkRequest request(QUrl(SERVER_URL + ""));
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      QStringLiteral("application/json;charset=utf-8"));

    request.setRawHeader("JSON_DATA", QJsonDocument(deleteGroupJson).toJson(QJsonDocument::Compact));
    qDebug() << "request data"<< QJsonDocument(deleteGroupJson).toJson(QJsonDocument::Compact) << endl;
    networkManagerDeleteGroup->post(
                request,
                QJsonDocument(deleteGroupJson).toJson(QJsonDocument::Compact)
                );
    qDebug() << "request send" << endl;


}
void Group::groupDeletePressed(){

    groupDelete->hide();
    deleteLabel->show();
    groupDeleteYes->show();
    groupDeleteNo->show();



}

void Group::groupDeleteNoPressed(){


    groupDelete->show();
    deleteLabel->hide();
    groupDeleteYes->hide();
    groupDeleteNo->hide();



}


void Group::onHttpResultDeleteGroup(QNetworkReply *reply){


    qDebug() << "http finished" << endl;
    if(!reply->error()) {
        QByteArray resp = reply->readAll();
        qDebug() <<"ETO OTVET SERVERA DELETE GRROUP :  " + resp  << endl;
        QJsonDocument doc = QJsonDocument::fromJson(resp);
        QJsonObject obj;

        std::string str = resp.toStdString();

        std::cout << "str  " + str << std::endl;

        nlohmann::json j = nlohmann::json::parse(str);

        std::string delete_group_result = j["delete_group"].get<std::string>();

        if(delete_group_result == "OK") {

            QMessageBox::information(this, tr("Group deleting"),
                                     tr("Group is delete!\n"));

            newRootScreen(MAIN_TAG);

            std::cout << "delete group: " << delete_group_result << std::endl;

        }

    } else {

        qDebug() << reply->errorString();

        qDebug() <<  reply->readAll() << endl;

        qDebug () << reply -> error ();

        QMessageBox::warning(this, tr("Error"),
                             "Connection ERROR!\n");
        // newRootScreen(MAIN_TAG);

    }
    reply->deleteLater();


    networkManagerDeleteGroup->clearAccessCache();


}








