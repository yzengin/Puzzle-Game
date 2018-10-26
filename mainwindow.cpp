#include "mainwindow.h"
#include "parca_liste.h"
#include "puzzle_sinif.h"

#include <QtWidgets>
#include <stdlib.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    menuYukle();
    ogeYukle();
    sayac = 0;
    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    setWindowTitle(tr("Puzzle Oyunu"));
}

void MainWindow::resimAc()
{
    const QString dosyaAdi =
        QFileDialog::getOpenFileName(this, tr("Resim AÇ"), QString(),
                                     tr("Resim Dosyaları (*.png *.jpg *.bmp)"));

    if (!dosyaAdi.isEmpty())
        resimYukle(dosyaAdi);
}

void MainWindow::resimYukle(const QString &dosyaAdi)
{
    QPixmap yeniResim;
    if (!yeniResim.load(dosyaAdi)) {
        QMessageBox::warning(this, tr("Resim AÇ"),
                             tr("Hata!,Resim Yüklenemedi."),
                             QMessageBox::Close);
        return;
    }
    puzzleResim = yeniResim;
    puzzleYukle();
}

void MainWindow::tamamlandi()
{
    QMessageBox::information(this, tr("Puzzle'ı bitirdin."),
                             tr("Tebrikler!\n"
                                "Başlamak için yeniden tıklayın."),
                             QMessageBox::Ok);

    puzzleYukle();
}

void MainWindow::puzzleYukle()
{
    int boyut = qMin(puzzleResim.width(), puzzleResim.height());
    puzzleResim = puzzleResim.copy((puzzleResim.width() - boyut)/2,
        (puzzleResim.height() - boyut)/2, boyut, boyut).scaled(puzzleSinif->width(),
            puzzleSinif->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    parcaListe->clear();

    for (int y = 0; y < 5; ++y) {
        for (int x = 0; x < 5; ++x) {
            int parcaBoyutu = puzzleSinif->parcaBoyutu();
            QPixmap parcaResim = puzzleResim.copy(x * parcaBoyutu, y * parcaBoyutu, parcaBoyutu, parcaBoyutu);
            parcaListe->parcaEkle(parcaResim, QPoint(x, y));
        }
    }

    qsrand(QCursor::pos().x() ^ QCursor::pos().y());

    for (int i = 0; i < parcaListe->count(); ++i) {
        if (int(2.0*qrand()/(RAND_MAX+1.0)) == 1) {
            QListWidgetItem *oge = parcaListe->takeItem(i);
            parcaListe->insertItem(0, oge);
        }
    }

    puzzleSinif->clear();
}

void MainWindow::menuYukle()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&Dosya"));

    QAction *openAction = fileMenu->addAction(tr("&Aç..."), this, &MainWindow::resimAc);
    openAction->setShortcuts(QKeySequence::Open);

    QAction *exitAction = fileMenu->addAction(tr("&Çıkış"), qApp, &QCoreApplication::quit);
    exitAction->setShortcuts(QKeySequence::Quit);

    QMenu *gameMenu = menuBar()->addMenu(tr("&Oyun"));

    gameMenu->addAction(tr("&Yeniden Başlat"), this, &MainWindow::puzzleYukle);
}

void MainWindow::ogeYukle()
{
    QFrame *frame = new QFrame;
    QHBoxLayout *frameLayout = new QHBoxLayout(frame);
    puzzleSinif = new PuzzleSinif(400);

    parcaListe = new ParcaListe(puzzleSinif->parcaBoyutu(), this);


    connect(puzzleSinif, &PuzzleSinif::puzzleTamamla,
            this, &MainWindow::tamamlandi, Qt::QueuedConnection);

    frameLayout->addWidget(parcaListe);
    frameLayout->addWidget(puzzleSinif);
    setCentralWidget(frame);
}
