#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    view = new ZoomingGraphicsView(ui->position, this);
    ui->horizontalLayout->addWidget(view);
    scene = new QGraphicsScene(view);
    view->setScene(scene);

    connect(ui->openButton, SIGNAL(clicked()), this, SLOT(open()));
    connect(ui->reloadButton, SIGNAL(clicked()), this, SLOT(reload()));
    connect(ui->mouse_tracking, SIGNAL(stateChanged(int)), this, SLOT(toggle_mouse_tracking(int)));

    QPolygon test;

    test << QPoint(0, 0);
    test << QPoint(2, 0);
    test << QPoint(2, 2);
    test << QPoint(-1, 2);
    test << QPoint(-1, -2);
    test << QPoint(1, -2);
    test << QPoint(1, -1);
    test << QPoint(0, -1);
    test << QPoint(0, 0);
    drawPolygon(test);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::open()
{
    QString path = settings.value("last_path").toString();
    QString filename = QFileDialog::getOpenFileName(this, tr("Otwórz plik"), path);
    if (!filename.isNull()) {
        read(filename);
    }
}

void MainWindow::reload()
{
    if (last_filename.isNull()) {
        QMessageBox::information(this, tr("Brak pliku"), tr("W przeszłości nie otwierałeś jeszcze żadnego pliku.\nWybierz plik do otwarcia."));
        open();
    } else {
        read(last_filename);
        ui->statusBar->showMessage(tr("Przeładowano plik: ") + last_filename, 10000);
    }

}

void MainWindow::toggle_mouse_tracking(int state)
{
    view->setTrackMouse(state == Qt::Checked);
}

void MainWindow::drawPolygon(const QPolygon & poly)
{
    static int MAX_ALLOWED_SIZE = 1000;
    if (poly.size() > MAX_ALLOWED_SIZE) {
        int res = QMessageBox::question(this,
                                        tr("Duży plik wejściowy"),
                                        tr("Wielokąt, który mam wczytać zawiera ponad ") + QString::number(MAX_ALLOWED_SIZE) + tr(" wierzchołków.\nPróba jego wczytania może spowolnić komputer.\nCzy mam kontynuować?"),
                                        QMessageBox::Yes,
                                        QMessageBox::No | QMessageBox::Default | QMessageBox::Escape);
        if (res != QMessageBox::Yes) {
            return;
        }
    }
    view->deleteDot();
    scene->clear();
    static int margin = 2;
    QPen pen(Qt::black);
    pen.setWidth(3);
    pen.setCosmetic(true);
    pen.setJoinStyle(Qt::RoundJoin);
    scene->addPolygon(poly, pen, Qt::gray);
    QRect bound = poly.boundingRect();
    bound.adjust(margin, margin, margin, margin);

    scene->setSceneRect(scene->itemsBoundingRect());
}

void MainWindow::read(QString filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, tr("Błąd otwierania!"), tr("Wystąpił błąd podczas próby otwarcia pliku. Upewnij się, że podana ścieżka jest poprawna oraz posiadasz odpowiednie uprawnienia."));
        return;
    }
    settings.setValue("last_path", QFileInfo(filename).path());
    last_filename = filename;
    bool ok = true;
    QTextStream in(&file);
    QPolygon poly;
    bool first_line = true;
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line == "NIE" and first_line) {
            ok = false;
            QMessageBox::warning(this, tr("Odpowiedź NIE"), tr("Wczytany plik zawiera odpowiedź \"NIE\".\nNie potrafię jej zwizualizować."));
            break;
        }
        first_line = false;
        QTextStream in_line(&line);
        int x, y;
        in_line >> x >> y;
        poly << QPoint(x, y);
        if (in_line.status() != QTextStream::Ok) {
            ok = false;
            QMessageBox::critical(this, tr("Niepoprawny format pliku!"), tr("Wystąpił błąd podczas wczytywania pliku.\nUpewnij się, że jego format jest poprawny."));
            break;
        }
    }
    file.close();
    if (ok) {
        poly << poly.first();
        drawPolygon(poly);
        ui->statusBar->showMessage(tr("Załadowano plik: ") + filename, 10000);
    }
}

