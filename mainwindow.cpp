#include <QtWidgets>

#include "mainwindow.h"
#include "drawingspace.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    drawingSpace = new DrawingSpace;
    setCentralWidget(drawingSpace);
    createActions();
    createMenu();
    setWindowTitle(tr("Totally Not MS Paint"));
}

void MainWindow::closeEvent(QCloseEvent *event){ //prompts user to save before they fully close out of app
    if(quickSave()){
        event->accept();
    }
    else{
        event->ignore();
    }
}

void MainWindow::open(){
    if(quickSave()){
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath());

        if(!fileName.isEmpty()){
            drawingSpace->openImage(fileName);
        }
    }
}

void MainWindow::save(){
    QAction *action = qobject_cast<QAction *>(sender());
    QByteArray fileFormat = action->data().toByteArray();
    saveFile(fileFormat);
}

void MainWindow::penColor(){
    QColor newColor = QColorDialog::getColor(drawingSpace->penColor());
    if(newColor.isValid()){
        drawingSpace->setPenColor(newColor);
    }
}

void MainWindow::penSize(){
    bool confirm;
    int newSize = QInputDialog::getInt(this, tr("Totally Not MS Paint"), tr("Select Pen Size: "), drawingSpace->penSize(), 1, 25, 1, &confirm);

    if(confirm){
        drawingSpace->setPenSize(newSize);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
