#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTcpServer>
#include <string>
#include <QTimer>
#include <vector>


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);
    std::string packSettings();

private slots:
    void onConnect();
    void onClickRender();
    void onClickApply();
    void onClickEnvMapBrowse();
    void clientDisconnected();
    void onGLDraw();
    void updateFPS();
    void onClickPinhole();
    void onClickThinLens();
    void onClickPreview();
    void onClickLambertian();
    void onClickPhong();
    void onClickGlass();
    void onClickThinDielectric();
    void onClickTransparent();
    void onClickOrenNayar();

private:
    QTimer* timer;
    Ui::MainWindow *ui;
    QTcpServer* server;
    QTcpSocket *previewConnection;
    std::vector<QTcpSocket*> clientConnections;
    int frame_count, num_connections;
    int refreshes;
};

#endif // MAINWINDOW_H
