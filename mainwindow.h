#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pathSelect_clicked();

    void on_scriptAHK_textChanged();

    void on_genSaveRun_clicked();

    void on_saveRun_clicked();

    void on_everyWordInNewLine_clicked();

    void on_reformatText_clicked();

    void on_fullReformatText_clicked();

    void on_smartReformat_clicked();

    void on_reformatTextSmart_clicked();

    void on_reformatText_2_clicked();

    void on_customTime_clicked();

private:
    void generate();

private:
    void save();

private:
    void run();

private:
    void selectSave();

private:
    void checkBox();

private:
    void reformat();

private:
    void fullRefomatSmart();

private:
    void fullRefomat();

private:
    void refomatSmart();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
