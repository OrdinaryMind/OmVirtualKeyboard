#include "keyboardwidget.h"
#include "ui_keyboardwidget.h"

#include <QFrame>
#include <QVBoxLayout>

#include "engkeyboard.h"
#include "ruskeyboard.h"

static constexpr short keyboard_width = 500;
static constexpr short keyboard_height = 180;

KeyboardWidget::KeyboardWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::KeyboardWidget)
{
    setInitialSettings();
    setDefaultKeyboard();
    setConnections();
}

KeyboardWidget::~KeyboardWidget()
{
    delete ui;
}

void KeyboardWidget::switchKeyboard()
{
    if (m_pEngKeyboard->isHidden()){
        m_pRusKeyboard->hide();
        m_pEngKeyboard->show();
    } else {
        m_pEngKeyboard->hide();
        m_pRusKeyboard->show();
    }
}

void KeyboardWidget::setInitialSettings()
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowDoesNotAcceptFocus |
                   Qt::Tool |
                   Qt::FramelessWindowHint |
                   Qt::WindowStaysOnTopHint);
    setFixedSize(keyboard_width, keyboard_height);
}

void KeyboardWidget::setDefaultKeyboard()
{
    m_pVLayout = new QVBoxLayout;
    m_pDigitsFrame = new DigitsFrame;
    m_pEngKeyboard = new EngKeyboard;
    m_pRusKeyboard = new RusKeyboard;
    m_pRusKeyboard->hide();

    m_pVLayout->addWidget(m_pDigitsFrame);
    m_pVLayout->addWidget(m_pEngKeyboard);
    m_pVLayout->addWidget(m_pRusKeyboard);
    m_pVLayout->setContentsMargins(2,2,2,2);

    setLayout(m_pVLayout);
}

void KeyboardWidget::setConnections()
{
    connect(m_pEngKeyboard, &EngKeyboard::capsKeyPressed,this,
            [&](){
        switchDigitsFrame(EngSpecialSymbols);
    });
    connect(m_pRusKeyboard, &EngKeyboard::capsKeyPressed,this,
            [&](){
        switchDigitsFrame(RusSpecialSymbols);
    });

    connect(m_pEngKeyboard,SIGNAL(switchLangPressed()),SLOT(switchKeyboard()));
    connect(m_pRusKeyboard,SIGNAL(switchLangPressed()),SLOT(switchKeyboard()));
}

void KeyboardWidget::switchDigitsFrame(DigitsFrameType digitsFrameType)
{
    DigitsFrameType frameType = m_pDigitsFrame->getFrameType();
    if (frameType != Digits){
        m_pDigitsFrame->setFrameType(Digits);
    } else {
        m_pDigitsFrame->setFrameType(digitsFrameType);
    }

    m_pDigitsFrame->switchFrame();
}
