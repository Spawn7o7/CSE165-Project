#include "brushsizeicons.h"

brushSizeIcons::brushSizeIcons(const QColor &brushColor, QWidget *parent)
    : QDialog(parent), selectedSize(0), currentBrushColor(brushColor) {  // Store the pen color

    setWindowTitle(tr("Select Size"));

    layout = new QVBoxLayout(this);

    for (int size : {1, 5, 10, 15, 20, 25}) {  // Create buttons for pen sizes
        QPushButton *button = new QPushButton(tr("Size %1").arg(size), this);
        button->setIcon(QIcon(createBrushIcon(size)));
        button->setIconSize(QSize(50, 50));
        layout->addWidget(button);

        connect(button, &QPushButton::clicked, this, [=]() {
            selectedSize = size;
            accept();
        });
    }
}

QPixmap brushSizeIcons::createBrushIcon(int size) {
    QPixmap pixmap(50, 50);  // Create a transparent pixmap
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setBrush(currentBrushColor);  // Hopefully this allows the icon to represent the color chosen by user
    painter.drawEllipse(25 - size / 2, 25 - size / 2, size, size);  // Circle to represent pen size
    return pixmap;
}

