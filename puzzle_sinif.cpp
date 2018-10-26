#include "puzzle_sinif.h"
#include "parca_liste.h"
#include <QDrag>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QPainter>

PuzzleSinif::PuzzleSinif(int resimBoyut, QWidget *parent)
    : QWidget(parent), m_resimBoyut(resimBoyut)
{
    setAcceptDrops(true);
    setMinimumSize(m_resimBoyut, m_resimBoyut);

    setMaximumSize(m_resimBoyut, m_resimBoyut);

}

void PuzzleSinif::clear()
{
    parcaYerleri.clear();

    parcaPixmaps.clear();

    parcaRects.clear();

    kareVurgu = QRect();
    yer = 0;
    update();
}

void PuzzleSinif::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat(ParcaListe::puzzleMimeType()))
        event->accept();
    else
        event->ignore();
}

void PuzzleSinif::dragLeaveEvent(QDragLeaveEvent *event)
{
    QRect guncelleRect = kareVurgu;
    kareVurgu = QRect();
    update(guncelleRect);
    event->accept();
}

void PuzzleSinif::dragMoveEvent(QDragMoveEvent *event)
{
    QRect guncelleRect = kareVurgu.united(kareler(event->pos()));

    if (event->mimeData()->hasFormat(ParcaListe::puzzleMimeType())
        && parcaRects.indexOf(kareler(event->pos())) == -1) {


        kareVurgu = kareler(event->pos());
        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else {
        kareVurgu = QRect();
        event->ignore();
    }

    update(guncelleRect);
}

void PuzzleSinif::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat(ParcaListe::puzzleMimeType())
        && parcaRects.indexOf(kareler(event->pos())) == -1) {

        QByteArray parcaData = event->mimeData()->data(ParcaListe::puzzleMimeType());
        QDataStream dataStream(&parcaData, QIODevice::ReadOnly);
        QRect kare = kareler(event->pos());
        QPixmap pixmap;
        QPoint parcaYeri;
        dataStream >> pixmap >> parcaYeri;

        parcaYerleri.append(parcaYeri);
        parcaPixmaps.append(pixmap);
        parcaRects.append(kare);

        kareVurgu = QRect();
        update(kare);

        event->setDropAction(Qt::MoveAction);
        event->accept();

        if (parcaYeri == QPoint(kare.x()/parcaBoyutu(), kare.y()/parcaBoyutu())) {
            yer++;
            if (yer == 25)
                emit puzzleTamamla();
        }
    } else {
        kareVurgu = QRect();
        event->ignore();
    }
}

void PuzzleSinif::mousePressEvent(QMouseEvent *event)
{
    QRect kare = kareler(event->pos());
    int bulunan = parcaRects.indexOf(kare);

    if (bulunan == -1)
        return;

    QPoint parcaYeri = parcaYerleri[bulunan];
    QPixmap pixmap = parcaPixmaps[bulunan];
    parcaYerleri.removeAt(bulunan);
    parcaPixmaps.removeAt(bulunan);
    parcaRects.removeAt(bulunan);

    if (parcaYeri == QPoint(kare.x()/parcaBoyutu(), kare.y()/parcaBoyutu()))
        yer--;

    update(kare);

    QByteArray ogeData;
    QDataStream dataStream(&ogeData, QIODevice::WriteOnly);

    dataStream << pixmap << parcaYeri;

    QMimeData *mimeData = new QMimeData;
    mimeData->setData(ParcaListe::puzzleMimeType(), ogeData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setHotSpot(event->pos() - kare.topLeft());
    drag->setPixmap(pixmap);

    if (!(drag->exec(Qt::MoveAction) == Qt::MoveAction)) {
        parcaYerleri.insert(bulunan, parcaYeri);
        parcaPixmaps.insert(bulunan, pixmap);
        parcaRects.insert(bulunan, kare);
        update(kareler(event->pos()));

        if (parcaYeri == QPoint(kare.x()/parcaBoyutu(), kare.y()/parcaBoyutu()))
            yer++;
    }
}

void PuzzleSinif::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.fillRect(event->rect(), Qt::white);

    if (kareVurgu.isValid()) {
        painter.setBrush(QColor("#ffcccc"));
        painter.setPen(Qt::NoPen);
        painter.drawRect(kareVurgu.adjusted(0, 0, -1, -1));
    }

    for (int i = 0; i < parcaRects.size(); ++i)
        painter.drawPixmap(parcaRects[i], parcaPixmaps[i]);
    painter.end();
}

const QRect PuzzleSinif::kareler(const QPoint &pozisyon) const
{
    return QRect(pozisyon.x()/parcaBoyutu() * parcaBoyutu(),
                 pozisyon.y()/parcaBoyutu() * parcaBoyutu(), parcaBoyutu(), parcaBoyutu());
}

int PuzzleSinif::parcaBoyutu() const
{
    return m_resimBoyut / 5;
}

int PuzzleSinif::resimBoyut() const
{
    return m_resimBoyut;
}
