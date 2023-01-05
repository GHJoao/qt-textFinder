#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->textCharFormat = ui->textoFonte->textCursor().charFormat();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_b_limpar_clicked()
{
    //https://stackoverflow.com/questions/20841081/how-to-pop-up-a-message-window-in-qt

    this->ocorrencias = 0;
    this->possuiHtml = false;

    //QMessageBox::information(
    //    this,
    //    tr("Teste"),
    //   tr(this->textoFontePuro.toLocal8Bit().data()) );
    //ui->textoFonte->setText("");
    //ui->textoFonte->clear();

    //esta parte de baixo seria pra que ao clicar em limpar o texto ficasse como se digitado
    //porém se foi destacado algo no texto, o usuário usa o mouse ou setas para selecionar
    //uma parte do texto sem destaque + uma com destaque, ao clicar em limpar fica tudo vermelho
    //não sei porque, aparentemente é algum bug no cursor do textEdit
    //Isso não afeta o funcionamento para o usuário, até se clicar de novo fica tudo certo
    //porém visualmente é estranho
    QTextCursor textCursor = ui->textoFonte->textCursor();
    textCursor.setCharFormat(this->textCharFormat);
    ui->textoFonte->setTextCursor(textCursor);
    textCursor.movePosition(QTextCursor::End);

    if(ui->textoFonte->toPlainText().isEmpty() || ui->textoFonte->toPlainText().isNull()) ui->textoFonte->setPlainText("");
    else ui->textoFonte->setPlainText(this->textoFontePuro);
    ui->textoFonte->setReadOnly(false);

    ui->textoLocalizar->setEnabled(true);
    ui->b_localizar->setEnabled(true);
    ui->c_caseSensitive->setEnabled(true);

    ui->t_resultado->setText("Resultado: 0 ocorrência(s).");
}

void MainWindow::on_b_localizar_clicked()
{
    this->localizar(ui->c_caseSensitive->checkState());
}

void MainWindow::localizar(int checkMarcado)
{
    ui->b_limpar->setEnabled(false);
    ui->textoFonte->setReadOnly(true);
    ui->textoFonte->setTextInteractionFlags(ui->textoFonte->textInteractionFlags() | Qt::TextSelectableByKeyboard);
    ui->textoLocalizar->setEnabled(false);
    ui->b_localizar->setEnabled(false);
    ui->c_caseSensitive->setEnabled(false);

    QString procurar = ui->textoLocalizar->text();
    QString fonte = ui->textoFonte->toPlainText();

    if(!(this->possuiHtml)) this->textoFontePuro = fonte;

    if(procurar.isEmpty() || procurar.isNull() || fonte.isEmpty() || fonte.isNull())
    {
        ui->b_limpar->setEnabled(true);
        ui->textoFonte->setReadOnly(false);
        ui->textoLocalizar->setEnabled(true);
        ui->b_localizar->setEnabled(true);
        ui->c_caseSensitive->setEnabled(true);
        return;
    }

    this->ocorrencias = 0;

    fonte.prepend("<pre>");
    fonte.append("</pre>");

    if(checkMarcado)
    {
        this->ocorrencias = fonte.count(procurar, Qt::CaseSensitive);
        fonte.replace(procurar, QString("<font color=\"#FF0000\">" + procurar + "</font>"), Qt::CaseSensitive);
    }
    else
    {
        this->ocorrencias = fonte.count(procurar, Qt::CaseInsensitive);
        int index = 0;
        while((index = fonte.indexOf(procurar,index,Qt::CaseInsensitive))!=-1)
        {
            QString aux;
            fonte.replace(index,procurar.size(),aux = QString("<font color=\"#FF0000\">" + fonte.mid(index,procurar.size()) + "</font>"));
            index+=aux.size();
        }
    }

    if(this->ocorrencias>0)
    {
        ui->textoFonte->setHtml(fonte);
        this->possuiHtml = true;
    }
    else
    {
        ui->textoFonte->setReadOnly(false);
        ui->b_localizar->setEnabled(true);
        ui->textoLocalizar->setEnabled(true);
        ui->c_caseSensitive->setEnabled(true);
    }

    ui->t_resultado->setText("Resultado: " + QString::number(this->ocorrencias) + " ocorrência(s).");
    ui->b_limpar->setEnabled(true);
}
