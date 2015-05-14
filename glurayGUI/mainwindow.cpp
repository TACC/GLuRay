#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QNetworkInterface>
#include <QFileDialog>
#include <sstream>
#include <iostream>
#include <cassert>
//#include "gl2manta.h"
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow), num_connections(0)
{
  refreshes = 0;
  previewConnection = 0;
  server = new QTcpServer();
  ui->setupUi(this);

  char* pc = getenv("GLURAY_PORT");

  int port = 3490;
  if (pc)
  {
    stringstream s(pc);
    s >> port;
  }
  cerr << "server listening on port " << port << endl;

  if (!server->listen(QHostAddress::LocalHost, port)) {
    QMessageBox::critical(this, tr("Server Error"),
        tr("Unable to start the server: %1.")
        .arg(server->errorString()));
    close();
    return;
  }
  QString ipAddress;
  QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
  // use the first non-localhost IPv4 address
  //for (int i = 0; i < ipAddressesList.size(); ++i) {
  //    if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
  //        ipAddressesList.at(i).toIPv4Address()) {
  //        ipAddress = ipAddressesList.at(i).toString();
  //        break;
  //    }
  //}
  // if we did not find one, use IPv4 localhost
  if (ipAddress.isEmpty())
    ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
  ui->statusLabel->setText(tr("The server is running on IP: %1 port: %2")
      .arg(ipAddress).arg(server->serverPort()));

  connect(server, SIGNAL(newConnection()), this, SLOT(onConnect()));
  connect(ui->rotatePB, SIGNAL(clicked()), ui->glview, SLOT(toggleAnimation()));
  connect(ui->applyPB, SIGNAL(clicked()), this, SLOT(onClickApply()));
  connect(ui->renderPB, SIGNAL(clicked()), this, SLOT(onClickRender()));
  //connect(ui->previewPB, SIGNAL(clicked()), ui->glview, SLOT(refreshGL()));
  connect(ui->previewPB, SIGNAL(clicked()), this, SLOT(onClickPreview()));
  ui->previewPB->setEnabled(false);
  connect(ui->glview, SIGNAL(onDraw()), this, SLOT(onGLDraw()));
  connect(ui->envPB, SIGNAL(clicked()), this, SLOT(onClickEnvMapBrowse()));
  connect(ui->pinholeRB, SIGNAL(clicked()), this, SLOT(onClickPinhole()));
  connect(ui->thinLensRB, SIGNAL(clicked()), this, SLOT(onClickThinLens()));

  connect(ui->lambertianRB, SIGNAL(clicked()), this, SLOT(onClickLambertian()));
  connect(ui->phongRB, SIGNAL(clicked()), this, SLOT(onClickPhong()));
  connect(ui->glassRB, SIGNAL(clicked()), this, SLOT(onClickGlass()));

  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(updateFPS()));
  timer->start(2000);
  frame_count=0;

}

void MainWindow::updateFPS()
{
  double fps = double(frame_count)/2.0;
  stringstream s;
  s << fps;
  ui->fpsLB->setText(s.str().c_str());
  frame_count = 0;
}

void MainWindow::onConnect()
{
  cout << __FUNCTION__ << endl;
  if (num_connections == 0)
  {
    ui->statusLabel->setText(tr("preview client connected"));
    cerr << "new connection\n";
    previewConnection = server->nextPendingConnection();
    ui->previewPB->setEnabled(true);
    connect(previewConnection, SIGNAL(disconnected()),
        this, SLOT(clientDisconnected()));
  }
  else
  {
    ui->statusLabel->setText(tr("new client connected"));
    cerr << "enabling buttons...\n";
    ui->applyPB->setEnabled(true);
    //ui->renderPB->setEnabled(true);  //TODO: render no longer works for now
    QTcpSocket* clientConnection = server->nextPendingConnection();
    connect(clientConnection, SIGNAL(disconnected()),
        this, SLOT(clientDisconnected()));
    clientConnections.push_back(clientConnection);
  }

  QByteArray block;
  QDataStream out(&block, QIODevice::WriteOnly);
  out.setVersion(QDataStream::Qt_4_0);
  out << "wee\0";
  //      QTcpSocket *clientConnection = server->nextPendingConnection();
  //   connect(clientConnection, SIGNAL(disconnected()),
  //               clientConnection, SLOT(deleteLater()));
  //clientConnection->write(block);
  // string msg = "weeHello there this is me\0";
  string msg;
  stringstream s;
  s << "-apply " ;//<< packSettings();
  msg = s.str();
  cout << "sending string: " << msg << endl;
  //   clientConnection->write(msg.c_str(), msg.size()+1);
  num_connections++;
}


MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
  QMainWindow::changeEvent(e);
  switch (e->type()) {
    case QEvent::LanguageChange:
      ui->retranslateUi(this);
      break;
    default:
      break;
  }
}

std::string MainWindow::packSettings()
{
  stringstream s("");
  s << "-spp " << ui->sppSB->value() << " ";
  if (ui->aoCB->isChecked())
    s << "-ao " << ui->aoSB->value() << " " << ui->ao_distanceSB->value() << " 0.7 ";
  else
    s << "-ao 0 0 0 ";
  if (ui->envCB->isChecked())
    s << "-env " << ui->envTB->text().toStdString() << " ";
  if (ui->shadowsCB->isChecked())
    s << "-shadows ";
  if (ui->skyDomeCB->isChecked())
    s << "-skyDome " << ui->skyDomeSB->value() << " 10 0.8 ";
  else
    s << "-skyDome " << 0 << " 10 0 ";
  if (ui->thinLensRB->isChecked())
    s << "-thinLens " << ui->focalDistanceSB->value() << " " << ui->apertureSB->value() << " ";
  if (ui->pinholeRB->isChecked())
    s << "-pinhole ";
  s << "-reflectivity " << ui->reflectivitySB->value() << " ";
  if (ui->lambertianRB->isChecked())
    s << "-lambertian ";
  if (ui->phongRB->isChecked())
    s << "-phong ";
  if (ui->glassRB->isChecked())
    s << "-glass " << ui->riSB->value() << " " << ui->ri2SB->value() << " ";
  if (ui->thinDielectricRB->isChecked())
    s << "-thinDielectric " << ui->etaSB->value() << " " << ui->thicknessSB->value() << " ";
  if (ui->transparentRB->isChecked())
    s << "-transparent ";
  if (ui->orenNayarRB->isChecked())
    s << "-orenNayar " << ui->roughnessSB->value() << " ";
  return s.str();

}

void MainWindow::onClickRender()
{
  string msg;
  stringstream s;
  s << "-renderOnce " << packSettings();
  msg = s.str();
  cout << "render: sending string: " << msg << endl;
  for(int i =0; i < clientConnections.size(); i++)
    clientConnections[i]->write(msg.c_str(), msg.size()+1);
}

void MainWindow::clientDisconnected()
{
  if (num_connections-- < 2)
  {
    ui->applyPB->setEnabled(false);
    ui->renderPB->setEnabled(false);
  }
  ui->statusLabel->setText(tr("client disconnected"));
}

void MainWindow::onClickApply()
{
  //    QByteArray block;
  //         QDataStream out(&block, QIODevice::WriteOnly);
  //         out.setVersion(QDataStream::Qt_4_0);
  //         out << "wee\0";
  //   QTcpSocket *clientConnection = server->nextPendingConnection();
  //   connect(clientConnection, SIGNAL(disconnected()),
  //               clientConnection, SLOT(deleteLater()));
  //clientConnection->write(block);
  string msg;
  stringstream s;
  s << "-apply " << packSettings();
  msg = s.str();
  cout << "apply: sending string: " << msg << endl;
  for(int i =0; i < clientConnections.size(); i++)
    clientConnections[i]->write(msg.c_str(), msg.size()+1);

  refreshes+=2;
  // sleep(1);
  // ui->glview->refreshGL();

}
void MainWindow::onClickEnvMapBrowse()
{
  ui->envTB->setText(QFileDialog::getOpenFileName(this, tr("Open Environment Map"), "", tr("Image Files (*.hdr)")));
}

void MainWindow::onGLDraw()
{
  frame_count++;
  if (refreshes > 0)
  {
    refreshes--;
    ui->glview->refreshGL();
  }
}


void MainWindow::onClickPinhole()
{
  ui->thinLensRB->setChecked(false);
}

void MainWindow::onClickThinLens()
{
  ui->pinholeRB->setChecked(false);
}

void MainWindow::onClickPreview()
{
  if(!previewConnection)
    return;
  string msg;
  stringstream s;
  s << "-apply " << packSettings();
  msg = s.str();
//msg = "-apply -spp 1 -threads 8 -skyDome 2 100 0.1 -reflectivity 0.03 -env /scratch/01336/carson/data/lightProbes/campus_probe.hdr -phong -fov 45";
  cout << "preview: sending string: " << msg << endl;
  previewConnection->write(msg.c_str(), msg.size()+1);
  refreshes+=2;
  //sleep(1);
  //ui->glview->refreshGL();
}

void MainWindow::onClickLambertian()
{
  ui->glassRB->setChecked(false);
  ui->phongRB->setChecked(false);
  //  ui->lambertianRB->setChecked(false);
  ui->thinDielectricRB->setChecked(false);
  ui->transparentRB->setChecked(false);
  ui->orenNayarRB->setChecked(false);
}

void MainWindow::onClickPhong()
{
  ui->glassRB->setChecked(false);
  ui->lambertianRB->setChecked(false);
  ui->thinDielectricRB->setChecked(false);
  ui->transparentRB->setChecked(false);
  ui->orenNayarRB->setChecked(false);
}

void MainWindow::onClickGlass()
{
  //ui->glassRB->setChecked(false);
  ui->phongRB->setChecked(false);
  ui->lambertianRB->setChecked(false);
  ui->thinDielectricRB->setChecked(false);
  ui->transparentRB->setChecked(false);
  ui->orenNayarRB->setChecked(false);
}

void MainWindow::onClickThinDielectric()
{
  ui->glassRB->setChecked(false);
  ui->phongRB->setChecked(false);
  ui->lambertianRB->setChecked(false);
  //ui->thinDielectricRB->setChecked(false);
  ui->transparentRB->setChecked(false);
  ui->orenNayarRB->setChecked(false);
}

void MainWindow::onClickTransparent()
{
  ui->glassRB->setChecked(false);
  ui->phongRB->setChecked(false);
  ui->lambertianRB->setChecked(false);
  ui->thinDielectricRB->setChecked(false);
  //ui->transparentRB->setChecked(false);
  ui->orenNayarRB->setChecked(false);
}

void MainWindow::onClickOrenNayar()
{
  ui->glassRB->setChecked(false);
  ui->phongRB->setChecked(false);
  ui->lambertianRB->setChecked(false);
  ui->thinDielectricRB->setChecked(false);
  ui->transparentRB->setChecked(false);
  //ui->orenNayarRB->setChecked(false);
}
