#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::Start()
{
    try
    {
        int *SmileArray = NULL;
        int N = 0;
        int SmileNumber;
        bool SmileFlag = false;
        bool toIntFlag = true;
        QString bufString;
        QStringList bufList;
        ui->lEStatus->setText("all right");
        ui->lEIntoAScreen->setText("");
        if(ui->intoAFile->isChecked())
        {
            if(ui->lEIntoAFile->text() == "")
            {
                throw 4;
            }
        }

        if(!ui->fromFile->isChecked() && !ui->fromKeyBoard->isChecked())
        {
            throw 8;
        }

        if(!ui->intoAFile->isChecked() && !ui->intoAScreen->isChecked())
        {
            throw 9;
        }

        if(ui->fromFile->isChecked())
        {
            if(ui->lEFromFile->text() == "")
            {
                throw 1;
            }
            QFile file_read(ui->lEFromFile->text());
            if(file_read.open(QIODevice::ReadOnly) == false)
            {
                throw 2;
            }
            QTextStream streamRead(&file_read);

            bufString = streamRead.readLine();

            file_read.close();
        }

        else if(ui->fromKeyBoard->isChecked())
        {
            if(ui->lEFromKeyboard->text() == "")
            {
                throw 3;
            }
            bufString = ui->lEFromKeyboard->text();
        }

        bufList = bufString.split(" ",QString::SkipEmptyParts);

        N = bufList.size();

        if(N == 0)
        {
            throw 10;
        }

        SmileArray =  new int [N];
        if(SmileArray == NULL)
        {
            throw 5;
        }

        for(int i=0;i<N;i++)
        {
            SmileArray[i] = bufList[i].toInt(&toIntFlag);
            if(toIntFlag == false)
            {
                throw 7;
            }
        }

        for(int i=N-1;i>=0;i--)
        {
            if(SmileFlag == true &&  abs(SmileArray[i]%2) == 1)
            {
                SmileArray[i] = SmileArray[i]*SmileNumber;
            }
            else if(abs(SmileArray[i]%2) == 1 && SmileFlag == false)
            {
                SmileNumber = SmileArray[i];
                SmileArray[i] = SmileArray[i]*SmileNumber;
                SmileFlag =true;
            }
        }

        if(ui->intoAFile->isChecked())
        {
            QFile file_write(ui->lEIntoAFile->text());
            if(file_write.open(QIODevice::WriteOnly) == false)
            {
                throw 6;
            }
            QTextStream streamWrite(&file_write);

            if(SmileFlag == true)
            {
                for(int i=0;i<N;i++)
                {
                    streamWrite<<SmileArray[i];
                    streamWrite<<" ";
                };
            }
            else
            {
                for(int i=0;i<N;i++)
                {
                    streamWrite<<0x263a;
                    streamWrite<<" ";
                }
            }
        }


        else if(ui->intoAScreen->isChecked())
        {
            QString bufString;
            QString bufChar;

            if(SmileFlag == true)
            {
                for(int i=0;i<N;i++)
                {
                    bufString.append(bufChar.setNum(SmileArray[i]));
                    bufString.append(" ");
                }
            }
            else
            {
                for(int i=0;i<N;i++)
                {
                    bufString.append(0x263a);
                    bufString.append(" ");
                }
            }

            ui->lEIntoAScreen->setText(bufString);
        }
        delete SmileArray;
    }


MainWindow::~MainWindow()
{
    delete ui;
}
