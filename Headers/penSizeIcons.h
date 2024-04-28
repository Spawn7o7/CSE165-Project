#ifndef PENSIZEICONS_H
#define PENSIZEICONS_H

#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QPainter>
#include <QIcon>
#include <QPixmap>
#include <QColor>

class penSizeIcons : public QDialog {
    Q_OBJECT

public:
    penSizeIcons(const QColor &penColor, QWidget *parent = nullptr);
    int getSelectedSize() const { return selectedSize; }

private:
    int selectedSize;
    QColor currentPenColor;
    QVBoxLayout *layout;
    QPixmap createPenIcon(int size);
};

#endif // PENSIZEICONS_H
