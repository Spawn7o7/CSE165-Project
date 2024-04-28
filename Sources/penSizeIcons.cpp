#include "penSizeIcons.h"

penSizeIcons::penSizeIcons(const QColor &penColor, QWidget *parent)
    : QDialog(parent), selectedSize(0), currentPenColor(penColor) {  // Store the pen color

    setWindowTitle(tr("Select Size"));

    layout = new QVBoxLayout(this);

    for (int size : {1, 5, 10, 15, 20, 25}) {  // Create buttons for pen sizes
        QPushButton *button = new QPushButton(tr("Size %1").arg(size), this);
        button->setIcon(QIcon(createPenIcon(size)));
        button->setIconSize(QSize(50, 50));
        layout->addWidget(button);

        connect(button, &QPushButton::clicked, this, [=]() {
            selectedSize = size;
            accept();
        });
    }
}

QPixmap penSizeIcons::createPenIcon(int size) {
    QPixmap pixmap(50, 50);  // Create a transparent pixmap
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setBrush(currentPenColor);  // Hopefully this allows the icon to represent the color chosen by user
    painter.drawEllipse(25 - size / 2, 25 - size / 2, size, size);  // Circle to represent pen size
    return pixmap;
}

