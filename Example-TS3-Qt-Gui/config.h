#pragma once
#include <QtWidgets/QDialog>
#pragma comment (lib, "Qt5Widgets")
#pragma comment (lib, "Qt5Core")
#include <QtCore/QSettings>

namespace Ui {
	class configui;
}

class config : public QDialog
{
	Q_OBJECT
public:
	config(const QString& configLocation, QWidget *parent = 0);
	~config();
	config(const config& other) = delete;
	config& operator=(const config& other) = delete;

	void setConfigOption(const QString& option, const QVariant& value);
	QVariant getConfigOption(const QString& option) const;

protected:
	void showEvent(QShowEvent* e) override;

private:
	Ui::configui* m_ui;
	QSettings* m_settings;

	void saveSettings();
	void loadSettings();
};

