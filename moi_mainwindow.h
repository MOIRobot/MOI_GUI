#ifndef MOI_MAINWINDOW_H
#define MOI_MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPushButton>
#include <QProcess>
#include <QtNetwork/QUdpSocket>
#include <QList>
#include <QString>
#include <QNetworkInterface>
#include <QMessageBox>
#include <QTimer>

namespace Ui {
class MOI_MainWindow;
}

class MOI_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MOI_MainWindow(QWidget *parent = 0);
    ~MOI_MainWindow();

private:
    Ui::MOI_MainWindow *ui;
    bool is_roscoreStarted=false;
    //udp 接受端
    QUdpSocket *udpSocketRecevier;
    //定时器
    QTimer *mTimer;

    void InitUdpSocket();

    QString text_details;
    bool isRobotOnline=false;
private slots:

    void ButtonClicked_fakeOdomPubliser();
    void ButtonClicked_realOdomPubliser();
    void ButtonClicked_btn_globalplanner();
    void ButtonClicked_btn_move_base();
    void ButtonClicked_btn_fake_ultrosonic_data();
    void ButtonClicked_btn_laser_301();
    void ButtonClicked_btn_borad_control();
    void ButtonClicked_roscore();
    void ButtonClicked_stageonerobot();
    void ButtonClicked_stagerobots();
    void ButtonClicked_gmapping();
    void ButtonClicked_hector_slam();
    void ButtonClicked_mapSave();
    void ButtonClicked_amcl();
    void ButtonClicked_cartographer();
    void ButtonClicked_tf_tree();
    void ButtonClicked_usbcam();
    void ButtonClicked_kinect();
    void ButtonClicked_asus();
    void ButtonClicked_rqt();
    //udp 接收端
    void readPendingDatagrams();
    void RobotOnlineCheck();


};

#endif // MOI_MAINWINDOW_H
