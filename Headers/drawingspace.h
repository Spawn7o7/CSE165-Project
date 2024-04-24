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

    void setPenColor(const QColor &newColor);
    void setPenSize(int newSize);

    bool isModified() const {return modified;}
    QColor penColor() const {return myPenColor;}
    int penSize() const {return myPenSize;}

public slots:
    void clearImage();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    void drawingTo(const QPoint &endPoint);
    void resizeImage(QImage *image, const QSize &newSize);

    bool modified;
    bool drawing;

    QColor myPenColor;
    int myPenSize;
    QImage image;
    QPoint lastPoint;

};


#endif // DRAWINGSPACE_H
