#include "Friends.h"
#include "Layouts/friendlayout.h"

#include "nlohmann/json.hpp"
#include <iostream>
#include <set>

#include "style/stylecontainer.h"
using namespace styles;
#include "screensfactory.h"

#include <QLabel>
#include <QNetworkAccessManager>
#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QJsonObject>
#include <QJsonDocument>
#include <QSettings>
#include <QMessageBox>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QScrollBar>

#include <QRegularExpression>
#include <ui/view/qsvgbutton.h>
#include <ui/view/waitingspinnerwidget.h>
using namespace screens;

Friends::Friends() {

    mainVLayout = new QVBoxLayout;
    QVBoxLayout *inputContainer = new QVBoxLayout;

    QHBoxLayout *titleContainer = new QHBoxLayout;
    QSvgButton *backButton = new QSvgButton(":/resc/resc/arrow_back.svg", QSize(24,24));
    titleLabel = new QLabel("Мои друзья");

    createButton = new QPushButton("Добавить друзей");


    QFrame *friendFrame = new QFrame;





    //QFrame *loadingContaiter = new QFrame;
   // loading = new WaitingSpinnerWidget(loadingContaiter, true, false);
    //loading->setColor(QT_COLOR_PRIMARY);
    //loadingContaiter->setMinimumWidth(100);


    titleLabel->setStyleSheet(TITLE_LABLE);
    connect(backButton, &QSvgButton::clicked, this, &Friends::onBackPressed);

    titleContainer->addWidget(backButton);
    titleContainer->addWidget(titleLabel);
    titleContainer->setContentsMargins(0,24,0,16);

    titleLabel->setContentsMargins(16,0,0,0);


    QHBoxLayout *addFriendContainer = new QHBoxLayout;


    addFriendEdit = new QLineEdit;


    connect(addFriendEdit, &QLineEdit::textChanged, this, &Friends::checkNameFriend);

    addFriendEdit->setMaximumWidth(355);                                          // поле ввода логина длна 355
    addFriendEdit->setStyleSheet(EDIT_TEXT);
    addFriendEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    addFriendEdit->setPlaceholderText("Никнейм");

    addFriendEdit->setMaximumWidth(400);
    addFriendEdit->setMinimumWidth(400);



    addFriendButton = new QPushButton("Добавить друга");

    addFriendButton->setMaximumWidth(300);
    addFriendButton->setMinimumWidth(300);


    connect(addFriendButton, &QPushButton::clicked, this, &Friends::addFriendButtonPressed);

    addFriendButton->setStyleSheet(BUTTON_DISABLED);
    addFriendButton->setDisabled(true);


    addFriendContainer->addWidget(addFriendEdit);

    addFriendContainer->addWidget(addFriendButton);

    addFriendButton->setStyleSheet(BUTTON_DISABLED);
    addFriendButton->setDisabled(true);








    inputContainer->setAlignment(Qt::AlignTop);
    inputContainer->addLayout(titleContainer);
   // mainVLayout->setAlignment(Qt::AlignLeft);
    //mainVLayout->addLayout(inputContainer);
    //mainVLayout->addLayout(friendContainer);
    //mainVLayout->addLayout(friendContainer2);





    //mainVLayout->addStretch();

    //this->setLayout(mainVLayout);





    QScrollArea *deskScrollArea = new QScrollArea;
    deskScrollArea->setFrameShape(QFrame::NoFrame);
    QWidget *scrolContainer = new QWidget;
    scrolContainer->setObjectName("container");
    scrolContainer->setStyleSheet(GLOBAL_BACK_WHITE);
    deskScrollArea->setStyleSheet(SCROL_BAR);
    QHBoxLayout *content = new QHBoxLayout;
    content->setAlignment(Qt::AlignHCenter);
    scrolContainer->setLayout(content);
    deskScrollArea->setWidget(scrolContainer);
    deskScrollArea->setWidgetResizable(true);
    deskScrollArea->horizontalScrollBar()->setEnabled(false);





    inputContainerFriends = new QVBoxLayout;

    inputContainerFriends->setAlignment(Qt::AlignTop);
    inputContainer->setAlignment(Qt::AlignTop);
    addFriendContainer->setAlignment(Qt::AlignTop);

    inputContainerFriends->addLayout(inputContainer);

     inputContainerFriends->addLayout(addFriendContainer);


    //mainHLayout->addWidget(deskScrollArea);
    //mainHLayout->addStretch();

   mainVLayout->setAlignment(Qt::AlignLeft);

    content->addLayout(inputContainerFriends);



    mainVLayout->addWidget(deskScrollArea);


    this->setLayout(mainVLayout);
    this->setStyleSheet(BACK_WHITE);
    this->setObjectName("fragment");

    checkData();

    networkManager = new QNetworkAccessManager();
    connect(networkManager, &QNetworkAccessManager::finished, this, &Friends::onHttpResult);

    addManagerFriend = new QNetworkAccessManager();
    connect(addManagerFriend, &QNetworkAccessManager::finished, this, &Friends::onHttpResultFriend);

    loadFriends();
}

Friends::~Friends() {


    //delete loading;
    delete titleLabel;
    networkManager->clearAccessCache();
}

void Friends::checkData() {

}

void Friends::onBackPressed() {
    back();
}



void Friends::onHttpResult(QNetworkReply *reply) {




    str = "{\"userID\":\"213564544\",\"Friends\":[\"Misha1991\", \"Igor\",  \"Alex\",  \"qwe\", \"piotr\"]}";

    nlohmann::json j = nlohmann::json::parse(str);


    std::cout << j.size() << std::endl;
    std::cout << j << std::endl;

    nlohmann::json::iterator it = j.begin();
    std::cout << it.key() << std::endl;

    std::string key = it.key();

    nlohmann::json value = j[key];

    std::cout << value << std::endl;


    std::set<std::string> s_friends;

    for (auto& element : j["Friends"]) {




        friendContainer2 = new QHBoxLayout;
        QLabel *friendImageLabel2 = new QLabel("");
        QPixmap friendImage2(":/resc/resc/user_circle.svg");
        friendImageLabel2->setPixmap(friendImage2);
        friendImageLabel2->setStyleSheet(FRIEND_IMAGE);





        friendName2 = new QLabel(QString::fromStdString(element.dump()).remove('"'));

        friendName2->setStyleSheet(FRIEND_NAME_SURNAME);


        QLabel *friendOnlineStatusLabel2 = new QLabel("");
        QPixmap friendOnlineStatusImage2(":/resc/resc/online_status_off.svg");
        friendOnlineStatusLabel2->setPixmap(friendOnlineStatusImage2.scaled(15,15, Qt::KeepAspectRatio));

        friendOnlineStatusLabel2->setStyleSheet(ONLINE_STATUS);



        QPushButton *inviteGroupButton2 = new QPushButton("Пригласить в группу");

        QPushButton *deleteFriendButton2 = new QPushButton("Удалить из друзей");


        inviteGroupButton2->setStyleSheet(BUTTON_SOLID);


        deleteFriendButton2->setStyleSheet(BUTTON_SOLID);

        QHBoxLayout *friendButtonContainer2 = new QHBoxLayout;


        //friendButtonContainer2->addWidget(inviteGroupButton2);
        friendButtonContainer2->addWidget(deleteFriendButton2);



        friendContainer2->addWidget(friendImageLabel2);
        friendContainer2->addWidget(friendName2);

        friendContainer2->addWidget(friendOnlineStatusLabel2);
        friendContainer2->addLayout(friendButtonContainer2);

        connect(deleteFriendButton2, &QPushButton::clicked, this, &Friends::deleteFriendPressed);






        inputContainerFriends->addLayout(friendContainer2);


        mButtonToLayoutMap.insert(deleteFriendButton2,friendContainer2);
    }

    for (auto& f: s_friends) {
        std::cout << "friend:" << f << std::endl;
    };

}

void Friends::onHttpResultFriend(QNetworkReply *reply) {



}

void Friends::loadFriends() {

    addFriendEdit->setText("");
    addFriendButton->setStyleSheet(BUTTON_DISABLED);
    addFriendButton->setDisabled(true);
    QJsonObject loadFriendsJson;
    QJsonObject userIDJson;

   // nlohmann::json aaa = nlohmann::json::parse(loadFriendsJson);

    userIDJson.insert("userID", "213564544");
    loadFriendsJson.insert("getFriend", userIDJson);

        qDebug() << "create request" << endl;



        QNetworkRequest request(QUrl(SERVER_URL + ""));
        request.setHeader(QNetworkRequest::ContentTypeHeader,
                          QStringLiteral("application/json;charset=utf-8"));
        qDebug() << "request data"<< QJsonDocument(loadFriendsJson).toJson(QJsonDocument::Compact) << endl;
        networkManager->post(
            request,
            QJsonDocument(loadFriendsJson).toJson(QJsonDocument::Compact)
        );
        qDebug() << "request send" << endl;
    }




void Friends::addFriendButtonPressed() {



    QJsonObject addFriendJson;
    QJsonObject bodyJson;
    bodyJson.insert("userID", "213564544");
    bodyJson.insert("friendName", addFriendEdit->text());
    addFriendJson.insert("setFriend", bodyJson);

        qDebug() << "create request" << endl;



        QNetworkRequest request(QUrl(SERVER_URL + ""));
        request.setHeader(QNetworkRequest::ContentTypeHeader,
                          QStringLiteral("application/json;charset=utf-8"));
        qDebug() << "request data"<< QJsonDocument(addFriendJson).toJson(QJsonDocument::Compact) << endl;
        addManagerFriend->post(
            request,
            QJsonDocument(addFriendJson).toJson(QJsonDocument::Compact)
        );
        qDebug() << "request send" << endl;




        friendContainer2 = new QHBoxLayout;
        friendImageLabel2 = new QLabel("");
        QPixmap friendImage2(":/resc/resc/user_circle.svg");
        friendImageLabel2->setPixmap(friendImage2);
        friendImageLabel2->setStyleSheet(FRIEND_IMAGE);


        friendName2 = new QLabel((addFriendEdit->text()));

        friendName2->setStyleSheet(FRIEND_NAME_SURNAME);


        QLabel *friendOnlineStatusLabel2 = new QLabel("");
        QPixmap friendOnlineStatusImage2(":/resc/resc/online_status_off.svg");
        friendOnlineStatusLabel2->setPixmap(friendOnlineStatusImage2.scaled(15,15, Qt::KeepAspectRatio));

        friendOnlineStatusLabel2->setStyleSheet(ONLINE_STATUS);



        inviteGroupButton2 = new QPushButton("Пригласить в группу");

        deleteFriendButton2 = new QPushButton("Удалить из друзей");



       connect(deleteFriendButton2, &QPushButton::clicked, this, &Friends::deleteFriendPressed);



        inviteGroupButton2->setStyleSheet(BUTTON_SOLID);


        deleteFriendButton2->setStyleSheet(BUTTON_SOLID);

             QHBoxLayout *friendButtonContainer2 = new QHBoxLayout;

        //friendButtonContainer2->addWidget(inviteGroupButton2);
        friendButtonContainer2->addWidget(deleteFriendButton2);



        friendContainer2->addWidget(friendImageLabel2);
        friendContainer2->addWidget(friendName2);

        friendContainer2->addWidget(friendOnlineStatusLabel2);
        friendContainer2->addLayout(friendButtonContainer2);

        connect(deleteFriendButton2, &QPushButton::clicked, this, &Friends::deleteFriendPressed);






        inputContainerFriends->addLayout(friendContainer2);


        mButtonToLayoutMap.insert(deleteFriendButton2,friendContainer2);

        addFriendEdit->setText("");
         addFriendButton->setStyleSheet(BUTTON_DISABLED);
         addFriendButton->setDisabled(true);



    }




void Friends::checkNameFriend() {
    if (addFriendEdit->text().length() >= 4) {
        addFriendButton->setStyleSheet(BUTTON_SOLID);
         addFriendButton->setDisabled(false);
    } else {
        addFriendButton->setStyleSheet(BUTTON_DISABLED);
         addFriendButton->setDisabled(true);
    }
}


void Friends::deleteFriendPressed(){


    QPushButton *button = qobject_cast<QPushButton*>(sender());

    QHBoxLayout *layout = mButtonToLayoutMap.take(button);


    QWidget * widget =  layout->itemAt(1)->widget();



    QLabel* xxx = dynamic_cast<QLabel*>(widget);


    QString aaa = xxx->text();

    QJsonObject deleteFriendJson;
        QJsonObject bodyJson;
        bodyJson.insert("userID", "213564544");
        bodyJson.insert("friendName", (aaa));
        deleteFriendJson.insert("deleteFriend", bodyJson);

            qDebug() << "create request" << endl;



            QNetworkRequest request(QUrl(SERVER_URL + ""));
            request.setHeader(QNetworkRequest::ContentTypeHeader,
                              QStringLiteral("application/json;charset=utf-8"));
            qDebug() << "request data"<< QJsonDocument(deleteFriendJson).toJson(QJsonDocument::Compact) << endl;
            addManagerFriend->post(
                request,
                QJsonDocument(deleteFriendJson).toJson(QJsonDocument::Compact)
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


void Friends::onHttpResultDeleteFriend(QNetworkReply *reply) {



}
