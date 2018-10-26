#ifndef PUZZLE_SINIF_H
#define PUZZLE_SINIF_H
#include <QList>
#include <QPoint>
#include <QPixmap>
#include <QWidget>

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
class QMouseEvent;
QT_END_NAMESPACE


class PuzzleSinif : public QWidget
{
    Q_OBJECT
public:
    explicit PuzzleSinif(int resimBoyut, QWidget *parent = 0);
    void clear();

    int parcaBoyutu() const;
    int resimBoyut() const;

signals:
    void puzzleTamamla();

protected:
    void dragEnterEvent(QDragEnterEvent *event) Q_DECL_OVERRIDE;
    void dragLeaveEvent(QDragLeaveEvent *event) Q_DECL_OVERRIDE;
    void dragMoveEvent(QDragMoveEvent *event) Q_DECL_OVERRIDE;
    void dropEvent(QDropEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    const QRect kareler(const QPoint &pozisyon) const;

    QList<QPixmap> parcaPixmaps;
    QList<QRect> parcaRects;
    QList<QPoint> parcaYerleri;
    QRect kareVurgu;
    int yer;
    int m_resimBoyut;
};

#endif // PUZZLE_SINIF_H
