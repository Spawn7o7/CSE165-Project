#include <QtWidgets>

#include "mainwindow.h"
#include "brushsizeicons.h"
#include "drawingspace.h"
#include "ui_mainwindow.h"

//might need to comment out UI window if it clashes with app code, have not run and tested yet.

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
    if(quickSave()){ // If save file found, allow user to select it or start a new drawing
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


void MainWindow::brushColor(){
    QColor newColor = QColorDialog::getColor(drawingSpace->brushColor());
    if(newColor.isValid()){
        drawingSpace->setBrushColor(newColor);
    }
}

void MainWindow::eraserBrush() {
    drawingSpace->setBrushColor(Qt::white);
}


void MainWindow::brushSize() {
    QColor currentColor = drawingSpace->brushColor();
    brushSizeIcons dialog(currentColor, this);
    if (dialog.exec() == QDialog::Accepted) {
        drawingSpace->setBrushSize(dialog.getSelectedSize());
    }
}


void MainWindow::createActions(){
    openAction = new QAction(tr("&Open"), this);
    openAction->setShortcuts(QKeySequence::Open);
    connect(openAction, SIGNAL(triggered(bool)), this, SLOT(open()));

    // Save drawing (choosing format type)
    foreach(QByteArray format, QImageWriter::supportedImageFormats()){
        QString text = tr("%1...").arg(QString(format).toUpper());
        QAction *action = new QAction(text, this);
        action->setData(format);
        connect(action, SIGNAL(triggered()), this, SLOT(save()));
        
        saveAsAction.append(action);
    }

    // Quitting the drawing program
    closeAction = new QAction(tr("&Exit"), this);
    closeAction->setShortcuts(QKeySequence::Quit);
    connect(closeAction, SIGNAL(triggered()), this, SLOT(close()));

    // Brush Customization
    brushColorAction = new QAction(tr("&Pen Color..."), this);
    connect(brushColorAction, SIGNAL(triggered()), this, SLOT(brushColor()));

    eraserBrushAction = new QAction(tr("Erase"), this);
    connect(eraserBrushAction, SIGNAL(triggered()), this, SLOT(eraserBrush()));

    brushSizeAction = new QAction(tr("Pen &Size..."), this);
    connect(brushSizeAction, SIGNAL(triggered()), this, SLOT(brushSize()));

    // Clears the screen
    deleteAllAction = new QAction(tr("&Delete All..."), this);
    connect(deleteAllAction, SIGNAL(triggered()), drawingSpace, SLOT(clearImage()));
}


void MainWindow::createMenu(){
    saveAs = new QMenu(tr("&Save As"), this);
    foreach(QAction *action, saveAsAction){
        saveAs->addAction(action);
    }

    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAction);
    fileMenu->addMenu(saveAs);
    fileMenu->addSeparator();
    fileMenu->addAction(closeAction);

    brushOptions = new QMenu(tr("&Brush"), this);
    brushOptions->addAction(brushColorAction);
    brushOptions->addAction(brushSizeAction);

    eraseOptions = new QMenu(tr("Erase"), this);
    eraseOptions->addAction(eraserBrushAction);
    fileMenu->addSeparator();
    eraseOptions->addAction(deleteAllAction);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(brushOptions);
    menuBar()->addMenu(eraseOptions);
}


bool MainWindow::quickSave(){
    if(drawingSpace->isModified()){
        QMessageBox::StandardButton prompt;
        prompt = QMessageBox::warning(this, tr("Totally Not MS Paint"),
                                   tr("Do you want to save your work?\n"
                                         "There are unsaved changes."),
                                   QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if(prompt == QMessageBox::Save){
            return saveFile("png");
        }
        else if(prompt == QMessageBox::Cancel){
            return false;
        }
    }
    return true;
}


bool MainWindow::saveFile(const QByteArray &fileFormat){
    QString initialPath = QDir::currentPath() + "/untitled." + fileFormat;
    QString fileName = QFileDialog::getSaveFileName(
        this,
        tr("Save As"),
        initialPath,
        tr("%1 Files (*.%2);; All Files(*)").arg(QString::fromLatin1(fileFormat.toUpper()), QString::fromLatin1(fileFormat))
        );

    if(fileName.isEmpty()){
        return false;
    }
    else{
        return drawingSpace->saveImage(fileName, fileFormat.constData());
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}
