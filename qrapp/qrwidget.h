#ifndef QRWIDGET_H
#define QRWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QMenuBar>

#ifdef Q_OS_MAC
#include "systemtrayiconmac.h"
#else
#include <QSystemTrayIcon>
#endif

#include "waitingspinnerwidget.h"

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

    void save();
    void quit();
private:
    QLabel *_label;
    QLineEdit *_lineEdit;
    QMenuBar *_menuBar;
    WaitingSpinnerWidget *_waitingSpinnerWidget;

#ifdef Q_OS_MAC
    SystemTrayIconMac _systemTrayIcon;
#else
    QSystemTrayIcon _systemTrayIcon;
#endif

};

#endif // QRWIDGET_H
