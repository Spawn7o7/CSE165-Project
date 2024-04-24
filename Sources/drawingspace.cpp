#include <QtWidgets>
#include "drawingspace.h"

DrawingSpace::DrawingSpace(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
    modified = false;
    drawing = false;
    myPenColor = Qt::black;
    myPenSize = 1;
}


bool DrawingSpace::openImage(const QString &fileName){
    QImage loadedImage;
    if(!loadedImage.load(fileName)){
        return false;
    }

    QSize newSize = loadedImage.size().expandedTo(size());
    resizeImage(&loadedImage, newSize);
    image = loadedImage;
    modified = false;
    update();
    return true;
}


bool DrawingSpace::saveImage(const QString &fileName, const char *fileFormat){
    QImage visibleImage = image;
    resizeImage(&visibleImage, size());
    if(visibleImage.save(fileName, fileFormat)){
        modified = false;
        return true;
    }
    else{
        return false;
    }
}


void DrawingSpace::setPenColor(const QColor &newColor){
    myPenColor = newColor;
}


void DrawingSpace::setPenSize(int newSize){
    myPenSize = newSize;
}


void DrawingSpace::clearImage(){
    image.fill(qRgb(255,255,255)); // Fills the canvas with white to 'clear' it
    modified = true;
    update();
}


void DrawingSpace::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        lastPoint = event->pos();
        drawing = true;
    }
}


void DrawingSpace::mouseMoveEvent(QMouseEvent *event){
    if((event->buttons() == Qt::LeftButton) && drawing){
        drawingTo(event->pos());
    }
}


void DrawingSpace::mouseReleaseEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton && drawing){
        drawingTo(event->pos());
        drawing = false;
    }
}


void DrawingSpace::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, image, dirtyRect);
}


void DrawingSpace::resizeEvent(QResizeEvent *event){ // resize the canvas
    if(width() > image.width() || height() > image.height()){
        int newWidth = qMax(width() +128, image.width());
        int newHeight = qMax(height() +128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}


void DrawingSpace::drawingTo(const QPoint &endPoint){
    QPainter painter(&image);
    painter.setPen(QPen(myPenColor, myPenSize, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawLine(lastPoint, endPoint);
    modified = true;

    // adds a bit of 'fluff' around the edges of the brush, might remove
    int filler = (myPenSize / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized().adjusted(-filler, -filler, +filler, +filler));
    lastPoint = endPoint;
}


void DrawingSpace::resizeImage(QImage *image, const QSize &newSize){
    if(image->size() == newSize){
        return;
    }

    QImage newImage(newSize, QImage::Format_ARGB32);
    newImage.fill(qRgb(255,255,255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0,0), *image);
    *image = newImage;
}
