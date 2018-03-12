#include "moi_mainwindow.h"
#include "ui_moi_mainwindow.h"
#include <QDebug>
#include <string>
using namespace std;
MOI_MainWindow::MOI_MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MOI_MainWindow)
{
    ui->setupUi(this);
    ui->btn_roscore->setStyleSheet("background:green;color:white");

    connect(ui->btn_roscore,SIGNAL(released()),this,SLOT(ButtonClicked_roscore()));
    connect(ui->btn_fakeOdomPubliser,SIGNAL(released()),this,SLOT(ButtonClicked_fakeOdomPubliser()));
    connect(ui->btn_realOdomPubliser,SIGNAL(released()),this,SLOT(ButtonClicked_realOdomPubliser()));
    connect(ui->btn_globalplanner,SIGNAL(released()),this,SLOT(ButtonClicked_btn_globalplanner()));
    connect(ui->btn_move_base,SIGNAL(released()),this,SLOT(ButtonClicked_btn_move_base()));
    connect(ui->btn_fake_ultrosonic_data,SIGNAL(released()),this,SLOT(ButtonClicked_btn_fake_ultrosonic_data()));
    connect(ui->btn_laser_301,SIGNAL(released()),this,SLOT(ButtonClicked_btn_laser_301()));
    connect(ui->btn_borad_control,SIGNAL(released()),this,SLOT(ButtonClicked_btn_borad_control()));
    connect(ui->btn_stageone,SIGNAL(released()),this,SLOT(ButtonClicked_stageonerobot()));
    connect(ui->btn_stagerobots,SIGNAL(released()),this,SLOT(ButtonClicked_stagerobots()));
    connect(ui->btn_gmapping,SIGNAL(released()),this,SLOT(ButtonClicked_gmapping()));
    connect(ui->btn_hector,SIGNAL(released()),this,SLOT(ButtonClicked_hector_slam()));
    connect(ui->btn_map_save,SIGNAL(released()),this,SLOT(ButtonClicked_mapSave()));
    connect(ui->btn_amcl,SIGNAL(released()),this,SLOT(ButtonClicked_amcl()));
    connect(ui->btn_cartographer,SIGNAL(released()),this,SLOT(ButtonClicked_cartographer()));
    connect(ui->btn_tf_tree,SIGNAL(released()),this,SLOT(ButtonClicked_tf_tree()));
    connect(ui->btn_usbcam,SIGNAL(released()),this,SLOT(ButtonClicked_usbcam()));
    connect(ui->btn_kinect,SIGNAL(released()),this,SLOT(ButtonClicked_kinect()));
    connect(ui->btn_asus,SIGNAL(released()),this,SLOT(ButtonClicked_asus()));
    connect(ui->btn_rqt,SIGNAL(released()),this,SLOT(ButtonClicked_rqt()));
    //启动roscore
    int res=system("bash -c 'source /opt/ros/indigo/setup.bash;roscore'&");
    qDebug()<<res;
    is_roscoreStarted=true;
    ui->btn_roscore->setText("关闭roscore");
    ui->btn_roscore->setStyleSheet("background:red;color:white");
    //初始化socket
    InitUdpSocket();
}

MOI_MainWindow::~MOI_MainWindow()
{
    udpSocketRecevier->close();
    delete ui;
}
void MOI_MainWindow::ButtonClicked_fakeOdomPubliser()
{
    int id=system("gnome-terminal -x bash -c 'source /opt/ros/indigo/setup.bash;echo \"PID of this script: $$\";source ~/MOI_Robot_Winter/devel/setup.bash;roslaunch winter_simulation fakeOdoPublisher.launch'&");
    qDebug()<<id;

}
void MOI_MainWindow::ButtonClicked_realOdomPubliser()
{}
void MOI_MainWindow::ButtonClicked_btn_globalplanner()
{
    system("gnome-terminal -x bash -c 'source /opt/ros/indigo/setup.bash;source ~/MOI_Robot_Winter/devel/setup.bash;roslaunch winter_simulation agv_fakeNavigation.launch'&");
}
void MOI_MainWindow::ButtonClicked_btn_move_base()
{
    system("gnome-terminal -x bash -c 'source /opt/ros/indigo/setup.bash;source ~/MOI_Robot_Winter/devel/setup.bash;roslaunch winter_simulation fake_move_base_winter.launch'&");
}
void MOI_MainWindow::ButtonClicked_btn_fake_ultrosonic_data()
{
    system("gnome-terminal -x bash -c 'source /opt/ros/indigo/setup.bash;source ~/MOI_Robot_Winter/devel/setup.bash;rosrun winter_simulation fake_ultro_withInput.py'&");
}
void MOI_MainWindow::ButtonClicked_btn_laser_301()
{
    system("gnome-terminal -x bash -c 'source /opt/ros/indigo/setup.bash;source ~/MOI_Robot_Winter/devel/setup.bash;roslaunch winter_laser moi_laser_lslidar_n301.launch'&");
}
void MOI_MainWindow::ButtonClicked_btn_borad_control()
{
    system("gnome-terminal -x bash -c 'source /opt/ros/indigo/setup.bash;source ~/MOI_Robot_Winter/devel/setup.bash;rosrun winter_keyboard telecop_direct.py'&");
}
void MOI_MainWindow::ButtonClicked_stageonerobot()
{
    system("gnome-terminal  -x bash -c 'source /opt/ros/indigo/setup.bash;source ~/MOI_Robot_Winter/devel/setup.bash;roslaunch winter_simulation stage_onerobot.launch'&");
}
void MOI_MainWindow::ButtonClicked_stagerobots()
{
    system("bash -c 'source /opt/ros/indigo/setup.bash;source ~/MOI_Robot_Winter/devel/setup.bash;roslaunch winter_simulation stage_multiplerobots.launch'&");
}
void MOI_MainWindow::ButtonClicked_gmapping()
{
    system("gnome-terminal -x bash -c 'source /opt/ros/indigo/setup.bash;source ~/MOI_Robot_Winter/devel/setup.bash;roslaunch winter_gmapping  gmapping_stage_onerobot.launch '&");
}
void MOI_MainWindow::ButtonClicked_hector_slam()
{
    system("bash -c 'source /opt/ros/indigo/setup.bash;source ~/MOI_Robot_Winter/devel/setup.bash;roslaunch winter_simulation stage_multiplerobots.launch'&");
}
void MOI_MainWindow::ButtonClicked_mapSave()
{
    system("gnome-terminal  -x bash -c 'source /opt/ros/indigo/setup.bash;source ~/MOI_Robot_Winter/devel/setup.bash;rosrun map_server map_saver -f ~/my_map'&");
}
void MOI_MainWindow::ButtonClicked_amcl()
{
    system("gnome-terminal  -x bash -c 'source /opt/ros/indigo/setup.bash; source ~/MOI_Robot_Winter/devel/setup.bash;roslaunch winter_simulation fake_amcl_move_base_winter.launch'&");
}
void MOI_MainWindow::ButtonClicked_cartographer()
{
    system("gnome-terminal  -x bash -c 'source /opt/ros/indigo/setup.bash; source ~/MOI_Robot_Winter/devel/setup.bash;source ~/cartographer_slam/install_isolated/setup.bash;roslaunch cartographer_ros demo_revo_lds.launch'&");
}
void MOI_MainWindow::ButtonClicked_tf_tree()
{
    system("bash -c 'source /opt/ros/indigo/setup.bash;rosrun rqt_tf_tree rqt_tf_tree'&");
}
void MOI_MainWindow::ButtonClicked_usbcam()
{
    system("gnome-terminal  -x bash -c 'source /opt/ros/indigo/setup.bash; roslaunch usb_cam usb_cam-test.launch'&");
}
void MOI_MainWindow::ButtonClicked_kinect()
{
    system("gnome-terminal  -x bash -c 'source /opt/ros/indigo/setup.bash; source ~/MOI_Robot_Winter/devel/setup.bash;source ~/cartographer_slam/install_isolated/setup.bash;roslaunch winter_camera kinect1.launch'&");
}
void MOI_MainWindow::ButtonClicked_asus()
{
    system("gnome-terminal  -x bash -c 'source /opt/ros/indigo/setup.bash; source ~/MOI_Robot_Winter/devel/setup.bash;source ~/cartographer_slam/install_isolated/setup.bash; roslaunch openni2_launch openni2.launch depth_registration:=true'&");
}
void MOI_MainWindow::ButtonClicked_rqt()
{
    system("bash -c 'source /opt/ros/indigo/setup.bash; source ~/MOI_Robot_Winter/devel/setup.bash;source ~/cartographer_slam/install_isolated/setup.bash; rqt'&");
}
void MOI_MainWindow::ButtonClicked_roscore()
{
    if(!is_roscoreStarted)
    {
        is_roscoreStarted=true;
        ui->btn_roscore->setText("关闭roscore");
        ui->btn_roscore->setStyleSheet("background:red;color:white");

        /*QProcess *proc= new QProcess;
        QStringList arguments;
        arguments.append("-c");
        arguments.append("/home/jobs/MOI_Robot_Winter/autoLoad.sh");

         qDebug()<<arguments;
         proc->start("bash",arguments);
         */
        //加一个&号让进程异步执行
        system("bash -c 'source /opt/ros/indigo/setup.bash;roscore'&");

    }
    else
    {
        is_roscoreStarted=false;
        QProcess *proc= new QProcess;
        QStringList arguments;
        arguments.append("-c");
        arguments.append("pgrep roscore");
        proc->start("bash",arguments);
        // 用于保存进程的控制台输出
        QByteArray procOutput;
            // 等待进程结束
        while (false == proc->waitForFinished())
            {
               return ;
            }
            // 读取进程输出到控制台的数据
        procOutput = proc->readAllStandardOutput();
        std::string str1("kill ");
        std::string str2(procOutput.data());
        std::string str3=str1+str2;
        system(str3.data());
        ui->btn_roscore->setText("启动roscore");
        ui->btn_roscore->setStyleSheet("background:green;color:white");

    }
}
void MOI_MainWindow::InitUdpSocket()
{
    QString details = "";
    QList<QNetworkInterface> mylist = QNetworkInterface::allInterfaces();
        for(int j = 0;j<mylist.count();j++)
        {
            QNetworkInterface interface = mylist.at(j);
            details = details + ("Device:") + interface.name() +"\n";
            details = details + ("Hardware Address:") + interface.hardwareAddress() +"\n";
            QList<QNetworkAddressEntry> list = interface.addressEntries();
            for(int i = 0;i<list.count();i++)
            {
                QNetworkAddressEntry entry = list.at(i);
                details = details + ("IP Address:") + entry.ip().toString() +"\n";
                details = details + ("Net Mask:") + entry.netmask().toString() +"\n";
                details = details + ("Board Cast:") + entry.broadcast().toString() +"\n";
            }
        }
      //显示ip信息
    //QMessageBox::information(this,("Details"),details);

    mTimer= new QTimer(this);
    connect(mTimer,SIGNAL(timeout()),this,SLOT(RobotOnlineCheck()));
    mTimer->start(8000);

    udpSocketRecevier=new QUdpSocket(this);
    if(udpSocketRecevier->bind(21567,QUdpSocket::ShareAddress))
    {
        text_details = text_details + ("Waiting message from robot!")+ "\n";
        ui->textEdit->setText("Robot message:\n");
        ui->textEdit->setText(text_details);

        connect(udpSocketRecevier,SIGNAL(readyRead()),this,SLOT(readPendingDatagrams()));
    }
    else
    {
        QMessageBox::information(this,("Details"),"绑定UDP出错");
    }
}
void MOI_MainWindow::readPendingDatagrams()
{
   QHostAddress client_address;//声明一个QHostAddress对象用于保存发送端的信息
   quint16 port;
   char buf[100];//声明一个字符数组用于接收发送过来的字符串
   if(udpSocketRecevier->hasPendingDatagrams())
       {
           udpSocketRecevier->readDatagram(buf,udpSocketRecevier->pendingDatagramSize(),&client_address,&port);
           text_details = text_details + ("receive ") + buf + (" from ") + client_address.toString() + "\n";
           isRobotOnline=true;
           //ui->textEdit->setText(text_details);
            QByteArray data="Confirmed!";
            ui->radioButton_robotstate->setChecked(true);
            ui->radioButton_robotstate->setText("机器人在线");
            udpSocketRecevier->writeDatagram(data.data(),data.size(),client_address,port);
       }
}
void MOI_MainWindow::RobotOnlineCheck()
{
    if(text_details.length()>500)
    {
        text_details="";
    }
    if(isRobotOnline)
    {
        text_details=text_details+"Robot OnLine\n";
        ui->textEdit->setText(text_details);

    }
    else
    {
        text_details=text_details+"Robot OffLine\n";
        ui->textEdit->setText(text_details);
        ui->radioButton_robotstate->setChecked(false);
        ui->radioButton_robotstate->setText("机器人掉线");
    }
    isRobotOnline=false;
}
