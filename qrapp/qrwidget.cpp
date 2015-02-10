// Own includes
#include "qrwidget.h"

// Qt includes
#include <QVBoxLayout>
#include <QGuiApplication>
#include <QClipboard>
#include <QFileDialog>

// QR Encode includes
#include "qtqrencode.h"

QRWidget::QRWidget(QWidget *parent)
    : QWidget(parent, Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool) {

    _systemTrayIcon.setIcon(QIcon(":/icons/qr.png"));
    _systemTrayIcon.show();

    QVBoxLayout *vBoxLayout = new QVBoxLayout();
    _label = new QLabel(this);
    _label->setScaledContents(true);
    _lineEdit = new QLineEdit(this);
    _lineEdit->setPlaceholderText("Enter data to be encoded here");
    _menuBar = new QMenuBar(this);
    _menuBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    vBoxLayout->addWidget(_menuBar);
    vBoxLayout->addWidget(_label);
    vBoxLayout->addWidget(_lineEdit);

    vBoxLayout->setSpacing(1);
    vBoxLayout->setContentsMargins(1, 1, 1, 1);
    setLayout(vBoxLayout);
    setFixedSize(460, 512);

    _waitingSpinnerWidget = new WaitingSpinnerWidget(_label);

    QAction *saveAction = _menuBar->addAction(tr("Save to file"));
    QAction *quitAction = _menuBar->addAction(tr("Quit"));

    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));
    connect(quitAction, SIGNAL(triggered()), this, SLOT(quit()));

    connect(_lineEdit, SIGNAL(textChanged(QString)),
            this, SLOT(generateQRCode(QString)));
    connect(&_systemTrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));
    connect(qGuiApp, SIGNAL(applicationStateChanged(Qt::ApplicationState)),
            this, SLOT(applicationStateChanged(Qt::ApplicationState)));

    setFocusProxy(_lineEdit);
}

QRWidget::~QRWidget() {

}

void QRWidget::generateQRCode(QString text) {
    _waitingSpinnerWidget->start();
    _label->setPixmap(QPixmap());
    if(!text.isEmpty()) {
        QREncode qrEncode;
        qrEncode.encode(text);
        QImage image = qrEncode.toQImage(_label->height());
        _label->setPixmap(QPixmap::fromImage(image));
    }
    _waitingSpinnerWidget->stop();
}

void QRWidget::trayIconActivated(QSystemTrayIcon::ActivationReason activationReason) {
    Q_UNUSED(activationReason);
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

void QRWidget::save() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Choose destination file"), QString(), "*.png");
    if(!fileName.isEmpty()) {
        _label->pixmap()->save(fileName, "PNG");
    }
}

void QRWidget::quit() {
    qGuiApp->quit();
}
