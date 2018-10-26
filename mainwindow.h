#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QPixmap>
#include <QMainWindow>

class ParcaListe;
class PuzzleSinif;
QT_BEGIN_NAMESPACE
class QListWidgetItem;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    MainWindow *anaekran;
    void resimYukle(const QString &yol);

public slots:
    void resimAc();
    void puzzleYukle();

private slots:
    void tamamlandi();

private:
    void menuYukle();
    void ogeYukle();

    QPixmap puzzleResim;
    ParcaListe *parcaListe;
    PuzzleSinif *puzzleSinif;
    int sayac;
};

#endif // MAINWINDOW_H
