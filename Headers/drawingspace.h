#ifndef DRAWINGSPACE_H
#define DRAWINGSPACE_H

#include <QWidget>
#include <QColor>
#include <QImage>
#include <QPoint>

class DrawingSpace : public QWidget{
    Q_OBJECT

public:
    DrawingSpace(QWidget *parent = 0);
    bool openImage(const QString &fileName);
    bool saveImage(const QString &fileName, const char *fileFormat);

    void setPenColor(const QColor &newColor);
    void setPenSize(int newSize);

    bool isModified() const {return modified;}
    int selectedSize = 0;

    QColor penColor() const {return selectedPenColor;}
    int penSize() const {return selectedPenSize;}

public slots:
    void clearImage();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    void drawingSeg(const QPoint &endPoint);
    void resizeImage(QImage *image, const QSize &newSize);

    bool modified;
    bool drawing;

    QColor selectedPenColor;
    int selectedPenSize;
    QImage image;
    QPoint startingPoint;

};


#endif // DRAWINGSPACE_H
