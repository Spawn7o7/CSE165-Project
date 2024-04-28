#ifndef BRUSHSIZEICONS_H
#define BRUSHSIZEICONS_H

#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QPainter>
#include <QIcon>
#include <QPixmap>
#include <QColor>

class brushSizeIcons : public QDialog {
    Q_OBJECT

public:
    brushSizeIcons(const QColor &brushColor, QWidget *parent = nullptr);
    int getSelectedSize() const { return selectedSize; }

private:
    int selectedSize;
    QColor currentBrushColor;
    QVBoxLayout *layout;
    QPixmap createBrushIcon(int size);
};

#endif // BRUSHSIZEICONS_H
