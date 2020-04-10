#include <QApplication>
#include <QCommandLineOption>
#include <QCommandLineParser>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  QCoreApplication::setOrganizationName("Progetto Qt");
  QCoreApplication::setApplicationName("Progetto Qt");
  QCoreApplication::setApplicationVersion(QT_VERSION_STR);
  QCommandLineParser parser;
  parser.setApplicationDescription(QCoreApplication::applicationName());
  parser.addHelpOption();
  parser.addVersionOption();
  parser.process(app);

  MainWindow mainWin;
  mainWin.setMinimumSize(1024, 768);
  mainWin.resize(1366, 768);
  mainWin.show();
  return app.exec();
}
