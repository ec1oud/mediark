#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QRectF>
#include <QStringList>

/**
*/
class Settings : public QSettings
{
    Q_OBJECT

public:
	static Settings* instance();

	int intOrDefault(QString group, QString key, int defaultVal);
	void setInt(QString group, QString key, int val);
	QString stringOrDefault(QString group, QString key, QString defaultVal = QString());
	void setString(QString group, QString key, QString val);
	QRectF scanGeometry(QString mediaType);
	void setScanGeometry(QString mediaType, QRectF geom);

	QStringList allMediaTypes() { return m_allMediaTypes; }
	QString chosenScanner() { return stringOrDefault("main", "scanner"); }
	void chosenScanner(QString v) { setString("main", "scanner", v); }

protected:
    Settings(QObject* parent = NULL);
    ~Settings();
	QRectF parseGeometryString(QString geom);
	QString toString(QRectF r);
	QStringList m_allMediaTypes;
};

#endif // SETTINGS_H
