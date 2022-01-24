#pragma once

#include <QLineEdit>
#include <QNetworkAccessManager>
#include <QPushButton>
#include <QWidget>
#include <QNetworkReply>
#include <QPlainTextEdit>
#include <QLabel>
#include <QStackedWidget>

#include <common/base/basefragment.h>

#include <ui/view/waitingspinnerwidget.h>

#include <models/deskmodel.h>

class profile : public BaseFragment{
    Q_OBJECT

private:

    QLineEdit *userNameEdit;
    QLabel *userNameLabel;

    std::string str;
    QLineEdit *userSurnameEdit;
    QLabel *userSurnameLabel;

    QLineEdit *userAgeEdit;
    QLabel *userAgeLabel;
    QString ID_QSTRING;


    QStackedWidget stackprofile;

    QLineEdit *userPhoneNumberEdit;
    QLabel *userPhoneNumberLabel;

    QLineEdit *userMailEdit;
    QLabel *userMailLabel;


    QLineEdit *usercountryEdit;
    QLabel *usercountryLabel;

    QLineEdit *userindexEdit;
    QLabel *userindexLabel;

    QLineEdit *usercityEdit;
    QLabel *usercityLabel;

    QLineEdit *userdistrictEdit;
    QLabel *userdistrictLabel;

    QLineEdit *userstreetEdit;
    QLabel *userstreetLabel;

    QLineEdit *userhousingEdit;
    QLabel *userhousingLabel;

    QLineEdit *userbuildingEdit;
    QLabel *userbuildingLabel;

    QLineEdit *userStatusEdit;
    QLabel *userStatusLabel;

    QLineEdit *userLabelEdit;
    QLabel *userLabelLabel;

    QLineEdit *userDescriptionEdit;
    QLabel *userDescriptionLabel;


    QPushButton *setprofileButton;
    QPushButton *setprofileRightButton;






    //    QPushButton *setprofileButton;
    //    QPushButton *setprofileRightButton;



    QLabel *titleLabel;
    QLineEdit *titleEdit;
    QPlainTextEdit *descriptionEdit;

    QNetworkAccessManager *networkManager;
    QNetworkAccessManager *networkManagerRight;

    QNetworkAccessManager *networkManagerSetprofile;
    QNetworkAccessManager *networkManagerSetprofileRight;

    void setData(BaseModel* model) override;
public:
    profile();
    ~profile();


public slots:
    void onBackPressed();
    void onCreatePressed();
    void checkprofile();

    void checkprofileRight();


    void setprofile();

    void setprofileRightPressed();
    void getprofile();
    void getprofileRight();
    void onHttpResult(QNetworkReply *reply);
    void onHttpResultRight(QNetworkReply *reply);
    void onHttpResultSetprofile(QNetworkReply *reply);
    void onHttpResultSetprofileRight(QNetworkReply *reply);

    /**
     * @brief checkData
     *
     * проверка введенных данных
     * на корректность.
     */
    void checkData();
};
