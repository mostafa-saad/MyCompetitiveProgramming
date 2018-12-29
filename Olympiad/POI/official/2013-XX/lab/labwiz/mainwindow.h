#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QPolygon>
#include <QPoint>
#include <QPainter>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QSettings>
#include "zoominggraphicsview.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void open();
    void reload();
    void read(QString filename);
    void toggle_mouse_tracking(int state);
private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    ZoomingGraphicsView *view;
    void drawPolygon(const QPolygon &poly);
    QString last_filename;
    QSettings settings;

};

#endif // MAINWINDOW_H
