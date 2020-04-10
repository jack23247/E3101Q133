#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUrl>
#include <QtCharts>
#include <QtNetwork>

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QTextBrowser;
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow();

 protected:
  void closeEvent(QCloseEvent* event) override;

 private slots:
  void about();
  void refresh();
  void emiReadyRead();
  void emiFinished();
  void universalReadyRead();
  void universalFinished();

 private:
  void decorate();
  void emiStartRequest();
  void universalStartRequest();
  QString parseArtistLine(const QString& artistLine, QVector<QChar>* initials);
  void fillPieSeries(QPieSeries* pieSeries, const QVector<QChar>* initials);
  void cleanup();

  QNetworkAccessManager emiNam;
  QNetworkReply* emiReply;
  QString emiBuf;
  QTextBrowser* emiTextArea;
  QVector<QChar>* emiInitials;
  QChart* emiPieChart;
  QPieSeries* emiPieSeries;

  QNetworkAccessManager universalNam;
  QNetworkReply* universalReply;
  QString universalBuf;
  QTextBrowser* universalTextArea;
  QVector<QChar>* universalInitials;
  QChart* universalPieChart;
  QPieSeries* universalPieSeries;

  QChart* overallBarChart;
  QHorizontalBarSeries* overallBarSeries;
};

#endif
