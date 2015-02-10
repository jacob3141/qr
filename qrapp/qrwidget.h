#ifndef QRWIDGET_H
#define QRWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>

#ifdef Q_OS_MAC
#include "systemtrayiconmac.h"
#else
#include <QSystemTrayIcon>
#endif

class QRWidget : public QWidget
{
    Q_OBJECT

public:
    QRWidget(QWidget *parent = 0);
    ~QRWidget();

public slots:
    void generateQRCode(QString text);
    void trayIconActivated(QSystemTrayIcon::ActivationReason activationReason);

    void applicationStateChanged(Qt::ApplicationState state);
private:
    QLabel *_label;
    QLineEdit *_lineEdit;
#ifdef Q_OS_MAC
    SystemTrayIconMac _systemTrayIcon;
#else
    QSystemTrayIcon _systemTrayicon;
#endif

};

#endif // QRWIDGET_H
