#include "qrwidget.h"

#include <QVBoxLayout>

#include "qtqrencode.h"

QRWidget::QRWidget(QWidget *parent)
    : QWidget(parent, Qt::FramelessWindowHint) {

    _systemTrayicon.setIcon(QIcon(":/icons/qr.png"));
    _systemTrayicon.show();

    QVBoxLayout *vBoxLayout = new QVBoxLayout();
    _label = new QLabel(this);
    _label->setScaledContents(true);
    _lineEdit = new QLineEdit(this);
    _lineEdit->setPlaceholderText("Enter data to be encoded here");
    vBoxLayout->addWidget(_label);
    vBoxLayout->addWidget(_lineEdit);
    setLayout(vBoxLayout);

    setFixedSize(480, 512);

    connect(_lineEdit, SIGNAL(textChanged(QString)), this, SLOT(generateQRCode(QString)));

    connect(&_systemTrayicon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this,
            SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));
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
    QRect geometry = _systemTrayicon.geometry();
    if(isVisible()) {
        hide();
    } else {
        show();
        move(geometry.x() + geometry.width() / 2 - width() / 2, geometry.y());

    }
}
