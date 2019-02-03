#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)


{
    ui->setupUi(this);
    ui->lineLimtChar->setHidden(true);
    ui->reformatTextSmart->setHidden(true);
    ui->fullReformatText->setHidden(true);
    ui->smartReformat->setHidden(true);
    ui->reformatText_2->setHidden(true);
    ui->fullReformatText->setHidden(true);
    ui->cutLine->setHidden(true);
    ui->dots->setHidden(true);
    ui->customTime->setHidden(true);
    ui->customSleepTime->setHidden(true);
    ui->customSleepTime->setEnabled(false);
    ui->yourMessage->setAcceptRichText(false);
    ui->scriptAHK->setAcceptRichText(false);
}

bool autoWrite = true;

MainWindow::~MainWindow()
{
    delete ui;
}

QString fixScript(QString script){

    script.replace("%","`%");
    script.replace("’","'");



    return script;
}

int calculateTime(int lc,int cc,int tt,int tbl,int kpt){

    cc = cc - lc + 1;

    int result = (tbl * (lc - 1)) + (tt * cc) + ((kpt * 2) * (lc));


    return result;
}

QString fixBox(QString script){

    script.replace("`","");
    while (script.count("  ")){
        script.replace("  "," ");
    }

    while (script.count("\n\n")){
        script.replace("\n ","\n");
        script.replace(" \n","\n");
        script.replace("\n\n","\n");
    }

    if (script != "" && script.at(0) == "\xa" ){
        script.replace(0,1,"");
    }

    if (script != "" && script.at(script.length() - 1) == "\xa"){
        script.replace(script.length() - 1,1,"");
    }

    return script;
}

void MainWindow::generate()
{
    autoWrite = false;
    QString script = ui->yourMessage->toPlainText();

    script = fixBox(script);


        if (script != ""){

            //Checkbox option every space new line
            if (ui->everyWordInNewLine->checkState()){
                script.replace(" ", "\n");

            }

            //Checkbox option reformat text
            if (ui->reformatText->checkState()){



            }
        ui->yourMessage->setText(script);





        QString lineSlice = ui->lineLimtChar->text();
        QString typingTime = ui->typeTime->text();
        QString timeBetweenLines = ui->timeBetweenLine->text();
        QString Keypresstime = ui->keyPressTime->text();
        QString shortcut= ui->shortcut->text();
        QString chatKey = ui->chatKey->text();


        int lineCounter = lineSlice.split(" ")[0].toInt();
        int characterCounter =  script.count();
        int typingTimeInt;
        int timeBetweenLinesInt;
        int KeypresstimeInt;


        typingTimeInt = typingTime.split(" ")[0].toInt();
        timeBetweenLinesInt = timeBetweenLines.split(" ")[0].toInt();
        KeypresstimeInt = Keypresstime.split(" ")[0].toInt();


        if (typingTimeInt <= 0){
            typingTimeInt = 0;
        }



        if (KeypresstimeInt <= 0){
            KeypresstimeInt = 0;
        }


       if (timeBetweenLinesInt <= 0){
            timeBetweenLinesInt = 550;
       }

       if (chatKey == ""){
           KeypresstimeInt = 0;
       }



        int time = calculateTime(lineCounter,characterCounter,typingTimeInt,timeBetweenLinesInt,KeypresstimeInt);

        ui->timeLabel->setText("Time: " + QString::number(time));

        script = fixScript(script);


        if (ui->customTime->checkState()){
            script.replace("...\n","...`");
            if (chatKey == ""){
                script.replace("\n", "\nsend, {Enter}\nsleep "+ QString::number(timeBetweenLinesInt) +"\n\nsend, ");
                script = "\nsend, " + script;
                script = script + "\nsend, {Enter}";
            }
            else if (KeypresstimeInt == 0){
                script.replace("\n", "\nsend, {Enter}\nsleep "+ QString::number(timeBetweenLinesInt) +"\n\nsend, {" + chatKey + " Down}\nsend, {" + chatKey + " Up}\nsend, ");
                script = "send, {" + chatKey + " Down}\nsend, {" + chatKey + " Up}\nsend, " + script;
                script = script + "\nsend, {Enter}";
            }
            else{
            script.replace("\n", "\nsend, {Enter}\nsleep "+ QString::number(timeBetweenLinesInt) +"\n\nsend, {" + chatKey + " Down}\nsleep " + QString::number(KeypresstimeInt) + "\nsend, {" + chatKey + " Up}\nsleep " + QString::number(KeypresstimeInt) + "\nsend, ");
            script = "send, {" + chatKey + " Down}\nsleep " + QString::number(KeypresstimeInt) + "\nsend, {" + chatKey + " Up}\nsleep " + QString::number(KeypresstimeInt) + "\nsend, " + script;
            script = script + "\nsend, {Enter}";
            }

            QString dotSleep = ui->customSleepTime->text();
            int dotSleepInt = dotSleep.split(" ")[0].toInt();

            if (dotSleepInt <= 0){
                dotSleepInt = 1;
            }


            if (chatKey == ""){
                script.replace("...`", "...\nsend, {Enter}\nsleep "+ QString::number(dotSleepInt) +"\n\nsend, ");

            }
            else if (KeypresstimeInt == 0){
                script.replace("...`", "...\nsend, {Enter}\nsleep "+ QString::number(dotSleepInt) +"\n\nsend, {" + chatKey + " Down}\nsend, {" + chatKey + " Up}\nsend, ");

            }
            else{
            script.replace("...`", "...\nsend, {Enter}\nsleep "+ QString::number(dotSleepInt) +"\n\nsend, {" + chatKey + " Down}\nsleep " + QString::number(KeypresstimeInt) + "\nsend, {" + chatKey + " Up}\nsleep " + QString::number(KeypresstimeInt) + "\nsend, ");

            }




        }
        else{

            if (chatKey == ""){
                script.replace("\n", "\nsend, {Enter}\nsleep "+ QString::number(timeBetweenLinesInt) +"\n\nsend, ");
                script = "\nsend, " + script;
                script = script + "\nsend, {Enter}";
            }
            else if (KeypresstimeInt == 0){
                script.replace("\n", "\nsend, {Enter}\nsleep "+ QString::number(timeBetweenLinesInt) +"\n\nsend, {" + chatKey + " Down}\nsend, {" + chatKey + " Up}\nsend, ");
                script = "send, {" + chatKey + " Down}\nsend, {" + chatKey + " Up}\nsend, " + script;
                script = script + "\nsend, {Enter}";
            }
            else{
            script.replace("\n", "\nsend, {Enter}\nsleep "+ QString::number(timeBetweenLinesInt) +"\n\nsend, {" + chatKey + " Down}\nsleep " + QString::number(KeypresstimeInt) + "\nsend, {" + chatKey + " Up}\nsleep " + QString::number(KeypresstimeInt) + "\nsend, ");
            script = "send, {" + chatKey + " Down}\nsleep " + QString::number(KeypresstimeInt) + "\nsend, {" + chatKey + " Up}\nsleep " + QString::number(KeypresstimeInt) + "\nsend, " + script;
            script = script + "\nsend, {Enter}";
            }

        }


        script = "SetKeyDelay, " + QString::number(typingTimeInt) + "\n\nF10::Suspend\nF11::Reload\nF12::ExitApp\n\n" + shortcut + "::\n"+ script;

        script += "\n\nReturn";
        ui->status->setText("Status: OK");
        ui->scriptAHK->setText(script);
        autoWrite = true;
    }

}

void MainWindow::reformat()
{
    QString script = ui->yourMessage->toPlainText();

    script = fixBox(script);

    QString lineSliceForThisIf = ui->lineLimtChar->text();
    int lineSliceForThisIfInt = lineSliceForThisIf.split(" ")[0].toInt();
    lineSliceForThisIfInt++;
    int characterCounterForThisIf = script.count();
    int i = lineSliceForThisIfInt;

    script += "\n";

    int j = 0;
    int k = 1;



    while (j < characterCounterForThisIf){

        i = j;
        int In = script.indexOf("\n",j);

        j = In;


        while (i < (j)){
            script.insert(i, "\n");
            i = i + lineSliceForThisIfInt;
            k++;
            j++;
        }
        characterCounterForThisIf = script.count();
        j += lineSliceForThisIfInt;
        k = 0;


    }
    script.replace(0,1,"");
    script = fixBox(script);
     ui->yourMessage->setText(script);
}

void MainWindow::selectSave(){
    QString file = QFileDialog::getSaveFileName(
                this,
                tr("Select Safe file"),
                "C://",
                "AutoHotKey (*.ahk)"
                );
    ui->AHKpath->setText(file);

}

void MainWindow::save()
{
    QString path = ui->AHKpath->text();
    QString script = ui->scriptAHK->toPlainText();
    QString status = ui->status->text();

    if (status == "Status: Modified"){
        QMessageBox::information(this,"Info","You are going to save modified script. Be aware that it may not work.");
    }



    if (path == ""){

        QMessageBox::information(this,"Ehem...","Please select save path before saving.");
        selectSave();
    }

    else if (script == "")
    {
        QMessageBox::information(this,"Whoa! what are you doing?","You cannot save empty script");

    }
    else{
    QFile file (path);
    file.remove();

        if ( file.open(QIODevice::ReadWrite) )
        {
            QTextStream stream( &file );
            stream << script;
        }


    }
}

void MainWindow::refomatSmart(){
    QString script = ui->yourMessage->toPlainText();
    int scriptSpaceSize = script.count(" ");
    int i = 0;

    QString word[99999];

    script = fixBox(script);

    script.replace("`","");


    script.replace("\n","`");
    script.replace(".",". ");
    script.replace(".  ",". ");

    int ch = script.count(" ") + 10;

    int firstLetter = 0;
    int lastLetter = script.indexOf(" ", 1);

    int wordLength = lastLetter - firstLetter;


    while (i <= scriptSpaceSize){

        word[i] = script.mid(firstLetter, wordLength);

        firstLetter = lastLetter + 1;
        lastLetter = script.indexOf(" ", firstLetter);

        wordLength = lastLetter - firstLetter;
        i++;
    }
    i = 0;


    QString LineCut = ui->lineLimtChar->text();
    int LineCutInt = LineCut.split(" ")[0].toInt();


    if (ui->dots->checkState()){
       LineCutInt -= 3;
       }

    int j = 0;

    int wordCounter = 0;

    QString scriptRewrite;

    bool cut = true;

    while (i <= ch){

        if (word[i].length() == 0)
        {

            break;
        }
        wordCounter++;
        if ((word[i].length()) >= LineCutInt){


            if (ui->dots->checkState()){
                word[i].replace("`","");
                QMessageBox::information(this,"Ops..","Smart reformating requare biggeer \"Line cut\" number." );
                 cut = false;
                 break;
            }
            else{

            word[i].replace("`","");
            QMessageBox::information(this,"Ops.."," Word \"" + word[i] + "\" has more or equal than " + QString::number(LineCutInt) + " letters\n Smart text reformating cannot be performed. Please fix that." );
             cut = false;
             break;
            }
        }
        i++;
    }
    if (ui->dots->checkState()) {
            LineCutInt -= 2;
    }


    QString fix;
    i = 0;
    if (cut){

        if (ui->dots->checkState()){
            while (j <= LineCutInt){

                if (word[0] == word[i] && i != 0)
                {
                    break;
                }

                if (word[i].contains(" ")){
                    word[i].replace(" ", "");
                }
                word[i] += " ";
                j += word[i].length();
                if (j <= LineCutInt){
                    scriptRewrite += word[i];
                }
                else
                {
                    i--;


                    if (QString::number(i) == fix){
                        i++;
                    }
                    fix = QString::number(i);

                    scriptRewrite += "...\n";
                    scriptRewrite.replace(" ...\n","...\n");
                    if (1 < word[i].length())
                    {
                        j = 0;
                    }
                }
                if (word[i].contains("`")){
                    j = word[i].length();
                }

                i++;
            }
        }
        else{
            while (j <= LineCutInt){

                if (word[0] == word[i] && i != 0)
                {
                    break;
                }

                if (word[i].contains(" ")){
                    word[i].replace(" ", "");
                }
                word[i] += " ";
                j += word[i].length();
                if (j <= LineCutInt){
                    scriptRewrite += word[i];
                }
                else
                {
                    i--;


                    if (QString::number(i) == fix){
                        i++;
                    }
                    fix = QString::number(i);

                    scriptRewrite += "\n";
                    if (1 < word[i].length())
                    {
                        j = 0;
                    }
                }
                if (word[i].contains("`")){
                    j = word[i].length();
                }

                i++;
            }
        }

        scriptRewrite.replace("`","\n");
        scriptRewrite = fixBox(scriptRewrite);
        scriptRewrite.replace("\n.\n.\n.","");
        script = scriptRewrite;

        QString dotCheck = "...";
        QString spaceDotCheck = " ...";

        if (script.mid(script.length() - 4,4) == spaceDotCheck){
            script = script.mid(0, script.length() - 4);
        }

        else if (script.mid(script.length() - 3,3) == dotCheck){
            script = script.mid(0, script.length() - 3);
        }


         ui->yourMessage->setText(script);
     }


}

void MainWindow::fullRefomat(){
    QString script = ui->yourMessage->toPlainText();

    script = fixBox(script);

    script.replace("\n", " ");

    QString lineSliceForThisIf = ui->lineLimtChar->text();
    int lineSliceForThisIfInt = lineSliceForThisIf.split(" ")[0].toInt();
    lineSliceForThisIfInt++;

    if (lineSliceForThisIfInt > 1){
        int characterCounterForThisIf = script.count();
        int i = lineSliceForThisIfInt;

        script += "\n";

        int j = 0;
        int k = 1;



        while (j < characterCounterForThisIf){

            i = j;
            int In = script.indexOf("\n",j);

            j = In;


            while (i < (j)){
                script.insert(i, "\n");
                i = i + lineSliceForThisIfInt;
                k++;
                j++;
            }
            characterCounterForThisIf = script.count();
            j += lineSliceForThisIfInt;
            k = 0;


        }
        script.replace(0,1,"");
        script = fixBox(script);
         ui->yourMessage->setText(script);
    }
    else {
        QMessageBox::information(this,"What?","Your \"Line cut\" number dosen't make any sencse." );
    }
}

void MainWindow::fullRefomatSmart(){

    QString script = ui->yourMessage->toPlainText();
    int scriptSpaceSize = script.count(" ");
    int i = 0;

    QString word[9999];

    script = fixBox(script);

    script.replace("\n"," ");

    int ch = script.count(" ");

    int firstLetter = 0;
    int lastLetter = script.indexOf(" ", 1);
    int wordLength = lastLetter - firstLetter;

    while (i <= scriptSpaceSize){

        word[i] = script.mid(firstLetter, wordLength);

        firstLetter = lastLetter + 1;
        lastLetter = script.indexOf(" ", firstLetter);

        wordLength = lastLetter - firstLetter;
        i++;
    }
    i = 0;

    QString LineCut = ui->lineLimtChar->text();
    int LineCutInt = LineCut.split(" ")[0].toInt();

    int j = 0;

    QString scriptRewrite;

    bool cut = true;

    while (i <= ch){
        if ((word[i].length()) >= LineCutInt){
            QMessageBox::information(this,"Ops.."," Word \"" + word[i] + "\" has more or equal than " + QString::number(LineCutInt) + " letters\n Smart text reformating cannot be performed. Please fix that." );
             cut = false;
             break;
        }
        i++;
    }


    QString fix;
    i = 0;
    if (cut){

        while (j <= LineCutInt){
            if (word[i].contains(" ")){
                word[i].replace(" ", "");
            }
            word[i] += " ";
            j += word[i].length();
            if (j <= LineCutInt){
                scriptRewrite += word[i];
            }
            else
            {
                i--;
                scriptRewrite += "\n";
                if (1 < word[i].length())
                {
                    j = 0;
                }
            }
            i++;

        }
        scriptRewrite = fixBox(scriptRewrite);
        script = scriptRewrite;
        script = fixBox(script);
        ui->yourMessage->setText(script);
    }
}

void MainWindow::run(){

    QString path = ui->AHKpath->text();

    QDesktopServices::openUrl(QUrl("file:///"+ path,QUrl::TolerantMode));
}

void MainWindow::checkBox(){


}

void MainWindow::on_pushButton_clicked()
{
    generate();
}

void MainWindow::on_pushButton_2_clicked()
{
   ui->yourMessage->setText("");
   ui->scriptAHK->setText("");
}

void MainWindow::on_pushButton_3_clicked()
{
    save();
}

void MainWindow::on_pathSelect_clicked()
{
    selectSave();
}

void MainWindow::on_scriptAHK_textChanged()
{
    if (autoWrite){
    ui->status->setText("Status: Modified");
    ui->timeLabel->setText("Time: Modified");
    }
}

void MainWindow::on_genSaveRun_clicked()
{
    generate();
    save();
    run();
}

void MainWindow::on_saveRun_clicked()
{
    save();
    run();

}

void MainWindow::on_everyWordInNewLine_clicked()
{
    ui->reformatText->setChecked(0);
    ui->lineLimtChar->setHidden(true);
    ui->reformatTextSmart->setHidden(true);
    ui->fullReformatText->setHidden(true);
    ui->smartReformat->setHidden(true);
    ui->reformatText_2->setHidden(true);
    ui->fullReformatText->setHidden(true);
    ui->dots->setHidden(true);
    ui->cutLine->setHidden(true);


}

void MainWindow::on_reformatText_clicked()
{
    ui->everyWordInNewLine->setChecked(0);

    if (ui->reformatText->checkState()){
        ui->lineLimtChar->setHidden(false);
        ui->reformatTextSmart->setHidden(false);
        ui->fullReformatText->setHidden(false);
        ui->smartReformat->setHidden(false);
        ui->reformatText_2->setHidden(false);
        ui->fullReformatText->setHidden(false);
        ui->customTime->setHidden(false);
        ui->customSleepTime->setHidden(false);
        ui->dots->setHidden(false);
        ui->cutLine->setHidden(false);
        ui->customTime->setChecked(0);
        ui->customSleepTime->setEnabled(false);

    }
     else {
        ui->customTime->setHidden(true);
        ui->customSleepTime->setHidden(true);
        ui->lineLimtChar->setHidden(true);
        ui->reformatTextSmart->setHidden(true);
        ui->fullReformatText->setHidden(true);
        ui->smartReformat->setHidden(true);
        ui->reformatText_2->setHidden(true);
        ui->fullReformatText->setHidden(true);
        ui->dots->setHidden(true);
        ui->cutLine->setHidden(true);
        ui->customTime->setHidden(true);
        ui->customSleepTime->setHidden(true);
    }
}


void MainWindow::on_fullReformatText_clicked()
{
    fullRefomat();
}

void MainWindow::on_smartReformat_clicked()
{
    refomatSmart();
}

void MainWindow::on_reformatTextSmart_clicked()
{
    fullRefomatSmart();
}

void MainWindow::on_reformatText_2_clicked()
{
    fullRefomat();
}

void MainWindow::on_customTime_clicked()
{
    if (ui->customTime->checkState()){
        ui->customSleepTime->setEnabled(true);
    }
    else{
        ui->customSleepTime->setEnabled(false);
    }
}
