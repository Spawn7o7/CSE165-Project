#include <QtWidgets>
#include "drawingspace.h"

DrawingSpace::DrawingSpace(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
    modified = false;
    drawing = false;
    selectedPenColor = Qt::black;
    selectedPenSize = 1;
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
    selectedPenColor = newColor;
}


void DrawingSpace::setPenSize(int newSize){
    selectedPenSize = newSize;
}


void DrawingSpace::clearImage(){
    image.fill(qRgb(255,255,255)); // Fills the canvas with white to 'clear' it
    modified = true;
    update();
}


void DrawingSpace::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        startingPoint = event->pos();
        drawing = true;
    }
}


void DrawingSpace::mouseMoveEvent(QMouseEvent *event){
    if((event->buttons() == Qt::LeftButton) && drawing){
        drawingSeg(event->pos());
    }
}


void DrawingSpace::mouseReleaseEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton && drawing){
        drawingSeg(event->pos());
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


void DrawingSpace::drawingSeg(const QPoint &endPoint){
    QPainter painter(&image);
    painter.setPen(QPen(selectedPenColor, selectedPenSize, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawLine(startingPoint, endPoint);
    modified = true;

    int filler = (selectedPenSize / 2) + 2;
    update(QRect(startingPoint, endPoint).normalized().adjusted(-filler, -filler, +filler, +filler));
    startingPoint = endPoint;
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
