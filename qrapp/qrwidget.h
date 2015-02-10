#ifndef QRWIDGET_H
#define QRWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>

#include <QSystemTrayIcon>

class QRWidget : public QWidget
{
    Q_OBJECT

public:
    QRWidget(QWidget *parent = 0);
    ~QRWidget();

public slots:
    void generateQRCode(QString text);
    void trayIconActivated(QSystemTrayIcon::ActivationReason activationReason);

private:
    QLabel *_label;
    QLineEdit *_lineEdit;
    QSystemTrayIcon _systemTrayicon;
};

#endif // QRWIDGET_H
