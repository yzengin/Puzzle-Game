#include "parca_liste.h"
#include "mainwindow.h"
#include <QDrag>
#include <QDragEnterEvent>
#include <QMimeData>

ParcaListe::ParcaListe(int parcaBoyutu, QWidget *parent)
    : QListWidget(parent), m_parcaBoyutu(parcaBoyutu)
{
    setDragEnabled(true);
    setViewMode(QListView::IconMode);
    setIconSize(QSize(m_parcaBoyutu, m_parcaBoyutu));
    setSpacing(10);
    setAcceptDrops(true);
    setDropIndicatorShown(true);
}

void ParcaListe::dragEnterEvent(QDragEnterEvent *event) // sürükle
{
    if (event->mimeData()->hasFormat(ParcaListe::puzzleMimeType()))
        event->accept();
    else
        event->ignore();
}

void ParcaListe::dragMoveEvent(QDragMoveEvent *event) //taşı
{
    if (event->mimeData()->hasFormat(ParcaListe::puzzleMimeType())) {
        event->setDropAction(Qt::MoveAction);
        event->accept();

    }
    else
    {
        event->ignore();
    }
}

void ParcaListe::dropEvent(QDropEvent *event) //bırak
{
    if (event->mimeData()->hasFormat(ParcaListe::puzzleMimeType()))
    {
        QByteArray parcaData = event->mimeData()->data(ParcaListe::puzzleMimeType());
        QDataStream dataStream(&parcaData, QIODevice::ReadOnly);
        QPixmap pixmap;
        QPoint parcaYeri;
        dataStream >> pixmap >> parcaYeri;

        parcaEkle(pixmap, parcaYeri);

        event->setDropAction(Qt::MoveAction);

        event->accept();

    }
    else
    {
        event->ignore();
    }

}
void ParcaListe::parcaEkle(QPixmap pixmap, QPoint parcaYeri)
{
    QListWidgetItem *parcaOge = new QListWidgetItem(this);

    parcaOge->setIcon(QIcon(pixmap));

    parcaOge->setData(Qt::UserRole, QVariant(pixmap));

    parcaOge->setData(Qt::UserRole+1, parcaYeri);

    parcaOge->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
}

void ParcaListe::startDrag(Qt::DropActions) //sürüklemeye başlarken
{
    QListWidgetItem *oge = currentItem();

    QByteArray ogeData;
    QDataStream dataStream(&ogeData, QIODevice::WriteOnly);
    QPixmap pixmap = qvariant_cast<QPixmap>(oge->data(Qt::UserRole));
    QPoint parcaYeri = oge->data(Qt::UserRole+1).toPoint();

    dataStream << pixmap << parcaYeri;

    QMimeData *mimeData = new QMimeData;
    mimeData->setData(ParcaListe::puzzleMimeType(), ogeData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setHotSpot(QPoint(pixmap.width()/2, pixmap.height()/2));
    drag->setPixmap(pixmap);

    if (drag->exec(Qt::MoveAction) == Qt::MoveAction)
        delete takeItem(row(oge));
}
