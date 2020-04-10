#include "mainwindow.h"

#include <QTextDocument>
#include <QtWidgets>

MainWindow::MainWindow() {
    emiTextArea = new QTextBrowser();
    emiInitials = new QVector<QChar>;
    emiPieChart = new QChart();
    emiPieSeries = new QPieSeries();

    universalTextArea = new QTextBrowser();
    universalInitials = new QVector<QChar>;
    universalPieChart = new QChart();
    universalPieSeries = new QPieSeries();

    overallBarChart = new QChart();
    overallBarSeries = new QHorizontalBarSeries();

    decorate();
}

void MainWindow::about() {
    QMessageBox::about(
                this, tr("Progetto Qt"),
                tr("Un'interfaccia grafica per la visualizzazione degli artisti "
                   "di due delle più prestigiose etichette discografiche mondiali."));
}

void MainWindow::refresh() {
    overallBarSeries->clear();

    emiTextArea->clear();
    emiInitials->clear();
    emiInitials->squeeze();
    emiPieSeries->clear();
    emiStartRequest();

    universalTextArea->clear();
    universalInitials->clear();
    universalInitials->squeeze();
    universalPieSeries->clear();
    universalStartRequest();
}

void MainWindow::decorate() {
    this->setWindowTitle("Progetto Qt");

    // Menu: File
    QMenu* fileMenu = menuBar()->addMenu(tr("&File"));

    // Aggiorna
    QAction* refAct = new QAction(tr("&Aggiorna"), this);
    refAct->setShortcuts(QKeySequence::Refresh);
    refAct->setStatusTip(tr("Aggiorna il file"));
    connect(refAct, &QAction::triggered, this, &MainWindow::refresh);
    fileMenu->addAction(refAct);
    fileMenu->addSeparator();

    // Esci
    QAction* exitAct = fileMenu->addAction(tr("&Esci"), this, &QWidget::close);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));

    // Menu: Aiuto
    QMenu* helpMenu = menuBar()->addMenu(tr("Ai&uto"));
    QAction* aboutAct =
            helpMenu->addAction(tr("&Informazioni"), this, &MainWindow::about);
    aboutAct->setStatusTip(tr("Mostra una finestra con le informazioni"));

    QAction* aboutQtAct = helpMenu->addAction(tr("Informazioni su &Qt"), qApp,
                                              &QApplication::aboutQt);
    aboutQtAct->setStatusTip(tr("Mostra la versione di Qt"));

    // Layout: Etichette
    QLabel* emiLabel = new QLabel(tr("EMI"));
    QLabel* universalLabel = new QLabel(tr("Universal"));
    QHBoxLayout* labelLayout = new QHBoxLayout();
    labelLayout->addWidget(emiLabel);
    labelLayout->addWidget(universalLabel);

    // Widgets: Etichette Discografiche
    emiTextArea->setOpenExternalLinks(true);
    emiPieChart->legend()->hide();
    emiPieChart->setTitle("Artisti per iniziale (EMI)");
    emiPieSeries->setPieSize(0.6);
    QChartView* emiPieView = new QChartView(emiPieChart);
    emiPieView->setRenderHint(QPainter::Antialiasing);

    universalTextArea->setOpenExternalLinks(true);
    universalPieChart->legend()->hide();
    universalPieChart->setTitle("Artisti per iniziale (Universal)");
    universalPieSeries->setPieSize(0.6);
    QChartView* universalPieView = new QChartView(universalPieChart);
    universalPieView->setRenderHint(QPainter::Antialiasing);

    // Layout: Etichette Discografiche
    QHBoxLayout* textAreaLayout = new QHBoxLayout();
    textAreaLayout->addWidget(emiTextArea);
    textAreaLayout->addWidget(emiPieView);
    textAreaLayout->addWidget(universalTextArea);
    textAreaLayout->addWidget(universalPieView);

    // Layout: Grafico a Barre - Numero di artisti per etichetta
    // Asse X
    QValueAxis* axisX = new QValueAxis();
    axisX->setRange(0, 1000);
    axisX->applyNiceNumbers();
    // Asse Y
    QBarCategoryAxis* axisY = new QBarCategoryAxis();
    axisY->append(QStringList(""));

    overallBarChart->setTitle("Numero di artisti per etichetta");
    overallBarChart->addSeries(overallBarSeries);
    overallBarChart->addAxis(axisX, Qt::AlignBottom);
    overallBarChart->addAxis(axisY, Qt::AlignLeft);
    overallBarSeries->attachAxis(axisX);
    overallBarSeries->attachAxis(axisY);

    QChartView* overallBarView = new QChartView(overallBarChart);
    overallBarView->setRenderHint(QPainter::Antialiasing);

    QHBoxLayout* artistAmountChart = new QHBoxLayout();
    artistAmountChart->addWidget(overallBarView);

    // Layout: VBox
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addLayout(labelLayout);
    mainLayout->addLayout(textAreaLayout);
    mainLayout->addLayout(artistAmountChart);

    // CentralWidget
    QWidget* cw = new QWidget();
    cw->setLayout(mainLayout);
    setCentralWidget(cw);
    refresh();
}

void MainWindow::emiStartRequest() {
    emiReply = emiNam.get(QNetworkRequest(QUrl(
                                              "http://www.ivl.disco.unimib.it/minisites/cpp/List_of_EMI_artists.txt")));
    connect(emiReply, &QNetworkReply::finished, this, &MainWindow::emiFinished);
    connect(emiReply, &QIODevice::readyRead, this, &MainWindow::emiReadyRead);
    statusBar()->showMessage(
                tr("Sto scaricando il file "
                   "\"http://www.ivl.disco.unimib.it/minisites/cpp/"
                   "List_of_EMI_artists.txt\"..."));
}

void MainWindow::emiReadyRead() {
    QByteArray tmp = "";
    while ((tmp += emiReply->readLine()) != nullptr) {
        emiBuf += parseArtistLine(tmp, emiInitials);
        tmp = "";
    }
}

void MainWindow::emiFinished() {
    if(emiReply->error()) {
        statusBar()->showMessage(tr("Impossibile contattare il server."));
        return;
    }
    emiTextArea->append(emiBuf);
    fillPieSeries(emiPieSeries, emiInitials);
    if (emiPieChart->series().empty()) {
        emiPieChart->addSeries(emiPieSeries);
    }
    QBarSet* tmpSet = new QBarSet("EMI");
    *tmpSet << emiInitials->length();
    overallBarSeries->append(tmpSet);
    statusBar()->showMessage(tr("Pronto."));
}

void MainWindow::universalStartRequest() {
    universalReply = universalNam.get(
                QNetworkRequest(QUrl("http://www.ivl.disco.unimib.it/minisites/cpp/"
                                     "List_of_Universal_artists.txt")));
    connect(universalReply, &QNetworkReply::finished, this,
            &MainWindow::universalFinished);
    connect(universalReply, &QIODevice::readyRead, this,
            &MainWindow::universalReadyRead);
    statusBar()->showMessage(
                tr("Sto scaricando il file "
                   "\"http://www.ivl.disco.unimib.it/minisites/cpp/"
                   "List_of_Universal_artists.txt\"..."));
}

void MainWindow::universalReadyRead() {
    QByteArray tmp = "";
    while ((tmp += universalReply->readLine()) != nullptr) {
        universalBuf += parseArtistLine(tmp, universalInitials);
        tmp = "";
    }
}

void MainWindow::universalFinished() {
    if(emiReply->error()) {
        statusBar()->showMessage(tr("Impossibile contattare il server."));
        return;
    }
    universalTextArea->append(universalBuf);
    fillPieSeries(universalPieSeries, universalInitials);
    if (universalPieChart->series().empty()) {
        universalPieChart->addSeries(universalPieSeries);
    }
    QBarSet* tmpSet = new QBarSet("Universal");
    *tmpSet << universalInitials->length();
    overallBarSeries->append(tmpSet);
    statusBar()->showMessage(tr("Pronto."));
}

QString MainWindow::parseArtistLine(const QString& artistLine,
                                    QVector<QChar>* initials) {
    QString tmp("<p><a href=\"https://it.wikipedia.org");
    QString work = artistLine.trimmed();
    int urlEnd = work.lastIndexOf('"') - 1;
    int sepIdx = work.indexOf(' ');
    QString artistName;
    if (sepIdx == -1) {
        artistName = "!!!! NOME MANCANTE NEL FILE !!!!";
    } else {
        artistName = work.mid(sepIdx).remove(' ').replace('_', ' ');
    }
    // qInfo() << "name: <" << artistName << ">";
    if (urlEnd == 0) {  // noUrlStrategy
        tmp = "<p>";
        tmp.append(artistName);
        tmp.append("</p></br>");
    } else {  // urlStremiategy
        QString artistUrl = work.mid(1, urlEnd);
        tmp.append(artistUrl);
        tmp.append("\">");
        tmp.append(artistName);
        tmp.append("</a></p></br>");
    }
    initials->append(artistName.front().toUpper().toLatin1());
    return tmp;
}

void MainWindow::fillPieSeries(QPieSeries* pieSeries,
                               const QVector<QChar>* initials) {
    QVector<QChar> src = *initials;
    QChar tmp;
    int cycle = 0;
    while (!src.empty()) {
        tmp = src.first();
        QPieSlice* tSlice = new QPieSlice(QString(tmp), src.count(tmp));
        tSlice->setLabelVisible();
        if ((cycle % 2) == 0) {
            tSlice->setLabelArmLengthFactor(0.15);
            tSlice->setLabelColor(Qt::GlobalColor::black);
        } else {
            tSlice->setLabelArmLengthFactor(0.35);
            tSlice->setLabelColor(Qt::GlobalColor::gray);
        }
        pieSeries->append(tSlice);
        // qInfo() << tmp << ":" << src.count(tmp);
        cycle++;
        src.removeAll(tmp);
    }
}

void MainWindow::cleanup() {
    emiTextArea = nullptr;
    emiInitials->clear();
    emiInitials->squeeze();
    emiInitials = nullptr;
    emiPieChart = nullptr;
    emiPieSeries = nullptr;

    universalTextArea = nullptr;
    universalInitials->clear();
    universalInitials->squeeze();
    universalInitials = nullptr;
    universalPieChart = nullptr;
    universalPieSeries = nullptr;

    overallBarChart = nullptr;
    overallBarSeries = nullptr;
}

void MainWindow::closeEvent(QCloseEvent *event) {
    cleanup();
    event->accept();
}
