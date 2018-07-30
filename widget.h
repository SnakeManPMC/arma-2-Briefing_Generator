#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
    class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

	void Load_Briefings();
	QVector<QString> briefings;

private slots:
	void on_pushButton_clicked();

private:
    Ui::Widget *ui;
    QString pmcVersion = "v0.0.1";
};

#endif // WIDGET_H
