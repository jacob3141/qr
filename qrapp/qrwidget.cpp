#include "qrwidget.h"

#include <QVBoxLayout>
#include <QGuiApplication>
#include <QClipboard>

#include "qtqrencode.h"

QRWidget::QRWidget(QWidget *parent)
    : QWidget(parent, Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint) {

    _systemTrayIcon.setIcon(QIcon(":/icons/qr.png"));
#ifndef Q_OS_MAC
    _systemTrayIcon.show();
#endif
    QVBoxLayout *vBoxLayout = new QVBoxLayout();
    _label = new QLabel(this);
    _label->setScaledContents(true);
    _lineEdit = new QLineEdit(this);
    _lineEdit->setPlaceholderText("Enter data to be encoded here");
    vBoxLayout->addWidget(_label);
    vBoxLayout->addWidget(_lineEdit);
    vBoxLayout->setSpacing(1);
    vBoxLayout->setContentsMargins(1, 1, 1, 1);
    setLayout(vBoxLayout);

    setFixedSize(480, 512);

    connect(_lineEdit, SIGNAL(textChanged(QString)), this, SLOT(generateQRCode(QString)));

    connect(&_systemTrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this,
            SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));

    connect(qGuiApp, SIGNAL(applicationStateChanged(Qt::ApplicationState)), this, SLOT(applicationStateChanged(Qt::ApplicationState)));

    setFocusProxy(_lineEdit);
}

QRWidget::~QRWidget() {

}

void QRWidget::generateQRCode(QString text) {
    if(!text.isEmpty()) {
        QREncode qrEncode;
        qrEncode.encode(text);
        QImage image = qrEncode.toQImage(_label->height());
        _label->setPixmap(QPixmap::fromImage(image));
    }
}

void QRWidget::trayIconActivated(QSystemTrayIcon::ActivationReason activationReason) {
    QRect geometry = _systemTrayIcon.geometry();
    if(isVisible()) {
        hide();
    } else {
        show();
        move(geometry.x() + geometry.width() / 2 - width() / 2, geometry.y());
        raise();
        _lineEdit->setText(qGuiApp->clipboard()->text());
    }
}

void QRWidget::applicationStateChanged(Qt::ApplicationState state) {
    if(state == Qt::ApplicationInactive) {
        hide();
    }
}

