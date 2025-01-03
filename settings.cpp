#include "settings.h"
#include "common.h"

static const QString FIVE_N_QUARTER_INCH = QString::fromUtf8("5¼ inch floppy");
static const QString THREE_N_HALF_INCH = QString::fromUtf8("3\u00BD inch floppy");

Settings* Settings::instance()
{
	static Settings* self = new Settings();
	return self;
}

Settings::Settings(QObject* parent) :
	QSettings(STR_ORGANIZATION, STR_PRODUCT, parent)
{
	qDebug() << "settings stored at" << fileName();
	m_allMediaTypes << FIVE_N_QUARTER_INCH << THREE_N_HALF_INCH;
	beginGroup(SETTING_GROUP_SCAN_GEOMETRY);
	QRectF r = parseGeometryString(value(FIVE_N_QUARTER_INCH).toString());
	if (r.isNull())
		setValue(FIVE_N_QUARTER_INCH, QVariant(toString(QRectF(0, 0, 143, 136))));
	r = parseGeometryString(value(THREE_N_HALF_INCH).toString());
	if (r.isNull())
		setValue(THREE_N_HALF_INCH, QVariant(toString(QRectF(0, 0, 90, 95))));
	endGroup();
	if (intOrDefault("main", "resolution", -1) < 0)
		setInt("main", "resolution", 300);
}

Settings::~Settings()
{
}

int Settings::intOrDefault(QString group, QString key, int defaultVal)
{
	beginGroup(group);
	QVariant v = value(key);
	bool ok = false;
	int ret = v.toInt(&ok);
	if (!ok)
		ret = defaultVal;
	endGroup();
	return ret;
}

void Settings::setInt(QString group, QString key, int val)
{
	beginGroup(group);
	setValue(key, QVariant(val));
	endGroup();
}

QRectF Settings::scanGeometry(QString mediaType)
{
	beginGroup(SETTING_GROUP_SCAN_GEOMETRY);
	QRectF ret = parseGeometryString(value(mediaType).toString());
	endGroup();
	return ret;
}

void Settings::setScanGeometry(QString mediaType, QRectF geom)
{
	beginGroup(SETTING_GROUP_SCAN_GEOMETRY);
	setValue(mediaType, QVariant(toString(geom)));
	endGroup();
}

QSize Settings::matrixDims(QString mediaType)
{
	beginGroup(SETTING_GROUP_SCAN_MATRIX);
	QSize ret = parseSizeString(value(mediaType).toString());
	endGroup();
	return ret;
}

void Settings::setMatrixDims(QString mediaType, QSize dims)
{
	beginGroup(SETTING_GROUP_SCAN_MATRIX);
	setValue(mediaType, QVariant(QString("%1,%2").arg(dims.width()).arg(dims.height())));
	endGroup();
}

QRectF Settings::parseGeometryString(QString geom)
{
	QVector<QString> nums = QVector<QString>::fromList(geom.split(","));
	if (nums.size() != 4)
		return QRectF();	// null rect
	bool ok0, ok1, ok2, ok3;
//	foreach (QString num, nums)
//		qDebug() << "for " << num << " we gets " << num.toDouble(NULL);
	qreal x = nums[0].toDouble(&ok0);
	qreal y = nums[1].toDouble(&ok1);
	QRectF ret( x, y, nums[2].toDouble(&ok2) - x, nums[3].toDouble(&ok3) - y );
	if (ok0 && ok1 && ok2 && ok3)
		return ret;
	return QRectF();
}

QSize Settings::parseSizeString(QString geom)
{
	QVector<QString> nums = QVector<QString>::fromList(geom.split(","));
	if (nums.size() != 2)
		return QSize();	// null size
	bool ok0, ok1;
	QSize ret(nums[0].toInt(&ok0), nums[1].toInt(&ok1));
	if (ok0 && ok1)
		return ret;
	return QSize();
}

QString Settings::toString(QRectF r)
{
	QStringList ret;
	ret << QString::number(r.x());
	ret << QString::number(r.y());
	ret << QString::number(r.width());
	ret << QString::number(r.height());
	return ret.join(",");
}

QString Settings::stringOrDefault(QString group, QString key, QString defaultVal)
{
	beginGroup(group);
	QVariant v = value(key, QVariant(defaultVal));
	endGroup();
	return v.toString();
}

void Settings::setString(QString group, QString key, QString val)
{
	beginGroup(group);
	setValue(key, QVariant(val));
	endGroup();
}
