#include <bits/stdc++.h>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <ostream>
#include <QPlainTextEdit>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Toolset.h"
#include "Utility.h"


Toolset *t;
Utility *u;
ofstream fileoutputstream;
treeNode* usersSample;
treeNode * dataRoot;

QString infilename;
QString outfilename;

QFile infile;
QFile outfile;

vector<string>result;
vector<Line>result2;
string r;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//choose file button
void MainWindow::on_pushButton_clicked()
{
    infilename = QFileDialog::getOpenFileName(
                    this,
                    tr("Open File")
                    );

        infile.setFileName(infilename);
        if(!infile.open(QIODevice::ReadOnly))
              QMessageBox::information(0,"info", infile.errorString());

        t = new Toolset(infilename.toStdString());
        usersSample = t->ans(usersSample);



        QTextStream in (&infile);
        ui->textBrowser->setText(in.readAll());


}

//prettify button
void MainWindow::on_pushButton_2_clicked()
{
    result = t->prettify();
    outfilename = "prettified.xml";
    fileoutputstream.open("prettified.xml");

    outfile.setFileName(outfilename);

    if(!outfile.open(QIODevice::ReadOnly))
          QMessageBox::information(0,"info", outfile.errorString());

    for(int i = 0; i<result.size(); i++){
        fileoutputstream << result[i] << endl;
    }

    QTextStream in (&outfile);
    ui->textBrowser_2->setText(in.readAll());


    fileoutputstream.close();
}

//compress button
void MainWindow::on_pushButton_4_clicked()
{
    result = t->Compress(infilename.toStdString());
    string extension = infilename.toStdString().substr(infilename.toStdString().size()-4,infilename.toStdString().size()-1);

    if(extension == ".xml"){
        outfilename = "compressed.xml";
        fileoutputstream.open("compressed.xml");

    }
    else{
        outfilename = "compressed.json";
        fileoutputstream.open("compressed.json");
    }

    outfile.setFileName(outfilename);


    if(!outfile.open(QIODevice::ReadOnly))
          QMessageBox::information(0,"info", outfile.errorString());


    for(int i = 0; i<result.size(); i++){
        fileoutputstream << result[i] << endl;
    }
    QTextStream in (&outfile);
    ui->textBrowser_2->setText(in.readAll());

    fileoutputstream.close();

}

//decompress button
void MainWindow::on_pushButton_5_clicked()
{
    result = t->DeCompress(infilename.toStdString());
    string extension = infilename.toStdString().substr(infilename.toStdString().size()-4,infilename.toStdString().size()-1);

    if(extension == ".xml"){
        outfilename = "Decompressed.xml";
        fileoutputstream.open("Decompressed.xml");
        t->set_str(result);
        result = t->prettify();

    }
    else{
        outfilename = "Decompressed.json";
        fileoutputstream.open("Decompressed.json");
    }

    outfile.setFileName(outfilename);

    if(!outfile.open(QIODevice::ReadOnly))
          QMessageBox::information(0,"info", outfile.errorString());

    for(int i = 0; i<result.size(); i++){
        fileoutputstream << result[i] << endl;
    }

    QTextStream in (&outfile);
    ui->textBrowser_2->setText(in.readAll());

    fileoutputstream.close();

}

//Minify button
void MainWindow::on_pushButton_6_clicked()
{
    r = t->MinifyXML();
    outfilename = "Minified.xml";
    fileoutputstream.open("Minified.xml");

    outfile.setFileName(outfilename);

    if(!outfile.open(QIODevice::ReadOnly))
          QMessageBox::information(0,"info", outfile.errorString());


    fileoutputstream << r << endl;
    QTextStream in (&outfile);
    ui->textBrowser_2->setText(in.readAll());

    fileoutputstream.close();

}

//detect errors button
void MainWindow::on_pushButton_7_clicked()
{
    t->checknode(usersSample);
    result2 = t->getdetected();
    outfilename = "errors.txt";
    fileoutputstream.open("errors.txt");

    outfile.setFileName(outfilename);
    if(!outfile.open(QIODevice::ReadOnly))
          QMessageBox::information(0,"info", outfile.errorString());

    for(int i = 0; i<result2.size(); i++){
        fileoutputstream << result2[i].text<<"was missing at line "<<result2[i].index << endl;
    }

    QTextStream in (&outfile);
    ui->textBrowser_2->setText(in.readAll());


    fileoutputstream.close();

    t->clear();

}

//correct errors button
void MainWindow::on_pushButton_8_clicked()
{
    t->checknode(usersSample);
    result = t->getCorrected();

    outfilename = "corrected.xml";
    fileoutputstream.open("corrected.xml");

    outfile.setFileName(outfilename);

    if(!outfile.open(QIODevice::ReadOnly))
          QMessageBox::information(0,"info", outfile.errorString());

    t->set_str(result);
    result = t->prettify();

    for(int i = 0; i<result.size(); i++){
        fileoutputstream << result[i] << endl;
    }

    QTextStream in (&outfile);
    ui->textBrowser_2->setText(in.readAll());


    fileoutputstream.close();
    t->clear();

}

//ToJSON button
void MainWindow::on_pushButton_9_clicked()
{
    dataRoot = new treeNode(0,"users","", {});
    result = t->XMLtoJSON(usersSample,dataRoot);

    outfilename = "ToJSON.json";
    fileoutputstream.open("ToJSON.json");

    outfile.setFileName(outfilename);

    if(!outfile.open(QIODevice::ReadOnly))
          QMessageBox::information(0,"info", outfile.errorString());

    for(int i = 0; i<result.size(); i++){
        fileoutputstream << result[i] << endl;
    }

    QTextStream in (&outfile);
    ui->textBrowser_2->setText(in.readAll());


    fileoutputstream.close();
    t->clear();
}

//save button
void MainWindow::on_pushButton_3_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this,tr("save file"));
    QFile::copy(outfile.fileName(),dir+'/'+outfilename);
}



//post search button
void MainWindow::on_pushButton_10_clicked()
{
    dataRoot = new treeNode(0,"users","", {});
    t->load_xml(usersSample,dataRoot);
    QString df = ui->plainTextEdit->toPlainText();
    vector<pair<int,int>>found = t->topic_search(dataRoot,df.toStdString());
    string r = u->printPosts(found);

    ui->textBrowser_2->setText(QString::fromStdString (r));
    t->clear();
}


void MainWindow::on_pushButton_11_clicked()
{
    nw->show();
        this->hide();
}

