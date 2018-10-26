#ifndef PARCA_LISTE_H
#define PARCA_LISTE_H

#include <QListWidget>
#include "puzzle_sinif.h"

class ParcaListe : public QListWidget
{
    Q_OBJECT
public:
    explicit ParcaListe(int parcaBoyutu, QWidget *parent = 0);
    void parcaEkle(QPixmap pixmap, QPoint parcaYeri);

     static QString puzzleMimeType()
     {
     return QStringLiteral("image/");
     }

protected:
    void dragEnterEvent(QDragEnterEvent *event) Q_DECL_OVERRIDE;
    void dragMoveEvent(QDragMoveEvent *event) Q_DECL_OVERRIDE;
    void dropEvent(QDropEvent *event) Q_DECL_OVERRIDE;
    void startDrag(Qt::DropActions supportedActions) Q_DECL_OVERRIDE;

    int m_parcaBoyutu;
};


#endif // PARCA_LISTE_H




