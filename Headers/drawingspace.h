#ifndef DRAWINGSPACE_H
#define DRAWINGSPACE_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>

//class drawingspace
//{
//public:
//    drawingspace();
//};

class DrawingSpace : public QWidget{
    Q_OBJECT

public:
    DrawingSpace(QWidget *parent = 0);
    bool openImage(const QString &fileName);
    bool saveImage(const QString &fileName, const char *fileFormat);

    void setBrushColor(const QColor &newColor);
    void setBrushSize(int newSize);

    bool isModified() const {return modified;}
    QColor brushColor() const {return selectedBrushColor;}
    int brushSize() const {return selectedBrushSize;}

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

    QColor selectedBrushColor;
    int selectedBrushSize;
    QImage image;
    QPoint startingPoint;

};


#endif // DRAWINGSPACE_H
