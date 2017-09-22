#include "dict_page.h"

DictPage::DictPage(QWidget *parent)
    : QWidget(parent),
      api(new YoudaoAPI(this))
{
    audio = new QMediaPlayer;
    mainLayout = new QVBoxLayout(this);
    layout = new QVBoxLayout();
    wordLayout = new QHBoxLayout();
    pronLayout = new QHBoxLayout();
    infoLayout = new QHBoxLayout();
    youdaoLayout = new QHBoxLayout();
    mainArea = new QScrollArea();
    nameLabel = new QLabel("");
    pronLabel1 = new QLabel("");
    pronLabel2 = new QLabel("");
    infoLabel = new QLabel();    

    pronButton1 = new DImageButton(NULL, NULL, NULL);
    pronButton2 = new DImageButton(NULL, NULL, NULL);

    mainArea->setLayout(layout);
    mainArea->setAlignment(Qt::AlignCenter);
    mainArea->setWidgetResizable(false);

    pronButton1->setFixedSize(24, 24);
    pronButton2->setFixedSize(24, 24);

    infoLabel->setWordWrap(true);
    nameLabel->setWordWrap(true);

    nameLabel->setStyleSheet("font-size: 22px; color:#2CA7F8;");
    pronLabel1->setStyleSheet("font-size: 13px");
    pronLabel2->setStyleSheet("font-size: 13px");
    infoLabel->setStyleSheet("font-size: 17px");

    wordLayout->addSpacing(25);
    wordLayout->addWidget(nameLabel);
    wordLayout->addSpacing(25);

    infoLayout->addSpacing(25);
    infoLayout->addWidget(infoLabel);
    infoLayout->addSpacing(25);

    pronLayout->addSpacing(24);
    pronLayout->addWidget(pronButton1);
    pronLayout->addWidget(pronLabel1);
    pronLayout->addSpacing(5);
    pronLayout->addWidget(pronButton2);
    pronLayout->addWidget(pronLabel2);

    layout->addSpacing(5);
    layout->addLayout(wordLayout);
    layout->addLayout(pronLayout);
    layout->addSpacing(20);
    layout->addLayout(infoLayout);
    layout->addStretch();

    mainLayout->addWidget(mainArea);
    mainLayout->addLayout(youdaoLayout);
    mainLayout->addSpacing(10);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    connect(pronButton1, &DImageButton::clicked, this, [=]{
        audio->setMedia(QUrl("http://dict.youdao.com/dictvoice?type=1&audio=" + nameLabel->text()));
        audio->play();
    });

    connect(pronButton2, &DImageButton::clicked, this, [=]{
        audio->setMedia(QUrl("http://dict.youdao.com/dictvoice?type=2&audio=" + nameLabel->text()));
        audio->play();
    });

    /*
    connect(searchEdit, SIGNAL(returnPressed()), this, SLOT(start()));
    connect(searchButton, SIGNAL(clicked()), this, SLOT(start()));
    */

    connect(api, SIGNAL(searchWordFinished(QString, QString, QString, QString)), this, SLOT(processingData(QString, QString, QString, QString)));

    init();
}

void DictPage::changeTheme(const QString &theme)
{
    if (theme == "light") {
        pronButton1->setNormalPic(":/resources/light/audio-volume-high-normal.png");
        pronButton1->setHoverPic(":/resources/light/audio-volume-high-hover.png");
        pronButton1->setPressPic(":/resources/light/audio-volume-high-press.png");
        pronButton2->setNormalPic(":/resources/light/audio-volume-high-normal.png");
        pronButton2->setHoverPic(":/resources/light/audio-volume-high-hover.png");
        pronButton2->setPressPic(":/resources/light/audio-volume-high-press.png");
    }else {
        pronButton1->setNormalPic(":/resources/dark/audio-volume-high-normal.png");
        pronButton1->setHoverPic(":/resources/dark/audio-volume-high-hover.png");
        pronButton1->setPressPic(":/resources/dark/audio-volume-high-press.png");
        pronButton2->setNormalPic(":/resources/dark/audio-volume-high-normal.png");
        pronButton2->setHoverPic(":/resources/dark/audio-volume-high-hover.png");
        pronButton2->setPressPic(":/resources/dark/audio-volume-high-press.png");
    }
}

void DictPage::start()
{

}

void DictPage::processingData(QString name, QString uk_phonetic, QString us_phonetic, QString text)
{
    if (uk_phonetic.isEmpty() && us_phonetic.isEmpty()) {
        pronLabel1->setVisible(false);
        pronLabel2->setVisible(false);
        pronButton1->setVisible(false);
        pronButton2->setVisible(false);
    }else {
        pronLabel1->setVisible(true);
        pronLabel2->setVisible(true);
        pronButton1->setVisible(true);
        pronButton2->setVisible(true);

        pronLabel1->setText(QString("英[%1]").arg(uk_phonetic));
        pronLabel2->setText(QString("美[%1]").arg(us_phonetic));
    }

    nameLabel->setText(name);
    infoLabel->setText(text);
}

void DictPage::init()
{
    QPixmap iconPixmap = QPixmap(":/resources/youdao-dict.svg");
    QLabel *iconLabel = new QLabel;
    iconLabel->setFixedSize(20, 20);
    iconLabel->setScaledContents(true);
    iconLabel->setPixmap(iconPixmap);

    QLabel *tips = new QLabel("数据来自有道词典");
    tips->setStyleSheet("QLabel {font-size: 12px; }");

    youdaoLayout->addSpacing(15);
    youdaoLayout->addWidget(iconLabel);
    youdaoLayout->addWidget(tips);

    pronLabel1->setVisible(false);
    pronLabel2->setVisible(false);
    pronButton1->setVisible(false);
    pronButton2->setVisible(false);
}
