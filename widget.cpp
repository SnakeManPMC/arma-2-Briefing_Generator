#include <QtWidgets>
#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("Briefing Generator " + pmcVersion + " by PMC");

    Load_Briefings();
    QTime timmy(0, 0, 0);
    qsrand(timmy.secsTo(QTime::currentTime()));
}

Widget::~Widget()
{
    delete ui;
}


/*

loads the text file "briefings.txt" into qvector qstrings array.

*/
void Widget::Load_Briefings()
{
    /*
    when you create the resource file, DO NOT USE PREFIX!
    you might have to manually edit qrc file and remove the prefix=/blabla part there to make it work.
    */
    QFile file( (":/text/briefings.txt") );

	if (!file.open(QIODevice::ReadOnly))
	{
		QMessageBox::information(this, tr("Unable to open file"),
		file.errorString());
		return;
	}

	QString line;
	QTextStream in(&file);

	while (!in.atEnd())
	{
		line = in.readLine();
		// skip empty line
		if (line.size() > 0) briefings.push_back(line);
		ui->briefing->append(line);
	}
	file.close();
}


/*

when user presses button to generate briefing, we replace the strings from text boxes and generate final briefing

*/
void Widget::on_pushButton_clicked()
{
    ui->briefing->clear();

    // randomly select one briefing and write it.
    int idx = qrand() % briefings.size();
    QString str = briefings[idx];

/*
all tags
<OPFOR_NAME>
<OPFOR_STRENGHT>
<TARGET_TYPE>
<TERRAIN_AREA>
<TERRAIN_AREA2>
<TERRAIN_AREA3>
<TERRAIN_NAME>
<TERRAIN_TYPE>
*/
    str.replace("<TERRAIN_NAME>", ui->terrain->text());
    str.replace("<TERRAIN_AREA>", ui->terrain_area->text());
    str.replace("<TERRAIN_AREA2>", ui->terrain_area2->text());
    str.replace("<TERRAIN_AREA3>", ui->terrain_area3->text());
    str.replace("<TERRAIN_TYPE>", ui->terrain_type->text());
    str.replace("<TARGET_TYPE>", ui->target_type->text());
    str.replace("<BLUFOR_NAME>", ui->blufor->text());
    str.replace("<OPFOR_NAME>", ui->opfor->text());
    str.replace("<OPFOR_STRENGHT>", ui->opfor_strenght->text());

    ui->briefing->append(str);
}
