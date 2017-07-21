#include "config.h"
#include "ui_configui.h"



config::config(const QString& configLocation, QWidget* parent /* = nullptr */) : QDialog(parent),
	m_ui(std::make_unique<Ui::configui>()),
	m_settings(std::make_unique<QSettings>(configLocation + "/QtGuiDemo.ini", QSettings::IniFormat, this))
{
	m_ui->setupUi(this);

	setWindowTitle("Qt-GUI Demo :: Config");

	// Connect UI Elements.
	connect(m_ui->pbOk, &QPushButton::clicked, this, &config::saveSettings);
	connect(m_ui->pbCancel, &QPushButton::clicked, this, &QWidget::close);
	// Show off some Lambda connect
	connect(m_ui->chkOption1, &QCheckBox::toggled, this, [&](bool checked) {
		m_ui->txtRandomText->setEnabled(checked);
		m_ui->label->setEnabled(checked);
	});
	// If we just care for a single element we could also connect that directly:
	//connect(m_ui->chkOption1, &QCheckBox::toggled, m_ui->txtRandomText, &QTextEdit::setEnabled);
}

config::~config() {
	m_settings->sync();
}


void config::setConfigOption(const QString& option, const QVariant& value) {
	m_settings->setValue(option, value);
}

QVariant config::getConfigOption(const QString& option) const {
	return m_settings->value(option);
}

void config::showEvent(QShowEvent* /* e */) {
	loadSettings();
}

void config::saveSettings() {
	setConfigOption("opt1", m_ui->chkOption1->isChecked());
	setConfigOption("intVal", m_ui->speSomeIntValue->value());
	setConfigOption("text", m_ui->txtRandomText->toPlainText());

	close();
}

void config::loadSettings() {
	m_ui->chkOption1->setChecked(getConfigOption("opt1").toBool());
	m_ui->txtRandomText->setPlainText(getConfigOption("text").toString());
	m_ui->speSomeIntValue->setValue(getConfigOption("intVal").toInt());

	// Manually set enabled state of textbox, as the event doesn't fire if the state is the same as it was already (ie. unchecked).
	m_ui->txtRandomText->setEnabled(m_ui->chkOption1->isChecked());
}