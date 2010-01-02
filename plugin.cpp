#include "plugin.h"
#include <QDir>

Plugin::Plugin()
{
	m_outputImagePath = Settings::instance()->
		stringOrDefault(SETTING_GROUP_SESSION, "sequenceDir");
	m_sequence = Settings::instance()->intOrDefault(SETTING_GROUP_SESSION, "sequenceNum", 0);
}

void Plugin::setPathAndSequenceStart(QFileInfo path, int start)
{
	m_outputImagePath = path;
	m_sequence = start;
	Settings::instance()->setString(SETTING_GROUP_SESSION, "sequenceDir", path.absoluteFilePath());
	Settings::instance()->setInt(SETTING_GROUP_SESSION, "sequenceNum", m_sequence);
}

QFileInfo Plugin::takeNextImageOutput()
{
	QFileInfo ret = nextImageOutput();
	++m_sequence;
	Settings::instance()->setInt(SETTING_GROUP_SESSION, "sequenceNum", m_sequence);
	return ret;
}

QFileInfo Plugin::nextImageOutput()
{
	QFileInfo ret(m_outputImagePath.dir(),
		QString("%1/image%2.%3").arg(m_outputImagePath.fileName())
			.arg(m_sequence, 4, 10, QLatin1Char('0')).arg(fileExt()));
	return ret;
}
