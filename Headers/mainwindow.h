#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QList>
#include <QMainWindow>
#include "drawingspace.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class drawingspace;

class MainWindow : public QMainWindow
{
    Q_OBJECT //declares our class as a Q_OBJECT (base class)

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots: //aka events
    void openFile();
    void saveFile();
    void penColor();
    void eraserPen();
    void penSize();

private:
    Ui::MainWindow *ui;
    void createActions();
    void createMenu();
    bool quickSave();   //if changes detected in drawing area, prompts the user to save
    bool saveFile(const QByteArray &fileFormat);

    DrawingSpace *drawingSpace;

    QMenu *fileMenu;
    QMenu *saveAs;
    QList<QAction *> saveAsAction; //this will allow the user to save file in various formats EX: jpg, png, etc
    QMenu *brushOptions;
    QMenu *eraseOptions;

    QAction *openAction;
    QAction *closeAction;
    QAction *penColorAction;
    QAction *eraserPenAction;
    QAction *penSizeAction;

    QAction *deleteAllAction;
};
#endif // MAINWINDOW_H
