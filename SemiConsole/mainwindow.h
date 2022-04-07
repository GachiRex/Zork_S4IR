#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE


#include <iostream>
#include <streambuf>
#include <string>

#include "qtextedit.h"

class QDebugStream : public std::basic_streambuf<char>
{
public:
    QDebugStream(std::ostream &stream, QTextEdit *text_edit) : m_stream(stream)
    {
        log_window = text_edit;
        m_old_buf = stream.rdbuf();
        stream.rdbuf(this);
    }
    ~QDebugStream()
    {
// output anything that is left
        if (!m_string.empty())
            log_window->append(m_string.c_str());

        m_stream.rdbuf(m_old_buf);
    }

protected:
    virtual int_type overflow(int_type v)
    {
        if (v == '\n') {
            log_window->append(m_string.c_str());
            m_string.erase(m_string.begin(), m_string.end());
        } else
            m_string += v;

        return v;
    }

    virtual std::streamsize xsputn(const char *p, std::streamsize n)
    {
        m_string.append(p, p + n);

        int pos = 0;
        while (pos != std::string::npos) {
            pos = m_string.find('\n');
            if (pos != std::string::npos) {
                std::string tmp(m_string.begin(), m_string.begin() + pos);
                log_window->append(tmp.c_str());
                m_string.erase(m_string.begin(), m_string.begin() + pos + 1);
            }
        }

        return n;
    }

private:
    std::ostream &m_stream;
    std::streambuf *m_old_buf;
    std::string m_string;


    QTextEdit *log_window;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_lineEdit_returnPressed();

    void Go(std::string dst);

    void Wordle();

    void on_pushButton_6_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_bullyButton_clicked();

    void on_interactButton_clicked();

    void on_hpBar_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    QDebugStream *redirect;
};




#endif // MAINWINDOW_H
