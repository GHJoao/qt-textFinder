#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "QString"
#include "QTextCharFormat"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_b_limpar_clicked();

    void on_b_localizar_clicked();

    void localizar(int);

private:
    Ui::MainWindow *ui;
    QString textoFontePuro = "";
    QTextCharFormat textCharFormat;
    int ocorrencias = 0;
    bool possuiHtml = false;
};
#endif // MAINWINDOW_H
